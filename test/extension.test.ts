import { beforeEach, describe, expect, it, vi } from "vitest";
import type * as vscode from "vscode";

const state = vi.hoisted(() => ({
  activeTextEditor: undefined as vscode.TextEditor | undefined,
  visibleTextEditors: [] as vscode.TextEditor[],
  activeTab: undefined as unknown,
  textDocuments: [] as vscode.TextDocument[],
  showWarningMessage: vi.fn(),
  showErrorMessage: vi.fn(),
  executeCommand: vi.fn(async () => undefined),
  openTextDocument: vi.fn(async (uri: vscode.Uri) => ({
    uri,
    isDirty: false,
    save: vi.fn(async () => true),
  })),
}));

vi.mock("vscode", () => ({
  ViewColumn: { Beside: -2 },
  Uri: {
    file: (fsPath: string) => ({ fsPath, path: fsPath, scheme: "file", toString: () => `file://${fsPath}` }),
  },
  window: {
    get activeTextEditor() { return state.activeTextEditor; },
    get visibleTextEditors() { return state.visibleTextEditors; },
    get tabGroups() {
      return {
        activeTabGroup: {
          get activeTab() { return state.activeTab; },
        },
      };
    },
    showWarningMessage: state.showWarningMessage,
    showErrorMessage: state.showErrorMessage,
  },
  commands: {
    executeCommand: state.executeCommand,
  },
  workspace: {
    get textDocuments() { return state.textDocuments; },
    openTextDocument: state.openTextDocument,
  },
}));

import { findKeymapUri, openVisualEditor, resolveKeymap } from "../src/extension";
import type { KeymapEditorProvider } from "../src/editor/provider";

function fakeProvider(lastDoc?: vscode.TextDocument): KeymapEditorProvider {
  return {
    getLastActiveDocument: () => lastDoc,
  } as unknown as KeymapEditorProvider;
}

function fakeEditor(fsPath: string): vscode.TextEditor {
  const uri = { fsPath, path: fsPath, scheme: "file", toString: () => fsPath } as vscode.Uri;
  return {
    document: {
      uri,
      isDirty: false,
      save: vi.fn(async () => true),
    } as unknown as vscode.TextDocument,
  } as vscode.TextEditor;
}

beforeEach(() => {
  vi.clearAllMocks();
  state.activeTextEditor = undefined;
  state.visibleTextEditors = [];
  state.activeTab = undefined;
  state.textDocuments = [];
});

describe("openVisualEditor path detection and warning dispatch", () => {
  it("opens visual editor for valid POSIX .../keymaps/<layout>/keymap.c without warning", async () => {
    state.activeTextEditor = fakeEditor("/home/user/lily58/keymaps/moo/keymap.c");
    const provider = fakeProvider();

    await openVisualEditor(provider);

    expect(state.showWarningMessage).not.toHaveBeenCalled();
    expect(state.executeCommand).toHaveBeenCalledWith(
      "vscode.openWith",
      state.activeTextEditor.document.uri,
      "qmkLens.keymap",
      -2,
    );
  });

  it("opens visual editor for valid Windows-style ...\\keymaps\\<layout>\\keymap.c without warning", async () => {
    state.activeTextEditor = fakeEditor(String.raw`C:\projects\moonlander\keymaps\default\keymap.c`);
    const provider = fakeProvider();

    await openVisualEditor(provider);

    expect(state.showWarningMessage).not.toHaveBeenCalled();
    expect(state.executeCommand).toHaveBeenCalledWith(
      "vscode.openWith",
      state.activeTextEditor.document.uri,
      "qmkLens.keymap",
      -2,
    );
  });

  it("opens visual editor when explicit valid URI argument is provided", async () => {
    state.activeTextEditor = undefined;
    const provider = fakeProvider();
    const uri = { fsPath: "/work/keyboards/crkbd/keymaps/sub/layout/keymap.c", scheme: "file" } as vscode.Uri;

    await openVisualEditor(provider, uri);

    expect(state.showWarningMessage).not.toHaveBeenCalled();
    expect(state.executeCommand).toHaveBeenCalledWith(
      "vscode.openWith",
      uri,
      "qmkLens.keymap",
      -2,
    );
  });

  it("falls back to last active document or visible editor when active editor is unfocused", async () => {
    const editor = fakeEditor("/workspace/keymaps/custom/keymap.c");
    state.activeTextEditor = undefined;
    state.visibleTextEditors = [editor];
    const provider = fakeProvider();

    await openVisualEditor(provider);

    expect(state.showWarningMessage).not.toHaveBeenCalled();
    expect(state.executeCommand).toHaveBeenCalledWith(
      "vscode.openWith",
      editor.document.uri,
      "qmkLens.keymap",
      -2,
    );
  });

  it("shows warning when active editor is an unrelated file", async () => {
    state.activeTextEditor = fakeEditor("/home/user/lily58/keymaps/moo/config.h");
    const provider = fakeProvider();

    await openVisualEditor(provider);

    expect(state.showWarningMessage).toHaveBeenCalledWith("QMK Lens: open a keymaps/*/keymap.c file first");
    expect(state.executeCommand).not.toHaveBeenCalled();
  });

  it("shows warning when keymap.c is not in a layout folder", async () => {
    state.activeTextEditor = fakeEditor("/home/user/lily58/keymaps/keymap.c");
    const provider = fakeProvider();

    await openVisualEditor(provider);

    expect(state.showWarningMessage).toHaveBeenCalledWith("QMK Lens: open a keymaps/*/keymap.c file first");
    expect(state.executeCommand).not.toHaveBeenCalled();
  });

  it("shows warning when no editor or file is active", async () => {
    state.activeTextEditor = undefined;
    state.visibleTextEditors = [];
    const provider = fakeProvider();

    await openVisualEditor(provider);

    expect(state.showWarningMessage).toHaveBeenCalledWith("QMK Lens: open a keymaps/*/keymap.c file first");
    expect(state.executeCommand).not.toHaveBeenCalled();
  });
});

describe("resolveKeymap target resolution", () => {
  it("resolves keymap and keyboard for standalone path without keyboards/ folder", async () => {
    state.activeTextEditor = fakeEditor(String.raw`C:\repos\planck\keymaps\default\keymap.c`);
    const provider = fakeProvider();

    const result = await resolveKeymap(undefined, provider);

    expect(result).toBeDefined();
    expect(result?.keyboard).toBe("planck");
    expect(result?.keymap).toBe("default");
  });
});
