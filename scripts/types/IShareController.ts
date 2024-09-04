import { EntryPointPayload } from "./definitions";

export interface IShareController {
  init();
  getEntryPointData(): Promise<EntryPointPayload>;
}