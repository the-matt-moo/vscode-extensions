import { describe, expect, it } from "vitest";
import { existsSync } from "node:fs";
import {
  loadKeycodeCatalogFromDir,
  loadKeycodeCatalog,
  buildCatalog,
  labelFor,
  type KeycodeCatalog,
} from "../src/model/keycodes";

const FIXTURE_DIR = "test/fixtures/keycodes";

describe("loadKeycodeCatalogFromDir", () => {
  let catalog: KeycodeCatalog;

  it("loads and merges hjson files in version order", () => {
    catalog = loadKeycodeCatalogFromDir(FIXTURE_DIR);
    expect(catalog.entries.size).toBeGreaterThan(0);
  });

  it("contains KC_A with label A", () => {
    catalog = loadKeycodeCatalogFromDir(FIXTURE_DIR);
    const kca = catalog.entries.get("KC_A");
    expect(kca).toBeDefined();
    expect(kca!.label).toBe("A");
    expect(kca!.group).toBe("basic");
  });

  it("has _______ alias for KC_TRANSPARENT", () => {
    catalog = loadKeycodeCatalogFromDir(FIXTURE_DIR);
    expect(catalog.byName.get("_______")).toBe("KC_TRANSPARENT");
    expect(catalog.entries.get("KC_TRANSPARENT")!.aliases).toContain("_______");
    expect(catalog.entries.get("KC_TRANSPARENT")!.aliases).toContain("KC_TRNS");
  });

  it("has XXXXXXX alias for KC_NO", () => {
    catalog = loadKeycodeCatalogFromDir(FIXTURE_DIR);
    expect(catalog.byName.get("XXXXXXX")).toBe("KC_NO");
  });

  it("0.0.2 adds new entries without breaking 0.0.1", () => {
    catalog = loadKeycodeCatalogFromDir(FIXTURE_DIR);
    expect(catalog.entries.get("KC_MISSION_CONTROL")).toBeDefined();
    expect(catalog.entries.get("KC_MISSION_CONTROL")!.group).toBe("media");
    expect(catalog.byName.get("KC_MCTL")).toBe("KC_MISSION_CONTROL");
    // 0.0.1 entries still present
    expect(catalog.entries.get("KC_A")).toBeDefined();
  });

  it("0.0.5 !reset! clears old aliases and sets new ones", () => {
    catalog = loadKeycodeCatalogFromDir(FIXTURE_DIR);
    // 0.0.1 defined MS_UP as key name "MS_UP" with aliases KC_MS_UP, KC_MS_U
    // 0.0.5 overrides key at same hex with key "QK_MOUSE_CURSOR_UP", aliases [!reset!, MS_UP]
    const entry = catalog.entries.get("QK_MOUSE_CURSOR_UP");
    expect(entry).toBeDefined();
    expect(entry!.aliases).toEqual(["MS_UP"]);
    expect(entry!.aliases).not.toContain("KC_MS_UP");
    expect(entry!.aliases).not.toContain("!reset!");
  });

  it("has function entries", () => {
    catalog = loadKeycodeCatalogFromDir(FIXTURE_DIR);
    expect(catalog.functions.length).toBeGreaterThan(0);
    const mo = catalog.functions.find((f) => f.key === "MO");
    expect(mo).toBeDefined();
    expect(mo!.template).toBe("MO(%layer%)");
    const lsftT = catalog.functions.find((f) => f.key === "LSFT_T");
    expect(lsftT).toBeDefined();
  });
});

describe("buildCatalog", () => {
  it("adds custom keycodes", () => {
    const base = loadKeycodeCatalogFromDir(FIXTURE_DIR);
    const cat = buildCatalog(base, { customKeycodes: ["MAC_UID", "MAC_CRED"] });
    expect(cat.entries.get("MAC_UID")).toBeDefined();
    expect(cat.entries.get("MAC_UID")!.group).toBe("custom");
    expect(cat.byName.get("MAC_UID")).toBe("MAC_UID");
    expect(cat.entries.get("MAC_CRED")!.group).toBe("custom");
  });

  it("adds tap dance entries", () => {
    const base = loadKeycodeCatalogFromDir(FIXTURE_DIR);
    const cat = buildCatalog(base, { tapDanceNames: ["WIN_LBRACKET", "WIN_RBRACKET"] });
    expect(cat.entries.get("TD(WIN_LBRACKET)")).toBeDefined();
    expect(cat.entries.get("TD(WIN_LBRACKET)")!.group).toBe("tap_dance");
    expect(cat.entries.get("TD(WIN_LBRACKET)")!.label).toBe("WIN_LBRACKET");
    expect(cat.byName.get("TD(WIN_RBRACKET)")).toBe("TD(WIN_RBRACKET)");
  });

  it("does not duplicate existing entries", () => {
    const base = loadKeycodeCatalogFromDir(FIXTURE_DIR);
    const cat = buildCatalog(base, { customKeycodes: ["KC_A"] });
    expect(cat.entries.get("KC_A")!.group).toBe("basic"); // not overwritten
  });

  it("does not mutate base catalog", () => {
    const base = loadKeycodeCatalogFromDir(FIXTURE_DIR);
    const sizeBefore = base.entries.size;
    buildCatalog(base, { customKeycodes: ["MY_KEY"], tapDanceNames: ["MY_TD"] });
    expect(base.entries.size).toBe(sizeBefore);
    expect(base.entries.has("MY_KEY")).toBe(false);
  });
});

describe("labelFor", () => {
  const catalog = loadKeycodeCatalogFromDir(FIXTURE_DIR);

  it("returns label for a known keycode", () => {
    expect(labelFor("KC_A", catalog)).toBe("A");
  });

  it("returns label via alias lookup", () => {
    expect(labelFor("KC_ESC", catalog)).toBe("Escape");
  });

  it("returns shortest name for _______", () => {
    // KC_TRANSPARENT label is empty string, so falls to shortest name.
    // "_______" and "KC_TRNS" are both 7 chars; reduce picks first encountered.
    const result = labelFor("_______", catalog);
    expect(["_______", "KC_TRNS"]).toContain(result);
    expect(result.length).toBeLessThanOrEqual("KC_TRANSPARENT".length);
  });

  it("returns raw text for unknown keycode", () => {
    expect(labelFor("MY_UNKNOWN", catalog)).toBe("MY_UNKNOWN");
  });

  it("returns label for function-wrapped keycodes (raw text)", () => {
    expect(labelFor("LSFT_T(KC_A)", catalog)).toBe("LSFT_T(KC_A)");
  });
});

describe.skipIf(!existsSync("C:/Users/Tench/qmk_firmware"))("live keycode catalog", () => {
  it("loads the full qmk_firmware catalog", () => {
    const catalog = loadKeycodeCatalog("C:/Users/Tench/qmk_firmware");
    expect(catalog.entries.size).toBeGreaterThan(100);
    expect(catalog.entries.get("KC_A")).toBeDefined();
    expect(catalog.byName.get("_______")).toBe("KC_TRANSPARENT");
    expect(catalog.byName.get("XXXXXXX")).toBe("KC_NO");
    console.log(`Full catalog: ${catalog.entries.size} entries`);
  });
});
