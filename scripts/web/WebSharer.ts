import { EntryPointPayload, InvitePayload } from "../types/definitions";
import { IShare, ShareDestinationType } from "../types/IShare";

export interface IPlatformHelper {

}

export class WebSharer implements IShare {
    constructor(platformHelper: IPlatformHelper) {
        this.platformHelper = platformHelper;
        this.getEntryPointData();
    }
    getContextType(): string {
        return "SOLO";
    }
    canCreateAsync(): boolean {
        return false;
    }
    createAsync(playerId: string): Promise<string> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    canChooseAsync(): boolean {
        return false;
    }
    chooseAsync(options?: FBInstant.ContextOptions): Promise<string> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    canSwitchAsync(): boolean {
        return false;
    }
    switchAsync(playerId: string, switchSilentlyIfSolo: boolean): Promise<boolean> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    canUpdateAsync(): boolean {
        return false;
    }
    updateAsync(payload: FBInstant.CustomUpdatePayload): Promise<boolean> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    canShare(): boolean {
        return true;
    }
    canGroupShare(): boolean {
        return false;
    }
    shareLinkAsync(message: string, link: string): Promise<boolean> {
        const copyText = message + '\n' + link;
        if (window.isSecureContext && navigator.clipboard) {
            console.log('Copied to clipboard');
            return navigator.clipboard.writeText(copyText).then(() => Promise.resolve(true));
        }
        console.log('Not copied to clipboard');
        return Promise.resolve(false);
    }
    shareImageAsync(imageData: string, payload: EntryPointPayload, title: string, body: string, shareDestinations: ShareDestinationType[]): Promise<boolean> {
        return Promise.reject("API NOT SUPPORTED");
    }
    shareLinkToGroup() {
        return Promise.reject("API_NOT_SUPPORTED")
    }
    shareImageToGroup() {
        return Promise.reject("API_NOT_SUPPORTED")
    }
    canInvite(): boolean {
        return false;
    }
    inviteLinkAsync(payload: InvitePayload): Promise<boolean> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    inviteImageAsync(payload: InvitePayload): Promise<boolean> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    getEntryPointData(): Promise<EntryPointPayload> {
        if (!this.entryPointData) {
            let urlString = window.parent.location.href;
            const url = new URL(urlString);
            try {
                const searchParamsPayload = url.searchParams.get("payload");
                const decodedPayload = window.atob(searchParamsPayload);

                //TODO: Add EntryPointPayload Validation

                this.entryPointData = JSON.parse(decodedPayload);
            } catch (err) {
            }
        }

        return Promise.resolve(this.entryPointData);
    }

    isValidEntryPointData(payload): boolean {
        return true;
    }

    private entryPointData: EntryPointPayload = null;
    private platformHelper: IPlatformHelper;
}