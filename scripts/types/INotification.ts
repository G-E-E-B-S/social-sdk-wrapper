
export default interface INotification {
    requestGranted(): boolean;
    requestAuth(): void;
    show(notificationType: NotificationType, id: number, title: string, body: string, attributionData: string, timeSecs: number, priority: NotificationPriority, shouldScheduleNotifByDate: boolean, notifStyle: string, isExactTimeNotification: boolean);
    cancel(notificationType: NotificationType, id: number, title: string, body: string, priority: NotificationPriority, notifStyle: string, attributionData: string);
    cancelAll(callback?: () => void);
    handleGameHideAndShow(): boolean;
    shouldScheduleNotifOnLaunch(): boolean;
}

export enum NotificationType {
    EXPANDABLE,
    TEXT,
    CUSTOM
}

export enum NotificationPriority {
    P0,
    P1,
    P2,
    P3,
    P4,
    P5,
    P6,
    P7,
    P8
}
