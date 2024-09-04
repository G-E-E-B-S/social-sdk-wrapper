#include "FirebaseDynamicLinksUtils.h"
#include "network/Uri.h"
#include "external/firebase/future.h"
#include "external/firebase/dynamic_links.h"
#include "external/firebase/dynamic_links/components.h"
#include "logger/log.h"
#include "FirebaseDynamicLinks.h"
#include "socialsdk/FacebookShare.h"
#if CC_VERSION_3_X
using namespace cc;
#else
using namespace cocos2d;
#endif

using namespace wrapper::social;
std::string FirebaseDynamicLinksUtils::androidPackage;
std::string FirebaseDynamicLinksUtils::iosPackage;
std::string FirebaseDynamicLinksUtils::iosStoreID;
std::string FirebaseDynamicLinksUtils::subdomainLink;

void FirebaseDynamicLinksUtils::shareLongLink(const std::string &deepLink,
                                 const std::string &title,
                                 const std::string &description,
                                 const std::string &imgUrl)
{
    auto link = generateLongLink(deepLink, title, description, imgUrl);
    FirebaseDynamicLinks::shareLink(link);
}
std::string FirebaseDynamicLinksUtils::generateLongLink(const std::string &deepLink,
                                                        const std::string &title,
                                                        const std::string &description,
                                                        const std::string &imgUrl)
{
    firebase::dynamic_links::DynamicLinkComponents components(deepLink.c_str(), subdomainLink.c_str());
    firebase::dynamic_links::AndroidParameters androidParams(FirebaseDynamicLinksUtils::androidPackage.c_str());
    firebase::dynamic_links::IOSParameters iosParams(FirebaseDynamicLinksUtils::iosPackage.c_str());
    iosParams.app_store_id = FirebaseDynamicLinksUtils::iosStoreID.c_str();
    iosParams.bundle_id = FirebaseDynamicLinksUtils::iosPackage.c_str();
    iosParams.fallback_url = "https://itunes.apple.com/us/app/card-party-fun-party-game/id1403007373?mt=8";
    components.android_parameters = &androidParams;
    components.ios_parameters = &iosParams;
    firebase::dynamic_links::SocialMetaTagParameters socialParams;
    if (title.size() > 0) {
        socialParams.title = title.c_str();
    }
    if (description.size() > 0) {
        socialParams.description = description.c_str();
    }
    if (imgUrl.size() > 0) {
        socialParams.image_url = imgUrl.c_str();
    }
    components.social_meta_tag_parameters = &socialParams;
    firebase::dynamic_links::GeneratedDynamicLink longLink =
        firebase::dynamic_links::GetLongLink(components);
    return longLink.url;
}

void OnShortLinkCompletion(const firebase::Future<firebase::dynamic_links::GeneratedDynamicLink>& result,
                           void* user_data)
{
	if (result.status() == firebase::kFutureStatusComplete) {
		if (result.error() == firebase::dynamic_links::kErrorCodeSuccess) {
			firebase::dynamic_links::GeneratedDynamicLink link = *result.result();
			wrapper::log("Create short link succeeded: %s, now sharing...", link.url.c_str());
			FirebaseDynamicLinks::shareLink(link.url);
		} else {
            wrapper::log("Create short link failed with error '%s'", result.error_message());
		}
	}
}
void OnShortLinkForMsgCompletion(const firebase::Future<firebase::dynamic_links::GeneratedDynamicLink>& result,
                                 void* user_data)
{
    if (result.status() == firebase::kFutureStatusComplete) {
        if (result.error() == firebase::dynamic_links::kErrorCodeSuccess) {
            firebase::dynamic_links::GeneratedDynamicLink link = *result.result();
            wrapper::log("Create short link succeeded: %s, now sharing...", link.url.c_str());
            FacebookShare::shareLink("", link.url);
        } else {
            wrapper::log("Create short link failed with error '%s'", result.error_message());
        }
    }
}
void OnShortLinkForFBCompletion(const firebase::Future<firebase::dynamic_links::GeneratedDynamicLink>& result,
                                      void* user_data)
{
    if (result.status() == firebase::kFutureStatusComplete) {
        if (result.error() == firebase::dynamic_links::kErrorCodeSuccess) {
            firebase::dynamic_links::GeneratedDynamicLink link = *result.result();
            wrapper::log("Create short link succeeded: %s, now sharing...", link.url.c_str());
            FacebookShare::shareLink("", link.url);
        } else {
            wrapper::log("Create short link failed with error '%s'", result.error_message());
        }
    }
}

void FirebaseDynamicLinksUtils::shareShortLink(const std::string &deepLink,
                                               const std::string &title,
                                               const std::string &description,
                                               const std::string &imgUrl,
                                               const bool onFB=false)
{
    std::string longLink = FirebaseDynamicLinksUtils::generateLongLink(deepLink,
                                                                       title,
                                                                       description,
                                                                       imgUrl);
    firebase::dynamic_links::DynamicLinkOptions shortLinkOptions;
    shortLinkOptions.path_length = firebase::dynamic_links::kPathLengthShort;
	firebase::Future<firebase::dynamic_links::GeneratedDynamicLink> future = firebase::dynamic_links::GetShortLink(longLink.c_str(), shortLinkOptions);
    if (onFB) {
        future.OnCompletion(OnShortLinkForFBCompletion, nullptr);
        return;
    }
    future.OnCompletion(OnShortLinkCompletion, nullptr);
}
void FirebaseDynamicLinksUtils::messageShortLink(const std::string &deepLink,
                                                 const std::string &title,
                                                 const std::string &description,
                                                 const std::string &imgUrl)
{
    std::string longLink = FirebaseDynamicLinksUtils::generateLongLink(deepLink,
                                                                       title,
                                                                       description,
                                                                       imgUrl);
    firebase::dynamic_links::DynamicLinkOptions shortLinkOptions;
    shortLinkOptions.path_length = firebase::dynamic_links::kPathLengthShort;
    firebase::Future<firebase::dynamic_links::GeneratedDynamicLink> future = firebase::dynamic_links::GetShortLink(longLink.c_str(), shortLinkOptions);
    future.OnCompletion(OnShortLinkForMsgCompletion, nullptr);
}

std::string FirebaseDynamicLinksUtils::getParamFromLink(const std::string &link, const std::string &param)
{
	network::Uri uri = network::Uri::parse(link);
	KeyValType params = uri.getQueryParams();
	for (auto iter = params.begin(); iter != params.end(); iter++) {
		if (iter->first == param) {
			return iter->second;
		}
    }
    return "";
}

std::string FirebaseDynamicLinksUtils::getDeepLinkWithParams(const std::string &deepLink, std::map<std::string, std::string> params)
{
    std::string paramStr = "";
    std::string sep = "?";
    for (auto iter = params.begin(); iter != params.end(); iter++) {
        paramStr += sep + iter->first + "=" + iter->second;
        sep = "&";
    }
    return deepLink + paramStr;
}

std::map<std::string, std::string>
FirebaseDynamicLinksUtils::getParamsFromLink(const std::string &link)
{
    network::Uri uri = network::Uri::parse(link);
    std::map<std::string, std::string> result;
    auto params = uri.getQueryParams();
    for (auto param : params) {
        result[param.first] = param.second;
    }
    return result;
}

void
FirebaseDynamicLinksUtils::Fetch()
{
    firebase::dynamic_links::Fetch();
}

