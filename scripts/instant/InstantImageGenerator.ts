// FIXME: this import won't work on cocos 2.x, need to make this work somehow
import { Node, Prefab, instantiate, isValid, resources } from "cc";

import CanvasUtils from "../CanvasUtils";
import { IImageGenerator } from "../types/IImageDataGenerator";
import IShareContent from "../types/IShareContent";

export class InstantImageGenerator implements IImageGenerator {
    createLink(): Promise<string> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    createImageData<T extends IShareContent>(asset: string, componentScript: {prototype: T}, initParams: unknown, parentNode: Node, checkNode: Node): Promise<string> {
        return new Promise<string>((resolve, reject) => {
            resources.load(asset, (err, prefab: Prefab) => {
                if (err) {
                    return reject(err);
                }
                const shareNode = instantiate(prefab);
                if (!isValid(shareNode)) {
                    return reject("INVALID_NODE")
                }
                if (componentScript) {
                    // @ts-ignore
                    const script: IShareContent = shareNode.getComponent(componentScript);
                    script.init(initParams, (success) => {
                        if (!success || !checkNode || !isValid(checkNode)) {
                            return reject("NOT_LOADED");
                        }
                        return resolve(CanvasUtils.base64FromNode(shareNode, parentNode))
                    });
                } else {
                    return resolve(CanvasUtils.base64FromNode(shareNode, parentNode))
                }

            });
        })
    }
}