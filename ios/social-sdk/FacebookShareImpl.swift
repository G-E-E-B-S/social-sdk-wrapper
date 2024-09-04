import Foundation
import UIKit
import FBSDKShareKit
class FBSharingDelegateImpl: SharingDelegate {
    func sharer(_ sharer: FBSDKShareKit.Sharing, didCompleteWithResults results: [String : Any]) {
        onShareSuccess()
    }
    func sharer(_ sharer: FBSDKShareKit.Sharing, didFailWithError error: Error) {
        onShareFailed(error.localizedDescription)
    }
    func sharerDidCancel(_ sharer: FBSDKShareKit.Sharing) {
        onShareFailed("USER_INPUT")
    }
}
@objc public class FacebookShareImpl: NSObject {
    @objc public func shareLink(linkStr: String, msg: String) {
        let content = ShareLinkContent()
        content.quote = msg;
        content.contentURL = URL.init(string: linkStr)
        let dialog = ShareDialog(viewController: getOwningViewController(), content: content, delegate: FBSharingDelegate())
        if !dialog.show() {
            onShareFailed("could not show")
        }
    }

    @objc public func messageLink(linkStr: String, msg: String) {
        let content = ShareLinkContent()
        content.quote = msg;
        content.contentURL = URL.init(string: linkStr)
        let dialog = MessageDialog.dialog(content: content, delegate: FBSharingDelegate())
        if !dialog.show() {
            onShareFailed("could not show")
        }
    }
    func getOwningViewController() -> UIViewController? {
        if var topController = UIApplication.shared.keyWindow?.rootViewController {
            while let presentedViewController = topController.presentedViewController {
                topController = presentedViewController
            }
            return topController
        }
        return nil
    }
}
