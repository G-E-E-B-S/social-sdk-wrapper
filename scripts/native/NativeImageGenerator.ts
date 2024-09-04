// FIXME: this import won't work on cocos 2.x, need to make this work somehow
import { instantiate, isValid, native, Node, Prefab, resources } from "cc";
import { Dictionary } from "typescript-collections";

import CanvasUtils from "../CanvasUtils";
import { AttributionData } from "../types/definitions";
import { IImageGenerator } from "../types/IImageDataGenerator";
import IShareContent from "../types/IShareContent";

export interface IBase64Helper {
    encode(data: string): string;
    decode(data: string): string;
}

export interface ILinkShortener {
    getShortenedURL(longLink: string): Promise<string>;
}

export class NativeImageGenerator implements IImageGenerator {
    private linkMap: Dictionary<string, string>;
    private base64Helper: IBase64Helper;
    private baseURLShortner: ILinkShortener;
    constructor(linkMap: Dictionary<string, string>, base64Helper: IBase64Helper, urlShortner: ILinkShortener) {
        this.linkMap = linkMap;
        this.base64Helper = base64Helper;
        this.baseURLShortner = urlShortner;
    }
    createLink(linkType: string, attributionData: AttributionData, payload: unknown): Promise<string> {
        let link = this.linkMap.getValue(linkType);
        if (link.indexOf('?') == -1) {
            link += '?';
        }
        const attributionParams = `utm_campaign=${attributionData.utm_campaign}` +
            `&utm_medium=${attributionData.utm_medium}` +
            `&utm_source=${attributionData.utm_source}`;
        const urlTobeShorten = link + attributionParams + `&_p=${this.base64Helper.encode(JSON.stringify(payload))}`

        return this.baseURLShortner.getShortenedURL(urlTobeShorten);
    }
    createImageData<T extends IShareContent>(asset: string, componentScript: { prototype: T }, initParams: unknown, parentNode: Node, checkNode: Node): Promise<string> {
        console.log("NativeImageGenerator::createImageData starting", Date.now())
        return new Promise<string>((resolve, reject) => {
            let shareNode: Node = null;
            resources.load(asset, Prefab, (err, prefab: Prefab) => {
                console.log("NativeImageGenerator::createImageData load complete", Date.now());
                shareNode = instantiate(prefab);
                if (!isValid(shareNode)) {
                    console.error("createImageData: error invalid node")
                    return reject("INVALID_NODE")
                }
                const regex = /[/_]/gi;
                if (componentScript) {
                    // @ts-ignore
                    const script: IShareContent = shareNode.getComponent(componentScript);
                    console.log("NativeImageGenerator::createImageData init component", Date.now());
                    script.init(initParams, (isSuccess) => {
                        console.log("NativeImageGenerator::createImageData init done %s", isSuccess, Date.now());
                        if (!isSuccess) {
                            console.error("createImageData: error component init");
                            return reject('ERROR_INIT_COMPONENT');
                        }
                        return this.getImageLink(shareNode, parentNode, asset.replace(regex, "_")).then(filePath => {
                            resolve(filePath);
                        });
                    });
                } else {
                    return this.getImageLink(shareNode, parentNode, asset.replace(regex, "_")).then(filePath => {
                        resolve(filePath);
                    });
                }
            });
        });
    }
    private async getImageLink(shareNode: Node, parentNode: Node, assetName: string): Promise<string> {
        const texture = await CanvasUtils.renderTextureFomNode(shareNode, parentNode);
        const data = texture.readPixels();
        const width = texture.width;
        const height = texture.height;
        console.log("generateTextureFromNode callback status: %s", texture.getPixelFormat());
        // console.log("texture: W: %s, H: %s F: %s D: %s", texture.width, texture.height, texture.getPixelFormat(), JSON.stringify(texture.readPixels()));
        const filePath = native.fileUtils.getWritablePath() + assetName + ".png";
        if (native.saveImageData(data, width, height, filePath)) {
            return Promise.resolve(filePath);
        } else {
            return Promise.reject("WRITE_FAILED");
        }
    }
}