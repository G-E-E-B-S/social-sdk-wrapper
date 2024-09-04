// FIXME: this import won't work on cocos 2.x, need to make this work somehow
import { Camera, ImageAsset, Node, Prefab, RenderTexture, Texture2D, UITransform, instantiate } from "cc";

export default class CanvasUtils {

    /** Returns the Base64 string of the provided RenderTexture.
     * @param  {cc.RenderTexture} renderTexture
     * @param  {number} width
     * @param  {number} height
     * @returns string
     */
    static getBase64FromTexture(renderTexture: RenderTexture, width: number, height: number): string {

        let pixels = renderTexture.readPixels();
        return CanvasUtils.getBase64FromPixels(pixels, width, height);
    }

    /** Returns the Base64 string of the provided pixels.
     * @param  {Uint8Array} pixels
     * @param  {number} width
     * @param  {number} height
     * @returns string
     */
    static getBase64FromPixels(pixels: Uint8Array, width: number, height: number): string {
        const canvas = document.createElement('canvas');
        canvas.width = width;
        canvas.height = height;
        const context = canvas.getContext('2d');
        const imageData = context.createImageData(canvas.width, canvas.height);
        imageData.data.set(pixels);
        context.putImageData(imageData, 0, 0);
        if (canvas.toDataURL) {
            return canvas.toDataURL("image/jpg");
        }
        return "";
    }
    /** Returns the Base64 string of the provided node.
    * @param  {cc.Node} sourceNode The node to provide Base64 string.
    * @param  {cc.Node} tempParentNode The temporary parent to add the sourceNode.
    * @returns string
    */
    static base64FromNode(sourceNode: Node, tempParentNode: Node): Promise<string> {

        if (!sourceNode.parent) {
            tempParentNode.addChild(sourceNode);
        }

        let camera = sourceNode.getComponentInChildren(Camera);
        if (!camera) {
            console.error("No Camera found in prefab. Camera should be child of Prefab only");
        }
        let renderTexture = new RenderTexture();
        const transform = sourceNode.getComponent(UITransform);
        renderTexture.initialize({ width: transform.width, height: transform.height });
        camera.targetTexture = renderTexture;
        return new Promise((resolve) => {
            setTimeout(() => {
                const pixels = camera.targetTexture.readPixels();
                sourceNode.active = false;
                sourceNode.removeFromParent();
                sourceNode.destroy();
                resolve(CanvasUtils.getBase64FromPixels(pixels, renderTexture.width, renderTexture.height));
            }, 200);
        });

    }
    /** Returns the Base64 string of the provided prefab.
    * @param  {cc.Prefab} prefab The prefab to provide Base64 string.
    * @param  {cc.Node} tempParentNode The temporary parent to add the prefab.
    * @returns string
    */
    static base64FromPrefab(prefab: Prefab, tempParentNode: Node): Promise<string> {
        let sourceNode = instantiate(prefab);
        return CanvasUtils.base64FromNode(sourceNode, tempParentNode);
    }

    static renderTextureFromPrefab(prefab: Prefab, parentNode: Node): Promise<RenderTexture> {
        let sourceNode = instantiate(prefab);
        return CanvasUtils.renderTextureFomNode(sourceNode, parentNode);
    }
    /** Returns the RenderTexture of the provided node.
    * @param  {cc.Node} sourceNode The node to provide RenderTexture.
    * @param  {cc.Node} parentNode The temporary parent to add the sourceNode.
    * @returns cc.RenderTexture
    */
    static renderTextureFomNode(sourceNode: Node, parentNode: Node): Promise<RenderTexture> {
        let camera = sourceNode.getComponentInChildren(Camera);
        if (!camera) {
            console.error("No Camera found in prefab. Camera should be child of Prefab only");
        }
        let renderTexture = new RenderTexture();
        const transform = sourceNode.getComponent(UITransform);
        renderTexture.initialize({ width: transform.width, height: transform.height });
        camera.targetTexture = renderTexture;

        if (!sourceNode.parent) {
            parentNode.addChild(sourceNode);
        }
        return new Promise((resolve) => {
            setTimeout(() => {
                resolve(camera.targetTexture);
                sourceNode.active = false;
                sourceNode.removeFromParent();
                sourceNode.destroy();
            }, 50)
        });
    }

    static takeScreenShotFromPrefba(prefab: Prefab, tempParentNode: Node): Promise<Texture2D> {

        let sourceNode = instantiate(prefab);

        return CanvasUtils.takeScreenShot(sourceNode, tempParentNode);
    }

    static takeScreenShot(sourceNode: Node, tempParentNode: Node): Promise<Texture2D> {
        if (!sourceNode.parent) {
            tempParentNode.addChild(sourceNode);
        }
        let camera = sourceNode.getComponentInChildren(Camera);
        if (!camera) {
            console.error("No Camera found in prefab. Camera should be child of Prefab only");
        }
        let renderTexture = new RenderTexture();
        const transform = sourceNode.getComponent(UITransform);
        renderTexture.initialize({ width: transform.width, height: transform.height });
        camera.targetTexture = renderTexture;
        return new Promise((resolve) => {
            setTimeout(() => {
                const pixels = camera.targetTexture.readPixels();
                sourceNode.active = false;
                sourceNode.removeFromParent();
                sourceNode.destroy();
                resolve(this.getTexture(pixels, transform.width, transform.height));
            }, 50);
        });
    }

    static getTexture(data: Uint8Array, width: number, height: number): Texture2D {

        let img = new ImageAsset();
        img.reset({
            _data: data, width: width, height: height, format: Texture2D.PixelFormat.RGBA8888,
            _compressed: false
        });

        let texture = new Texture2D();
        texture.image = img;
        return texture;
    }
}

