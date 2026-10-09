// Pure keymap.c model. Must not import vscode.
import { Language, Parser, type Node } from "web-tree-sitter";
import { readFileSync } from "node:fs";
import * as path from "node:path";

export interface Key {
  text: string;
  /** UTF-8 byte offsets into the source. */
  startByte: number;
  endByte: number;
  /** UTF-16 string offsets (JS string indices); use these for slicing and edits. */
  start: number;
  end: number;
}

export interface Layer {
  designator: string;
  layoutMacro: string;
  keys: Key[];
  readOnlyReason?: string;
}

export interface KeymapModel {
  layers: Layer[];
  customKeycodes: string[];
  tapDanceNames: string[];
  error?: string;
}

export function parsePath(fsPath: string): { keyboard: string; keymap: string } | undefined {
  const m = /(?:^|\/)keyboards\/(.+)\/keymaps\/([^/]+)\/keymap\.c$/.exec(fsPath.replace(/\\/g, "/"));
  return m ? { keyboard: m[1], keymap: m[2] } : undefined;
}

let parser: Parser | undefined;

/** wasmDir holds tree-sitter.wasm; cWasmDir (default wasmDir) holds tree-sitter-c.wasm. */
export async function initParser(wasmDir: string, cWasmDir = wasmDir): Promise<void> {
  if (parser) return;
  await Parser.init({ locateFile: (f: string) => path.join(wasmDir, f) });
  const lang = await Language.load(readFileSync(path.join(cWasmDir, "tree-sitter-c.wasm")));
  const p = new Parser();
  p.setLanguage(lang);
  parser = p;
}

const kids = (nodes: (Node | null)[]): Node[] => nodes.filter((c): c is Node => c !== null);

function* walk(n: Node): Generator<Node> {
  yield n;
  for (const c of kids(n.children)) yield* walk(c);
}

/** Why this subtree cannot be edited safely, if at all. */
function unsafeReason(n: Node, where: string): string | undefined {
  let reason: string | undefined;
  for (const d of walk(n)) {
    // tree-sitter-c has no preproc rule for argument/initializer lists, so `#ifdef` there becomes ERROR.
    if (d.type.startsWith("preproc") || (d.isError && /^\s*#/m.test(d.text))) return `Preprocessor directive inside ${where}`;
    if (d.isError || d.isMissing) reason ??= `Parse error inside ${where}`;
  }
  return reason;
}

function findKeymapsInitializer(root: Node): Node | undefined {
  for (const d of walk(root)) {
    if (d.type !== "init_declarator") continue;
    let decl = d.childForFieldName("declarator");
    while (decl && decl.type !== "identifier") decl = decl.childForFieldName("declarator");
    const value = d.childForFieldName("value");
    if (decl?.text === "keymaps" && value?.type === "initializer_list") return value;
  }
  return undefined;
}

function layoutCall(n: Node | null): Node | undefined {
  const fn = n?.type === "call_expression" ? n.childForFieldName("function") : null;
  return fn?.type === "identifier" && fn.text.startsWith("LAYOUT") ? n! : undefined;
}

export function parseKeymap(source: string): KeymapModel {
  if (!parser) throw new Error("initParser() must be called first");
  const tree = parser.parse(source);
  if (!tree) return { layers: [], customKeycodes: [], tapDanceNames: [], error: "Parse failed" };
  try {
    const root = tree.rootNode;
    const model: KeymapModel = { layers: [], customKeycodes: enumMembers(root, "custom_keycodes"), tapDanceNames: tapDances(root) };
    const list = findKeymapsInitializer(root);
    if (!list) return { ...model, error: "No keymaps[] initializer found" };

    // web-tree-sitter parses JS strings as UTF-16, so startIndex/endIndex are already UTF-16 offsets.
    const toByte = byteOffsets(source);
    let arrayReason: string | undefined;
    for (const item of kids(list.children)) {
      if (item.type === "comment" || (["{", "}", ","].includes(item.type) && !item.isMissing)) continue;
      const call = item.type === "initializer_pair" ? layoutCall(item.childForFieldName("value")) : layoutCall(item);
      if (!call) {
        // Anything between layers that is not a layer makes every layer unsafe.
        arrayReason ??= unsafeReason(item, "keymaps[]") ?? `Unexpected ${item.type} inside keymaps[]`;
        continue;
      }
      const designatorNode = item.type === "initializer_pair" ? item.childForFieldName("designator") : null;
      const keys: Key[] = [];
      for (const a of kids(call.childForFieldName("arguments")!.namedChildren)) {
        if (a.type === "comment") continue;
        keys.push({ text: a.text, start: a.startIndex, end: a.endIndex, startByte: toByte(a.startIndex), endByte: toByte(a.endIndex) });
      }
      const layer: Layer = {
        designator: designatorNode ? kids(designatorNode.namedChildren)[0]?.text ?? designatorNode.text : String(model.layers.length),
        layoutMacro: call.childForFieldName("function")!.text,
        keys,
      };
      const reason = unsafeReason(item, `layer ${layer.designator}`);
      if (reason) layer.readOnlyReason = reason;
      model.layers.push(layer);
    }
    if (arrayReason) for (const l of model.layers) l.readOnlyReason ??= arrayReason;
    return model;
  } finally {
    tree.delete();
  }
}

/** Monotonic UTF-16 index -> UTF-8 byte offset (callers ask in increasing order). */
function byteOffsets(source: string): (index: number) => number {
  let i = 0;
  let b = 0;
  return (index) => {
    if (index < i) (i = 0), (b = 0);
    for (; i < index; i++) {
      const c = source.charCodeAt(i);
      b += c < 0x80 ? 1 : c < 0x800 ? 2 : c >= 0xd800 && c <= 0xdbff ? 4 : c >= 0xdc00 && c <= 0xdfff ? 0 : 3;
    }
    return b;
  };
}

function enumMembers(root: Node, name: string): string[] {
  for (const d of walk(root)) {
    if (d.type === "enum_specifier" && d.childForFieldName("name")?.text === name) return enumeratorNames(d);
  }
  return [];
}

function enumeratorNames(enumSpec: Node): string[] {
  const body = enumSpec.childForFieldName("body");
  return body ? kids(body.namedChildren).filter((e) => e.type === "enumerator").map((e) => e.childForFieldName("name")!.text) : [];
}

/** Identifiers used as TD(x) plus all members of any enum that contains one of them. */
function tapDances(root: Node): string[] {
  const used = new Set<string>();
  const enums: Node[] = [];
  for (const d of walk(root)) {
    if (d.type === "enum_specifier") enums.push(d);
    if (d.type === "call_expression" && d.childForFieldName("function")?.text === "TD") {
      const args = d.childForFieldName("arguments");
      const arg = args && kids(args.namedChildren).find((a) => a.type !== "comment");
      if (arg?.type === "identifier") used.add(arg.text);
    }
  }
  const out = new Set(used);
  for (const e of enums) {
    const names = enumeratorNames(e);
    if (names.some((n) => used.has(n))) names.forEach((n) => out.add(n));
  }
  return [...out];
}

/** Replace one key's text by its UTF-16 range. */
export function applyEdit(source: string, key: Pick<Key, "start" | "end">, newText: string): string {
  return source.slice(0, key.start) + newText + source.slice(key.end);
}
