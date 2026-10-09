# Changelog

## 0.0.1 - Unreleased

- QMK MSYS runner with banner stripping and POSIX argument quoting.
- `QMK Lens: Doctor` command: qmk version, qmk_home, toolchain presence.
- Tree-sitter keymap parser: layers, per-key ranges, read-only detection, custom keycodes, tap dance names, `applyEdit`.
- Geometry parser: `parseQmkInfo`, `resolveLayout` (alias resolution), `bounds` helper.
- Geometry loader: `loadGeometry` with mtime+git-HEAD cache fingerprint.
- Keycode catalog: version-ordered hjson merge, `!reset!` alias handling, function entries (MO/LT/LSFT_T/etc.), `buildCatalog` for custom keycodes + tap dance, `labelFor` display labels.
- `hjson` 3.2.2 dependency added.
