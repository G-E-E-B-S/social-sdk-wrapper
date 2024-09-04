#include "ScheduledNotification.h"
#import <UIKit/UIKit.h>
#import <UserNotifications/UserNotifications.h>

using namespace std;
namespace wrapper {
    namespace social {
        namespace  {
            const int HOUR_SEC = 3600;
            bool grantedPermission = false;
        }
        void ScheduledNotification::init() {
            if (@available(iOS 10.0, *)) {
                UNUserNotificationCenter* center = [UNUserNotificationCenter currentNotificationCenter];
                [center getNotificationSettingsWithCompletionHandler:^(UNNotificationSettings * _Nonnull settings) {
                    grantedPermission = settings.authorizationStatus == UNAuthorizationStatusAuthorized;
                }];
            }
        }
        bool ScheduledNotification::requestGranted() {
            if (@available(iOS 10.0, *)) {
                return grantedPermission;
            } else if (@available(iOS 8.0, *)) {
                return true;
            }
            return true;
        }
        void ScheduledNotification::requestAuth()
        {
            if (@available(iOS 10.0, *)) {
                UNUserNotificationCenter* center = [UNUserNotificationCenter currentNotificationCenter];
                UNAuthorizationOptions options = UNAuthorizationOptionAlert | UNAuthorizationOptionSound | UNAuthorizationOptionBadge;
                [center requestAuthorizationWithOptions:options completionHandler:^(BOOL granted, NSError * _Nullable error) {
                    if (!granted) {
                        NSLog(@"LocalNotification auth Something went wrong");
                    }
                }];
            } else if (@available(iOS 8.0, *)) {
                [[UIApplication sharedApplication] registerUserNotificationSettings:[UIUserNotificationSettings settingsForTypes:UIUserNotificationTypeAlert|UIUserNotificationTypeBadge|UIUserNotificationTypeSound categories:nil]];
            }
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
            auto identifierStr = std::to_string(identifier);
            interval = std::max(1, interval);
            NSString *nsMessage = [NSString stringWithCString:message.c_str()
                                                    encoding:NSUTF8StringEncoding];
            NSString *nsTitle = [NSString stringWithCString:title.c_str()
                                                encoding:NSUTF8StringEncoding];
            NSString *nsIdentifier = [NSString stringWithCString:identifierStr.c_str()
                                                        encoding:NSUTF8StringEncoding];
            //    NSLog(@"LocalNotification show %d: %dsecs, %@", identifier, interval, nsMessage);
            if (@available(iOS 10.0, *)) {
                UNMutableNotificationContent* content = [[UNMutableNotificationContent alloc] init];
                content.title = nsTitle;
                content.body = nsMessage;
                UNNotificationSound *turn = [UNNotificationSound soundNamed:@"turn.caf"];
                content.sound = turn;
                UNTimeIntervalNotificationTrigger* trigger = [UNTimeIntervalNotificationTrigger triggerWithTimeInterval:interval repeats:false];
                UNNotificationRequest* request = [UNNotificationRequest
                                                requestWithIdentifier:nsIdentifier content:content trigger:trigger];
                UNUserNotificationCenter* center = [UNUserNotificationCenter currentNotificationCenter];
                [center addNotificationRequest:request withCompletionHandler:^(NSError * _Nullable error) {
                    if (error != nil) {
                        NSLog(@"%@", error.localizedDescription);
                    }
                }];
            } else {
                UILocalNotification *notification = [[UILocalNotification alloc] init];
                
                notification.fireDate = [[NSDate date] dateByAddingTimeInterval:interval];
                notification.timeZone = [NSTimeZone defaultTimeZone];
                if (@available(iOS 8.2, *)) {
                    notification.alertTitle = nsTitle;
                }
                notification.alertBody = nsMessage;
                notification.alertAction = @"Open";
                notification.soundName = @"turn.caf";
                
                NSDictionary *infoDict = [NSDictionary dictionaryWithObject:nsIdentifier forKey:@"ID"];
                notification.userInfo = infoDict;
                
                [[UIApplication sharedApplication] scheduleLocalNotification:notification];
            }
        }

        void ScheduledNotification::cancel(int notificationType,
                                        int identifier,
                                        const std::string &title,
                                        const std::string &message,
                                        int priority,
                                        const std::string& notifStyle,
                                        const std::string &attributionData)
        {
            auto identifierStr = std::to_string(identifier);
            NSString *myIDToCancel = [NSString stringWithCString:identifierStr.c_str()
                                                        encoding:NSUTF8StringEncoding];
            //    NSLog(@"LocalNotification cancel %@", myIDToCancel);
            if (@available(iOS 10.0, *)) {
                UNUserNotificationCenter* center = [UNUserNotificationCenter currentNotificationCenter];
                NSArray *idList = [NSArray arrayWithObjects:myIDToCancel, nil];
                [center removePendingNotificationRequestsWithIdentifiers:idList];
            } else {
                UILocalNotification *notificationToCancel=nil;
                for(UILocalNotification *aNotif in [[UIApplication sharedApplication] scheduledLocalNotifications]) {
                    if([[aNotif.userInfo objectForKey:@"ID"] isEqualToString:myIDToCancel]) {
                        notificationToCancel=aNotif;
                        break;
                    }
                }
                if(notificationToCancel) [[UIApplication sharedApplication] cancelLocalNotification:notificationToCancel];
            }
        }
        void ScheduledNotification::cancelAll() {
            // TODO:
        }
    }
}
