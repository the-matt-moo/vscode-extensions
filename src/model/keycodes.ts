// Pure keycode catalog. Must not import vscode.
import * as Hjson from "hjson";
import { readFileSync, readdirSync } from "node:fs";
import * as path from "node:path";

export interface KeycodeEntry {
  key: string;
  aliases: string[];
  label?: string;
  group?: string;
}

export interface FunctionEntry {
  key: string;
  template: string;
  group: string;
}

export interface KeycodeCatalog {
  /** Keyed by primary key name (e.g. KC_A). */
  entries: Map<string, KeycodeEntry>;
  /** All aliases and primary keys -> primary key for fast lookup. */
  byName: Map<string, string>;
  functions: FunctionEntry[];
}

// -- Parsing hjson files --

interface RawKeycode {
  group?: string;
  key: string;
  label?: string;
  aliases?: string[];
}

/** Compare semantic versions: "0.0.2" > "0.0.1". */
function cmpVersion(a: string, b: string): number {
  const pa = a.split(".").map(Number);
  const pb = b.split(".").map(Number);
  for (let i = 0; i < Math.max(pa.length, pb.length); i++) {
    const diff = (pa[i] ?? 0) - (pb[i] ?? 0);
    if (diff !== 0) return diff;
  }
  return 0;
}

function parseVersion(filename: string): string | undefined {
  const m = /^keycodes_(\d+\.\d+\.\d+)/.exec(filename);
  return m?.[1];
}

/**
 * Sort hjson files by version then filename so later versions override earlier ones.
 * Files without a version prefix are skipped (e.g. the `extras/` dir).
 */
function sortedKeycodeFiles(dir: string): string[] {
  const files = readdirSync(dir).filter((f) => f.endsWith(".hjson") && parseVersion(f));
  return files.sort((a, b) => {
    const va = parseVersion(a)!;
    const vb = parseVersion(b)!;
    const vc = cmpVersion(va, vb);
    return vc !== 0 ? vc : a.localeCompare(b);
  });
}

function mergeKeycodes(
  target: Map<string, KeycodeEntry>,
  raw: Record<string, RawKeycode>,
): void {
  for (const [_hex, entry] of Object.entries(raw)) {
    if (!entry || typeof entry !== "object" || !entry.key) continue;

    const existing = target.get(entry.key);
    let aliases = entry.aliases ?? [];

    // Handle !reset!: clear existing aliases, use only what follows
    const resetIdx = aliases.indexOf("!reset!");
    if (resetIdx !== -1) {
      aliases = aliases.filter((a) => a !== "!reset!");
    } else if (existing) {
      // Merge with existing aliases
      const merged = new Set(existing.aliases);
      for (const a of aliases) merged.add(a);
      aliases = [...merged];
    }

    target.set(entry.key, {
      key: entry.key,
      aliases,
      ...(entry.label ? { label: entry.label } : {}),
      ...(entry.group ? { group: entry.group } : {}),
    });
  }
}

/**
 * Load keycode catalog from qmk_firmware's `data/constants/keycodes/` directory.
 * Reads all `keycodes_<ver>*.hjson` files in version order; later versions override.
 */
export function loadKeycodeCatalog(qmkHome: string): KeycodeCatalog {
  const dir = path.join(qmkHome, "data", "constants", "keycodes");
  const entries = new Map<string, KeycodeEntry>();

  for (const file of sortedKeycodeFiles(dir)) {
    const text = readFileSync(path.join(dir, file), "utf8");
    const parsed = Hjson.parse(text) as { keycodes?: Record<string, RawKeycode> };
    if (parsed.keycodes) mergeKeycodes(entries, parsed.keycodes);
  }

  return finalize(entries);
}

/**
 * Load from a specific directory of hjson files (for tests).
 */
export function loadKeycodeCatalogFromDir(dir: string): KeycodeCatalog {
  const entries = new Map<string, KeycodeEntry>();
  for (const file of sortedKeycodeFiles(dir)) {
    const text = readFileSync(path.join(dir, file), "utf8");
    const parsed = Hjson.parse(text) as { keycodes?: Record<string, RawKeycode> };
    if (parsed.keycodes) mergeKeycodes(entries, parsed.keycodes);
  }
  return finalize(entries);
}

function finalize(entries: Map<string, KeycodeEntry>): KeycodeCatalog {
  // Ensure _______ and XXXXXXX aliases exist
  const trns = entries.get("KC_TRANSPARENT");
  if (trns && !trns.aliases.includes("_______")) trns.aliases.push("_______");
  const no = entries.get("KC_NO");
  if (no && !no.aliases.includes("XXXXXXX")) no.aliases.push("XXXXXXX");

  const byName = new Map<string, string>();
  for (const [key, entry] of entries) {
    byName.set(key, key);
    for (const a of entry.aliases) byName.set(a, key);
  }

  return { entries, byName, functions: FUNCTION_ENTRIES };
}

// -- Function entries (parameterized keycodes) --

const FUNCTION_ENTRIES: FunctionEntry[] = [
  // Layer
  { key: "MO", template: "MO(%layer%)", group: "function" },
  { key: "TG", template: "TG(%layer%)", group: "function" },
  { key: "TO", template: "TO(%layer%)", group: "function" },
  { key: "TT", template: "TT(%layer%)", group: "function" },
  { key: "OSL", template: "OSL(%layer%)", group: "function" },
  { key: "LT", template: "LT(%layer%, %kc%)", group: "function" },
  // Mod
  { key: "OSM", template: "OSM(%mod%)", group: "function" },
  { key: "MT", template: "MT(%mod%, %kc%)", group: "function" },
  // Tap dance
  { key: "TD", template: "TD(%n%)", group: "function" },
  // One-shot mod wrappers
  { key: "LCTL", template: "LCTL(%kc%)", group: "function" },
  { key: "LSFT", template: "LSFT(%kc%)", group: "function" },
  { key: "LALT", template: "LALT(%kc%)", group: "function" },
  { key: "LGUI", template: "LGUI(%kc%)", group: "function" },
  { key: "RCTL", template: "RCTL(%kc%)", group: "function" },
  { key: "RSFT", template: "RSFT(%kc%)", group: "function" },
  { key: "RALT", template: "RALT(%kc%)", group: "function" },
  { key: "RGUI", template: "RGUI(%kc%)", group: "function" },
  // Mod-tap
  { key: "LCTL_T", template: "LCTL_T(%kc%)", group: "function" },
  { key: "LSFT_T", template: "LSFT_T(%kc%)", group: "function" },
  { key: "LALT_T", template: "LALT_T(%kc%)", group: "function" },
  { key: "LGUI_T", template: "LGUI_T(%kc%)", group: "function" },
  { key: "RCTL_T", template: "RCTL_T(%kc%)", group: "function" },
  { key: "RSFT_T", template: "RSFT_T(%kc%)", group: "function" },
  { key: "RALT_T", template: "RALT_T(%kc%)", group: "function" },
  { key: "RGUI_T", template: "RGUI_T(%kc%)", group: "function" },
];

// -- buildCatalog: merge file-local entries --

export interface BuildOptions {
  customKeycodes?: string[];
  tapDanceNames?: string[];
}

/**
 * Add file-local custom keycodes and tap-dance entries to a catalog.
 * Returns a new catalog; the original is not mutated.
 */
export function buildCatalog(base: KeycodeCatalog, opts: BuildOptions): KeycodeCatalog {
  const entries = new Map(base.entries);
  const byName = new Map(base.byName);

  if (opts.customKeycodes) {
    for (const key of opts.customKeycodes) {
      if (!entries.has(key)) {
        entries.set(key, { key, aliases: [], group: "custom" });
        byName.set(key, key);
      }
    }
  }

  if (opts.tapDanceNames) {
    for (const name of opts.tapDanceNames) {
      const tdKey = `TD(${name})`;
      if (!entries.has(tdKey)) {
        entries.set(tdKey, { key: tdKey, aliases: [], label: name, group: "tap_dance" });
        byName.set(tdKey, tdKey);
      }
    }
  }

  return { entries, byName, functions: base.functions };
}

// -- labelFor: short display label --

/**
 * Return a short display label for a keycode text.
 * Uses catalog label if available, or shortest alias, else raw text.
 */
export function labelFor(text: string, catalog: KeycodeCatalog): string {
  const primary = catalog.byName.get(text);
  if (primary) {
    const entry = catalog.entries.get(primary)!;
    if (entry.label) return entry.label;
    // Return shortest alias or key name
    const candidates = [entry.key, ...entry.aliases];
    return candidates.reduce((a, b) => (a.length <= b.length ? a : b));
  }
  return text;
}
