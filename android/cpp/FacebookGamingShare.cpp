#include "android/cpp/FacebookGamingShare.h"
#include "socialsdk/NativeShare.h"
#if CC_VERSION_3_X
#include "platform/java/jni/JniHelper.h"
using namespace cc;
#else
#include "platform/android/jni/JniHelper.h"
using namespace cocos2d;
#endif
namespace wrapper {
    namespace social {
        void FacebookGamingShare::shareImage(const std::string &imagePath, const std::string &caption) {
            JniHelper::callStaticVoidMethod(
                    "com/wrapper/social/facebook/FacebookGamingShare",
                    "shareImage", imagePath, caption);
        }

        void FacebookGamingShare::shareLink(ShareType shareType, const std::string &msg,
                                            const std::string &linkStr) {
            JniHelper::callStaticVoidMethod(
                    "com/wrapper/social/facebook/FacebookGamingShare",
                    "shareLink", (int) shareType, msg, linkStr);
        }


        void FacebookGamingShare::inviteAsync() {
            JniHelper::callStaticVoidMethod(
                    "com/wrapper/social/facebook/FacebookGamingShare",
                    "inviteToNewFriend");
        }
    }
}

extern "C" {
JNIEXPORT void JNICALL
Java_com_wrapper_social_facebook_FacebookGamingShare_onShareComplete(JNIEnv *env,
                                                                        jobject thiz,
                                                                        jboolean status) {
    wrapper::social::NativeShare::getInstance()->getListener()->onShareComplete(status);
}
JNIEXPORT void JNICALL
Java_com_wrapper_social_facebook_FacebookGamingShare_onShareFailed(JNIEnv *env,
                                                                      jobject thiz,
                                                                      jstring error) {
    wrapper::social::NativeShare::getInstance()->getListener()->onShareFailed(JniHelper::jstring2string(error));
}
JNIEXPORT void JNICALL
Java_com_wrapper_social_facebook_FacebookGamingShare_onContextChooseComplete(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jstring contextId) {
    wrapper::social::NativeShare::getInstance()->getListener()->onContextChooseComplete(JniHelper::jstring2string(contextId));
}
JNIEXPORT void JNICALL
Java_com_wrapper_social_facebook_FacebookGamingShare_onContextChooseFailed(JNIEnv *env,
jobject thiz,
        jstring error) {
    wrapper::social::NativeShare::getInstance()->getListener()->onContextChooseFailed(JniHelper::jstring2string(error));
}
JNIEXPORT void JNICALL
Java_com_wrapper_social_facebook_FacebookGamingShare_onContextCreateComplete(JNIEnv *env,
                                                                                jobject thiz,
                                                                                jstring contextId) {
    wrapper::social::NativeShare::getInstance()->getListener()->onContextCreateComplete(JniHelper::jstring2string(contextId));
}
JNIEXPORT void JNICALL
Java_com_wrapper_social_facebook_FacebookGamingShare_onContextCreateFailed(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jstring error) {
    wrapper::social::NativeShare::getInstance()->getListener()->onContextCreateFailed(JniHelper::jstring2string(error));
}
JNIEXPORT void JNICALL
Java_com_wrapper_social_facebook_FacebookGamingShare_onContextSwitchComplete(JNIEnv *env,
                                                                                jobject thiz) {
    wrapper::social::NativeShare::getInstance()->getListener()->onContextSwitchComplete();
}
JNIEXPORT void JNICALL
Java_com_wrapper_social_facebook_FacebookGamingShare_onContextSwitchFailed(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jstring error) {
    wrapper::social::NativeShare::getInstance()->getListener()->onContextSwitchFailed(JniHelper::jstring2string(error));
}
JNIEXPORT void JNICALL
Java_com_wrapper_social_facebook_FacebookGamingShare_onCustomUpdateSuccess(JNIEnv *env,
                                                                                jobject thiz) {
    wrapper::social::NativeShare::getInstance()->getListener()->onCustomUpdateSuccess();
}
JNIEXPORT void JNICALL
Java_com_wrapper_social_facebook_FacebookGamingShare_onCustomUpdateFailed(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jstring error) {
    wrapper::social::NativeShare::getInstance()->getListener()->onCustomUpdateFailed(JniHelper::jstring2string(error));
}
}
