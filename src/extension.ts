import * as vscode from "vscode";
import { run, runShell, type RunOptions } from "./qmk/runner";

const TOOLS = ["avr-gcc", "arm-none-eabi-gcc", "dfu-util", "dfu-programmer"];

function runOptions(): RunOptions {
  return { msysRoot: vscode.workspace.getConfiguration("qmkLens").get<string>("msysRoot") || "C:/QMK_MSYS" };
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
    for (const tool of TOOLS) {
      const r = await runShell(`command -v ${tool}`, opts);
      out.appendLine(`${tool}: ${r.code === 0 ? r.stdout.trim() : "MISSING"}`);
    }
  } catch (e) {
    out.appendLine(`Error: ${(e as Error).message}. Check qmkLens.msysRoot.`);
  }
}

export function activate(context: vscode.ExtensionContext): void {
  const out = vscode.window.createOutputChannel("QMK Lens");
  context.subscriptions.push(out, vscode.commands.registerCommand("qmkLens.doctor", () => doctor(out)));
}

export function deactivate(): void {}
