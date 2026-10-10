# vscode-extensions

Monorepo for my VS Code extensions. Each extension is an independent npm package with its own lockfile.

| Extension | Path |
|---|---|
| QMK Keymap Lens | [extensions/qmk-keymap-lens](extensions/qmk-keymap-lens) |

## Working on an extension

```sh
cd extensions/<name>
npm ci
npm run typecheck && npm run build && npm test && npm run package   # build first: tests load dist/*.wasm
```

## Adding an extension

Create `extensions/<name>/` with its own `package.json`, then add it to the table above.
