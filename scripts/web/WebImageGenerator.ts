import { IImageGenerator } from "../types/IImageDataGenerator";
import { AttributionData } from "../types/definitions";

export class WebImageGenerator implements IImageGenerator {
    createImageData(): Promise<string> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    getImageData(): string {
        return "NO IMAGE DATA";
    }
    createLink(linkType:string, attributionData: AttributionData, payload: unknown): Promise<string> {
        const { origin, pathname } = window.parent.location;
        const copyText = origin + pathname + `?utm_source=&${attributionData.utm_source}` +
        `&utm_medium=&${attributionData.utm_medium}` +
        `&utm_campaign=&${attributionData.utm_campaign}` +
        `&payload=${window.btoa(JSON.stringify(payload))}`;
        return Promise.resolve(copyText);
    }
}