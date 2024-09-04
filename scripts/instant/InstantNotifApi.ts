import { IA2UStyle } from "../ScheduledNotifApi";
import INotification, { NotificationPriority, NotificationType } from "../types/INotification";

export class InstantNotifApi implements INotification {

    constructor(enableA2Us?: boolean) {
        this.a2uEnabled = enableA2Us ?? false;
    }
    handleGameHideAndShow(): boolean {
        return false;
    }

    shouldScheduleNotifOnLaunch(): boolean {
        return true;
    }

    requestGranted(): boolean {
        return this.a2uEnabled;
    }

    requestAuth(): void {
        // No-op
    }

    show(notificationType: NotificationType, id: number, title: string, body: string, attributionData: string, timeSecs: number, priority: NotificationPriority, shouldScheduleNotifByDate: boolean, notifStyle: string) {
        if (!this.a2uEnabled) {
            return;
        }

        if (shouldScheduleNotifByDate) {
            timeSecs -= Math.round((new Date().setHours(0,0,0,0) - Date.now()) / 1000);
        }

        const styleOptions: IA2UStyle = JSON.parse(notifStyle);
        const data = {
            message: {
                title: title,
                body: body,
                media_url: styleOptions.imageUrl
            },
            label: id.toString(),
            payload: attributionData,
            schedule_interval: timeSecs
        };

        // @ts-ignore
        FBInstant.graphApi.requestAsync("/me/notifications", "POST", data)
                 .then((response) => {
                     console.log("InstantNotifApi::show Notification " + id + " success: " + response.success + ", notificationId: " + response.notification_id);
                 }).catch((error) => {
                    console.warn("InstantNotifApi::show Notification " + id + " error: ", error);
                });
    }

    cancel(notificationType: NotificationType, id: number, title: string, body: string, priority: NotificationPriority, notifStyle: string, attributionData: string) {
        if (!this.a2uEnabled) {
            return;
        }

        console.log("Notification:Cancel InstantNotifApi",id, title, body, priority, notifStyle, attributionData);
        const data = {
            "label": id.toString()
        };

        // @ts-ignore
        FBInstant.graphApi.requestAsync("/me/cancel_all_notifications", "POST", data)
                 .then((response) => {
                     console.log("InstantNotifApi::cancel Notification " + id + " success: " + response.success);
                 }).catch((error) => {
                    console.warn("InstantNotifApi::cancel Notification " + id + " error: ", error);
                });
    }

    cancelAll(callback?: () => void) {
        // @ts-ignore
        FBInstant.graphApi.requestAsync("/me/cancel_all_notifications", "POST", {})
                 .then((response) => {
                     console.log("InstantNotifApi::cancelAll success: " + response.success);
                     if (callback) callback();
                 }).catch((error) => {
                     console.warn("InstantNotifApi::cancelAll error: ", error);
                     if (callback) callback();
                });
    }

    private readonly a2uEnabled: boolean;
}
