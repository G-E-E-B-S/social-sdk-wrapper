#ifndef SOCIAL_SDK_SCHEDULED_NOTIFICATION_H
#define SOCIAL_SDK_SCHEDULED_NOTIFICATION_H

#include <string>
namespace wrapper
{
    namespace social
    {
        class ScheduledNotification
        {
        public:
            static void init();
            static bool requestGranted();

            static void requestAuth();

            /**
             * Show local notification
             * @param message  Message should be shown in notificatin
             * @param interval Interval in seconds
             * @param identifier      identifier to specify notification
             */
            static void show(int notificationType,
                             int identifier,
                             const std::string &title,
                             const std::string &message,
                             const std::string &attributionData,
                             int interval,
                             int priority,
                             bool shouldScheduleNotifByDate,
                             const std::string &notifStyle,
                             bool isExactTimeNotification);

            /**
             * Cancel local notification specified by ID
             * @param identifier identifier of local notification
             */
            static void cancel(int notificationType,
                               int identifier,
                               const std::string &title,
                               const std::string &message,
                               int priority,
                               const std::string &notifStyle,
                               const std::string &attributionData);
            static void cancelAll();
        };
    }
}

#endif // SOCIAL_SDK_SCHEDULED_NOTIFICATION_H
