import { describe, expect, it } from "vitest";
import { normalizeOutputPath, parseDiagnostics, parseFirmwarePath } from "../src/qmk/output";

const home = "C:/Users/Tench/qmk_firmware";

describe("QMK compile output", () => {
  it("parses the copied firmware path from real QMK output", () => {
    const output = [
      "Creating binary load file for flashing: .build/zsa_moonlander_moo.bin                               \u001b[32;01m[OK]\u001b[0m",
      "Copying zsa_moonlander_moo.bin to qmk_firmware folder                                               \u001b[32;01m[OK]\u001b[0m",
    ].join("\n");
    expect(parseFirmwarePath(output, home)).toBe("C:\\Users\\Tench\\qmk_firmware\\zsa_moonlander_moo.bin");
  });

  it("returns undefined when a failed build copied no firmware", () => {
    expect(parseFirmwarePath("make: *** Error 1", home)).toBeUndefined();
  });
});

describe("QMK diagnostics", () => {
  it("parses ANSI-colored errors and normalizes relative paths", () => {
    const output = "\u001b[01mkeyboards/lily58/lib/layer_state_reader.c:31:72:\u001b[0m \u001b[01;31merror: \u001b[0mformat mismatch";
    expect(parseDiagnostics(output, home)).toEqual([{
      path: "C:\\Users\\Tench\\qmk_firmware\\keyboards\\lily58\\lib\\layer_state_reader.c",
      line: 31,
      column: 72,
      severity: "error",
      message: "format mismatch",
    }]);
  });

  it("normalizes MSYS and Windows absolute paths", () => {
    expect(normalizeOutputPath("/c/Users/Tench/qmk_firmware/keymap.c", home)).toBe("C:\\Users\\Tench\\qmk_firmware\\keymap.c");
    expect(normalizeOutputPath("D:/qmk/keymap.c", home)).toBe("D:\\qmk\\keymap.c");
  });
});
