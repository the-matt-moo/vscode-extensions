import { beforeEach, describe, expect, it, vi } from "vitest";
import * as path from "node:path";
import type * as vscode from "vscode";
import type { WebviewMessage } from "../src/shared/protocol";

const host = vi.hoisted(() => ({
  receive: undefined as ((message: WebviewMessage) => void) | undefined,
  change: undefined as ((event: { document: vscode.TextDocument }) => void) | undefined,
  applyEdit: vi.fn(async (_edit: unknown) => true),
  showQuickPick: vi.fn(),
  showInputBox: vi.fn(),
  showWarningMessage: vi.fn(),
  showErrorMessage: vi.fn(),
  executeCommand: vi.fn(),
}));

vi.mock("vscode", () => ({
  Uri: { joinPath: (uri: { fsPath: string }, ...parts: string[]) => ({ fsPath: path.join(uri.fsPath, ...parts) }) },
  Range: class {
    constructor(public start: unknown, public end: unknown) {}
  },
  WorkspaceEdit: class {
    replacements: unknown[] = [];
    replace(uri: unknown, range: unknown, text: string) { this.replacements.push({ uri, range, text }); }
  },
  workspace: {
    applyEdit: host.applyEdit,
    onDidChangeTextDocument: (listener: typeof host.change) => {
      host.change = listener;
      return { dispose() {} };
    },
  },
  window: {
    showQuickPick: host.showQuickPick,
    showInputBox: host.showInputBox,
    showWarningMessage: host.showWarningMessage,
    showErrorMessage: host.showErrorMessage,
  },
  commands: { executeCommand: host.executeCommand },
}));

import { KeymapEditorProvider } from "../src/editor/provider";

const source = `const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(KC_A, KC_B),
  [_FN] = LAYOUT(KC_C, KC_D)
};`;

async function editor() {
  let text = source;
  let version = 1;
  const uri = { fsPath: "M:/test/keyboards/test/keymaps/smoke/keymap.c", toString: () => "test:keymap" };
  const document = {
    uri, get version() { return version; }, getText: () => text, positionAt: (offset: number) => offset,
  } as unknown as vscode.TextDocument;
  const panel = {
    active: true,
    webview: {
      cspSource: "test:", asWebviewUri: (value: unknown) => String(value), postMessage: vi.fn(async () => true),
      onDidReceiveMessage: (listener: typeof host.receive) => {
        host.receive = listener;
        return { dispose() {} };
      },
    },
    onDidChangeViewState: () => ({ dispose() {} }), onDidDispose: () => ({ dispose() {} }),
  } as unknown as vscode.WebviewPanel;
  const context = {
    extensionUri: { fsPath: path.resolve(".") }, globalStorageUri: { fsPath: path.resolve(".vitest") },
  } as unknown as vscode.ExtensionContext;
  const provider = new KeymapEditorProvider(context, () => ({ msysRoot: "unused" }), async () => "");
  await provider.resolveCustomTextEditor(document, panel);
  return {
    document,
    send: (message: WebviewMessage) => host.receive!(message),
    change: (next: string) => { text = next; version++; },
  };
}

function pendingPick() {
  let choose!: (value: unknown) => void;
  host.showQuickPick.mockReturnValueOnce(new Promise((resolve) => { choose = resolve; }));
  return () => choose({ choice: "entry", expression: "KC_Z" });
}

beforeEach(() => { vi.clearAllMocks(); });

describe("editor host messages", () => {
  it("routes compile and flash to the document without running QMK", async () => {
    const view = await editor();
    view.send({ type: "compile" });
    view.send({ type: "flash" });
    expect(host.executeCommand.mock.calls).toEqual([
      ["qmkLens.compile", view.document.uri], ["qmkLens.flash", view.document.uri],
    ]);
  });

  it("applies a picker result to the selected key when unchanged", async () => {
    const view = await editor();
    const choose = pendingPick();
    view.send({ type: "editKey", layer: 1, key: 0 });
    await vi.waitFor(() => expect(host.showQuickPick).toHaveBeenCalledOnce());
    choose();
    await vi.waitFor(() => expect(host.applyEdit).toHaveBeenCalledOnce());
    const start = source.indexOf("KC_C");
    expect(host.applyEdit.mock.calls[0][0]).toMatchObject({
      replacements: [{ uri: view.document.uri, range: { start, end: start + 4 }, text: "KC_Z" }],
    });
  });

  it.each([
    ["layer removal", source.replace("  [_BASE] = LAYOUT(KC_A, KC_B),\n", "")],
    ["key insertion", source.replace("LAYOUT(KC_A", "LAYOUT(KC_X, KC_A")],
    ["key replacement", source.replace("KC_A", "KC_X")],
    ["unrelated text edit", `// changed\n${source}`],
  ])("rejects a picker result after %s", async (_name, next) => {
    const view = await editor();
    const choose = pendingPick();
    view.send({ type: "editKey", layer: 0, key: 0 });
    await vi.waitFor(() => expect(host.showQuickPick).toHaveBeenCalledOnce());
    view.change(next);
    choose();
    await vi.waitFor(() => expect(host.showWarningMessage).toHaveBeenCalledWith(expect.stringContaining("changed")));
    expect(host.applyEdit).not.toHaveBeenCalled();
  });

  it("rejects edits even if changed text is restored while the picker is open", async () => {
    const view = await editor();
    const choose = pendingPick();
    view.send({ type: "editKey", layer: 0, key: 0 });
    await vi.waitFor(() => expect(host.showQuickPick).toHaveBeenCalledOnce());
    view.change(source.replace("KC_A", "KC_X"));
    view.change(source);
    choose();
    await vi.waitFor(() => expect(host.showWarningMessage).toHaveBeenCalled());
    expect(host.applyEdit).not.toHaveBeenCalled();
  });

  it.each(["editKey", "swapKeys"] as const)("rejects %s if text changes during initial loading", async (type) => {
    const view = await editor();
    view.send(type === "editKey" ? { type, layer: 0, key: 0 } : { type, layer: 0, a: 0, b: 1 });
    view.change(source.replace("KC_A", "KC_X"));
    await vi.waitFor(() => expect(host.showWarningMessage).toHaveBeenCalledWith(expect.stringContaining("changed")));
    expect(host.showQuickPick).not.toHaveBeenCalled();
    expect(host.applyEdit).not.toHaveBeenCalled();
  });

  it("swaps both keys in one workspace edit", async () => {
    const view = await editor();
    view.send({ type: "swapKeys", layer: 0, a: 0, b: 1 });
    await vi.waitFor(() => expect(host.applyEdit).toHaveBeenCalledOnce());
    expect(host.applyEdit.mock.calls[0][0]).toMatchObject({ replacements: [{ text: "KC_B" }, { text: "KC_A" }] });
  });
});
