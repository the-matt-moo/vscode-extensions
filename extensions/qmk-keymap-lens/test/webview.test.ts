import { readFileSync } from "node:fs";
import { runInNewContext } from "node:vm";
import { transformSync } from "esbuild";
import { describe, expect, it } from "vitest";
import type { HostMessage, WebviewMessage } from "../src/shared/protocol";

// shortcut: this DOM harness checks behavior, not layout/CSP; use a real webview for those checks.
class Element extends EventTarget {
  children: Element[] = [];
  attributes = new Map<string, string>();
  className = "";
  title = "";
  type = "";
  hidden = false;
  disabled = false;
  draggable = false;
  private text = "";
  get textContent(): string { return this.text + this.children.map((child) => child.textContent).join(""); }
  set textContent(value: string) { this.text = value; this.children = []; }
  append(...children: Element[]) { this.children.push(...children); }
  replaceChildren(...children: Element[]) { this.text = ""; this.children = children; }
  setAttribute(name: string, value: string) { this.attributes.set(name, value); }
  click() { if (!this.disabled) this.dispatchEvent(new Event("click")); }
}

const code = transformSync(readFileSync("src/webview/main.ts", "utf8"), { loader: "ts", format: "iife" }).code;
const message: HostMessage = {
  type: "model", keyboard: "test/board", keymap: "smoke",
  layers: [
    { designator: "_BASE", layoutMacro: "LAYOUT", keys: [{ text: "KC_A", label: "A" }, { text: "KC_B", label: "B" }] },
    { designator: "_FN", layoutMacro: "LAYOUT", keys: [{ text: "MO(_BASE)", label: "MO(_BASE)" }, { text: "KC_C", label: "C" }] },
  ],
  geometry: { keys: [{ x: 0, y: 0, w: 1, h: 1 }, { x: 2, y: 1, w: 1.5, h: 2 }] },
};

function webview(savedState?: { selectedLayer: string }) {
  const elements = Object.fromEntries(["title", "tabs", "keyboard", "error", "readonly", "positions", "compile", "flash", "encoders"]
    .map((id) => [id, new Element()]));
  const sheet = {
    cssRules: [] as string[],
    insertRule(rule: string) { this.cssRules.push(rule); },
    deleteRule(index: number) { this.cssRules.splice(index, 1); },
  };
  Object.assign(elements.positions, { sheet });
  const window = new EventTarget();
  const sent: WebviewMessage[] = [];
  let state = savedState;
  runInNewContext(code, {
    window,
    document: { getElementById: (id: string) => elements[id], createElement: () => new Element() },
    acquireVsCodeApi: () => ({
      getState: () => state,
      setState: (next: typeof state) => { state = next; },
      postMessage: (value: WebviewMessage) => sent.push(value),
    }),
  });
  return {
    elements, sheet, sent,
    get state() { return state; },
    get keys() { return elements.keyboard.children[0]?.children ?? []; },
    receive: (data: unknown) => window.dispatchEvent(Object.assign(new Event("message"), { data })),
  };
}

function drag(key: Element, type: string) {
  const data = new Map<string, string>();
  const event = Object.assign(new Event(type, { cancelable: true }), {
    dataTransfer: { setData: (name: string, value: string) => data.set(name, value) },
  });
  key.dispatchEvent(event);
  return { event, data };
}

describe("webview UI smoke", () => {
  it("requests a model and renders geometry, labels, titles and accessible tabs", () => {
    const view = webview();
    expect(view.sent).toEqual([{ type: "ready" }]);
    view.receive(message);
    expect(view.elements.title.textContent).toBe("test/board / smoke — LAYOUT");
    expect(view.elements.tabs.children.map((tab) => tab.textContent)).toEqual(["_BASE", "_FN"]);
    expect(view.elements.tabs.children[0].attributes.get("aria-selected")).toBe("true");
    expect(view.elements.tabs.children[1].attributes.get("role")).toBe("tab");
    expect(view.keys.map((key) => key.textContent)).toEqual(["A", "B"]);
    expect(view.keys[0].title).toBe("KC_A");
    expect(view.keys[0].attributes.get("aria-label")).toBe("Layer 0 key 0: KC_A");
    expect(view.sheet.cssRules).toContain(".canvas-size { width: 189px; height: 162px; }");
    expect(view.sheet.cssRules).toContain(".key-position-1 { left: 110px; top: 56px; width: 77px; height: 104px; }");
    expect(view.elements.error.hidden).toBe(true);
    expect(view.elements.readonly.hidden).toBe(true);
  });

  it("switches layers and sends edit indices for the selected layer", () => {
    const view = webview();
    view.receive(message);
    view.elements.tabs.children[1].click();
    expect(view.state).toEqual({ selectedLayer: "_FN" });
    expect(view.elements.tabs.children[1].attributes.get("aria-selected")).toBe("true");
    expect(view.keys.map((key) => key.textContent)).toEqual(["MO(_BASE)", "C"]);
    view.keys[1].click();
    expect(view.sent.at(-1)).toEqual({ type: "editKey", layer: 1, key: 1 });
  });

  it("restores selection, retains it across updates, and falls back if removed", () => {
    const view = webview({ selectedLayer: "_FN" });
    view.receive(message);
    expect(view.keys[1].textContent).toBe("C");
    view.receive({ ...message, layers: [message.layers[1], message.layers[0]] });
    view.keys[0].click();
    expect(view.sent.at(-1)).toEqual({ type: "editKey", layer: 0, key: 0 });
    view.receive({ ...message, layers: [message.layers[0]] });
    expect(view.state).toEqual({ selectedLayer: "_BASE" });
    expect(view.keys[0].textContent).toBe("A");
  });

  it("sends a same-layer drag swap but not self-drops or ended drags", () => {
    const view = webview();
    view.receive(message);
    expect(drag(view.keys[0], "dragstart").data.get("text/plain")).toBe("0");
    expect(drag(view.keys[1], "dragover").event.defaultPrevented).toBe(true);
    drag(view.keys[1], "drop");
    expect(view.sent.at(-1)).toEqual({ type: "swapKeys", layer: 0, a: 0, b: 1 });
    const count = view.sent.length;
    drag(view.keys[0], "dragstart");
    drag(view.keys[0], "drop");
    drag(view.keys[0], "dragstart");
    drag(view.keys[0], "dragend");
    drag(view.keys[1], "drop");
    expect(view.sent).toHaveLength(count);
  });

  it.each(["model update", "layer switch"])("cancels an in-progress drag after %s", (action) => {
    const view = webview();
    view.receive(message);
    drag(view.keys[0], "dragstart");
    if (action === "model update") view.receive({
      ...message, layers: [{ ...message.layers[0], keys: [...message.layers[0].keys].reverse() }, message.layers[1]],
    });
    else view.elements.tabs.children[1].click();
    expect(drag(view.keys[1], "dragover").event.defaultPrevented).toBe(false);
    drag(view.keys[1], "drop");
    expect(view.sent).toEqual([{ type: "ready" }]);
  });

  it("sends compile and flash only after explicit button clicks", () => {
    const view = webview();
    view.receive(message);
    expect(view.sent).toEqual([{ type: "ready" }]);
    view.elements.compile.click();
    view.elements.flash.click();
    expect(view.sent).toEqual([{ type: "ready" }, { type: "compile" }, { type: "flash" }]);
  });

  it("renders errors as text, disables read-only keys, and clears banners on recovery", () => {
    const view = webview();
    const error = "<script>unsafe()</script>";
    view.receive({ ...message, error, layers: [{ ...message.layers[0], readOnlyReason: "Parse error inside layer" }] });
    expect(view.elements.error.hidden).toBe(false);
    expect(view.elements.error.textContent).toBe(error);
    expect(view.elements.error.children).toHaveLength(0);
    expect(view.elements.readonly.hidden).toBe(false);
    expect(view.elements.readonly.textContent).toBe("Parse error inside layer");
    expect(view.keys.every((key) => key.disabled && !key.draggable)).toBe(true);
    view.keys[0].click();
    expect(view.sent).toEqual([{ type: "ready" }]);
    view.receive(message);
    expect(view.elements.error.hidden).toBe(true);
    expect(view.elements.readonly.hidden).toBe(true);
    expect(view.keys.every((key) => !key.disabled && key.draggable)).toBe(true);
  });

  it.each([null, { keys: message.geometry!.keys.slice(0, 1) }])("uses an argument-order grid for absent or mismatched geometry", (geometry) => {
    const view = webview();
    view.receive({ ...message, geometry });
    expect(view.keys).toHaveLength(2);
    expect(view.sheet.cssRules).toContain(".key-position-1 { left: 56px; top: 2px; width: 50px; height: 50px; }");
  });

  it("renders an empty error model and ignores unrelated host messages", () => {
    const view = webview();
    view.receive({ ...message, layers: [], geometry: null, error: "No keymaps[] initializer found" });
    expect(view.elements.keyboard.textContent).toBe("No keymap layers found.");
    expect(view.elements.tabs.children).toHaveLength(0);
    expect(view.elements.title.textContent).toBe("test/board / smoke");
    expect(view.elements.readonly.hidden).toBe(true);
    expect(view.elements.error.hidden).toBe(false);
    view.receive({ type: "unrelated" });
    expect(view.elements.keyboard.textContent).toBe("No keymap layers found.");
  });

  it("renders encoder section when layer has encoder data", () => {
    const view = webview();
    const withEncoders = {
      ...message,
      layers: message.layers.map((l, i) => i === 0
        ? { ...l, encoders: [{ cw: "KC_VOLU", ccw: "KC_VOLD", cwLabel: "Vol+", ccwLabel: "Vol-" }] }
        : l),
    };
    view.receive(withEncoders);
    expect(view.elements.encoders.hidden).toBe(false);
    expect(view.elements.encoders.children).toHaveLength(1);
    expect(view.elements.encoders.children[0].textContent).toContain("Vol-");
    expect(view.elements.encoders.children[0].textContent).toContain("Vol+");
    // Switch to _FN (no encoders) -> section hidden
    view.elements.tabs.children[1].click();
    expect(view.elements.encoders.hidden).toBe(true);
  });
});
