# QMK Keymap Lens

VS Code extension (in progress) for visual editing of QMK `keymap.c` files. Edits splice single
`LAYOUT(...)` arguments in place via tree-sitter; the rest of the file is never regenerated.

## Status

- M0 done: QMK MSYS runner, `QMK Lens: Doctor` command.
- M1 done: pure `KeymapModel` parser (`src/model/keymap.ts`).
- M2 done: geometry loader + keycode catalog (`src/model/geometry.ts`, `src/qmk/geometryLoader.ts`, `src/model/keycodes.ts`).
- No UI yet.

### Moonlander keymap-level keyboard.json

`zsa/moonlander/keymaps/moo/keyboard.json` exists but does **not** change geometry.
`qmk info -km moo` and `-km default` produce identical layouts (`LAYOUT`: 72 keys,
`LAYOUT_halfmoon`: 36 keys) and the same alias (`LAYOUT_moonlander` → `LAYOUT`).
The keymap-level file likely only configures features/settings, not physical layout.
`qmk info -km <km>` still merges it, so always passing `-km` is correct.

### Lily58 revision resolution

`qmk info -kb lily58 -km moo` resolves automatically to `lily58/rev1`. No explicit
revision is needed in the `-kb` argument.

## Settings

- `qmkLens.msysRoot` (default `C:/QMK_MSYS`): QMK MSYS install root. Commands run via `<root>/usr/bin/bash.exe -lc`.
- `qmkLens.qmkHome` (default empty): qmk_firmware path; empty = `qmk config user.qmk_home`.

## Parser notes

- `web-tree-sitter` 0.25.10 + `tree-sitter-c` 0.24.1. The `tree-sitter-c` npm package ships
  `tree-sitter-c.wasm` (ABI 15), loaded by web-tree-sitter 0.25. Native bindings are not used;
  install with `--ignore-scripts` is fine.
- `npm run build` copies `tree-sitter.wasm` and `tree-sitter-c.wasm` into `dist/`.
  `initParser(wasmDir, cWasmDir?)` takes the directory explicitly (tests use `node_modules`).
- Key `start`/`end` are UTF-16 string offsets (web-tree-sitter indexes JS strings in UTF-16);
  `startByte`/`endByte` are UTF-8 byte offsets.
- Layers with a preprocessor directive or parse error are flagged `readOnlyReason`. A directive
  between layers flags all layers.

## Dev

```
npm install
npm run typecheck
npm test        # live QMK test skips if C:/QMK_MSYS is absent
npm run build   # dist/extension.js + wasm
```
