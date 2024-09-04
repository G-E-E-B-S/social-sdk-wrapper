#include "FacebookShare.h"
#include <string>
#import <social_sdk/social_sdk-Swift.h>
namespace wrapper {
    namespace social {
        namespace {
            FacebookShareImpl* s_fbShareDelegate = [[FacebookShareImpl alloc] init];
        }

        void FacebookShare::shareLink(const std::string& msg, const std::string &linkStr)
        {
            NSString *linkNsStr = [NSString stringWithCString:linkStr.c_str()
                                                    encoding:NSUTF8StringEncoding];
            NSString* msgStr = [NSString stringWithCString:msg.c_str()
                                                encoding:NSUTF8StringEncoding];
            [s_fbShareDelegate shareLinkWithLinkStr:linkNsStr msg:msgStr];
        }

        void FacebookShare::messageLink(const std::string& msg, const std::string &linkStr)
        {
            NSString *linkNsStr = [NSString stringWithCString:linkStr.c_str()
                                                    encoding:NSUTF8StringEncoding];
            NSString* msgStr = [NSString stringWithCString:msg.c_str()
                                                encoding:NSUTF8StringEncoding];
            [s_fbShareDelegate messageLinkWithLinkStr:linkNsStr msg:msgStr];
        }
        void FacebookShare::shareImage(const std::string& imgstr) {
            // TODO:
        }
    }
}
