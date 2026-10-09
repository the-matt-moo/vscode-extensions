// Geometry loader: runs qmk info and caches result. May import runner, not vscode.
import { readFileSync, writeFileSync, mkdirSync, existsSync, statSync } from "node:fs";
import * as path from "node:path";
import { type Geometry, parseQmkInfo } from "../model/geometry";
import { run, runShell, type RunOptions } from "./runner";

export interface LoadOptions {
  msysRoot: string;
  qmkHome: string;
  cacheDir: string;
}

/** Files whose mtimes contribute to the cache fingerprint, walking from keyboards/<kb> up to keyboards/. */
function fingerprintFiles(qmkHome: string, kb: string, km: string): string[] {
  const kbDir = path.join(qmkHome, "keyboards", ...kb.split("/"));
  const files: string[] = [];
  const targets = ["info.json", "keyboard.json", "rules.mk"];

  // Walk from keyboards/<kb> up to keyboards/
  let dir = kbDir;
  const kbRoot = path.join(qmkHome, "keyboards");
  while (true) {
    for (const t of targets) {
      const p = path.join(dir, t);
      if (existsSync(p)) files.push(p);
    }
    if (path.resolve(dir) === path.resolve(kbRoot)) break;
    const parent = path.dirname(dir);
    if (parent === dir) break;
    dir = parent;
  }

  // Keymap-level files
  const kmDir = path.join(kbDir, "keymaps", km);
  for (const f of ["keyboard.json", "keymap.json"]) {
    const p = path.join(kmDir, f);
    if (existsSync(p)) files.push(p);
  }

  return files;
}

function mtimeMs(filePath: string): number {
  try {
    return statSync(filePath).mtimeMs;
  } catch {
    return 0;
  }
}

export interface CacheKey {
  kb: string;
  km: string;
  gitHead: string;
  mtimes: Record<string, number>;
}

export function buildCacheKey(qmkHome: string, kb: string, km: string, gitHead: string): CacheKey {
  const files = fingerprintFiles(qmkHome, kb, km);
  const mtimes: Record<string, number> = {};
  for (const f of files) {
    // Store relative to qmkHome for portability
    mtimes[path.relative(qmkHome, f).replace(/\\/g, "/")] = mtimeMs(f);
  }
  return { kb, km, gitHead, mtimes };
}

function cacheFileName(kb: string, km: string): string {
  return `geom_${kb.replace(/\//g, "_")}_${km}.json`;
}

interface CacheEntry {
  key: CacheKey;
  data: unknown;
}

function readCache(cacheDir: string, kb: string, km: string, currentKey: CacheKey): unknown | undefined {
  const fp = path.join(cacheDir, cacheFileName(kb, km));
  if (!existsSync(fp)) return undefined;
  try {
    const entry: CacheEntry = JSON.parse(readFileSync(fp, "utf8"));
    if (JSON.stringify(entry.key) === JSON.stringify(currentKey)) return entry.data;
  } catch {
    /* corrupt cache */
  }
  return undefined;
}

function writeCache(cacheDir: string, kb: string, km: string, key: CacheKey, data: unknown): void {
  mkdirSync(cacheDir, { recursive: true });
  const entry: CacheEntry = { key, data };
  writeFileSync(path.join(cacheDir, cacheFileName(kb, km)), JSON.stringify(entry));
}

async function getGitHead(opts: RunOptions, qmkHome: string): Promise<string> {
  try {
    const r = await runShell(`git -C '${qmkHome.replace(/\\/g, "/")}' rev-parse HEAD`, opts);
    return r.code === 0 ? r.stdout.trim() : "";
  } catch {
    return "";
  }
}

export async function loadGeometry(
  kb: string,
  km: string,
  opts: LoadOptions,
): Promise<Geometry> {
  const runOpts: RunOptions = { msysRoot: opts.msysRoot };
  const gitHead = await getGitHead(runOpts, opts.qmkHome);
  const key = buildCacheKey(opts.qmkHome, kb, km, gitHead);

  const cached = readCache(opts.cacheDir, kb, km, key);
  if (cached) return parseQmkInfo(cached);

  // Always pass -km to avoid the broken default keymap config
  const result = await run(["info", "-kb", kb, "-km", km, "-f", "json"], runOpts);
  if (result.code !== 0) {
    throw new Error(`qmk info failed (exit ${result.code}): ${result.stderr.slice(0, 500)}`);
  }

  // qmk outputs warnings on stderr; parse stdout only
  const data = JSON.parse(result.stdout);
  writeCache(opts.cacheDir, kb, km, key, data);
  return parseQmkInfo(data);
}
