import { EntryPointPayload } from "../types/definitions";
import { IShare } from "../types/IShare";
import { IBase64Helper } from "./NativeImageGenerator";
import { NativeShareWrapper } from "./NativeShareWrapper";
import { AuthMethod } from "./types";
export interface IPlatformHelper {
    getAuthMethod(): AuthMethod;
}
export class NativeSharer implements IShare {
    private nativeShareWrapper: NativeShareWrapper;
    private platformHelper: IPlatformHelper;
    constructor(platformHelper: IPlatformHelper, base64Helper: IBase64Helper) {
        this.platformHelper = platformHelper;
        this.nativeShareWrapper = new NativeShareWrapper(base64Helper);
    }
    canCreateAsync(): boolean {
        return this.platformHelper.getAuthMethod() == AuthMethod.FACEBOOK_GAMING_LOGIN;
    }
    createAsync(playerId: string): Promise<string> {
        if (!this.canCreateAsync()) {
            return Promise.reject({
                name: "createAsync",
                code: "API_NOT_SUPPORTED"
            });
        }
        return new Promise<string>((resolve, reject) => {
            return this.nativeShareWrapper.createContext(playerId, (error, contextId) => {
                if (error) {
                    reject({
                        name: "createAsync",
                        code: error
                    });
                } else {
                    resolve(contextId);
                }
            });
        });
    }
    canChooseAsync(): boolean {
        return this.platformHelper.getAuthMethod() == AuthMethod.FACEBOOK_GAMING_LOGIN;
    }
    chooseAsync(options?: FBInstant.ContextOptions): Promise<string> {
        if (!this.canChooseAsync()) {
            return Promise.reject({
                name: "chooseAsync",
                code: "API_NOT_SUPPORTED"
            });
        }
        return new Promise<string>((resolve, reject) => {
            return this.nativeShareWrapper.chooseContext(options, (error, contextId) => {
                if (error) {
                    reject({
                        name: "chooseAsync",
                        code: error
                    });
                } else {
                    resolve(contextId);
                }
            });
        });
    }
    canSwitchAsync(): boolean {
        return this.platformHelper.getAuthMethod() == AuthMethod.FACEBOOK_GAMING_LOGIN;
    }
    switchAsync(contextId: string) {
        if (!this.canSwitchAsync()) {
            return Promise.reject({
                name: "switchAsync",
                code: "API_NOT_SUPPORTED"
            })
        }
        return new Promise<boolean>((resolve, reject) => {
            return this.nativeShareWrapper.switchContext(contextId, (error) => {
                if (error) {
                    reject({
                        name: "switchAsync",
                        code: error
                    });
                } else {
                    resolve(true);
                }
            });
        });
    }
    canUpdateAsync(): boolean {
        // TODO: add logic to detect current context.
        return this.platformHelper.getAuthMethod() == AuthMethod.FACEBOOK_GAMING_LOGIN;
    }
    updateAsync(payload: FBInstant.CustomUpdatePayload): Promise<boolean> {
        if (!this.canUpdateAsync()) {
            return Promise.reject({
                name: "updateAsync",
                code: "API_NOT_SUPPORTED"
            })
        }
        return new Promise<boolean>((resolve, reject) => {
            return this.nativeShareWrapper.updateAsync(payload, (error, status) => {
                if (error) {
                    reject({
                        name: "updateAsync",
                        code: error
                    });
                } else {
                    resolve(status);
                }
            });
        });
    }
    canShare(): boolean {
        return true;
    }
    canGroupShare(): boolean {
        return false;
    }
    shareLinkAsync(message: string, link: string): Promise<boolean> {
        return new Promise<boolean>((resolve, reject) => {
            this.nativeShareWrapper.shareLink(this.platformHelper.getAuthMethod(), message, link, (error, success) => {
                if (error) {
                    reject({
                        name: "shareLinkAsync",
                        code: error
                    });
                } else {
                    resolve(success);
                }
            })
        });
    }
    shareImageAsync(imageData: string, payload: EntryPointPayload, title: string, body: string): Promise<boolean> {
        console.log("NativeSharer:shareImage %s", imageData, Date.now());
        return new Promise<boolean>((resolve, reject) => {
            this.nativeShareWrapper.shareImage(this.platformHelper.getAuthMethod(), imageData, payload, title, body, (error, success) => {
                if (error) {
                    reject({
                        name: "shareImageAsync",
                        code: error
                    });
                } else {
                    resolve(success);
                }
            });
        });
    }
    shareLinkToGroup() {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    shareImageToGroup() {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    canInvite(): boolean {
        return this.platformHelper.getAuthMethod() == AuthMethod.FACEBOOK_GAMING_LOGIN;
    }
    inviteLinkAsync(): Promise<boolean> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    inviteImageAsync(): Promise<boolean> {
        console.log("NativeSharer:inviteImageAsync %s", Date.now());
        return new Promise<boolean>((resolve, reject) => {
            this.nativeShareWrapper.inviteImageAsync((error, success) => {
                if (error) {
                    reject({
                        name: "inviteImageAsync",
                        code: error
                    });
                } else {
                    resolve(success);
                }
            });
        });
    }
    getEntryPointData(): Promise<EntryPointPayload> {
        console.log("NativeSharer::getEntryPointData called")
        const promise = new Promise((resolve, reject) => {
            this.nativeShareWrapper.getEntryPointData((payload: EntryPointPayload) => {
                console.warn("NativeSharer::getEntryPointData %s", JSON.stringify(payload));
                resolve(payload);
            }, (error) => {
                console.warn("NativeSharer::getEntryPointData error %s", error);
                reject(error);
            });
        }) as Promise<EntryPointPayload>;
        return promise;
    }
    getContextType(): string {
        return "SOLO";
    }
}