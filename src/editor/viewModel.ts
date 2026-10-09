import { resolveLayout, type Geometry, type KeyGeom } from "../model/geometry";
import { labelFor, type KeycodeCatalog } from "../model/keycodes";
import type { KeymapModel } from "../model/keymap";
import type { ViewLayer } from "../shared/protocol";

export interface EditorViewModel {
  layers: ViewLayer[];
  geometry: { keys: KeyGeom[] } | null;
  error?: string;
}

export function buildViewModel(
  model: KeymapModel,
  geometry: Geometry | null,
  catalog: KeycodeCatalog,
): EditorViewModel {
  const resolved = geometry ? model.layers.map((layer) => resolveLayout(geometry, layer.layoutMacro)) : [];
  let keys = resolved[0]?.keys;
  let error = model.error;

  if (geometry && model.layers.length && !keys) {
    error ??= `Layout ${model.layers[0].layoutMacro} was not found; showing argument-order grid`;
  }

  if (keys && resolved.some((layout) => !layout || !sameGeometry(keys!, layout.keys))) {
    keys = undefined;
    error ??= "Layers use different layouts; showing argument-order grid";
  }

  const layers = model.layers.map((layer, index): ViewLayer => {
    const layout = resolved[index];
    const mismatch = layout && layout.keys.length !== layer.keys.length
      ? `Layout has ${layout.keys.length} keys, keymap layer has ${layer.keys.length}`
      : undefined;
    return {
      designator: layer.designator,
      layoutMacro: layer.layoutMacro,
      ...(layer.readOnlyReason || mismatch ? { readOnlyReason: layer.readOnlyReason ?? mismatch } : {}),
      keys: layer.keys.map((key) => ({ text: key.text, label: labelFor(key.text, catalog) })),
    };
  });

  return {
    layers,
    geometry: keys ? { keys } : null,
    ...(error ? { error } : {}),
  };
}

function sameGeometry(a: KeyGeom[], b: KeyGeom[]): boolean {
  return a.length === b.length && a.every((key, i) => {
    const other = b[i];
    return key.x === other.x && key.y === other.y && key.w === other.w && key.h === other.h;
  });
}
