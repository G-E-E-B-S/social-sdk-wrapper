#include "socialsdk/FacebookShare.h"
#include "socialsdk/NativeShare.h"
#include "socialsdk/IShareListenerJS.h"
#if CC_VERSION_3_X
#include "platform/java/jni/JniHelper.h"
using namespace cc;
#else
#include "platform/android/jni/JniHelper.h"
using namespace cocos2d;
#endif
namespace wrapper {
    namespace social {
        void FacebookShare::shareLink(const std::string &msg, const std::string &linkStr) {
            JniHelper::callStaticVoidMethod(
                    "com/wrapper/social/facebook/FacebookShare",
                    "shareLink", msg, linkStr);
        }

        void FacebookShare::messageLink(const std::string &msg, const std::string &linkStr) {
            JniHelper::callStaticVoidMethod(
                    "com/wrapper/social/facebook/FacebookShare",
                    "messageLink", msg, linkStr);
        }

        void FacebookShare::shareImage(const std::string &imgstr) {
            JniHelper::callStaticVoidMethod(
                    "com/wrapper/social/facebook/FacebookShare",
                    "shareScoreImage", imgstr);
        }
    }
}

extern "C" {
JNIEXPORT void JNICALL
Java_com_wrapper_social_facebook_FacebookShare_onShareComplete(JNIEnv *env,
                                                       jobject thiz,
                                                       jboolean status) {
    wrapper::social::NativeShare::getInstance()->getListener()->onShareComplete(status);
}
JNIEXPORT void JNICALL
Java_com_wrapper_social_facebook_FacebookShare_onShareFailed(JNIEnv *env,
                                                     jobject thiz,
                                                     jstring error) {
    wrapper::social::NativeShare::getInstance()->getListener()->onShareFailed(JniHelper::jstring2string(error));
}
}
