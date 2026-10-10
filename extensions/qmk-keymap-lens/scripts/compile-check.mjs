import { parseDiagnostics, parseFirmwarePath, stripAnsi } from "../src/qmk/output.ts";
import { run } from "../src/qmk/runner.ts";

if (process.env.QMK_LIVE !== "1") {
  console.error("Set QMK_LIVE=1 to run real QMK compiles.");
  process.exit(2);
}

const options = { msysRoot: process.env.QMK_MSYS_ROOT || "C:/QMK_MSYS" };
const config = await run(["config", "user.qmk_home"], options);
const qmkHome = /user\.qmk_home=(.*)/.exec(config.stdout)?.[1]?.trim();
if (config.code !== 0 || !qmkHome) throw new Error("Could not resolve user.qmk_home");

let failed = false;
for (const [keyboard, keymap] of [["lily58/rev1", "moo"], ["zsa/moonlander", "moo"]]) {
  const started = Date.now();
  const result = await run(["compile", "-kb", keyboard, "-km", keymap], { ...options, cwd: qmkHome });
  const output = `${result.stdout}\n${result.stderr}`;
  const diagnostics = parseDiagnostics(output, qmkHome);
  const errors = diagnostics.filter((item) => item.severity === "error").slice(0, 3);
  if (result.code !== 0) failed = true;
  console.log(JSON.stringify({
    keyboard,
    keymap,
    exitCode: result.code,
    durationMs: Date.now() - started,
    firmwarePath: parseFirmwarePath(output, qmkHome) ?? null,
    errors: errors.length ? errors.map((item) => `${item.path}:${item.line}:${item.column}: ${item.message}`) : failureLines(output),
  }));
}

process.exitCode = failed ? 1 : 0;

function failureLines(output) {
  return stripAnsi(output)
    .split(/\r?\n/)
    .filter((line) => /(?:error:|make: \*\*\*)/i.test(line))
    .slice(0, 3)
    .map((line) => line.trim());
}
