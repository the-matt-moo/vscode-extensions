import { beforeAll, describe, expect, it } from "vitest";
import { readFileSync } from "node:fs";
import { applyEdit, initParser, parseKeymap, parsePath, type KeymapModel } from "../src/model/keymap";

const fixture = (name: string) => readFileSync(`test/fixtures/${name}.c`, "utf8");
const EXPECTED: Record<string, { layers: number; keys: number }> = {
  lily58_moo: { layers: 4, keys: 58 },
  lily58_MOOku: { layers: 2, keys: 58 },
  moonlander_moo: { layers: 5, keys: 72 },
  moonlander_new_moo: { layers: 4, keys: 72 },
  cu7_tench: { layers: 1, keys: 7 },
};

beforeAll(async () => {
  // Tests load the wasm straight from node_modules; the extension loads it from dist/.
  await initParser("node_modules/web-tree-sitter", "node_modules/tree-sitter-c");
}, 30_000);

function rebuild(src: string, m: KeymapModel): string {
  let out = "";
  let pos = 0;
  for (const k of m.layers.flatMap((l) => l.keys)) {
    out += src.slice(pos, k.start) + k.text;
    pos = k.end;
  }
  return out + src.slice(pos);
}

describe.each(Object.keys(EXPECTED))("fixture %s", (name) => {
  const src = fixture(name);
  it("parses layers with the expected key count", () => {
    const m = parseKeymap(src);
    expect(m.error).toBeUndefined();
    expect(m.layers.length).toBeGreaterThan(0);
    if (EXPECTED[name].layers) expect(m.layers.length).toBe(EXPECTED[name].layers);
    for (const l of m.layers) {
      expect(l.keys.length, `layer ${l.designator}`).toBe(EXPECTED[name].keys);
      expect(l.readOnlyReason).toBeUndefined();
      expect(l.layoutMacro).toMatch(/^LAYOUT/);
    }
  });
  it("round-trips byte-identically", () => {
    const m = parseKeymap(src);
    for (const k of m.layers.flatMap((l) => l.keys)) expect(src.slice(k.start, k.end)).toBe(k.text);
    expect(rebuild(src, m)).toBe(src);
  });
  it("single edit changes only the target range", () => {
    const m = parseKeymap(src);
    const k = m.layers[0].keys[3];
    const out = applyEdit(src, k, "KC_NO");
    expect(out.slice(0, k.start)).toBe(src.slice(0, k.start));
    expect(out.slice(k.start + 5)).toBe(src.slice(k.end));
    expect(out.slice(k.start, k.start + 5)).toBe("KC_NO");
    expect(parseKeymap(out).layers[0].keys[3].text).toBe("KC_NO");
  });
});

describe("keymap model", () => {
  it("records counts and parse time", () => {
    for (const name of Object.keys(EXPECTED)) {
      const src = fixture(name);
      const t0 = performance.now();
      const m = parseKeymap(src);
      const ms = performance.now() - t0;
      console.log(`${name}: ${m.layers.length} layers x [${[...new Set(m.layers.map((l) => l.keys.length))].join(",")}] keys, ${ms.toFixed(1)} ms`);
    }
  });

  it("keeps CRLF line endings through parse and edit", () => {
    // Real fixtures are LF; build a CRLF variant.
    const src = fixture("moonlander_moo").replace(/\n/g, "\r\n");
    const m = parseKeymap(src);
    expect(m.layers[0].keys.length).toBe(72);
    expect(rebuild(src, m)).toBe(src);
    const out = applyEdit(src, m.layers[1].keys[10], "KC_NO");
    expect(/(?<!\r)\n/.test(out)).toBe(false);
    expect(out.split("\r\n").length).toBe(src.split("\r\n").length);
  });

  it("keeps nested args as one key", () => {
    const m = parseKeymap(fixture("moonlander_moo"));
    const all = m.layers.flatMap((l) => l.keys.map((k) => k.text));
    expect(all).toContain("LSFT_T(KC_LEFT)");
    expect(all).toContain("LGUI(LSFT(KC_R))");
  });

  it("marks a layer with #ifdef read-only", () => {
    const src = [
      "const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {",
      "  [_BASE] = LAYOUT(KC_A, KC_B),",
      "  [1] = LAYOUT(",
      "#ifdef FOO",
      "    KC_C,",
      "#else",
      "    KC_D,",
      "#endif",
      "    KC_E),",
      "};",
    ].join("\n");
    const m = parseKeymap(src);
    const base = m.layers.find((l) => l.designator === "_BASE");
    expect(base?.keys.map((k) => k.text)).toEqual(["KC_A", "KC_B"]);
    expect(base?.readOnlyReason).toBeUndefined();
    expect(m.layers.find((l) => l.designator === "1")?.readOnlyReason).toMatch(/Preprocessor/);
  });

  it("marks all layers read-only for #ifdef between layers", () => {
    const src = [
      "const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {",
      "  [0] = LAYOUT(KC_A, KC_B),",
      "#ifdef FOO",
      "  [1] = LAYOUT(KC_C, KC_D),",
      "#endif",
      "};",
    ].join("\n");
    const m = parseKeymap(src);
    expect(m.layers.length).toBeGreaterThan(0);
    for (const l of m.layers) expect(l.readOnlyReason).toMatch(/Preprocessor/);
  });

  it("uses UTF-16 offsets after non-ASCII text", () => {
    const src = "// é 😀 ü\nconst uint16_t PROGMEM keymaps[][1][1] = { [0] = LAYOUT(KC_A, LGUI(KC_B)) };\n";
    const m = parseKeymap(src);
    const [a, b] = m.layers[0].keys;
    expect(src.slice(a.start, a.end)).toBe("KC_A");
    expect(src.slice(b.start, b.end)).toBe("LGUI(KC_B)");
    const bytes = Buffer.from(src, "utf8");
    expect(bytes.subarray(b.startByte, b.endByte).toString("utf8")).toBe("LGUI(KC_B)");
    expect(applyEdit(src, a, "KC_Z")).toBe(src.replace("KC_A", "KC_Z"));
  });

  it("extracts custom keycodes and tap dance names", () => {
    expect(parseKeymap(fixture("lily58_moo")).customKeycodes.length).toBeGreaterThan(0);
    const ml = parseKeymap(fixture("moonlander_moo"));
    expect(ml.customKeycodes).toContain("MAC_UID");
    expect(ml.tapDanceNames).toContain("WIN_LBRACKET");
    expect(ml.tapDanceNames).not.toContain("SINGLE_TAP");
  });

  it("reports missing keymaps", () => {
    expect(parseKeymap("int x;").error).toBeDefined();
  });
});

describe("parsePath", () => {
  it.each([
    [String.raw`C:\Users\T\qmk_firmware\keyboards\zsa\moonlander\keymaps\new_moo\keymap.c`, { keyboard: "zsa/moonlander", keymap: "new_moo" }],
    ["/home/t/qmk_firmware/keyboards/lily58/keymaps/moo/keymap.c", { keyboard: "lily58", keymap: "moo" }],
    ["C:/q/keyboards/capsunlocked/cu7/keymaps/tench/keymap.c", { keyboard: "capsunlocked/cu7", keymap: "tench" }],
    ["C:/q/keyboards/lily58/keymaps/moo/config.h", undefined],
    ["C:/q/keyboards/lily58/keymap.c", undefined],
  ])("%s", (p, want) => expect(parsePath(p)).toEqual(want));
});
