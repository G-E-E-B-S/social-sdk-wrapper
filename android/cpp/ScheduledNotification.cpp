#include "socialsdk/ScheduledNotification.h"
#if CC_VERSION_3_X
#include "platform/java/jni/JniHelper.h"
using namespace cc;
#else
#include "platform/android/jni/JniHelper.h"
using namespace cocos2d;
#endif

using namespace std;
namespace wrapper
{
    namespace social
    {
        void ScheduledNotification::init()
        {
            // NO-op
        }
        bool ScheduledNotification::requestGranted()
        {
            return JniHelper::callStaticBooleanMethod(
                "com/wrapper/notification/ScheduledNotification",
                "requestGranted");
        }
        // Java class
        // NativeActivity
        void ScheduledNotification::requestAuth()
        {
            JniHelper::callStaticVoidMethod(
                "com/wrapper/notification/ScheduledNotification",
                "requestAuth");
        }

        void ScheduledNotification::show(int notificationType,
                                         int identifier,
                                         const std::string &title,
                                         const std::string &message,
                                         const std::string &attributionData,
                                         int interval,
                                         int priority,
                                         bool shouldScheduleNotifByDate,
                                         const std::string &notifStyle,
                                         bool isExactTimeNotification)
        {
            JniHelper::callStaticVoidMethod(
                "com/wrapper/notification/ScheduledNotification",
                "showLocalNotification", notificationType, identifier, title, message, attributionData, interval, priority, shouldScheduleNotifByDate, notifStyle, isExactTimeNotification);
        }

        void ScheduledNotification::cancel(int notificationType,
                                           int identifier,
                                           const std::string &title,
                                           const std::string &message,
                                           int priority,
                                           const std::string &notifStyle,
                                           const std::string &attributionData)
        {
            JniHelper::callStaticVoidMethod(
                "com/wrapper/notification/ScheduledNotification",
                "cancel", notificationType, identifier, title, message, priority, notifStyle, attributionData);
        }

        void ScheduledNotification::cancelAll()
        {
            JniHelper::callStaticVoidMethod(
                "com/wrapper/notification/ScheduledNotification",
                "cancelAll");
        }
    }
}
