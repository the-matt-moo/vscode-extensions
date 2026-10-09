import { randomBytes } from "node:crypto";
import * as vscode from "vscode";
import { computeSwapEdits, validateRawExpression } from "./editing";
import { buildViewModel } from "./viewModel";
import { buildCatalog, loadKeycodeCatalog, type FunctionEntry, type KeycodeCatalog } from "../model/keycodes";
import { initParser, parseKeymap, parsePath, type KeymapModel } from "../model/keymap";
import { loadGeometry } from "../qmk/geometryLoader";
import type { RunOptions } from "../qmk/runner";
import type { HostMessage, WebviewMessage } from "../shared/protocol";
import type { Geometry } from "../model/geometry";

interface Resources {
  geometry: Geometry | null;
  catalog: KeycodeCatalog;
  error?: string;
}

interface CurrentState {
  model: KeymapModel;
  catalog: KeycodeCatalog;
  resources: Resources;
}

type Choice = vscode.QuickPickItem &
  ({ choice: "raw" } | { choice: "entry"; expression: string } | { choice: "function"; fn: FunctionEntry });

let parserReady: Promise<void> | undefined;
const catalogs = new Map<string, Promise<KeycodeCatalog>>();

export class KeymapEditorProvider implements vscode.CustomTextEditorProvider {
  private lastActiveDocument: vscode.TextDocument | undefined;

  constructor(
    private readonly context: vscode.ExtensionContext,
    private readonly getRunOptions: () => RunOptions,
    private readonly resolveQmkHome: (options: RunOptions) => Promise<string>,
  ) {}

  getLastActiveDocument(): vscode.TextDocument | undefined {
    return this.lastActiveDocument;
  }

  async resolveCustomTextEditor(document: vscode.TextDocument, panel: vscode.WebviewPanel): Promise<void> {
    if (panel.active) this.lastActiveDocument = document;
    panel.webview.options = {
      enableScripts: true,
      localResourceRoots: [
        vscode.Uri.joinPath(this.context.extensionUri, "dist"),
        vscode.Uri.joinPath(this.context.extensionUri, "media"),
      ],
    };
    panel.webview.html = this.html(panel.webview);

    const parsedPath = parsePath(document.uri.fsPath);
    let disposed = false;
    let timer: ReturnType<typeof setTimeout> | undefined;
    let resourcesPromise: Promise<Resources> | undefined;
    let refreshSeq = 0;

    const resources = (): Promise<Resources> => resourcesPromise ??= parsedPath
      ? this.loadResources(parsedPath.keyboard, parsedPath.keymap)
      : Promise.resolve({ geometry: null, catalog: emptyCatalog(), error: "This is not a QMK keymap.c path" });

    const currentState = async (): Promise<CurrentState> => {
      await this.ensureParser();
      const model = parseKeymap(document.getText());
      const loaded = await resources();
      return {
        model,
        resources: loaded,
        catalog: buildCatalog(loaded.catalog, {
          customKeycodes: model.customKeycodes,
          tapDanceNames: model.tapDanceNames,
        }),
      };
    };

    const refresh = async (): Promise<void> => {
      const seq = ++refreshSeq;
      if (!parsedPath || disposed) {
        if (!disposed) await panel.webview.postMessage(errorModel("", "", "This is not a QMK keymap.c path"));
        return;
      }
      try {
        const state = await currentState();
        if (disposed || seq !== refreshSeq) return;
        const view = buildViewModel(state.model, state.resources.geometry, state.catalog);
        const error = [state.resources.error, view.error].filter(Boolean).join("; ") || undefined;
        const message: HostMessage = {
          type: "model",
          keyboard: parsedPath.keyboard,
          keymap: parsedPath.keymap,
          layers: view.layers,
          geometry: view.geometry,
          ...(error ? { error } : {}),
        };
        await panel.webview.postMessage(message);
      } catch (error) {
        if (!disposed && seq === refreshSeq) await panel.webview.postMessage(errorModel(parsedPath.keyboard, parsedPath.keymap, messageOf(error)));
      }
    };

    const scheduleRefresh = (): void => {
      if (timer) clearTimeout(timer);
      timer = setTimeout(() => void refresh(), 150);
    };

    const documentSubscription = vscode.workspace.onDidChangeTextDocument((event) => {
      if (event.document.uri.toString() === document.uri.toString()) scheduleRefresh();
    });
    const viewSubscription = panel.onDidChangeViewState(({ webviewPanel }) => {
      if (webviewPanel.active) this.lastActiveDocument = document;
    });
    const messageSubscription = panel.webview.onDidReceiveMessage((message: WebviewMessage) => {
      if (message.type === "ready") void refresh();
      else if (message.type === "compile") void vscode.commands.executeCommand("qmkLens.compile", document.uri);
      else if (message.type === "flash") void vscode.commands.executeCommand("qmkLens.flash", document.uri);
      else if (message.type === "editKey") void this.editKey(document, message.layer, message.key, currentState);
      else if (message.type === "swapKeys") void this.swapKeys(document, message.layer, message.a, message.b, currentState);
    });

    panel.onDidDispose(() => {
      disposed = true;
      if (timer) clearTimeout(timer);
      documentSubscription.dispose();
      viewSubscription.dispose();
      messageSubscription.dispose();
    });
  }

  private ensureParser(): Promise<void> {
    const dist = vscode.Uri.joinPath(this.context.extensionUri, "dist").fsPath;
    return parserReady ??= initParser(dist).catch((e) => { parserReady = undefined; throw e; });
  }

  private async loadResources(keyboard: string, keymap: string): Promise<Resources> {
    const options = this.getRunOptions();
    let home: string;
    try {
      home = await this.resolveQmkHome(options);
    } catch (error) {
      return { geometry: null, catalog: emptyCatalog(), error: `QMK home: ${messageOf(error)}` };
    }
    if (!home) return { geometry: null, catalog: emptyCatalog(), error: "QMK home is not configured" };

    const catalogPromise = catalogs.get(home) ?? Promise.resolve().then(() => loadKeycodeCatalog(home));
    catalogs.set(home, catalogPromise);
    const [geometry, catalog] = await Promise.allSettled([
      loadGeometry(keyboard, keymap, {
        msysRoot: options.msysRoot,
        qmkHome: home,
        cacheDir: this.context.globalStorageUri.fsPath,
      }),
      catalogPromise,
    ]);
    const errors: string[] = [];
    if (geometry.status === "rejected") errors.push(`Geometry: ${messageOf(geometry.reason)}`);
    if (catalog.status === "rejected") {
      catalogs.delete(home);
      errors.push(`Keycodes: ${messageOf(catalog.reason)}`);
    }
    return {
      geometry: geometry.status === "fulfilled" ? geometry.value : null,
      catalog: catalog.status === "fulfilled" ? catalog.value : emptyCatalog(),
      ...(errors.length ? { error: errors.join("; ") } : {}),
    };
  }

  private async editKey(
    document: vscode.TextDocument,
    layerIndex: number,
    keyIndex: number,
    getState: () => Promise<CurrentState>,
  ): Promise<void> {
    try {
      const version = document.version;
      const state = await getState();
      if (document.version !== version) return void vscode.window.showWarningMessage("QMK Lens: document changed; select the key again");
      const layer = state.model.layers[layerIndex];
      const key = layer?.keys[keyIndex];
      const reason = buildViewModel(state.model, state.resources.geometry, state.catalog).layers[layerIndex]?.readOnlyReason;
      if (reason) return void vscode.window.showWarningMessage(`QMK Lens: ${reason}`);
      if (!layer || !key) return void vscode.window.showWarningMessage("QMK Lens: key no longer exists");

      const expression = await pickExpression(state.catalog, state.model, key.text);
      if (expression === undefined) return;
      const validation = validateRawExpression(expression);
      if (validation) return void vscode.window.showWarningMessage(`QMK Lens: ${validation}`);

      // Numeric indices can point to a different key after any external edit.
      if (document.version !== version) return void vscode.window.showWarningMessage("QMK Lens: document changed; select the key again");

      const edit = new vscode.WorkspaceEdit();
      edit.replace(document.uri, rangeFor(document, key.start, key.end), expression);
      if (!await vscode.workspace.applyEdit(edit)) vscode.window.showErrorMessage("QMK Lens could not apply the edit");
    } catch (error) {
      vscode.window.showErrorMessage(`QMK Lens: ${messageOf(error)}`);
    }
  }

  private async swapKeys(
    document: vscode.TextDocument,
    layerIndex: number,
    a: number,
    b: number,
    getState: () => Promise<CurrentState>,
  ): Promise<void> {
    try {
      const version = document.version;
      const state = await getState();
      if (document.version !== version) return void vscode.window.showWarningMessage("QMK Lens: document changed; select the keys again");
      const reason = buildViewModel(state.model, state.resources.geometry, state.catalog).layers[layerIndex]?.readOnlyReason;
      if (reason) return void vscode.window.showWarningMessage(`QMK Lens: ${reason}`);
      const replacements = computeSwapEdits(state.model, layerIndex, a, b);
      if (!replacements.length) return;
      const edit = new vscode.WorkspaceEdit();
      for (const replacement of replacements) {
        edit.replace(document.uri, rangeFor(document, replacement.start, replacement.end), replacement.text);
      }
      if (!await vscode.workspace.applyEdit(edit)) vscode.window.showErrorMessage("QMK Lens could not swap the keys");
    } catch (error) {
      vscode.window.showWarningMessage(`QMK Lens: ${messageOf(error)}`);
    }
  }

  private html(webview: vscode.Webview): string {
    const nonce = randomBytes(16).toString("base64");
    const script = webview.asWebviewUri(vscode.Uri.joinPath(this.context.extensionUri, "dist", "webview.js"));
    const style = webview.asWebviewUri(vscode.Uri.joinPath(this.context.extensionUri, "media", "editor.css"));
    return `<!doctype html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="Content-Security-Policy" content="default-src 'none'; style-src ${webview.cspSource} 'nonce-${nonce}'; script-src 'nonce-${nonce}';">
  <link rel="stylesheet" href="${style}">
  <style id="positions" nonce="${nonce}"></style>
  <title>QMK Lens</title>
</head>
<body>
  <header>
    <span id="title">QMK Lens</span>
    <span class="actions">
      <button id="compile" type="button">Compile</button>
      <button id="flash" type="button">Flash</button>
    </span>
  </header>
  <div id="error" class="banner error" hidden></div>
  <nav id="tabs" aria-label="Keymap layers"></nav>
  <div id="readonly" class="banner" hidden></div>
  <main id="keyboard" aria-live="polite"><p class="loading">Loading keyboard geometry…</p></main>
  <section id="encoders" hidden></section>
  <script nonce="${nonce}" src="${script}"></script>
</body>
</html>`;
  }
}

function rangeFor(document: vscode.TextDocument, start: number, end: number): vscode.Range {
  return new vscode.Range(document.positionAt(start), document.positionAt(end));
}

function errorModel(keyboard: string, keymap: string, error: string): HostMessage {
  return { type: "model", keyboard, keymap, layers: [], geometry: null, error };
}

function emptyCatalog(): KeycodeCatalog {
  return { entries: new Map(), byName: new Map(), functions: [] };
}

function messageOf(error: unknown): string {
  return error instanceof Error ? error.message : String(error);
}

async function pickExpression(catalog: KeycodeCatalog, model: KeymapModel, current: string): Promise<string | undefined> {
  const choices: Choice[] = [
    { label: "$(edit) Enter raw expression…", choice: "raw", detail: "Use a keycode or one C macro expression" },
    ...[...catalog.entries.values()].sort((a, b) => a.key.localeCompare(b.key)).map((entry): Choice => ({
      label: entry.key,
      choice: "entry",
      expression: entry.key,
      description: [entry.label, entry.aliases.join(", ")].filter(Boolean).join(" — ") || undefined,
      detail: entry.group,
    })),
    ...catalog.functions.map((fn): Choice => ({
      label: fn.key,
      choice: "function",
      fn,
      description: fn.template,
      detail: fn.group,
    })),
  ];
  const picked = await vscode.window.showQuickPick(choices, {
    placeHolder: `Replace ${current}`,
    matchOnDescription: true,
    matchOnDetail: true,
  });
  if (!picked) return undefined;
  if (picked.choice === "entry") return picked.expression;
  if (picked.choice === "function") return fillTemplate(picked.fn.template, model, current);
  return vscode.window.showInputBox({
    title: "Enter raw QMK key expression",
    value: current,
    validateInput: validateRawExpression,
  });
}

async function fillTemplate(template: string, model: KeymapModel, current: string): Promise<string | undefined> {
  const names = [...new Set([...template.matchAll(/%([a-z]+)%/g)].map((match) => match[1]))];
  let result = template;
  for (const name of names) {
    let value: string | undefined;
    if (name === "layer") {
      value = (await vscode.window.showQuickPick(
        model.layers.map((layer) => ({ label: layer.designator, description: layer.layoutMacro })),
        { placeHolder: "Choose a layer" },
      ))?.label;
    } else {
      const initial = name === "kc" ? current : name === "mod" ? "MOD_LSFT" : model.tapDanceNames[0] ?? "0";
      value = await vscode.window.showInputBox({
        title: `Enter ${name} for ${template}`,
        value: initial,
        validateInput: (input) => input.trim() ? undefined : "A value is required",
      });
    }
    if (value === undefined) return undefined;
    result = result.replaceAll(`%${name}%`, value.trim());
  }
  return result;
}
