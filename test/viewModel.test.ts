import { describe, expect, it } from "vitest";
import { buildViewModel } from "../src/editor/viewModel";
import type { Geometry } from "../src/model/geometry";
import type { KeycodeCatalog } from "../src/model/keycodes";
import type { KeymapModel } from "../src/model/keymap";

const catalog: KeycodeCatalog = {
  entries: new Map([["KC_A", { key: "KC_A", aliases: [], label: "A", group: "basic" }]]),
  byName: new Map([["KC_A", "KC_A"]]),
  functions: [],
};

const model: KeymapModel = {
  layers: [
    {
      designator: "_BASE",
      layoutMacro: "LAYOUT_alias",
      keys: [
        { text: "KC_A", start: 10, end: 14, startByte: 10, endByte: 14 },
        { text: "MY_KEY", start: 16, end: 22, startByte: 16, endByte: 22 },
      ],
    },
  ],
  customKeycodes: ["MY_KEY"],
  tapDanceNames: [],
};

const geometry: Geometry = {
  keyboard: "Test",
  aliases: { LAYOUT_alias: "LAYOUT" },
  layouts: {
    LAYOUT: [
      { x: 0, y: 0, w: 1, h: 1 },
      { x: 1, y: 0, w: 1, h: 1 },
    ],
  },
};

describe("buildViewModel", () => {
  it("maps layers, geometry, and display labels", () => {
    const view = buildViewModel(model, geometry, catalog);
    expect(view.layers[0]).toMatchObject({ designator: "_BASE", layoutMacro: "LAYOUT_alias" });
    expect(view.layers[0].keys).toEqual([
      { text: "KC_A", label: "A" },
      { text: "MY_KEY", label: "MY_KEY" },
    ]);
    expect(view.geometry?.keys).toHaveLength(2);
  });

  it("marks key-count mismatches read-only", () => {
    const short = { ...model, layers: [{ ...model.layers[0], keys: model.layers[0].keys.slice(0, 1) }] };
    expect(buildViewModel(short, geometry, catalog).layers[0].readOnlyReason)
      .toBe("Layout has 2 keys, keymap layer has 1");
  });

  it("keeps geometry null when it is unavailable", () => {
    const view = buildViewModel(model, null, catalog);
    expect(view.geometry).toBeNull();
    expect(view.layers[0].readOnlyReason).toBeUndefined();
  });

  it("maps global encoder bindings to ViewEncoder", () => {
    const withEncoders = { ...model, encoderBindings: [{ cw: "KC_VOLU", ccw: "KC_VOLD" }] };
    const view = buildViewModel(withEncoders, geometry, catalog);
    expect(view.layers[0].encoders).toEqual([{ cw: "KC_VOLU", ccw: "KC_VOLD", cwLabel: "KC_VOLU", ccwLabel: "KC_VOLD" }]);
  });

  it("prefers encoderMap over encoderBindings per layer", () => {
    const withMap = {
      ...model,
      encoderBindings: [{ cw: "KC_A", ccw: "KC_B" }],
      encoderMap: [[{ cw: "KC_UP", ccw: "KC_DOWN" }]],
    };
    const view = buildViewModel(withMap, geometry, catalog);
    expect(view.layers[0].encoders![0].cw).toBe("KC_UP");
  });

  it("omits encoders when no encoder data exists", () => {
    const view = buildViewModel(model, geometry, catalog);
    expect(view.layers[0].encoders).toBeUndefined();
  });
});
