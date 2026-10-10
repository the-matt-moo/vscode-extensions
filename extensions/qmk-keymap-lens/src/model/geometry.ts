// Pure geometry types and parser. Must not import vscode.

export interface KeyGeom {
  x: number;
  y: number;
  w: number;
  h: number;
  matrix?: [number, number];
  label?: string;
}

export interface Geometry {
  keyboard: string;
  layouts: Record<string, KeyGeom[]>;
  aliases: Record<string, string>;
}

/** Parse `qmk info -f json` stdout into a Geometry. */
export function parseQmkInfo(json: unknown): Geometry {
  const obj = json as Record<string, unknown>;
  const keyboard = String(obj["keyboard_name"] ?? "");
  const rawLayouts = (obj["layouts"] ?? {}) as Record<string, { layout: RawKey[] }>;
  const layouts: Record<string, KeyGeom[]> = {};
  for (const [name, val] of Object.entries(rawLayouts)) {
    layouts[name] = (val.layout ?? []).map(toKeyGeom);
  }
  const aliases = (obj["layout_aliases"] ?? {}) as Record<string, string>;
  return { keyboard, layouts, aliases };
}

interface RawKey {
  x: number;
  y: number;
  w?: number;
  h?: number;
  matrix?: [number, number];
  label?: string;
}

function toKeyGeom(k: RawKey): KeyGeom {
  return {
    x: k.x,
    y: k.y,
    w: k.w ?? 1,
    h: k.h ?? 1,
    ...(k.matrix ? { matrix: k.matrix } : {}),
    ...(k.label ? { label: k.label } : {}),
  };
}

/**
 * Resolve a LAYOUT macro name to an actual layout in the geometry.
 * Tries exact match first, then follows aliases (one hop).
 */
export function resolveLayout(
  geom: Geometry,
  macroName: string,
): { name: string; keys: KeyGeom[] } | undefined {
  if (geom.layouts[macroName]) return { name: macroName, keys: geom.layouts[macroName] };
  const target = geom.aliases[macroName];
  if (target && geom.layouts[target]) return { name: target, keys: geom.layouts[target] };
  // Reverse alias: macroName is an alias target, find any alias pointing to it
  for (const [alias, t] of Object.entries(geom.aliases)) {
    if (alias === macroName || t === macroName) {
      const resolved = geom.layouts[t] ?? geom.layouts[alias];
      if (resolved) return { name: t, keys: resolved };
    }
  }
  return undefined;
}

/** Bounding box of a set of keys: [maxX+w, maxY+h]. */
export function bounds(keys: KeyGeom[]): { width: number; height: number } {
  let width = 0;
  let height = 0;
  for (const k of keys) {
    const r = k.x + k.w;
    const b = k.y + k.h;
    if (r > width) width = r;
    if (b > height) height = b;
  }
  return { width, height };
}
