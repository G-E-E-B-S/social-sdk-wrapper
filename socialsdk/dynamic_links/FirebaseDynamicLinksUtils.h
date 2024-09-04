
#ifndef FirebaseDynamicLinksUtils_h
#define FirebaseDynamicLinksUtils_h

#include <map>
#include <vector>
#include <string>
//#include "firebase/dynamic_links/components.h"

typedef std::vector<std::pair<std::string, std::string>> KeyValType;

class FirebaseDynamicLinksUtils
{
public:
    static void init(const std::string &androidPackage,
                     const std::string &iosPackage,
                     const std::string &iosStoreId,
                     const std::string &subdomainLink)
    {
        FirebaseDynamicLinksUtils::androidPackage = androidPackage;
        FirebaseDynamicLinksUtils::iosPackage = iosPackage;
        FirebaseDynamicLinksUtils::iosStoreID = iosStoreID;
        FirebaseDynamicLinksUtils::subdomainLink = subdomainLink;
    }
    static void shareLongLink(const std::string &deepLink,
                                     const std::string &title,
                                     const std::string &description,
                                     const std::string &imgUrl);
    
    static void shareShortLink(const std::string &deepLink,
                               const std::string &title,
                               const std::string &description,
                               const std::string &imgUrl,
                               const bool onFB);
    static void messageShortLink(const std::string &deepLink,
                                const std::string &title,
                                const std::string &description,
                                const std::string &imgUrl);
    static std::string getParamFromLink(const std::string &link, const std::string &param);
    static std::map<std::string, std::string> getParamsFromLink(const std::string &link);
    static std::string getDeepLinkWithParams(const std::string &deepLink, std::map<std::string, std::string> params);
    static void Fetch();
private:
    static std::string generateLongLink(const std::string &deepLink,
                                        const std::string &title,
                                        const std::string &description,
                                        const std::string &imgUrl);
    static std::string androidPackage;
    static std::string iosPackage;
    static std::string iosStoreID;
    static std::string subdomainLink;
};

#endif /* FirebaseDynamicLinksUtils_h */
