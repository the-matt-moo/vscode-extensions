import type { KeymapModel } from "../model/keymap";

export interface Replacement {
  start: number;
  end: number;
  text: string;
}

export function validateRawExpression(value: string): string | undefined {
  const text = value.trim();
  if (!text) return "Enter a keycode expression";

  let depth = 0;
  for (const char of text) {
    if (char === "(") depth++;
    else if (char === ")") {
      if (--depth < 0) return "Parentheses are not balanced";
    } else if (char === "," && depth === 0) {
      return "A key must be one expression (no top-level comma)";
    }
  }
  return depth === 0 ? undefined : "Parentheses are not balanced";
}

export function computeSwapEdits(model: KeymapModel, layerIndex: number, a: number, b: number): Replacement[] {
  const layer = model.layers[layerIndex];
  if (!layer) throw new RangeError("Layer no longer exists");
  if (layer.readOnlyReason) throw new Error(layer.readOnlyReason);
  const first = layer.keys[a];
  const second = layer.keys[b];
  if (!first || !second) throw new RangeError("Key no longer exists");
  if (a === b) return [];
  return [
    { start: first.start, end: first.end, text: second.text },
    { start: second.start, end: second.end, text: first.text },
  ];
}
