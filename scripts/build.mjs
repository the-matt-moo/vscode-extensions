import { build } from "esbuild";
import { copyFileSync, mkdirSync } from "node:fs";

await Promise.all([
  build({
    entryPoints: ["src/extension.ts"],
    bundle: true,
    platform: "node",
    format: "cjs",
    target: "node20",
    external: ["vscode"],
    outfile: "dist/extension.js",
    sourcemap: true,
    // web-tree-sitter's ESM build reads import.meta.url; give it a CJS equivalent.
    banner: { js: "const __importMetaUrl = require('url').pathToFileURL(__filename).href;" },
    define: { "import.meta.url": "__importMetaUrl" },
  }),
  build({
    entryPoints: ["src/webview/main.ts"],
    bundle: true,
    platform: "browser",
    format: "iife",
    target: "es2020",
    outfile: "dist/webview.js",
    sourcemap: true,
  }),
]);

mkdirSync("dist", { recursive: true });
for (const f of ["node_modules/web-tree-sitter/tree-sitter.wasm", "node_modules/tree-sitter-c/tree-sitter-c.wasm"]) {
  copyFileSync(f, `dist/${f.split("/").pop()}`);
}
