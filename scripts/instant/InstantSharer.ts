import { EntryPointPayload, InvitePayload } from "../types/definitions";
import { IShare, ShareDestinationType } from "../types/IShare";

export class InstantSharer implements IShare {
    // TODO: handle error and setting these flags to true on api error.
    private groupShareDisabled = false;
    private shareDisabled = false;
    private entryPointData: EntryPointPayload;
    getEntryPointData(): Promise<EntryPointPayload> {
        if (!this.entryPointData && FBInstant.getSupportedAPIs().indexOf("getEntryPointData") != -1) {
            this.entryPointData = FBInstant.getEntryPointData();
        }
        return Promise.resolve(this.entryPointData);
    }
    canCreateAsync(): boolean {
        return FBInstant.getSupportedAPIs().indexOf("context.createAsync") != -1;
    }
    createAsync(playerId: string): Promise<string> {
        try {
            return FBInstant.context.createAsync(playerId).then(() => {
                return FBInstant.context.getID();
            }).catch((reason) => {
                return Promise.reject(reason);
            });
        } catch (e) {
            return Promise.reject(e);
        }
    }
    canChooseAsync(): boolean {
        return FBInstant.getSupportedAPIs().indexOf("context.chooseAsync") != -1;
    }
    chooseAsync(options?: FBInstant.ContextOptions): Promise<string> {
        try {
            return FBInstant.context.chooseAsync(options).then(() => {
                return FBInstant.context.getID();
            }).catch((error) => {
                return Promise.reject(error);
            });
        } catch (e) {
            return Promise.reject(e);
        }
    }
    canSwitchAsync(): boolean {
        return FBInstant.getSupportedAPIs().indexOf("context.switchAsync") != -1;
    }
    switchAsync(contextId: string, switchSilentlyIfSolo: boolean): Promise<boolean> {
        if (!this.canSwitchAsync()) {
            return Promise.reject("API_NOT_SUPPORTED")
        }
        try {
            //@ts-ignore: switchSilentlyIfSolo flag is added in fbinstant 7.1
            return FBInstant.context.switchAsync(contextId, switchSilentlyIfSolo).then(() => {
                return true;
            }).catch((error) => {
                return Promise.reject(error);
            });
        } catch (e) {
            return Promise.reject(e);
        }
    }
    canUpdateAsync(): boolean {
        const ok = FBInstant.context.getID() ? true : false;
        return ok && FBInstant.getSupportedAPIs().indexOf("updateAsync") != -1;
    }
    updateAsync(payload: FBInstant.CustomUpdatePayload): Promise<boolean> {
        if (!this.canUpdateAsync()) {
            return Promise.reject("API_NOT_SUPPORTED")
        }
        try {
            return FBInstant.updateAsync(payload).then(() => {
                return true;
            }).catch((error) => {
                return Promise.reject(error);
            });
        } catch (e) {
            return Promise.reject(e);
        }
    }
    canShare(): boolean {
        if (this.shareDisabled) {
            return false;
        }
        try {
            return FBInstant.shareAsync && FBInstant.getSupportedAPIs().indexOf("shareAsync") != -1
        } catch(e) {
            console.error("canShare: exception %s", JSON.stringify(e));
            return false;
        }
    }
    canGroupShare(): boolean {
        if (this.groupShareDisabled) {
            return false;
        }

        const isWeb = FBInstant.getPlatform() === "WEB" || FBInstant.getPlatform() === "MOBILE_WEB";

        try {
            return !isWeb && FBInstant.getSupportedAPIs().indexOf("shareAsync") != -1;
        } catch (e) {
            console.error("canShare: exception %s", JSON.stringify(e));
            return false;
        }
    }
    shareLinkAsync(): Promise<boolean> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    shareImageAsync(imageData: string, payload: EntryPointPayload, title: string, body: string, shareDestinations?: ShareDestinationType[]): Promise<boolean> {
        // TODO: handle title.
        const sharePayload: FBInstant.SharePayload = {
            intent: (shareDestinations && shareDestinations.length > 0) ? 'REQUEST' : 'INVITE',
            image: imageData,
            text: body,
            data: payload
        }
        return this.shareAsync(sharePayload, shareDestinations);
    }
    shareLinkToGroup() {
        return Promise.reject("API_NOT_SUPPORTED")
    }
    shareImageToGroup() {
        return Promise.reject("API_NOT_SUPPORTED")
    }
    canInvite(): boolean {
        return FBInstant.getSupportedAPIs().indexOf("inviteAsync") != -1;
    }
    inviteLinkAsync(payload: InvitePayload): Promise<boolean> {
        return this.inviteAsync(payload);
    }
    inviteImageAsync(payload: InvitePayload): Promise<boolean> {
        return this.inviteAsync(payload);
    }
    getContextType(): string {
        try {
            return FBInstant.context.getType();
        } catch(e) {
            return "SOLO";
        }
    }
    private shareAsync(sharePayload: FBInstant.SharePayload, shareDestinations: ShareDestinationType[]) {
        if (shareDestinations && shareDestinations.length > 0) {
            const destinations: string[] = [];
            shareDestinations.forEach(element => {
                destinations.push(element);
            });

            // experimental share destinations feature
            //@ts-ignore
            sharePayload.shareDestination = destinations;
        }
        try {
            return FBInstant.shareAsync(sharePayload).then(() => {
                return true;
            }).catch(e => {
                if (e && e.code === "CLIENT_UNSUPPORTED_OPERATION") {
                    if (shareDestinations && shareDestinations.length && shareDestinations.indexOf(ShareDestinationType.GROUP) != -1) {
                        this.groupShareDisabled = true;
                    } else {
                        this.shareDisabled = true;
                    }
                }
                return Promise.reject(e);
            });
        } catch (e) {
            return Promise.reject("Api error");
        }
    }
    private inviteAsync(payload: InvitePayload) {
        try {
            return FBInstant.inviteAsync(payload).then(() => {
                return Promise.resolve(true);
            }).catch((error) => {
                return Promise.reject(error);
            });
        } catch (e) {
            return Promise.reject("Api error");
        }
    }
}