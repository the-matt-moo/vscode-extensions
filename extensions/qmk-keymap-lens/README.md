# QMK Keymap Lens

VS Code extension for visual editing and building of QMK `keymap.c` files. Edits splice single `LAYOUT(...)` arguments in place via tree-sitter; the rest of the file is never regenerated.

## Setup

1. Install [QMK MSYS](https://msys.qmk.fm/) and complete `qmk setup`.
2. Install this extension's `.vsix` from **Extensions: Install from VSIX...**.
3. Open a `keyboards/<keyboard>/keymaps/<keymap>/keymap.c` file from the configured `qmk_firmware` checkout.
4. Run **QMK Lens: Doctor** and resolve any missing tools needed by the target board.

| Setting | Default | Purpose |
|---|---|---|
| `qmkLens.msysRoot` | `C:/QMK_MSYS` | QMK MSYS install root; commands use `usr/bin/bash.exe -lc`. |
| `qmkLens.qmkHome` | empty | `qmk_firmware` path. Empty reads `qmk config user.qmk_home`. |
| `qmkLens.toolboxPath` | `C:/Program Files/QMK Toolbox/qmk_toolbox.exe` | QMK Toolbox executable. |

## Usage

1. Run **QMK Lens: Open Visual Editor** or use the editor-title action. **Reopen Editor With...** also lists **QMK Lens Visual Editor**.
2. Select a layer and click a key to choose a catalog entry, function template, file-local keycode, tap dance, or validated raw expression.
3. Drag one key onto another in the same layer to swap both in one undo step. Model updates or layer switches cancel an in-progress drag. If the document changes while a key picker is open, the selection is discarded with a warning; select the key again.
4. Select **Compile** in the visual editor or run **QMK Lens: Compile Keymap**. The document is saved, output streams to **QMK Lens**, compiler errors appear as `qmk` diagnostics, and the produced firmware path is remembered.
5. Select **Flash** or run **QMK Lens: Flash Keymap**. An interactive QMK MSYS terminal opens so the board can enter its bootloader. QMK Lens never flashes without this command.
6. Run **QMK Lens: Open in QMK Toolbox** to open the last successfully built `.hex`, `.bin`, or `.uf2` file.

## Features

- QMK geometry from `qmk info`, with layer tabs and an argument-order grid fallback.
- Live 150 ms updates when the text editor changes.
- Unsafe or key-count-mismatched layers remain visible but read-only.
- Compile output, firmware detection, diagnostics, interactive flashing, and QMK Toolbox handoff.
- **QMK Lens: Doctor** checks QMK MSYS, `qmk_home`, toolchains, `dfu-util`, `dfu-programmer`, and QMK Toolbox.

## Limits and out of scope

QMK Lens does not add, remove, or reorder layers; edit macro, tap-dance, combo, or encoder bodies; edit RGB/ledmap data; re-align C columns; provide Vial/VIA; compare keymaps; or publish firmware. Layers containing parser errors or preprocessor directives are read-only. If geometry cannot be loaded or a layout macro is unknown, keys use an argument-order grid; verify physical positions before editing or swapping.

Flash still depends on the correct bootloader driver and hardware timing. QMK Toolbox is the fallback for boards that need a GUI workflow.

## Troubleshooting

- Run **QMK Lens: Doctor** first. `dfu-programmer` is required for `atmel-dfu` boards such as Lily58; other boards may need `dfu-util` or an ARM toolchain.
- QMK MSYS needs `MSYSTEM=MINGW64`, `HOME=/c/Users/<name>`, and `USERPROFILE=C:\Users\<name>`. QMK Lens supplies these automatically. If commands work in QMK MSYS but not here, verify `qmkLens.msysRoot` and `qmkLens.qmkHome`.
- A stale or invalid `qmk config user.keymap` can break QMK commands that omit the keymap. QMK Lens always passes `-km <keymap>` explicitly, so it does not use that default.
- If **Open in QMK Toolbox** says no build exists, compile that keymap first. If Toolbox is missing, update `qmkLens.toolboxPath`.
- Build failures from keymap or keyboard source are reported but never rewritten by QMK Lens.

### Moonlander keymap-level keyboard.json

`zsa/moonlander/keymaps/moo/keyboard.json` does not change geometry. `qmk info -km moo` and `-km default` produce identical layouts (`LAYOUT`: 72 keys, `LAYOUT_halfmoon`: 36 keys) and the same alias (`LAYOUT_moonlander` to `LAYOUT`). `qmk info -km <km>` still merges keymap configuration, so always passing `-km` is correct.

### Lily58 revision resolution

`qmk info -kb lily58 -km moo` resolves automatically to `lily58/rev1`. No explicit revision is needed in the `-kb` argument.

## Development

```text
npm install
npm run typecheck
npm test
npm run build
npm run package
```

`npm test` includes dependency-free DOM smoke tests for webview rendering/messages and mocked-host regression tests for stale picker edits. These do not verify browser layout, CSP enforcement, or live VS Code integration.

`npm run build` bundles extension/runtime dependencies into `dist/extension.js` and `dist/webview.js`, then copies `tree-sitter.wasm` and `tree-sitter-c.wasm` into `dist/`. Run real compile checks only with `QMK_LIVE=1 npm run compile-check`; they write QMK build output under the configured checkout's `.build/` directory.
