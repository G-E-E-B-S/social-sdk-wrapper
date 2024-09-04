export interface TournamentConfig {
    title?: string;
    image?: string;
    sortOrder?: TournamentSortOrder;
    scoreFormat?: TournamentScoreFormat;
    endTime?: number;
}

export interface TournamentPayload {
    "entry_source"?: string;
}

export enum TournamentSortOrder {
    LOWER_IS_BETTER = "LOWER_IS_BETTER",
    HIGHER_IS_BETTER = "HIGHER_IS_BETTER"
}

export enum TournamentScoreFormat {
    NUMERIC = "NUMERIC",
    TIME = "TIME"
}

export interface Tournament {
    getID(): string;
    getContextID(): string;
    getEndTime(): number;
    getPayload(): unknown;
}
export interface InvitePayload {
    image: string,
    text: string,
    data: unknown,
}
export enum FBApiResponse {
    Failure,
    Cancelled,
    Success,
}
export interface FBApiError {
    code: string;
    message: string;
    name?: string,
}

export enum PayloadType {
    ATTRIBUTION = "attribution",
    A2U = "a2u",
    SOLO = "solo",
}

export interface ButtonPayload {
    type: string;
    payload?: AttributionData | SenderAttributionData;
}

export interface AttributionData {
    utm_medium: string;
    utm_source: string;
    utm_campaign: string;
}

export interface SenderAttributionData extends AttributionData {
    senderUserID: string;
    senderName?: string;
    senderAvatar?: string;
}
/**
 * @deprecated This type should not be used going forward.
 * Legacy type.
 */
export interface EntryPointData extends ButtonPayload {
    data: unknown;
}

export interface EntryPointPayload {
    type: string,
    attributionData?: AttributionData,
    payload?: unknown,
}