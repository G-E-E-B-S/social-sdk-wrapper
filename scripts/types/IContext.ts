interface IContextHelper {
    isAvailable(): boolean;
    chooseAsync(): Promise<boolean>;
    createAsync(): Promise<boolean>
    switchAsync(): Promise<boolean>;
    updateAsync(): Promise<boolean>;
}