#ifndef FirebaseDynamicLinksReceiver_h
#define FirebaseDynamicLinksReceiver_h
#include <memory>
#include <queue>
#include <string>
#include "firebase/dynamic_links.h"
#include "include/JSListenerBase.h"


class FirebaseDynamicLinksReceiver : public firebase::dynamic_links::Listener, public wrapper::jsbhelper::JSListenerBase
{
public:
    static void init() {
        _initialized = true;
    }
    static bool isInitialized() {
        return _initialized;
    }
    static FirebaseDynamicLinksReceiver* getInstance() {
        if (_instance.get() == nullptr) {
            _instance.reset(new FirebaseDynamicLinksReceiver());
        }
        return _instance.get();
    }
    void OnDynamicLinkReceived(const firebase::dynamic_links::DynamicLink* dynamic_link) override;
    void consumeDeepLinks();
    void passMessageToJs(const std::string dynamicLink);
    void passMessageToJsOnGLThread(const std::string dynamicLink);
    void queueMessage(const std::string dynamicLink);
private:
    void onLinkReceived(const std::string dynamicLink);
    std::queue<std::string> _deepLinkQueue;
    FirebaseDynamicLinksReceiver() {};
    static std::unique_ptr<FirebaseDynamicLinksReceiver> _instance;
    static bool _initialized;
};

#endif /* FirebaseDynamicLinksReceiver_h */
