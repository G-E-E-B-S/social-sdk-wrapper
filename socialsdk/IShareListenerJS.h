#ifndef SOCIAL_SDK_ISHARELISTENERJS_H
#define SOCIAL_SDK_ISHARELISTENERJS_H
#include <string>
namespace wrapper {
    namespace social {
        class IShareListenerJS {
        public:
            virtual ~IShareListenerJS() {}
            virtual bool onShareComplete(bool status) = 0;
            virtual bool onShareFailed(const std::string& error) = 0;
            virtual bool onInviteLinkFetchComplete(const std::string& payload) = 0;
            virtual bool onInviteLinkFetchError(const std::string& error) = 0;
            virtual bool onContextChooseComplete(const std::string& contextId) = 0;
            virtual bool onContextChooseFailed(const std::string& error) = 0;
            virtual bool onContextCreateComplete(const std::string& contextId) = 0;
            virtual bool onContextCreateFailed(const std::string& error) = 0;
            virtual bool onContextSwitchComplete() = 0;
            virtual bool onContextSwitchFailed(const std::string& error) = 0;
            virtual bool onCustomUpdateSuccess() = 0;
            virtual bool onCustomUpdateFailed(const std::string& error) = 0;
        };
    }
}
#endif //SOCIAL_SDK_ISHARELISTENERJS_H