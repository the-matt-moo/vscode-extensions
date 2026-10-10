import { describe, expect, it } from "vitest";
import { computeSwapEdits, validateRawExpression } from "../src/editor/editing";
import type { KeymapModel } from "../src/model/keymap";

const model: KeymapModel = {
  layers: [{
    designator: "0",
    layoutMacro: "LAYOUT",
    keys: [
      { text: "KC_A", start: 10, end: 14, startByte: 10, endByte: 14 },
      { text: "LT(1, KC_B)", start: 16, end: 27, startByte: 16, endByte: 27 },
    ],
  }],
  customKeycodes: [],
  tapDanceNames: [],
};

describe("validateRawExpression", () => {
  it.each(["KC_A", "MO(_FN)", "LT(_FN, KC_A)", "LGUI(LSFT(KC_R))"])("accepts %s", (value) => {
    expect(validateRawExpression(value)).toBeUndefined();
  });

  it.each(["", "KC_A, KC_B", "MO(_FN", "KC_A)"])("rejects %s", (value) => {
    expect(validateRawExpression(value)).toBeTypeOf("string");
  });
});

describe("computeSwapEdits", () => {
  it("returns two replacements using the original texts and UTF-16 ranges", () => {
    expect(computeSwapEdits(model, 0, 0, 1)).toEqual([
      { start: 10, end: 14, text: "LT(1, KC_B)" },
      { start: 16, end: 27, text: "KC_A" },
    ]);
  });

  it("does nothing when a key is dropped on itself", () => {
    expect(computeSwapEdits(model, 0, 1, 1)).toEqual([]);
  });

  it("rejects read-only layers", () => {
    const readOnly = { ...model, layers: [{ ...model.layers[0], readOnlyReason: "Unsafe" }] };
    expect(() => computeSwapEdits(readOnly, 0, 0, 1)).toThrow("Unsafe");
  });
});
