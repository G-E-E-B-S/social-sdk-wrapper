import Foundation
import UIKit
import FBSDKShareKit
import FBSDKGamingServicesKit
import os.log

@objc public enum ShareType: Int {
    case ShareTypeNewFriend,
         ShareTypeInGameFriend
}
class ChooseContextDelegate: ContextDialogDelegate {
    func contextDialogDidComplete(_ contextDialog: FBSDKGamingServicesKit.ContextWebDialog) {
        onContextChooseComplete(GamingContext.current?.identifier);
    }
    func contextDialog(_ contextDialog: FBSDKGamingServicesKit.ContextWebDialog, didFailWithError error: Error) {
        onContextChooseFailed(error.localizedDescription)
    }
    func contextDialogDidCancel(_ contextDialog: FBSDKGamingServicesKit.ContextWebDialog) {
        onContextChooseFailed("USER_INPUT")
    }
}
class CreateContextDelegate: ContextDialogDelegate {
    func contextDialogDidComplete(_ contextDialog: FBSDKGamingServicesKit.ContextWebDialog) {
        onContextCreateComplete(GamingContext.current?.identifier)
    }
    func contextDialog(_ contextDialog: FBSDKGamingServicesKit.ContextWebDialog, didFailWithError error: Error) {
        onContextCreateFailed(error.localizedDescription)
    }
    func contextDialogDidCancel(_ contextDialog: FBSDKGamingServicesKit.ContextWebDialog) {
        onContextCreateFailed("USER_INPUT")
    }
}
class SwitchContextDelegate: ContextDialogDelegate {
    func contextDialogDidComplete(_ contextDialog: FBSDKGamingServicesKit.ContextWebDialog) {
        onContextSwitchComplete()
    }
    func contextDialog(_ contextDialog: FBSDKGamingServicesKit.ContextWebDialog, didFailWithError error: Error) {
        onContextSwitchFailed(error.localizedDescription)
    }
    func contextDialogDidCancel(_ contextDialog: FBSDKGamingServicesKit.ContextWebDialog) {
        onContextSwitchFailed("USER_INPUT")
    }
}
class RequestDialogDelegate : GameRequestDialogDelegate {
    func gameRequestDialog(_ gameRequestDialog: FBSDKGamingServicesKit.GameRequestDialog, didCompleteWithResults results: [String : Any]) {
        // TODO:
    }
    func gameRequestDialog(_ gameRequestDialog: FBSDKGamingServicesKit.GameRequestDialog, didFailWithError error: Error) {
        // TODO:
    }
    func gameRequestDialogDidCancel(_ gameRequestDialog: FBSDKGamingServicesKit.GameRequestDialog) {
        // TODO:
    }
}
class FBSharingDelegate: SharingDelegate {
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
@objc public class FacebookGamingShareImpl: NSObject {
    @objc public func shareImage(imagePath: String, caption: String) {
        if let image = UIImage.init(contentsOfFile: imagePath) {
            let config = GamingImageUploaderConfiguration(image: image, caption: caption, shouldLaunchMediaDialog: true);
            GamingImageUploader.uploadImage(with: config) { success, result, error in
                if (error != nil) {
                    os_log("Failed to upload Image, error: %@", error! as CVarArg);
                    onShareFailed(error?.localizedDescription)
                } else {
                    os_log("Image Upload Complete");
                    onShareSuccess()
                }
            }
        } else {
            onShareFailed(String(format:"%@ %s", "Image not found on path", imagePath))
        }
    }
    @objc public func shareLink(shareType: ShareType, msg: String, linkStr: String) {
        let link = ShareLinkContent.init()
        link.contentURL = URL.init(string: linkStr)
        link.quote = msg
        ShareDialog.show(viewController: getOwningViewController(), content: link, delegate: FBSharingDelegate())
    }
    @objc public func chooseContext() {
        ContextDialogPresenter().makeAndShowChooseContextDialog(content: ChooseContextContent(), delegate: ChooseContextDelegate())
    }
    @objc public func createContext(playerId: String) {
        do {
            try ContextDialogPresenter().makeAndShowCreateContextDialog(content: CreateContextContent(playerID: playerId), delegate: CreateContextDelegate())
        } catch {
            onContextCreateFailed(error.localizedDescription)
        }
    }
    @objc public func switchContext(contextId: String) {
        do {
            try ContextDialogPresenter().makeAndShowSwitchContextDialog(content: SwitchContextContent(contextID: contextId), delegate: SwitchContextDelegate())
        } catch {
            onContextSwitchFailed(error.localizedDescription)
        }
    }
    @objc public func updateAsync(message: String, cta: String, imagePath: String, payload: String) {
        if let image = UIImage.init(contentsOfFile: imagePath) {
            do {
                try CustomUpdateGraphRequest().request(content: CustomUpdateContentImage(message: message, image: image, cta: cta, payload: payload)) {result in
                    // TODO:
                }
            } catch {
                // TODO:
            }
        } else {
            // TODO:
        }
    }
    @objc public func inviteNewFriend() {
        FriendFinderDialog.launch { success, error in
            if error != nil {
                os_log("Failed to find friend, error: %@", type: .error, error! as CVarArg)
            } else {
                os_log("inviteNewFriend Complete %@", success)
            }
        }
    }
    func inviteInGameFriend() {
        GameRequestDialog.show(content: GameRequestContent.init(), delegate: RequestDialogDelegate())
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
