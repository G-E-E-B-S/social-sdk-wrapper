#include "FirebaseDynamicLinksReceiver.h"
#include "FirebaseDynamicLinksUtils.h"
#include "logger/log.h"
#include "network/Uri.h"

#if IS_ANDROID
#if CC_VERSION_3_X
#include "platform/java/jni/JniHelper.h"
using namespace cc;
#else
#include "platform/android/jni/JniHelper.h"
using namespace cocos2d;
#endif
#endif

// TODO: fix thread safety of this.
std::unique_ptr<FirebaseDynamicLinksReceiver> FirebaseDynamicLinksReceiver::_instance = std::unique_ptr<FirebaseDynamicLinksReceiver>(nullptr);
bool FirebaseDynamicLinksReceiver::_initialized = false;

void FirebaseDynamicLinksReceiver::OnDynamicLinkReceived(const firebase::dynamic_links::DynamicLink* dynamicLink) {
    auto url = dynamicLink->url;
    logger::log("Cpp Firebase dynamic link received: %s", url.c_str());
    passMessageToJs(url);
#if IS_ANDROID
    JniHelper::callStaticVoidMethod(
            "org/cocos2dx/javascript/AppActivity",
            "nullIntent");
#endif
}

// NOTE: this function is not thread safe, should be called from GL thread.
void FirebaseDynamicLinksReceiver::consumeDeepLinks() {
    logger::log("FirebaseDynamicLinksReceiver:consumeDeepLinks: %d", _deepLinkQueue.size());
    while (!_deepLinkQueue.empty()) {
        auto deepLink = _deepLinkQueue.front();
        _deepLinkQueue.pop();
        // TODO: needs to be moved to JSListener Base
        logger::log("no dynamic link receiver, ignoring message");
    }
}

void FirebaseDynamicLinksReceiver::passMessageToJs(const std::string dynamicLink)
{
    RUN_ON_MAIN_THREAD_BEGIN
    this->passMessageToJsOnGLThread(dynamicLink);
    RUN_ON_MAIN_THREAD_END
}
void FirebaseDynamicLinksReceiver::passMessageToJsOnGLThread(const std::string dynamicLink) {
    // TODO: needs to be moved to JSListener Base
    if (_JSDelegate.isObject()) {
        onLinkReceived(dynamicLink);
    } else {
        queueMessage(dynamicLink);
    }
}
// NOTE: this function is not thread safe, should be called from GL thread.
void FirebaseDynamicLinksReceiver::queueMessage(const std::string dynamicLink)
{
    _deepLinkQueue.push(dynamicLink);

}

void FirebaseDynamicLinksReceiver::onLinkReceived(const std::string dynamicLink) {
    logger::log("Cpp Firebase dynamic link received");
    auto funcName = __FUNCTION__;
    se::ValueArray args;
    args.push_back(se::Value(dynamicLink));
    invokeJSFunNow(funcName, args);
}
#if IS_ANDROID
extern "C" {
JNIEXPORT void JNICALL
Java_org_cocos2dx_javascript_AppActivity_handleDynamicLink(JNIEnv *env, jobject obj, jstring jstr) {
    const std::string uri = JniHelper::jstring2string(jstr);
    FirebaseDynamicLinksReceiver::getInstance()->passMessageToJs(uri);
}
JNIEXPORT void JNICALL
Java_org_cocos2dx_javascript_AppActivity_queueDynamicLink(JNIEnv *env, jobject obj, jstring jstr) {
    const std::string uri = JniHelper::jstring2string(jstr);
    FirebaseDynamicLinksReceiver::getInstance()->queueMessage(uri);
}
}
#endif
