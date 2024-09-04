export type StringArgAPICallback = (status: string) => void;
export type BoolArgAPICallback = (status: boolean) => void;
export type BoolStringAPICallback = (error: string, status: boolean) => void;
export type StringStringAPICallback = (error: string, result: string) => void;

export enum AuthMethod {
    NON_FACEBOOK,
    FACEBOOK_CLASSIC,
    FACEBOOK_GAMING_LOGIN,
};