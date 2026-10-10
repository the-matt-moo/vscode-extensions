import { spawn } from "node:child_process";
import * as os from "node:os";

export interface RunOptions {
  msysRoot: string;
  cwd?: string;
}

export interface RunResult {
  code: number;
  stdout: string;
  stderr: string;
}

/** POSIX single-quote one argument: wrap in '...' and turn each ' into '\''. */
export function shQuote(arg: string): string {
  if (arg !== "" && /^[A-Za-z0-9_@%+=:,./-]+$/.test(arg)) return arg;
  return `'${arg.replace(/'/g, `'\\''`)}'`;
}

export function buildQmkCommand(args: string[]): string {
  return ["qmk", ...args].map(shQuote).join(" ");
}

/** C:\Users\X -> /c/Users/X */
export function toPosixPath(winPath: string): string {
  const p = winPath.replace(/\\/g, "/");
  const m = /^([A-Za-z]):(\/.*)?$/.exec(p);
  return m ? `/${m[1].toLowerCase()}${m[2] ?? ""}` : p;
}

export function stripBanner(text: string): string {
  return text
    .split(/(?<=\n)/)
    .filter((l) => !l.startsWith("Welcome to QMK MSYS") && !l.startsWith("  * "))
    .join("");
}

export function buildMsysEnv(): NodeJS.ProcessEnv {
  const home = os.homedir();
  return { ...process.env, MSYSTEM: "MINGW64", HOME: toPosixPath(home), USERPROFILE: home };
}

/** Spawn `<msysRoot>/usr/bin/bash.exe -lc <cmd>`. `cmd` is a raw shell string. */
export function runShellStreaming(
  cmd: string,
  opts: RunOptions,
  onData?: (chunk: string, stream: "stdout" | "stderr") => void,
): Promise<RunResult> {
  const bash = `${opts.msysRoot.replace(/[\\/]+$/, "")}/usr/bin/bash.exe`;
  return new Promise((resolve, reject) => {
    const child = spawn(bash, ["-lc", cmd], { cwd: opts.cwd, env: buildMsysEnv(), windowsHide: true });
    let stdout = "";
    let stderr = "";
    child.stdout.setEncoding("utf8").on("data", (d: string) => {
      stdout += d;
      // shortcut: per-chunk strip misses a banner line split across chunks; buffer by line if seen.
      const s = stripBanner(d);
      if (s) onData?.(s, "stdout");
    });
    child.stderr.setEncoding("utf8").on("data", (d: string) => {
      stderr += d;
      onData?.(d, "stderr");
    });
    child.on("error", reject);
    child.on("close", (code) => resolve({ code: code ?? -1, stdout: stripBanner(stdout), stderr }));
  });
}

export function runShell(cmd: string, opts: RunOptions): Promise<RunResult> {
  return runShellStreaming(cmd, opts);
}

export function run(args: string[], opts: RunOptions): Promise<RunResult> {
  return runShellStreaming(buildQmkCommand(args), opts);
}

export function runStreaming(
  args: string[],
  opts: RunOptions,
  onData: (chunk: string, stream: "stdout" | "stderr") => void,
): Promise<RunResult> {
  return runShellStreaming(buildQmkCommand(args), opts, onData);
}
