# Changelog

## 0.1.2 - 2026-10-09

- Cancel key-picker edits when the document changes, including during initial loading; reject stale swaps during loading.
- Cancel in-progress drags when the model or selected layer changes.
- Add dependency-free webview UI smoke tests and host edit-concurrency regression tests.

## 0.1.2 - 2026-10-09

- Fix "Open Visual Editor" failing when the active panel is the webview or no text editor is focused.

## 0.1.1 - 2026-10-09

- Fix cached rejected catalog/parser promises poisoning the session forever.
- Fix concurrent refresh race where a slow refresh could overwrite newer data.
- Fix unquoted `qmkHome` in geometry cache git command (shell injection with `'` in path).

## 0.1.0 - 2026-10-09

- Visual editor with QMK geometry, layer tabs, grid fallback, strict CSP, and live text updates.
- Key editing through the QMK catalog, function templates, raw expressions, and same-layer drag swaps.
- QMK compile command with streamed output, diagnostics, firmware-path tracking, and save-before-build behavior.
- Interactive QMK flash terminal and QMK Toolbox handoff for the last successful build.
- Doctor checks for QMK, toolchains, flashing tools, and QMK Toolbox.
- Packaged VS Code extension with bundled runtime dependencies and parser WASM files.
