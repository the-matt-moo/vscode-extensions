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

export interface EncoderBinding {
  cw: string;
  ccw: string;
  cwStart?: number;
  cwEnd?: number;
  ccwStart?: number;
  ccwEnd?: number;
}

export interface KeymapModel {
  layers: Layer[];
  /** Per-layer encoder bindings from encoder_map[layer][encoder]. */
  encoderMap?: EncoderBinding[][];
  /** Global encoder bindings from encoder_update_user (when encoder_map is absent). */
  encoderBindings?: EncoderBinding[];
  customKeycodes: string[];
  tapDanceNames: string[];
  error?: string;
}

export function parsePath(fsPath: string): { keyboard: string; keymap: string } | undefined {
  if (!fsPath) return undefined;
  let normalized: string;
  try {
    normalized = decodeURI(fsPath.trim()).replace(/\\/g, "/");
  } catch {
    normalized = fsPath.trim().replace(/\\/g, "/");
  }
  const kmMatch = /(?:^|\/)keymaps\/(.+)\/keymap\.c$/i.exec(normalized);
  if (!kmMatch) return undefined;
  const keymap = kmMatch[1];

  const lower = normalized.toLowerCase();
  const kmIndex = lower.lastIndexOf("/keymaps/");
  const effectiveKmIndex = kmIndex !== -1 ? kmIndex : (lower.startsWith("keymaps/") ? 0 : -1);

  if (effectiveKmIndex !== -1) {
    const beforeKm = normalized.slice(0, effectiveKmIndex);
    const lowerBeforeKm = beforeKm.toLowerCase();
    const kbIndex = lowerBeforeKm.lastIndexOf("/keyboards/");
    if (kbIndex !== -1) {
      const keyboard = beforeKm.slice(kbIndex + "/keyboards/".length);
      if (keyboard) return { keyboard, keymap };
    }
    if (lowerBeforeKm.startsWith("keyboards/")) {
      const keyboard = beforeKm.slice("keyboards/".length);
      if (keyboard) return { keyboard, keymap };
    }
    if (beforeKm) {
      const slashIndex = beforeKm.lastIndexOf("/");
      const rawKb = slashIndex !== -1 ? beforeKm.slice(slashIndex + 1) : beforeKm;
      const keyboard = rawKb === "." || rawKb === ".." || /^[a-zA-Z]:$/.test(rawKb) ? "" : rawKb;
      return { keyboard, keymap };
    }
  }

  return { keyboard: "", keymap };
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

    // Encoder bindings: prefer declarative encoder_map, fall back to encoder_update_user extraction
    const encoderMap = parseEncoderMap(root);
    if (encoderMap) {
      model.encoderMap = encoderMap;
    } else {
      const bindings = extractOldStyleEncoders(root);
      if (bindings.length) model.encoderBindings = bindings;
    }

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

// -- Encoder parsing --

/** Parse `encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS]` (new-style declarative encoders). */
function parseEncoderMap(root: Node): EncoderBinding[][] | undefined {
  for (const d of walk(root)) {
    if (d.type !== "init_declarator") continue;
    let decl = d.childForFieldName("declarator");
    while (decl && decl.type !== "identifier") decl = decl.childForFieldName("declarator");
    const value = d.childForFieldName("value");
    if (decl?.text !== "encoder_map" || value?.type !== "initializer_list") continue;

    const layers: EncoderBinding[][] = [];
    for (const item of kids(value.children)) {
      if (item.type === "comment" || (["{" , "}", ","].includes(item.type) && !item.isMissing)) continue;
      const listNode = item.type === "initializer_pair" ? item.childForFieldName("value") : item;
      if (listNode?.type !== "initializer_list") continue;
      const encoders: EncoderBinding[] = [];
      for (const enc of kids(listNode.children)) {
        if (enc.type === "comment" || (["{" , "}", ","].includes(enc.type) && !enc.isMissing)) continue;
        const call = enc.type === "call_expression" ? enc : undefined;
        if (call) {
          const fn = call.childForFieldName("function");
          if (fn?.text === "ENCODER_CCW_CW") {
            const args = kids(call.childForFieldName("arguments")!.namedChildren).filter((a) => a.type !== "comment");
            if (args.length >= 2) {
              const ccwNode = args[0];
              const cwNode = args[1];
              encoders.push({
                cw: cwNode.text, ccw: ccwNode.text,
                cwStart: cwNode.startIndex, cwEnd: cwNode.endIndex,
                ccwStart: ccwNode.startIndex, ccwEnd: ccwNode.endIndex,
              });
            }
          }
        }
      }
      layers.push(encoders);
    }
    return layers.length ? layers : undefined;
  }
  return undefined;
}

/** Extract encoder bindings from encoder_update_user (old-style callback). Best-effort. */
function extractOldStyleEncoders(root: Node): EncoderBinding[] {
  for (const d of walk(root)) {
    if (d.type !== "function_definition") continue;
    let decl = d.childForFieldName("declarator");
    while (decl && decl.type !== "identifier") decl = decl.childForFieldName("declarator");
    if (decl?.text !== "encoder_update_user") continue;
    const body = d.childForFieldName("body");
    if (!body) return [];

    const bindings = new Map<number, EncoderBinding>();
    for (const n of walk(body)) {
      // Pattern 1: ternary — tap_code16(clockwise ? CW : CCW)
      if (n.type === "conditional_expression") {
        const cond = n.childForFieldName("condition");
        if (!cond || !isClockwiseNode(cond)) continue;
        const neg = cond.text.includes("!");
        const a = n.childForFieldName("consequence");
        const b = n.childForFieldName("alternative");
        if (a && b) {
          const cwNode = neg ? b : a;
          const ccwNode = neg ? a : b;
          bindings.set(encoderIndexOf(n), {
            cw: cwNode.text, ccw: ccwNode.text,
            cwStart: cwNode.startIndex, cwEnd: cwNode.endIndex,
            ccwStart: ccwNode.startIndex, ccwEnd: ccwNode.endIndex,
          });
        }
      }
      // Pattern 2: if (clockwise) { tap_code(CW); } else { tap_code(CCW); }
      if (n.type === "if_statement") {
        const cond = n.childForFieldName("condition");
        if (!cond || !isClockwiseNode(unwrap(cond))) continue;
        const neg = cond.text.includes("!");
        const cwBranch = neg ? n.childForFieldName("alternative") : n.childForFieldName("consequence");
        const ccwBranch = neg ? n.childForFieldName("consequence") : n.childForFieldName("alternative");
        const cw = cwBranch && firstTapArg(cwBranch);
        const ccw = ccwBranch && firstTapArg(ccwBranch);
        if (cw && ccw) {
          bindings.set(encoderIndexOf(n), {
            cw: cw.text, ccw: ccw.text,
            cwStart: cw.startIndex, cwEnd: cw.endIndex,
            ccwStart: ccw.startIndex, ccwEnd: ccw.endIndex,
          });
        }
      }
    }
    return [...bindings].sort((a, b) => a[0] - b[0]).map(([, v]) => v);
  }
  return [];
}

function isClockwiseNode(n: Node): boolean {
  const t = n.text.replace(/[()]/g, "").trim();
  return t === "clockwise" || t === "!clockwise";
}

function unwrap(n: Node): Node {
  while (n.type === "parenthesized_expression" && n.namedChildren[0]) n = n.namedChildren[0];
  return n;
}

/** Walk ancestors looking for if (index == N). */
function encoderIndexOf(n: Node): number {
  let p = n.parent;
  while (p) {
    if (p.type === "if_statement") {
      const c = p.childForFieldName("condition");
      const m = c && /index\s*==\s*(\d+)/.exec(c.text);
      if (m) return Number(m[1]);
    }
    p = p.parent;
  }
  return 0;
}

function firstTapArg(n: Node): Node | undefined {
  for (const d of walk(n)) {
    if (d.type === "call_expression") {
      const fn = d.childForFieldName("function");
      if (fn && /^(?:tap_code|tap_code16|register_code|register_code16)$/.test(fn.text)) {
        const args = d.childForFieldName("arguments");
        const arg = args && kids(args.namedChildren).find((a) => a.type !== "comment");
        return arg;
      }
    }
  }
  return undefined;
}

/** Replace one key's text by its UTF-16 range. */
export function applyEdit(source: string, key: Pick<Key, "start" | "end">, newText: string): string {
  return source.slice(0, key.start) + newText + source.slice(key.end);
}
