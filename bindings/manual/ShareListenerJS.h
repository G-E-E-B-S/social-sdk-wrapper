#ifndef SOCIAL_SDK_SHARE_LISTENER_JS_H
#define SOCIAL_SDK_SHARE_LISTENER_JS_H

#include "include/JSListenerBase.h"
#include "socialsdk/NativeShare.h"
#include <string>
namespace wrapper {
    namespace social {
        class ShareListenerJS : public IShareListenerJS, public wrapper::jsbhelper::JSListenerBase {
        public:
            bool onShareComplete(bool status);

            bool onShareFailed(const std::string &error);

            bool onInviteLinkFetchComplete(const std::string &payload);

            bool onInviteLinkFetchError(const std::string &error);

            bool onContextChooseComplete(const std::string &contextId);

            bool onContextChooseFailed(const std::string &error);

            bool onContextCreateComplete(const std::string &contextId);

            bool onContextCreateFailed(const std::string &error);

            bool onContextSwitchComplete();

            bool onContextSwitchFailed(const std::string &error);

            bool onCustomUpdateSuccess();

            bool onCustomUpdateFailed(const std::string &error);
        };
    }
}
#endif // SOCIAL_SDK_SHARE_LISTENER_JS_H
