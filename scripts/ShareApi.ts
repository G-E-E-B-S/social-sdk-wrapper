// FIXME: this import won't work on cocos 2.x, need to make this work somehow
import { Node } from "cc";
import { AttributionData, EntryPointPayload, InvitePayload } from "./types/definitions";
import { IImageGenerator } from "./types/IImageDataGenerator";
import { IShare, ShareDestinationType } from "./types/IShare";
import IShareContent from "./types/IShareContent";

export class ShareApi {
    private generator: IImageGenerator;
    private sharer: IShare;
    private static instance: ShareApi;
    static getInstance(): ShareApi {
        return this.instance;
    }

    static init(sharer: IShare, generator: IImageGenerator): void {
        if (!this.instance) {
            this.instance = new ShareApi(sharer, generator);
        }
    }
    constructor(sharer: IShare, generator: IImageGenerator) {
        this.generator = generator;
        this.sharer = sharer;
    }
    canInvite(): boolean {
        return this.sharer.canInvite();
    }
    inviteAsync(payload: InvitePayload): Promise<boolean> {
        return this.sharer.inviteImageAsync(payload);
    }
    canChooseAsync(): boolean {
        return this.sharer.canChooseAsync();
    }
    chooseAsync(options?: FBInstant.ContextOptions): Promise<string> {
        return this.sharer.chooseAsync(options);
    }
    canCreateAsync(): boolean {
        return this.sharer.canCreateAsync();
    }
    createAsync(playerId: string): Promise<string> {
        return this.sharer.createAsync(playerId);
    }
    canUpdateAsync(): boolean {
        return this.sharer.canUpdateAsync();
    }
    updateAsync(payload: FBInstant.CustomUpdatePayload): Promise<boolean> {
        return this.sharer.updateAsync(payload);
    }
    canShare(): boolean {
        return this.sharer.canShare();
    }
    canGroupShare(): boolean {
        return this.sharer.canGroupShare();
    }
    shareImage(imageData: string, payload: EntryPointPayload, title: string, body: string, shareDestinations: ShareDestinationType[]): Promise<boolean> {
        return this.sharer.shareImageAsync(imageData, payload, title, body, shareDestinations);
    }
    createImageData<T extends IShareContent>(asset: string, componentScript:  {prototype: T}, initParams: unknown, parentNode: Node, checkNode: Node): Promise<string> {
        return this.generator.createImageData(asset, componentScript, initParams, parentNode, checkNode);
    }
    createLink(linkType:string, attributionData: AttributionData, paramsData: unknown): Promise<string> {
        return this.generator.createLink(linkType, attributionData, paramsData);
    }
    shareLink(message: string, link: string): Promise<boolean> {
        return this.sharer.shareLinkAsync(message, link);
    }
    canSwitchAsync(): boolean {
        return this.sharer.canSwitchAsync();
    }
    switchAsync(contextId: string, switchSilentlyIfSolo: boolean): Promise<boolean> {
        return this.sharer.switchAsync(contextId, switchSilentlyIfSolo);
    }
    getEntryPointData(): Promise<EntryPointPayload> {
        console.log("ShareApi::getEntryPointData called")
        return this.sharer.getEntryPointData();
    }
    getContextType(): string {
        return this.sharer.getContextType();
    }
}
