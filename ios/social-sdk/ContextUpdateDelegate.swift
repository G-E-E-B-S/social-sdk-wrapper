import Foundation
import FBSDKGamingServicesKit
import UIKit

@objc public class ContextUpdateDelegate: NSObject {
    @objc static public func sendUpdate(message: String, cta: String, payload: String, image: UIImage) {
        let request = CustomUpdateGraphRequest();
        do {
            try request.request(content: CustomUpdateContentImage(message: message, image: image, cta: cta, payload: payload)) { result in
                switch result {
                case .success(let status):
                    // TODO: handle success
                    print("ContextUpdateDelegate:sendUpdate success: \(status)");
                    break;
                case .failure(let error):
                    print("ContextUpdateDelegate:sendUpdate got error: \(error)");
                    // TODO: handle failure
                    break;
                }
            }
        } catch {
            // TODO: send feedback to caller
            print("ContextUpdateDelegate:sendUpdate Caught error: \(error)");
        }
    }
}
