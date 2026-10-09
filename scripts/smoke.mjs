import { existsSync, readFileSync } from "node:fs";

for (const file of ["dist/extension.js", "dist/webview.js"]) {
  if (!existsSync(file)) throw new Error(`Missing bundle: ${file}`);
}

const manifest = JSON.parse(readFileSync("package.json", "utf8"));
const source = readFileSync("src/extension.ts", "utf8");
for (const { command } of manifest.contributes.commands) {
  if (!source.includes(`registerCommand("${command}"`)) throw new Error(`Command is not registered: ${command}`);
}
for (const { viewType } of manifest.contributes.customEditors) {
  if (!source.includes(`registerCustomEditorProvider("${viewType}"`)) throw new Error(`Custom editor is not registered: ${viewType}`);
}

console.log("Bundle smoke check passed");
