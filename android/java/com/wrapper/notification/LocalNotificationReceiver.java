package com.wrapper.notification;

import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.util.Log;

import androidx.core.app.NotificationManagerCompat;


abstract public class LocalNotificationReceiver extends BroadcastReceiver {

    private static final String TAG = "LocalNotificationReceiver";

    public LocalNotificationReceiver() {
    }

    @Override
    public void onReceive(Context context, Intent receivedIntent) {
        int notificationId = receivedIntent.getIntExtra("notification_id", 0);
        String title = receivedIntent.getStringExtra("title");
        String message = receivedIntent.getStringExtra("message");
        String bgImage = receivedIntent.getStringExtra("bgImage");
        String fgImage = receivedIntent.getStringExtra("fgImage");
        String bigPictureIconName = receivedIntent.getStringExtra("bigPictureIconName");
        String expandablePictureName = receivedIntent.getStringExtra("expandablePictureName");
        String notifLargeIcon = receivedIntent.getStringExtra("notifLargeIcon");
        NotificationStyle notificationStyle = NotificationStyle.values()[receivedIntent.getIntExtra("notificationType", 0)];
        NotificationPriority priority = NotificationPriority.values()[receivedIntent.getIntExtra("priority", 8)];
        IGameNotificationHelper gameNotificationHelper = getGameNotificationHelper();
        if (title == null && message == null) {
            return;
        }
        if (title == null) {
            title = "";
        }
        if (message == null) {
            message = "";
        }
        try {
            if (!areNotificationsEnabled(context)) {
                return;
            }
            PendingIntent clickIntent = getOnClickPendingIntent(context, receivedIntent, notificationId);
            PendingIntent dismissIntent = getOnDismissPendingIntent(context, receivedIntent, notificationId);

            CustomNotification.Builder builder = new CustomNotification.Builder();
            builder.title(title).
                    message(message).
                    onClickIntent(clickIntent).
                    onDismissIntent(dismissIntent).
                    backgroundImage(bgImage).
                    foregroundImage(fgImage).
                    bigPictureIconName(bigPictureIconName).
                    expandablePictureName(expandablePictureName).
                    notifLargeIcon(notifLargeIcon).
                    notificationStyle(notificationStyle).
                    notificationPriority(priority);
            builder.channel(context.getString(gameNotificationHelper.getNotificationChannelId()));

            CustomNotification customNotification = builder.build();
            NotificationManagerCompat managerCompat = NotificationManagerCompat.from(context);
            managerCompat.notify(notificationId, customNotification.getCustomBuilder(context, gameNotificationHelper).build());
            trackNotificationView(context, receivedIntent.getStringExtra(ScheduledNotification.NOTIFICATION_TRACKING_DATA_KEY));
        } catch (Exception e) {
            Log.e(TAG, "Error sending notif " + e.getLocalizedMessage());
        }
    }

    private PendingIntent getOnClickPendingIntent(Context context, Intent receivedIntent, int notificationId) {
        Intent createdIntent = new Intent(context, getLaunchActivityClass());
        createdIntent.putExtra(ScheduledNotification.NOTIFICATION_TRACKING_DATA_KEY, receivedIntent.getStringExtra(ScheduledNotification.NOTIFICATION_TRACKING_DATA_KEY));
        createdIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        return PendingIntent.getActivity(context, notificationId, createdIntent, PendingIntent.FLAG_IMMUTABLE);
    }

    private PendingIntent getOnDismissPendingIntent(Context context, Intent receivedIntent, int notificationId) {
        Intent deletedIntent = new Intent(context, getDeleteBroadcastReceiverClass());
        deletedIntent.setAction(getDeleteIntentAction());
        deletedIntent.putExtra(ScheduledNotification.NOTIFICATION_TRACKING_DATA_KEY, receivedIntent.getStringExtra(ScheduledNotification.NOTIFICATION_TRACKING_DATA_KEY));
        return PendingIntent.getBroadcast(context, notificationId, deletedIntent, PendingIntent.FLAG_IMMUTABLE);
    }

    private static boolean areNotificationsEnabled(Context context) {
        boolean areNotificationsEnabled = NotificationManagerCompat.from(context).areNotificationsEnabled();
        return areNotificationsEnabled;
    }

    protected abstract IGameNotificationHelper getGameNotificationHelper();

    protected abstract Class getDeleteBroadcastReceiverClass();

    protected abstract String getDeleteIntentAction();

    protected abstract Class getLaunchActivityClass();

    protected abstract void trackNotificationView(Context context, String payload);
}

