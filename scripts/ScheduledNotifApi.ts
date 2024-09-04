import INotification, { NotificationPriority, NotificationType } from "./types/INotification";

export interface IGameHelper {
    /**
     * If cooldown is active, messages won't be rescheduled.
     */
    isCooldownActive(notifId: number): boolean;
    /**
     * Update schedule time to make cooldown active.
     */
    updateLastScheduledTime(notifId: number);
    getNotifications(isToCancel: boolean): INotifData[];
    onGameHide(callback: () => void): void;
    onGameShow(callback: () => void): void;
}

export interface IA2UStyle {
    imageUrl: string;
}

export interface ICustomStyle {
    foregroundImageName: string,
    backgroundImageName?: string,
}

export interface IExpandableImgStyle {
    bigPictureIconName: string,
    expandablePictureName: string,
}

export interface IBigTextStyle {
    notifLargeIcon: string
}

export interface INotifData {
    notificationType: NotificationType,
    id: number,
    body: string,
    title: string,
    /**
     * time when the scheduled notif is supposed to trigger in seconds from now.
     */
    timeToTrigger: number,
    priority: NotificationPriority,
    shouldScheduleNotifByDate: boolean,
    notifStyle: IA2UStyle | ICustomStyle | IExpandableImgStyle | IBigTextStyle
    /* Used to determine if the notification should be scheduled at the exact time or not. 
     * If true, Please add SCHEDULE_EXACT_ALARM permission to the game, 
           The game targeting SDK level 31 or higher need to request the SCHEDULE_EXACT_ALARM permission to use this 
           else it will fallback to isExactTimeNotification as false.
    */
    isExactTimeNotification: boolean
    attributionData?: string,
}

export class ScheduledNotifApi {

    static init(delegate: INotification, gameHelper: IGameHelper) {
        //Initialise only after gameData fetch completes
        if (ScheduledNotifApi.instance) {
            return;
        }
        ScheduledNotifApi.instance = new ScheduledNotifApi(delegate, gameHelper);
        if (delegate.handleGameHideAndShow()) {
            gameHelper.onGameHide(() => {
                ScheduledNotifApi.instance.showLocalNotifications();
            });
            gameHelper.onGameShow(() => {
                ScheduledNotifApi.instance.cancelLocalNotifications();
            });
        }
        ScheduledNotifApi.instance.cancelAllLocalNotifications(() => {
            if (delegate.shouldScheduleNotifOnLaunch()) {
                ScheduledNotifApi.instance.showLocalNotifications();
            }
        });
    }

    static getInstance(): ScheduledNotifApi {
        return ScheduledNotifApi.instance;
    }

    private constructor(delegate: INotification, gameHelper: IGameHelper) {
        this.notificationDelegate = delegate;
        this.gameHelper = gameHelper;
    }

    getLastNotifSentTime(): number {
        return 0;
    }

    scheduleNotif(notifData: INotifData) {
        if (this.gameHelper.isCooldownActive(notifData.id)) {
            return;
        }
        console.log("notif time = " + notifData.timeToTrigger);
        this.gameHelper.updateLastScheduledTime(notifData.id);
        this.notificationDelegate.show(notifData.notificationType,
            notifData.id,
            notifData.title,
            notifData.body,
            notifData.attributionData,
            notifData.timeToTrigger,
            notifData.priority,
            notifData.shouldScheduleNotifByDate,
            JSON.stringify(notifData.notifStyle),
            notifData.isExactTimeNotification);
    }

    cancelNotif(notifData: INotifData) {
        this.notificationDelegate.cancel(
            notifData.notificationType,
            notifData.id,
            notifData.title,
            notifData.body,
            notifData.priority,
            JSON.stringify(notifData.notifStyle),
            notifData.attributionData);
    }

    private showLocalNotifications() {
        const notifications = this.gameHelper.getNotifications(false);
        for (let i = 0; i < notifications.length; i++) {
            const notifData = notifications[i];
            if (!notifData) continue;
            this.scheduleNotif(notifData);
        }
    }

    private cancelLocalNotifications() {
        const notifications = this.gameHelper.getNotifications(true);
        console.log("Utils cancelLocalNotifications()");
        for (let i = 0; i < notifications.length; i++) {
            const notifData = notifications[i];
            if (!notifData) continue;
            this.cancelNotif(notifData);
        }
    }

    private cancelAllLocalNotifications(callback?: () => void) {
        console.log("Utils cancelAllLocalNotifications()");
        // this.notificationDelegate.cancelAll(callback);
        const notifications = this.gameHelper.getNotifications(true);
        console.log("Utils cancelLocalNotifications()");
        for (let i = 0; i < notifications.length; i++) {
            const notifData = notifications[i];
            if (!notifData) continue;
            this.cancelNotif(notifData);
        }
        if (callback) callback();
    }

    private static instance: ScheduledNotifApi = null;
    private gameHelper: IGameHelper;
    private notificationDelegate: INotification;
}
