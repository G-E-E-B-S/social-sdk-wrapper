#include "socialsdk/NativeShare.h"
#include "socialsdk/FacebookShare.h"
#include "FacebookGamingShare.h"

#if CC_VERSION_3_X
#include "platform/java/jni/JniHelper.h"
using namespace cc;
#else
#include "platform/android/jni/JniHelper.h"
using namespace cocos2d;
#endif


namespace wrapper {
    namespace social {
        namespace {
            FacebookGamingShare *sGamingShare = nullptr;
            FacebookShare *sFacebookShare = nullptr;
        }
        std::unique_ptr<NativeShare> NativeShare::_instance;
        NativeShare::NativeShare() {
            if (sGamingShare == nullptr) {
                sGamingShare = new FacebookGamingShare();
            }
            if (sFacebookShare == nullptr) {
                sFacebookShare = new FacebookShare();
            }
        }

        NativeShare::~NativeShare() = default;

        void NativeShare::shareImage(AuthMethod authMethod, const std::string &imageFullPath,
                                     const std::string &titleMsg,
                                     const std::string &shareMsg) {
            if (authMethod == AuthMethod::FACEBOOK_GAMING_LOGIN) {
                sGamingShare->shareImage(imageFullPath, titleMsg);
            } else {
                JniHelper::callStaticVoidMethod("com/wrapper/social/NativeShare",
                                                "shareImage", imageFullPath, shareMsg, titleMsg);
            }
        }

        void NativeShare::inviteAsync() {
            sGamingShare->inviteAsync();
        }

        void NativeShare::shareLink(AuthMethod authMethod, const std::string &msg,
                                    const std::string &linkStr) {
            // TODO: fixme
            std::string shareLink = msg + linkStr;
            if (authMethod == AuthMethod::FACEBOOK_CLASSIC) {
                sFacebookShare->shareLink(msg, linkStr);
            } else if (authMethod == AuthMethod::FACEBOOK_GAMING_LOGIN) {
                sGamingShare->shareLink(ShareType::NewFriend, msg, linkStr);
            } else {
                JniHelper::callStaticVoidMethod("com/wrapper/social/NativeShare",
                                                "shareLink", shareLink);
            }
        }

        void NativeShare::updateAsync(const std::string &text,
                                      const std::string &cta,
                                      const std::string &imagePath,
                                      const std::string &data) {
            JniHelper::callStaticVoidMethod("com/wrapper/social/facebook/FacebookGamingShare",
                                            "updateAsync", text, cta, imagePath, data);
        }

        void NativeShare::chooseContext() {
            JniHelper::callStaticVoidMethod("com/wrapper/social/facebook/FacebookGamingShare",
                                            "chooseContext");
        }

        void NativeShare::createContext(const std::string &playerId) {
            JniHelper::callStaticVoidMethod("com/wrapper/social/facebook/FacebookGamingShare",
                                            "createContext", playerId);
        }

        void NativeShare::switchContext(const std::string &contextId) {
            JniHelper::callStaticVoidMethod("com/wrapper/social/facebook/FacebookGamingShare",
                                            "switchContext", contextId);
        }

        void NativeShare::getEntryPointData() {
            JniHelper::callStaticVoidMethod("com/wrapper/payload/SingularLinkController",
                                            "getLinkPayLoad");
        }

        extern "C" {
        JNIEXPORT void JNICALL
        Java_com_wrapper_social_NativeShare_onShareComplete(JNIEnv *env,
                                                               jobject thiz,
                                                               jboolean status) {
            NativeShare::getInstance()->getListener()->onShareComplete(status);
        }
        JNIEXPORT void JNICALL
        Java_com_wrapper_social_NativeShare_onShareFailed(JNIEnv *env,
                                                             jobject thiz,
                                                             jstring error) {
            NativeShare::getInstance()->getListener()->onShareFailed(
                    JniHelper::jstring2string(error));
        }

        JNIEXPORT void JNICALL
        Java_com_wrapper_payload_SingularLinkController_onInviteLinkFetchComplete(JNIEnv *env,
                                                                                     jobject thiz,
                                                                                     jstring payload) {
            NativeShare::getInstance()->getListener()->onInviteLinkFetchComplete(
                    JniHelper::jstring2string(payload));
        }

        JNIEXPORT void JNICALL
        Java_com_wrapper_payload_SingularLinkController_onInviteLinkFetchError(JNIEnv *env,
                                                                                  jobject thiz,
                                                                                  jstring error) {
            NativeShare::getInstance()->getListener()->onInviteLinkFetchError(
                    JniHelper::jstring2string(error));
        }
        }
    }
}
