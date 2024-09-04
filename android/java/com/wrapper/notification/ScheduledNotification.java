package com.wrapper.notification;

import android.app.Activity;
import android.app.AlarmManager;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.provider.Settings;
import android.util.Log;

import org.json.JSONObject;

import java.util.Calendar;
import java.util.List;

public class ScheduledNotification {
    public static String ACTION_RECEIVE_SCHEDULED_NOTIF = "com.wrapper.ScheduledNotification.notification.ACTION_RECEIVE_SCHEDULED_NOTIF";
    public static String NOTIFICATION_TRACKING_DATA_KEY = "notification_tracking_data_key";
    private static final String TAG = "ScheduledNotification";
    private static Activity sActivity;
    private static Class sReceiverClass;
    private static final int HOUR_SEC = 3600;

    public static class ChannelConfig {
        String id;
        String description;
        String name;
        int importance;

        public ChannelConfig(String id, String description, String name, int importance) {
            this.id = id;
            this.description = description;
            this.name = name;
            this.importance = importance;
        }
    }

    public static void init(Activity activity,
                            List<ChannelConfig> configs,
                            Class receiverClass) {
        sActivity = activity;
        sReceiverClass = receiverClass;
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
            ScheduledNotification.createChannels(configs);
        }
    }

    public static boolean requestGranted() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
            AlarmManager am = (AlarmManager) sActivity.getSystemService(Context.ALARM_SERVICE);
            return am.canScheduleExactAlarms();
        }
        return true;
    }

    public static void requestAuth() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
            AlarmManager am = (AlarmManager) sActivity.getSystemService(Context.ALARM_SERVICE);
            if (!am.canScheduleExactAlarms()) {
                Intent intent = new Intent(Settings.ACTION_REQUEST_SCHEDULE_EXACT_ALARM);
                sActivity.startActivity(intent);
            }
        }
    }

    public static void showLocalNotification(
            int notificationType,
            int identifier,
            String title,
            String message,
            // should be a json
            String attributionData,
            int interval,
            int priority,
            boolean shouldScheduleNotifByDate,
            // should be a json
            String notifStyle,
            boolean isExactTimeNotification) {
        PendingIntent sender = getPendingIntent(notificationType, identifier, title, message, attributionData, priority, notifStyle);
        Calendar calendar = Calendar.getInstance();
        calendar.setTimeInMillis(System.currentTimeMillis());
        if (shouldScheduleNotifByDate) {
            calendar.set(Calendar.MILLISECOND, 0);
            calendar.set(Calendar.SECOND, 0);
            calendar.set(Calendar.MINUTE, 0);
            calendar.set(Calendar.HOUR_OF_DAY, 0);
        }
        AlarmManager am = (AlarmManager) sActivity.getSystemService(Context.ALARM_SERVICE);
        if (am == null) {
            return;
        }
        // Todo: remove this logic -> "interval * 1000" and replace it with calendar.add/roll logic
        long triggerTimeInMillis = calendar.getTimeInMillis() + interval * 1000;

        if (ScheduledNotification.shouldScheduleExactAlarm(am, isExactTimeNotification)) {
            am.setExact(AlarmManager.RTC_WAKEUP, triggerTimeInMillis, sender);
        } else {
            am.set(AlarmManager.RTC_WAKEUP, triggerTimeInMillis, sender);
        }
    }

    private static boolean shouldScheduleExactAlarm(AlarmManager am, boolean isExactNotificationRequested) {
        if (isExactNotificationRequested) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
                return am.canScheduleExactAlarms();
            } else {
                return true;
            }
        } else {
            return false;
        }
    }

    public static void cancel(
            int notificationType,
            int identifier,
            String title,
            String message,
            int priority,
            // should be a json
            String notifStyle,
            // should be a json
            String attributionData) {
        NotificationManager notificationManager = (NotificationManager) sActivity.getSystemService(Context.NOTIFICATION_SERVICE);
        notificationManager.cancel(identifier);

        PendingIntent sender = getPendingIntent(notificationType, identifier, title, message, attributionData, priority, notifStyle);

        if (sender == null) {
            return;
        }
        AlarmManager am = (AlarmManager) sActivity.getSystemService(Context.ALARM_SERVICE);
        if (am == null) {
            return;
        }
        am.cancel(sender);
        sender.cancel();
    }

    public static void cancelAll() {
        NotificationManager notificationManager = (NotificationManager) sActivity.getSystemService(Context.NOTIFICATION_SERVICE);
        notificationManager.cancelAll();
    }

    private static void createChannels(List<ScheduledNotification.ChannelConfig> configs) {
        for (int idx = 0; idx < configs.size(); idx++) {
            createChannel(configs.get(idx));
        }
    }

    private static PendingIntent getPendingIntent(int notificationType,
                                                  int identifier,
                                                  String title,
                                                  String message,
                                                  // should be a json
                                                  String attributionData,
                                                  int priority,
                                                  // should be a json
                                                  String notifStyle) {

        Intent intent = new Intent(sActivity, sReceiverClass);
        intent.setAction(ACTION_RECEIVE_SCHEDULED_NOTIF);

        String bgImage = "";
        String fgImage = "";
        String bigPictureIconName = "";
        String expandablePictureName = "";
        String notifLargeIcon = "";

        try {
            JSONObject reader = new JSONObject(notifStyle);
            bgImage = reader.optString("backgroundImageName", "");
            fgImage = reader.optString("foregroundImageName", "");
            bigPictureIconName = reader.optString("bigPictureIconName", "");
            expandablePictureName = reader.optString("expandablePictureName", "");
            notifLargeIcon = reader.optString("notifLargeIcon", "");
        } catch (Exception e) {
            Log.w("Error", "JSON Parse Error in getPendingIntent " + e);
        }


        intent.putExtra("notification_id", identifier);
        intent.putExtra("title", title);
        intent.putExtra("message", message);
        intent.putExtra("bgImage", bgImage);
        intent.putExtra("fgImage", fgImage);
        intent.putExtra("bigPictureIconName", bigPictureIconName);
        intent.putExtra("expandablePictureName", expandablePictureName);
        intent.putExtra("notifLargeIcon", notifLargeIcon);
        intent.putExtra("notificationType", notificationType);
        intent.putExtra("priority", priority);
        intent.putExtra(NOTIFICATION_TRACKING_DATA_KEY, attributionData);
        return getPendingIntent(identifier, intent);
    }

    private static PendingIntent getPendingIntent(int identifier, Intent intent) {
        return PendingIntent.getBroadcast(sActivity.getApplicationContext(),
                identifier, intent, PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE);
    }

    private static void createChannel(ChannelConfig config) {
        NotificationChannel channel = new NotificationChannel(config.id,
                config.name,
                config.importance);
        channel.setDescription(config.description);
        // Register the channel with the system; you can't change the importance
        // or other notification behaviors after this
        NotificationManager notificationManager = sActivity.getSystemService(NotificationManager.class);
        notificationManager.createNotificationChannel(channel);
    }
}
