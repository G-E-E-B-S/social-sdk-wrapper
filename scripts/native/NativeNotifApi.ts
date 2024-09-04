import INotification, { NotificationPriority, NotificationType } from "../types/INotification";
declare const social;
export class NativeNotifApi implements INotification {
    handleGameHideAndShow(): boolean {
        return true;
    }
    shouldScheduleNotifOnLaunch(): boolean {
        return false;
    }
    requestGranted(): boolean {
        return social.ScheduledNotification.requestGranted();
    }
    requestAuth(): void {
        social.ScheduledNotification.requestAuth();
    }
    show(notificationType: NotificationType, id: number, title: string, body: string, attributionData: string, timeSecs: number, priority: NotificationPriority, shouldScheduleNotifByDate: boolean, notifStyle: string, isExactTimeNotification: Boolean) {
        social.ScheduledNotification.show(notificationType, id, title, body, attributionData, timeSecs, priority, shouldScheduleNotifByDate, notifStyle, isExactTimeNotification);
    }
    cancel(notificationType: NotificationType, id: number, title: string, body: string, priority: NotificationPriority, notifStyle: string, attributionData: string) {
        social.ScheduledNotification.cancel(notificationType, id, title, body, priority, notifStyle, attributionData);
    }
    cancelAll(callback?: () => void) {
        social.ScheduledNotification.cancelAll();
        if (callback) callback();
    }
}
