# QMK Keymap Lens

VS Code extension (in progress) for visual editing of QMK `keymap.c` files. Edits splice single
`LAYOUT(...)` arguments in place via tree-sitter; the rest of the file is never regenerated.

## Status

- M0 done: QMK MSYS runner, `QMK Lens: Doctor` command.
- M1 done: pure `KeymapModel` parser (`src/model/keymap.ts`).
- No UI yet.

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
