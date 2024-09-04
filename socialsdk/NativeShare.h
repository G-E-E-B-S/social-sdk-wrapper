#ifndef SOCIAL_SDK_NATIVE_SHARE_H
#define SOCIAL_SDK_NATIVE_SHARE_H
#include <string>
#include "socialsdk/IShareListenerJS.h"
namespace wrapper {
    namespace social {
        enum AuthMethod {
            NON_FACEBOOK,
            FACEBOOK_CLASSIC,
            FACEBOOK_GAMING_LOGIN,
        };

        class NativeShare {
        public:
            static void init() {
                _instance.reset(new NativeShare());
            }

            static NativeShare *getInstance() {
                return _instance.get();
            }

            IShareListenerJS *getListener() {
                return _listener.get();
            };

            void setListener(IShareListenerJS *listener) {
                _listener.reset(listener);
            }

            NativeShare();

            ~NativeShare();

            void shareImage(AuthMethod authMethod, const std::string &imageFullPath,
                            const std::string &titleMsg, const std::string &shareMsg);

            void
            shareLink(AuthMethod authMethod, const std::string &msg, const std::string &linkStr);

            void updateAsync(const std::string &text, const std::string &cta,
                             const std::string &imagePath, const std::string &data);

            void inviteAsync();

            void chooseContext();

            void createContext(const std::string &playerId);

            void switchContext(const std::string &contextId);

            void getEntryPointData();

        private:
            std::unique_ptr<IShareListenerJS> _listener;
            static std::unique_ptr<NativeShare> _instance;
        };
    }
}

#endif /* SOCIAL_SDK_NATIVE_SHARE_H */

