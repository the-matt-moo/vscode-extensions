import type { HostMessage, ViewEncoder, ViewLayer, WebviewMessage } from "../shared/protocol";
import type { KeyGeom } from "../model/geometry";

declare function acquireVsCodeApi<T = unknown>(): {
  postMessage(message: WebviewMessage): void;
  getState(): T | undefined;
  setState(state: T): void;
};

interface SavedState {
  selectedLayer?: string;
}

const vscode = acquireVsCodeApi<SavedState>();
const title = element("title");
const tabs = element("tabs");
const keyboard = element("keyboard");
const errorBanner = element("error");
const readOnlyBanner = element("readonly");
const encoderSection = element("encoders");
const positionSheet = getPositionSheet();
let model: HostMessage | undefined;
let selectedLayer = vscode.getState()?.selectedLayer;
let dragged: { layer: number; key: number } | undefined;

element("compile").addEventListener("click", () => vscode.postMessage({ type: "compile" }));
element("flash").addEventListener("click", () => vscode.postMessage({ type: "flash" }));

window.addEventListener("message", (event: MessageEvent<HostMessage>) => {
  if (event.data.type !== "model") return;
  model = event.data;
  if (!model.layers.some((layer) => layer.designator === selectedLayer)) selectedLayer = model.layers[0]?.designator;
  saveState();
  render();
});

vscode.postMessage({ type: "ready" });

function render(): void {
  if (!model) return;
  dragged = undefined;
  const layerIndex = Math.max(0, model.layers.findIndex((layer) => layer.designator === selectedLayer));
  const layer = model.layers[layerIndex];

  title.textContent = layer
    ? `${model.keyboard} / ${model.keymap} — ${layer.layoutMacro}`
    : `${model.keyboard} / ${model.keymap}`;
  showBanner(errorBanner, model.error);
  showBanner(readOnlyBanner, layer?.readOnlyReason);

  tabs.replaceChildren(...model.layers.map((item) => layerTab(item, item === layer)));
  keyboard.replaceChildren();
  if (!layer) {
    const empty = document.createElement("p");
    empty.textContent = "No keymap layers found.";
    keyboard.append(empty);
    return;
  }

  const geometry = model.geometry?.keys.length === layer.keys.length
    ? model.geometry.keys
    : gridGeometry(layer.keys.length);
  while (positionSheet.cssRules.length) positionSheet.deleteRule(0);
  const canvas = document.createElement("div");
  canvas.className = "key-canvas canvas-size";
  const maxX = Math.max(0, ...geometry.map((key) => key.x + key.w));
  const maxY = Math.max(0, ...geometry.map((key) => key.y + key.h));
  positionSheet.insertRule(`.canvas-size { width: ${maxX * 54}px; height: ${maxY * 54}px; }`);
  canvas.append(...layer.keys.map((key, keyIndex) => keyButton(layer, layerIndex, keyIndex, geometry[keyIndex])));
  keyboard.append(canvas);
  renderEncoders(layer);
}

function layerTab(layer: ViewLayer, selected: boolean): HTMLButtonElement {
  const button = document.createElement("button");
  button.className = "tab";
  button.type = "button";
  button.textContent = layer.designator;
  button.title = layer.layoutMacro;
  button.setAttribute("role", "tab");
  button.setAttribute("aria-selected", String(selected));
  button.addEventListener("click", () => {
    selectedLayer = layer.designator;
    saveState();
    render();
  });
  return button;
}

function keyButton(
  layer: ViewLayer,
  layerIndex: number,
  keyIndex: number,
  geometry: KeyGeom,
): HTMLButtonElement {
  const key = layer.keys[keyIndex];
  const button = document.createElement("button");
  button.className = `key key-position-${keyIndex}`;
  button.type = "button";
  button.textContent = key.label;
  button.title = key.text;
  button.disabled = Boolean(layer.readOnlyReason);
  button.draggable = !button.disabled;
  button.setAttribute("aria-label", `Layer ${layerIndex} key ${keyIndex}: ${key.text}`);
  positionSheet.insertRule(`.key-position-${keyIndex} { left: ${geometry.x * 54 + 2}px; top: ${geometry.y * 54 + 2}px; width: ${geometry.w * 54 - 4}px; height: ${geometry.h * 54 - 4}px; }`);
  button.addEventListener("click", () => vscode.postMessage({ type: "editKey", layer: layerIndex, key: keyIndex }));
  button.addEventListener("dragstart", (event) => {
    dragged = { layer: layerIndex, key: keyIndex };
    event.dataTransfer?.setData("text/plain", String(keyIndex));
  });
  button.addEventListener("dragover", (event) => {
    if (dragged?.layer === layerIndex) event.preventDefault();
  });
  button.addEventListener("drop", (event) => {
    event.preventDefault();
    if (dragged?.layer === layerIndex && dragged.key !== keyIndex) {
      vscode.postMessage({ type: "swapKeys", layer: layerIndex, a: dragged.key, b: keyIndex });
    }
    dragged = undefined;
  });
  button.addEventListener("dragend", () => { dragged = undefined; });
  return button;
}

function renderEncoders(layer: ViewLayer | undefined): void {
  const list = layer?.encoders;
  if (!list?.length) { encoderSection.hidden = true; return; }
  encoderSection.hidden = false;
  encoderSection.replaceChildren(...list.map((enc, i) => encoderRow(enc, i, list.length > 1)));
}

function encoderRow(enc: ViewEncoder, index: number, showIndex: boolean): HTMLElement {
  const row = document.createElement("div");
  row.className = "encoder";
  const label = document.createElement("span");
  label.className = "encoder-name";
  label.textContent = showIndex ? `Encoder ${index}` : "Encoder";
  const ccw = document.createElement("span");
  ccw.className = "encoder-dir";
  ccw.textContent = `\u21BA ${enc.ccwLabel}`;
  ccw.title = enc.ccw;
  const cw = document.createElement("span");
  cw.className = "encoder-dir";
  cw.textContent = `\u21BB ${enc.cwLabel}`;
  cw.title = enc.cw;
  row.append(label, ccw, cw);
  return row;
}

function gridGeometry(count: number): KeyGeom[] {
  return Array.from({ length: count }, (_, index) => ({
    x: index % 14,
    y: Math.floor(index / 14),
    w: 1,
    h: 1,
  }));
}

function showBanner(target: HTMLElement, text: string | undefined): void {
  target.hidden = !text;
  target.textContent = text ?? "";
}

function saveState(): void {
  vscode.setState({ selectedLayer });
}

function element(id: string): HTMLElement {
  const found = document.getElementById(id);
  if (!found) throw new Error(`Missing #${id}`);
  return found;
}

function getPositionSheet(): CSSStyleSheet {
  const sheet = (element("positions") as HTMLStyleElement).sheet;
  if (!sheet) throw new Error("Missing position stylesheet");
  return sheet;
}
