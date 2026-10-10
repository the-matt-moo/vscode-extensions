import { describe, expect, it } from "vitest";
import { existsSync } from "node:fs";
import { buildQmkCommand, run, shQuote, stripBanner, toPosixPath } from "../src/qmk/runner";

describe("quoting", () => {
  it("leaves safe args bare", () => {
    expect(buildQmkCommand(["compile", "-kb", "zsa/moonlander", "-km", "new_moo"])).toBe("qmk compile -kb zsa/moonlander -km new_moo");
  });
  it("single-quotes unsafe args and escapes quotes", () => {
    expect(shQuote("")).toBe("''");
    expect(shQuote("a b")).toBe("'a b'");
    expect(shQuote("it's")).toBe(String.raw`'it'\''s'`);
    expect(shQuote("$(rm -rf /);`x`")).toBe("'$(rm -rf /);`x`'");
    expect(shQuote(String.raw`C:\Users\"x"`)).toBe(String.raw`'C:\Users\"x"'`);
  });
});

describe("helpers", () => {
  it("converts Windows paths to MSYS paths", () => {
    expect(toPosixPath(String.raw`C:\Users\Tench`)).toBe("/c/Users/Tench");
    expect(toPosixPath("D:/x")).toBe("/d/x");
  });
  it("strips the QMK MSYS banner", () => {
    const s = "Welcome to QMK MSYS!\r\n  * Docs: x\r\n  * Help: y\r\n1.1.7\r\n";
    expect(stripBanner(s)).toBe("1.1.7\r\n");
  });
});

describe.skipIf(!existsSync("C:/QMK_MSYS/usr/bin/bash.exe"))("live QMK MSYS", () => {
  it("runs qmk --version", async () => {
    const r = await run(["--version"], { msysRoot: "C:/QMK_MSYS" });
    expect(r.code).toBe(0);
    expect(r.stdout.trim()).toMatch(/^1\.\d+\.\d+$/);
  }, 30_000);
});
