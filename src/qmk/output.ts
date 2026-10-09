// Pure QMK output parsing. Must not import vscode.
import * as path from "node:path";

export interface QmkDiagnostic {
  path: string;
  line: number;
  column: number;
  severity: "error" | "warning";
  message: string;
}

const ANSI = /\x1b\[[0-?]*[ -/]*[@-~]/g;

export function stripAnsi(text: string): string {
  return text.replace(ANSI, "");
}

export function parseFirmwarePath(output: string, qmkHome: string): string | undefined {
  const clean = stripAnsi(output);
  const match = /^Copying\s+(.+?\.(?:bin|hex|uf2))\s+to qmk_firmware folder\s*(?:\[OK\])?\s*$/gim.exec(clean);
  if (!match) return undefined;
  return normalizeOutputPath(match[1].trim(), qmkHome);
}

export function parseDiagnostics(output: string, qmkHome: string): QmkDiagnostic[] {
  const diagnostics: QmkDiagnostic[] = [];
  for (const line of stripAnsi(output).split(/\r?\n/)) {
    const match = /^\s*(.+?):(\d+):(\d+):\s*(error|warning):\s*(.+?)\s*$/.exec(line);
    if (!match) continue;
    diagnostics.push({
      path: normalizeOutputPath(match[1], qmkHome),
      line: Number(match[2]),
      column: Number(match[3]),
      severity: match[4] as QmkDiagnostic["severity"],
      message: match[5],
    });
  }
  return diagnostics;
}

export function normalizeOutputPath(outputPath: string, qmkHome: string): string {
  const msys = /^\/([a-zA-Z])\/(.*)$/.exec(outputPath);
  const windowsPath = msys ? `${msys[1].toUpperCase()}:/${msys[2]}` : outputPath;
  if (path.win32.isAbsolute(windowsPath)) return path.win32.normalize(windowsPath);
  return path.win32.resolve(qmkHome, windowsPath.replace(/\//g, "\\"));
}
