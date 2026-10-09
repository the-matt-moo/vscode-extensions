import type { KeyGeom } from "../model/geometry";

export interface ViewKey {
  text: string;
  label: string;
}

export interface ViewEncoder {
  cw: string;
  ccw: string;
  cwLabel: string;
  ccwLabel: string;
}

export interface ViewLayer {
  designator: string;
  layoutMacro: string;
  readOnlyReason?: string;
  keys: ViewKey[];
  encoders?: ViewEncoder[];
}

export interface ModelMessage {
  type: "model";
  keyboard: string;
  keymap: string;
  layers: ViewLayer[];
  geometry: { keys: KeyGeom[] } | null;
  error?: string;
}

export type HostMessage = ModelMessage;

export type WebviewMessage =
  | { type: "ready" }
  | { type: "compile" }
  | { type: "flash" }
  | { type: "editKey"; layer: number; key: number }
  | { type: "swapKeys"; layer: number; a: number; b: number };
