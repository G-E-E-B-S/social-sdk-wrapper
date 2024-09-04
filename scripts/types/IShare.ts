import { EntryPointPayload, InvitePayload } from "./definitions";

export enum ShareDestinationType {
    NEWSFEED = "NEWSFEED",
    MESSENGER = "MESSENGER",
    GROUP = "GROUP",
}
export interface IShareParams {
    payload: string,
    imageData: string,
    body: string,
    title: string,
    switchContext: boolean,
}
export interface IInviteParams {
    payload: string,
    imageData: string,
    body: string,
    title: string,
    buttonCta: string,
    filters: string[],
    // TODO: integrate sections as defined in FB latest IG sdk.
}
export interface IShare {
    canShare(): boolean;
    canGroupShare(): boolean;
    shareLinkAsync(message: string, link: string): Promise<boolean>;
    shareImageAsync(imageData: string, payload: EntryPointPayload, title: string, body: string, shareDestinations?: ShareDestinationType[]): Promise<boolean>;

    shareLinkToGroup(): Promise<boolean>;
    shareImageToGroup(): Promise<boolean>;

    canInvite(): boolean;
    /**
     * share link to an image.
     */
    inviteLinkAsync(payload: InvitePayload): Promise<boolean>;
    /**
     * share image data
     */
    inviteImageAsync(payload: InvitePayload): Promise<boolean>;
    canChooseAsync(): boolean;
    chooseAsync(options?: FBInstant.ContextOptions): Promise<string>;
    canUpdateAsync(): boolean;
    updateAsync(payload: FBInstant.CustomUpdatePayload): Promise<boolean>;
    canCreateAsync(): boolean;
    createAsync(playerId: string): Promise<string>;
    canSwitchAsync(): boolean;
    switchAsync(contextId: string, switchSilentlyIfSolo: boolean): Promise<boolean>;
    getEntryPointData(): Promise<EntryPointPayload>;
    getContextType(): string;
}