#include "NativeShare.h"
#import <social_sdk/social_sdk-Swift.h>

#import <UIKit/UIKit.h>
namespace wrapper {
    namespace social {
        namespace {
        FacebookShareImpl* s_fbShareDelegate = nil;
        FacebookGamingShareImpl* s_fbGamingShareDelegate = nil;
        }
        std::unique_ptr<NativeShare> NativeShare::_instance;
        NativeShare::NativeShare() {
            if (s_fbShareDelegate == nil) {
                s_fbShareDelegate = [[FacebookShareImpl alloc] init];
            }
            if (s_fbGamingShareDelegate == nil) {
                s_fbGamingShareDelegate = [[FacebookGamingShareImpl alloc] init];
            }
        }
        NativeShare::~NativeShare() = default;
        void NativeShare::shareImage(AuthMethod authMethod, const std::string& imageFullPath, const std::string& titleMsg, const std::string& shareMsg)
        {
            if (authMethod == AuthMethod::FACEBOOK_GAMING_LOGIN) {
                [s_fbGamingShareDelegate shareImageWithImagePath:[NSString stringWithUTF8String:imageFullPath.c_str()] caption:[NSString stringWithUTF8String:titleMsg.c_str()]];
            } else {
                NSString *pathNsStr = [NSString stringWithCString:imageFullPath.c_str()
                                                        encoding:NSUTF8StringEncoding];
                NSString *shareMsgNsStr = [NSString stringWithCString:shareMsg.c_str()
                                                            encoding:NSUTF8StringEncoding];
                NSString *titleNsStr = [NSString stringWithCString:titleMsg.c_str()
                                                        encoding:NSUTF8StringEncoding];
                UIImage *image = [[UIImage alloc] initWithContentsOfFile:pathNsStr];
                NSArray *objectsToShare = @[shareMsgNsStr, image];
                UIActivityViewController *activityVC = [[UIActivityViewController alloc] initWithActivityItems:objectsToShare applicationActivities:nil];
                UIViewController *objViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
                CGRect rect = objViewController.view.bounds;
                rect.origin.x = objViewController.view.bounds.size.width / 2;
                rect.origin.y = objViewController.view.bounds.size.height / 2;
                activityVC.popoverPresentationController.sourceView = objViewController.view;
                activityVC.popoverPresentationController.sourceRect = rect;
                [objViewController presentViewController:activityVC animated:true completion:^() {
                    getListener()->onShareComplete(true);
                }];
            }
        }

        void NativeShare::shareLink(AuthMethod authMethod, const std::string& msg, const std::string& link)
        {
            NSString* msgStr = [NSString stringWithUTF8String:msg.c_str()];
            NSString* linkStr = [NSString stringWithUTF8String:link.c_str()];
            if (authMethod == AuthMethod::FACEBOOK_CLASSIC) {
                [s_fbShareDelegate shareLinkWithLinkStr:linkStr msg:msgStr];
            } else if (authMethod == AuthMethod::FACEBOOK_GAMING_LOGIN) {
                [s_fbGamingShareDelegate shareLinkWithShareType:ShareTypeShareTypeNewFriend msg:msgStr linkStr:linkStr];
            } else {
                NSArray *objectsToShare = @[linkStr];
                UIActivityViewController *activityVC = [[UIActivityViewController alloc] initWithActivityItems:objectsToShare applicationActivities:nil];
                UIViewController *objViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
                CGRect rect = objViewController.view.bounds;
                rect.origin.x = objViewController.view.bounds.size.width / 2;
                rect.origin.y = objViewController.view.bounds.size.height / 2;
                activityVC.popoverPresentationController.sourceView = objViewController.view;
                activityVC.popoverPresentationController.sourceRect = rect;
                
                [objViewController presentViewController:activityVC animated:true completion:nil];
            }
        }
        void NativeShare::chooseContext() {
            [s_fbGamingShareDelegate chooseContext];
        }
        void NativeShare::createContext(const std::string &playerId) {
            [s_fbGamingShareDelegate createContextWithPlayerId:[NSString stringWithUTF8String:playerId.c_str()]];
        }

        void NativeShare::switchContext(const std::string &contextId) {
            [s_fbGamingShareDelegate switchContextWithContextId:[NSString stringWithUTF8String:contextId.c_str()]];
        }

        void NativeShare::updateAsync(const std::string& text, const std::string& cta, const std::string& imagePath, const std::string& data) {
            [s_fbGamingShareDelegate
            updateAsyncWithMessage:[NSString stringWithUTF8String:text.c_str()]
            cta:[NSString stringWithUTF8String:cta.c_str()]
            imagePath:[NSString stringWithUTF8String:imagePath.c_str()]
            payload:[NSString stringWithUTF8String:data.c_str()]];
        }
        void NativeShare::getEntryPointData() {
            getListener()->onInviteLinkFetchComplete("");
        }
        void NativeShare::inviteAsync() {
            [s_fbGamingShareDelegate inviteNewFriend];
        }
    }
}
