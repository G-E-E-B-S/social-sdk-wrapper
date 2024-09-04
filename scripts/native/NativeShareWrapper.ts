import { EntryPointPayload } from "../types/definitions";
import { IBase64Helper } from "./NativeImageGenerator";
import { AuthMethod, BoolStringAPICallback, StringArgAPICallback, StringStringAPICallback } from "./types";

declare const social;
interface IShareListener {
    onInviteLinkFetchComplete: (payload: string) => void;
    onContextChooseFailed: (error: string) => void;
    onContextChooseComplete: (contextId: string) => void;
    onContextCreateFailed: (error: string) => void;
    onContextCreateComplete: (contextId: string) => void;
    onContextSwitchFailed: (error: string) => void;
    onContextSwitchComplete: () => void;
    onCustomUpdateFailed: (error: string) => void;
    onCustomUpdateSuccess: () => void;
    onShareFailed: (error: string) => void;
    onShareComplete(status: boolean): void;
}
export class NativeShareWrapper {
    constructor(base64Helper: IBase64Helper) {
        this.setupDelegate();
        this.base64Helper = base64Helper;
    }
    shareImage(authMethod: AuthMethod, imageData: string, payload: EntryPointPayload, title: string, body: string, callback: BoolStringAPICallback) {
        // TODO: attach payload to image.
        console.log("NativeShareWrapper:shareImage", Date.now());
        this.shareDelegate.shareImage(authMethod, imageData, title, body);
        this.onShareComplete = callback;
    }
    inviteImageAsync(callback: BoolStringAPICallback) {
        console.log("NativeShareWrapper:inviteImageAsync", Date.now());
        this.shareDelegate.inviteAsync();
        this.onShareComplete = callback;
    }
    shareLink(authMethod: AuthMethod, message: string, link: string, callback: BoolStringAPICallback) {
        this.onShareComplete = callback;
        this.shareDelegate.shareLink(authMethod, message, link);
    }
    updateAsync(payload: FBInstant.CustomUpdatePayload, callback: BoolStringAPICallback) {
        this.onUpdateAsyncComplete = callback;
        this.shareDelegate.updateAsync(JSON.stringify(payload.text), payload.cta, payload.image, JSON.stringify(payload.data));
    }
    chooseContext(options: FBInstant.ContextOptions, callback: StringStringAPICallback) {
        // TODO: support options.
        this.shareDelegate.chooseContext();
        this.onChooseContextComplete = callback;
    }
    createContext(contextId: string, callback: StringStringAPICallback) {
        this.shareDelegate.createContext(contextId);
        this.onCreateContextComplete = callback;
    }
    switchContext(contextId: string, callback: StringArgAPICallback) {
        this.shareDelegate.switchContext(contextId);
        this.onSwitchAsyncComplete = callback;
    }
    getEntryPointData(onSuccess: (payload: EntryPointPayload) => void, onFailure: StringArgAPICallback) {
        console.log("NativeShareWrapper::getEntryPointData called");
        this.shareDelegate.getEntryPointData();
        this.onInviteLinkFetchComplete = onSuccess;
        this.onInviteLinkFetchError = onFailure;
    }
    private setupDelegate() {
        this.shareDelegate = social.getSharer();
        const obj = {} as IShareListener;
        obj.onShareComplete = (status: boolean) => {
            console.log("NativeShareWrapper:shareImage share complete", Date.now());
            this.onShareComplete(null, status);
        }
        obj.onShareFailed = (error: string) => {
            this.onShareComplete(error, false);
        }
        obj.onCustomUpdateSuccess = () => {
            this.onUpdateAsyncComplete(null, true);
        }
        obj.onCustomUpdateFailed = (error: string) => {
            this.onUpdateAsyncComplete(error, false);
        }
        obj.onContextSwitchComplete = () => {
            this.onSwitchAsyncComplete(null);
        }
        obj.onContextSwitchFailed = (error: string) => {
            this.onSwitchAsyncComplete(error);
        }
        obj.onContextCreateComplete = (contextId: string) => {
            this.onCreateContextComplete(null, contextId);
        }
        obj.onContextCreateFailed = (error: string) => {
            this.onCreateContextComplete(error, null);
        }
        obj.onContextChooseComplete = (contextId: string) => {
            this.onChooseContextComplete(null, contextId);
        }
        obj.onContextChooseFailed = (error: string) => {
            this.onChooseContextComplete(error, null);
        }
        obj.onInviteLinkFetchComplete = (payload: string) => {
            if (!this.onInviteLinkFetchComplete) {
                return;
            }
            const decryptedPayload = this.base64Helper.decode(payload);
            console.log("NativeShareWrapper:onInviteLinkFetchComplete fetch complete ", decryptedPayload);
            try {
                const entryPointData: EntryPointPayload = JSON.parse(decryptedPayload);
                this.onInviteLinkFetchComplete(entryPointData);
            } catch (err) {
                console.warn("Payload parsing error %s", payload);
                this.onInviteLinkFetchError(err);
            }
            this.onInviteLinkFetchComplete = null
            this.onInviteLinkFetchError = null;
        };
        social.setShareListener(obj);
    }
    private onShareComplete: BoolStringAPICallback;
    private onUpdateAsyncComplete: BoolStringAPICallback;
    private onSwitchAsyncComplete: StringArgAPICallback;
    private onCreateContextComplete: StringStringAPICallback;
    private onChooseContextComplete: StringStringAPICallback;
    private onInviteLinkFetchComplete: (payload: EntryPointPayload) => void;
    private onInviteLinkFetchError: StringArgAPICallback;
    private shareDelegate = null;
    private base64Helper: IBase64Helper;
}