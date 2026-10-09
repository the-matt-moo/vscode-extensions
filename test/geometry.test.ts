import { beforeAll, describe, expect, it } from "vitest";
import { readFileSync } from "node:fs";
import { parseQmkInfo, resolveLayout, bounds, type Geometry } from "../src/model/geometry";
import { initParser, parseKeymap } from "../src/model/keymap";

const loadFixture = (name: string) => JSON.parse(readFileSync(`test/fixtures/${name}.json`, "utf8"));

let moonlander: Geometry;
let lily58: Geometry;
let cu7: Geometry;

beforeAll(async () => {
  moonlander = parseQmkInfo(loadFixture("qmkinfo_moonlander_moo"));
  lily58 = parseQmkInfo(loadFixture("qmkinfo_lily58_moo"));
  cu7 = parseQmkInfo(loadFixture("qmkinfo_cu7_tench"));
  await initParser("node_modules/web-tree-sitter", "node_modules/tree-sitter-c");
}, 30_000);

describe("parseQmkInfo", () => {
  it("parses moonlander with 2 layouts and alias", () => {
    expect(moonlander.keyboard).toBe("Moonlander Mark I");
    expect(Object.keys(moonlander.layouts)).toEqual(["LAYOUT", "LAYOUT_halfmoon"]);
    expect(moonlander.layouts["LAYOUT"].length).toBe(72);
    expect(moonlander.layouts["LAYOUT_halfmoon"].length).toBe(36);
    expect(moonlander.aliases).toEqual({ LAYOUT_moonlander: "LAYOUT" });
  });

  it("parses lily58 with 58 keys, no aliases", () => {
    expect(lily58.keyboard).toBe("Lily58");
    expect(Object.keys(lily58.layouts)).toEqual(["LAYOUT"]);
    expect(lily58.layouts["LAYOUT"].length).toBe(58);
    expect(lily58.aliases).toEqual({});
  });

  it("parses cu7 with 7 keys", () => {
    expect(cu7.keyboard).toBe("CU7");
    expect(cu7.layouts["LAYOUT"].length).toBe(7);
  });

  it("populates KeyGeom fields with defaults", () => {
    const k = moonlander.layouts["LAYOUT"][0];
    expect(k.x).toBe(0);
    expect(k.y).toBe(0.375);
    expect(k.w).toBe(1);
    expect(k.h).toBe(1);
    expect(k.matrix).toEqual([0, 0]);
  });

  it("preserves explicit w/h", () => {
    // cu7 key 0 has w:2, h:2
    const k = cu7.layouts["LAYOUT"][0];
    expect(k.w).toBe(2);
    expect(k.h).toBe(2);
  });
});

describe("resolveLayout", () => {
  it("resolves exact layout name", () => {
    const r = resolveLayout(moonlander, "LAYOUT");
    expect(r).toBeDefined();
    expect(r!.name).toBe("LAYOUT");
    expect(r!.keys.length).toBe(72);
  });

  it("resolves LAYOUT_moonlander alias -> LAYOUT (72 keys)", () => {
    const r = resolveLayout(moonlander, "LAYOUT_moonlander");
    expect(r).toBeDefined();
    expect(r!.name).toBe("LAYOUT");
    expect(r!.keys.length).toBe(72);
  });

  it("returns undefined for unknown layout", () => {
    expect(resolveLayout(moonlander, "LAYOUT_nonexistent")).toBeUndefined();
  });

  it("resolves lily58 LAYOUT directly", () => {
    const r = resolveLayout(lily58, "LAYOUT");
    expect(r).toBeDefined();
    expect(r!.keys.length).toBe(58);
  });
});

describe("bounds", () => {
  it("computes moonlander LAYOUT bounds", () => {
    const b = bounds(moonlander.layouts["LAYOUT"]);
    expect(b.width).toBeGreaterThan(0);
    expect(b.height).toBeGreaterThan(0);
  });

  it("computes cu7 bounds including w/h", () => {
    const b = bounds(cu7.layouts["LAYOUT"]);
    // Key 0 at x:0.5, w:2 => right edge 2.5
    expect(b.width).toBeGreaterThanOrEqual(2.5);
    expect(b.height).toBeGreaterThanOrEqual(2);
  });

  it("returns 0,0 for empty keys", () => {
    expect(bounds([])).toEqual({ width: 0, height: 0 });
  });
});

describe("cross-check: keymap key count == resolved layout key count", () => {
  const CROSS_CHECKS: Array<{ fixture: string; infoFixture: string; layoutMacro: string }> = [
    { fixture: "moonlander_moo", infoFixture: "qmkinfo_moonlander_moo", layoutMacro: "LAYOUT_moonlander" },
    { fixture: "lily58_moo", infoFixture: "qmkinfo_lily58_moo", layoutMacro: "LAYOUT" },
    { fixture: "cu7_tench", infoFixture: "qmkinfo_cu7_tench", layoutMacro: "LAYOUT" },
  ];

  it.each(CROSS_CHECKS)("$fixture: parser keys == geometry keys", ({ fixture, infoFixture, layoutMacro }) => {
    const src = readFileSync(`test/fixtures/${fixture}.c`, "utf8");
    const model = parseKeymap(src);
    const geom = parseQmkInfo(loadFixture(infoFixture));
    const resolved = resolveLayout(geom, layoutMacro);
    expect(resolved).toBeDefined();

    for (const layer of model.layers) {
      expect(layer.keys.length, `layer ${layer.designator}: ${layer.keys.length} keys vs ${resolved!.keys.length} geom keys`).toBe(resolved!.keys.length);
    }
  });
});
