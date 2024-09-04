#ifndef FACEBOOK_SHARE
#define FACEBOOK_SHARE

#include <string>
namespace wrapper {
    namespace social {
        class FacebookShare {
        public:
            static void shareLink(const std::string &msg, const std::string &linkStr);

            static void messageLink(const std::string &msg, const std::string &linkStr);

            static void shareImage(const std::string &imgstr);
        };
    }
}

#endif

