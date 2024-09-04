#ifndef SOCIAL_SDK_FACEBOOK_GAMING_SHARE_H
#define SOCIAL_SDK_FACEBOOK_GAMING_SHARE_H

#include <string>
namespace wrapper {
    namespace social {
        enum ShareType {
            NewFriend,
            InGameFriend,
        };

        class FacebookGamingShare {
        public:
            FacebookGamingShare() {};

            ~FacebookGamingShare() {};

            void shareImage(const std::string &imagePath, const std::string &caption);

            void shareLink(ShareType shareType, const std::string &msg, const std::string &linkStr);

            void inviteAsync();

        private:
            /* data */
        };
    }
}


#endif /* SOCIAL_SDK_FACEBOOK_GAMING_SHARE_H */
