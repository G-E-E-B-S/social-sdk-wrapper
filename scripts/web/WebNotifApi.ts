import INotification, { NotificationPriority, NotificationType } from "../types/INotification";

export class WebNotifApi implements INotification {
    handleGameHideAndShow(): boolean {
        return false;
    }
    shouldScheduleNotifOnLaunch(): boolean {
        return false;
    }
    requestGranted(): boolean {
        if (!this.isNotificationAvailable()) {
            console.log('Notification not supported by the browser');
            return false;
        }
        return window.Notification.permission === 'granted';
    }
    requestAuth(): void {
        console.log("Requesting Notification Permisssion ...");
        if (!this.isNotificationAvailable()) {
            console.log('Notification not supported by the browser');
            return;
        }
        window.Notification.requestPermission().then((permission) => {
            if (permission === "granted") {
                this.permission = permission;
                console.log("Notification Permission Granted");
            } else {
                console.log("Notification Permission Denied!");
            }
        }).catch(err => {
            console.error("Notification Permission Error: ", err);
        });
    }

    show(notificationType: NotificationType, id: number, title: string, body: string, attributionData: string, timeSecs: number, priority: NotificationPriority, shouldScheduleNotifByDate: boolean, notifStyle: string) {
        const styleData = JSON.parse(notifStyle);
        const data = {
            id: id,
            title: title,
            body: body,
            foregroundImageName: styleData.foregroundImageName,
            backgroundImageName: styleData.backgroundImageName,
            attributionData,
            timeSecs: timeSecs
        }
        // Send notification message to the service-worker
        if (window.isSecureContext && navigator.serviceWorker) {
            navigator.serviceWorker.ready.then((registration) => {
                registration.active.postMessage({ type: "SCHEDULE_NOTIFICATION", ...data });
            }).catch((error) => {
                console.error('Service worker not ready', error);
            });
        } else {
            console.log('Service worker not supported by the browser');
        }
    }

    cancel(id: number) {
        // Send message to service-worker to cancel set timouts created
        if (window.isSecureContext && navigator.serviceWorker) {
            navigator.serviceWorker.ready.then((registration) => {
                registration.active.postMessage({ type: "CANCEL_NOTIFICATION", id: id });
            });
        } else {
            console.log('Service worker not supported by the browser');
        }
    }

    cancelAll(callback?: () => void) {
        // FIXME figure out what's up wth this
        if (callback) callback();
    }

    private isNotificationAvailable() {
        return typeof window.Notification !== "undefined";
    }

    private permission;
}
