#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "FirebaseDynamicLinks.h"
#include "platform/android/jni/JniHelper.h"
#include <string>

void FirebaseDynamicLinks::shareLink(std::string linkStr) {
    cocos2d::JniHelper::callStaticVoidMethod(
            "com/wrapper/payload/FirebaseDynamicLinks",
            "shareLink", linkStr);
}
#endif

