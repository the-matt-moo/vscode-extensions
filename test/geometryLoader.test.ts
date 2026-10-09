import { describe, expect, it } from "vitest";
import { buildCacheKey, type CacheKey } from "../src/qmk/geometryLoader";
import { existsSync, mkdirSync, writeFileSync, utimesSync, rmSync } from "node:fs";
import * as path from "node:path";
import * as os from "node:os";

const TMP = path.join(os.tmpdir(), "qmk-lens-cache-test");

function setupFakeQmkHome(): string {
  const qmkHome = path.join(TMP, "qmk_firmware");
  rmSync(TMP, { recursive: true, force: true });

  // keyboards/test_kb/info.json
  const kbDir = path.join(qmkHome, "keyboards", "test_kb");
  mkdirSync(kbDir, { recursive: true });
  writeFileSync(path.join(kbDir, "info.json"), "{}");
  writeFileSync(path.join(kbDir, "rules.mk"), "");

  // keyboards/test_kb/keymaps/moo/keymap.json
  const kmDir = path.join(kbDir, "keymaps", "moo");
  mkdirSync(kmDir, { recursive: true });
  writeFileSync(path.join(kmDir, "keymap.json"), "{}");

  // keyboards/ level rules.mk
  const kbRoot = path.join(qmkHome, "keyboards");
  writeFileSync(path.join(kbRoot, "rules.mk"), "");

  return qmkHome;
}

describe("buildCacheKey", () => {
  it("includes kb, km, gitHead and file mtimes", () => {
    const qmkHome = setupFakeQmkHome();
    const key = buildCacheKey(qmkHome, "test_kb", "moo", "abc123");

    expect(key.kb).toBe("test_kb");
    expect(key.km).toBe("moo");
    expect(key.gitHead).toBe("abc123");
    expect(Object.keys(key.mtimes).length).toBeGreaterThan(0);

    // Should include keyboard-level and keymap-level files
    const paths = Object.keys(key.mtimes);
    expect(paths.some((p) => p.includes("test_kb/info.json"))).toBe(true);
    expect(paths.some((p) => p.includes("keymaps/moo/keymap.json"))).toBe(true);
  });

  it("changes when file mtime changes", () => {
    const qmkHome = setupFakeQmkHome();
    const key1 = buildCacheKey(qmkHome, "test_kb", "moo", "abc123");

    // Touch info.json
    const infoPath = path.join(qmkHome, "keyboards", "test_kb", "info.json");
    const future = new Date(Date.now() + 5000);
    utimesSync(infoPath, future, future);

    const key2 = buildCacheKey(qmkHome, "test_kb", "moo", "abc123");
    expect(JSON.stringify(key1)).not.toBe(JSON.stringify(key2));
  });

  it("changes when gitHead changes", () => {
    const qmkHome = setupFakeQmkHome();
    const key1 = buildCacheKey(qmkHome, "test_kb", "moo", "abc123");
    const key2 = buildCacheKey(qmkHome, "test_kb", "moo", "def456");
    expect(JSON.stringify(key1)).not.toBe(JSON.stringify(key2));
  });

  it("handles nested keyboard paths (vendor/kb)", () => {
    const qmkHome = path.join(TMP, "qmk_firmware2");
    rmSync(qmkHome, { recursive: true, force: true });
    const kbDir = path.join(qmkHome, "keyboards", "zsa", "moonlander");
    mkdirSync(kbDir, { recursive: true });
    writeFileSync(path.join(kbDir, "keyboard.json"), "{}");
    // Also create the zsa/ level
    writeFileSync(path.join(qmkHome, "keyboards", "zsa", "rules.mk"), "");
    // keyboards/ root
    mkdirSync(path.join(qmkHome, "keyboards"), { recursive: true });
    const kmDir = path.join(kbDir, "keymaps", "moo");
    mkdirSync(kmDir, { recursive: true });
    writeFileSync(path.join(kmDir, "keyboard.json"), "{}");

    const key = buildCacheKey(qmkHome, "zsa/moonlander", "moo", "head");
    const paths = Object.keys(key.mtimes);
    expect(paths.some((p) => p.includes("moonlander/keyboard.json"))).toBe(true);
    expect(paths.some((p) => p.includes("keymaps/moo/keyboard.json"))).toBe(true);
    expect(paths.some((p) => p.includes("zsa/rules.mk"))).toBe(true);
  });
});

// Live loadGeometry integration test needs runner + QMK MSYS;
// covered by fixture cross-check in geometry.test.ts.
