import { spawn } from "node:child_process";
import { existsSync } from "node:fs";
import * as vscode from "vscode";
import { KeymapEditorProvider } from "./editor/provider";
import { parsePath } from "./model/keymap";
import { parseDiagnostics, parseFirmwarePath } from "./qmk/output";
import { buildMsysEnv, buildQmkCommand, run, runShell, runStreaming, type RunOptions } from "./qmk/runner";

const TOOLS = ["avr-gcc", "arm-none-eabi-gcc", "dfu-util", "dfu-programmer"];

function runOptions(): RunOptions {
  return { msysRoot: vscode.workspace.getConfiguration("qmkLens").get<string>("msysRoot") || "C:/QMK_MSYS" };
}

function toolboxPath(): string {
  return vscode.workspace.getConfiguration("qmkLens").get<string>("toolboxPath") || "C:/Program Files/QMK Toolbox/qmk_toolbox.exe";
}

export async function qmkHome(opts: RunOptions): Promise<string> {
  const configured = vscode.workspace.getConfiguration("qmkLens").get<string>("qmkHome");
  if (configured) return configured;
  const r = await run(["config", "user.qmk_home"], opts);
  // Output: "user.qmk_home=C:/Users/X/qmk_firmware"
  return /user\.qmk_home=(.*)/.exec(r.stdout)?.[1]?.trim() ?? "";
}

async function doctor(out: vscode.OutputChannel): Promise<void> {
  out.show(true);
  const opts = runOptions();
  out.appendLine(`msysRoot: ${opts.msysRoot}`);
  try {
    const v = await run(["--version"], opts);
    out.appendLine(`qmk --version: ${v.code === 0 ? v.stdout.trim() : `FAILED (${v.code}) ${v.stderr.trim()}`}`);
    out.appendLine(`qmk_home: ${(await qmkHome(opts)) || "(not set)"}`);
    let dfuProgrammerMissing = false;
    for (const tool of TOOLS) {
      const r = await runShell(`command -v ${tool}`, opts);
      const missing = r.code !== 0;
      if (tool === "dfu-programmer") dfuProgrammerMissing = missing;
      out.appendLine(`${tool}: ${missing ? "MISSING" : r.stdout.trim()}`);
    }
    if (dfuProgrammerMissing) out.appendLine("Hint: dfu-programmer is required for atmel-dfu boards such as Lily58.");
    const toolbox = toolboxPath();
    out.appendLine(`QMK Toolbox: ${existsSync(toolbox) ? toolbox : `MISSING (${toolbox})`}`);
  } catch (e) {
    out.appendLine(`Error: ${(e as Error).message}. Check qmkLens.msysRoot.`);
  }
}

export function documentPath(documentOrUri: vscode.TextDocument | vscode.Uri): string {
  const uri = "uri" in documentOrUri ? documentOrUri.uri : documentOrUri;
  return uri.fsPath || uri.path || "";
}

export function findKeymapUri(provider: KeymapEditorProvider, targetUri?: vscode.Uri): vscode.Uri | undefined {
  if (targetUri && parsePath(documentPath(targetUri))) {
    return targetUri;
  }
  const active = vscode.window.activeTextEditor?.document;
  if (active && parsePath(documentPath(active))) {
    return active.uri;
  }
  const lastActive = provider.getLastActiveDocument();
  if (lastActive && parsePath(documentPath(lastActive))) {
    return lastActive.uri;
  }
  const activeTab = vscode.window.tabGroups?.activeTabGroup?.activeTab;
  const tabUri = (activeTab?.input as { uri?: vscode.Uri } | undefined)?.uri;
  if (tabUri && parsePath(documentPath(tabUri))) {
    return tabUri;
  }
  for (const editor of vscode.window.visibleTextEditors ?? []) {
    if (parsePath(documentPath(editor.document))) {
      return editor.document.uri;
    }
  }
  return undefined;
}

export async function openVisualEditor(provider: KeymapEditorProvider, uri?: vscode.Uri): Promise<void> {
  const targetUri = findKeymapUri(provider, uri);
  if (!targetUri) {
    vscode.window.showWarningMessage("QMK Lens: open a keymaps/*/keymap.c file first");
    return;
  }
  await vscode.commands.executeCommand("vscode.openWith", targetUri, "qmkLens.keymap", vscode.ViewColumn.Beside);
}

export interface ResolvedKeymap {
  document: vscode.TextDocument;
  keyboard: string;
  keymap: string;
}

export async function resolveKeymap(
  uri: vscode.Uri | undefined,
  provider: KeymapEditorProvider,
): Promise<ResolvedKeymap | undefined> {
  const targetUri = findKeymapUri(provider, uri);
  const document = targetUri
    ? vscode.workspace.textDocuments.find((item) => item.uri.toString() === targetUri.toString()) ?? await vscode.workspace.openTextDocument(targetUri)
    : undefined;
  const parsed = document && parsePath(documentPath(document));
  if (!document || !parsed) {
    vscode.window.showErrorMessage("QMK Lens: select a keymaps/*/keymap.c file first");
    return undefined;
  }
  if (document.isDirty && !await document.save()) {
    vscode.window.showErrorMessage("QMK Lens: save the keymap before building");
    return undefined;
  }
  return { document, ...parsed };
}

function firmwareStateKey(keyboard: string, keymap: string): string {
  return `qmkLens.firmware.${keyboard}:${keymap}`;
}

async function compileKeymap(
  uri: vscode.Uri | undefined,
  provider: KeymapEditorProvider,
  context: vscode.ExtensionContext,
  out: vscode.OutputChannel,
  diagnostics: vscode.DiagnosticCollection,
): Promise<void> {
  const target = await resolveKeymap(uri, provider);
  if (!target) return;
  diagnostics.clear();
  out.show(true);
  out.appendLine(`\n> qmk compile -kb ${target.keyboard} -km ${target.keymap}`);
  try {
    const options = runOptions();
    const home = await qmkHome(options);
    if (!home) throw new Error("qmk_home is not configured");
    const result = await vscode.window.withProgress(
      { location: vscode.ProgressLocation.Notification, title: `QMK: compiling ${target.keyboard}:${target.keymap}` },
      () => runStreaming(
        ["compile", "-kb", target.keyboard, "-km", target.keymap],
        { ...options, cwd: home },
        (chunk) => out.append(chunk),
      ),
    );
    const output = `${result.stdout}\n${result.stderr}`;
    publishDiagnostics(diagnostics, parseDiagnostics(output, home));
    if (result.code !== 0) {
      vscode.window.showErrorMessage(`QMK compile failed with exit code ${result.code}. See QMK Lens output.`);
      return;
    }
    const firmware = parseFirmwarePath(output, home);
    if (firmware) await context.globalState.update(firmwareStateKey(target.keyboard, target.keymap), firmware);
    vscode.window.showInformationMessage(firmware
      ? `QMK compile succeeded: ${firmware}`
      : "QMK compile succeeded, but no firmware path was reported.");
  } catch (error) {
    vscode.window.showErrorMessage(`QMK compile failed: ${messageOf(error)}`);
  }
}

function publishDiagnostics(collection: vscode.DiagnosticCollection, items: ReturnType<typeof parseDiagnostics>): void {
  const grouped = new Map<string, vscode.Diagnostic[]>();
  for (const item of items) {
    const uri = vscode.Uri.file(item.path);
    const diagnostic = new vscode.Diagnostic(
      new vscode.Range(item.line - 1, item.column - 1, item.line - 1, item.column),
      item.message,
      item.severity === "error" ? vscode.DiagnosticSeverity.Error : vscode.DiagnosticSeverity.Warning,
    );
    const key = uri.toString();
    const group = grouped.get(key) ?? [];
    group.push(diagnostic);
    grouped.set(key, group);
  }
  collection.set([...grouped].map(([uri, items]) => [vscode.Uri.parse(uri), items]));
}

async function flashKeymap(uri: vscode.Uri | undefined, provider: KeymapEditorProvider): Promise<void> {
  const target = await resolveKeymap(uri, provider);
  if (!target) return;
  try {
    const options = runOptions();
    const home = await qmkHome(options);
    if (!home) throw new Error("qmk_home is not configured");
    const command = `${buildQmkCommand(["flash", "-kb", target.keyboard, "-km", target.keymap])}; code=$?; echo; read -p "Press Enter to close"; exit $code`;
    const terminal = vscode.window.createTerminal({
      name: "QMK Flash",
      shellPath: `${options.msysRoot.replace(/[\\/]+$/, "")}/usr/bin/bash.exe`,
      shellArgs: ["-lc", command],
      cwd: home,
      env: buildMsysEnv(),
    });
    terminal.show();
  } catch (error) {
    vscode.window.showErrorMessage(`QMK flash could not start: ${messageOf(error)}`);
  }
}

async function openToolbox(
  uri: vscode.Uri | undefined,
  provider: KeymapEditorProvider,
  context: vscode.ExtensionContext,
): Promise<void> {
  const target = await resolveKeymap(uri, provider);
  if (!target) return;
  const firmware = context.globalState.get<string>(firmwareStateKey(target.keyboard, target.keymap));
  if (!firmware || !existsSync(firmware)) {
    vscode.window.showWarningMessage("QMK Lens: compile this keymap before opening QMK Toolbox.");
    return;
  }
  const executable = toolboxPath();
  if (!existsSync(executable)) {
    vscode.window.showErrorMessage(`QMK Toolbox was not found at ${executable}. Check qmkLens.toolboxPath.`);
    return;
  }
  const child = spawn(executable, [firmware], { detached: true, stdio: "ignore", windowsHide: false });
  child.once("error", (error) => vscode.window.showErrorMessage(`QMK Toolbox could not start: ${error.message}`));
  child.unref();
}

function messageOf(error: unknown): string {
  return error instanceof Error ? error.message : String(error);
}

export function activate(context: vscode.ExtensionContext): void {
  const out = vscode.window.createOutputChannel("QMK Lens");
  const diagnostics = vscode.languages.createDiagnosticCollection("qmk");
  const provider = new KeymapEditorProvider(context, runOptions, qmkHome);
  context.subscriptions.push(
    out,
    diagnostics,
    vscode.window.onDidChangeActiveTextEditor((editor) => {
      if (editor?.document && parsePath(documentPath(editor.document))) {
        provider.setLastActiveDocument(editor.document);
      }
    }),
    vscode.commands.registerCommand("qmkLens.doctor", () => doctor(out)),
    vscode.commands.registerCommand("qmkLens.openVisual", (uri?: vscode.Uri) => openVisualEditor(provider, uri)),
    vscode.commands.registerCommand("qmkLens.compile", (uri?: vscode.Uri) => compileKeymap(uri, provider, context, out, diagnostics)),
    vscode.commands.registerCommand("qmkLens.flash", (uri?: vscode.Uri) => flashKeymap(uri, provider)),
    vscode.commands.registerCommand("qmkLens.openToolbox", (uri?: vscode.Uri) => openToolbox(uri, provider, context)),
    vscode.window.registerCustomEditorProvider("qmkLens.keymap", provider, { supportsMultipleEditorsPerDocument: true }),
  );
}

export function deactivate(): void {}
