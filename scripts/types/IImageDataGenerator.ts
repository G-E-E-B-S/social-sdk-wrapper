// FIXME: this import won't work on cocos 2.x, need to make this work somehow
import { Node } from "cc";
import { AttributionData } from "./definitions";
import IShareContent from "./IShareContent";

export interface IImageGenerator {
    createImageData<T extends IShareContent>(asset: string, componentScript: {prototype: T}, initParams: unknown, parentNode: Node, checkNode: Node): Promise<string>;
    createLink(linkType: string, attributionData: AttributionData, payload: unknown): Promise<string>;
}