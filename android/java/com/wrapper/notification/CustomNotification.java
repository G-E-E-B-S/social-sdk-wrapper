package com.wrapper.notification;

import android.app.PendingIntent;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.ImageDecoder;
import android.media.RingtoneManager;
import android.net.Uri;
import android.os.Build;
import android.provider.MediaStore;
import android.util.Log;
import android.widget.RemoteViews;

import androidx.core.app.NotificationCompat;

public class CustomNotification {
    private final String title;
    private final String message;
    private final String backgroundImage;
    private final String channel;
    private final PendingIntent clickIntent;
    private final PendingIntent dismissIntent;
    private final String foregroundImage;
    private final NotificationStyle notificationType;
    private final String bigPictureIconName;
    private final String expandablePictureName;
    private final String notifLargeIcon;

    public NotificationCompat.Builder getCustomBuilder(Context context, IGameNotificationHelper helper) {
        NotificationCompat.Builder builder = new NotificationCompat.Builder(context, channel);
        builder.setSmallIcon(helper.getSmallIconId());

        builder = getNotifPropertiesByType(context, helper, builder);
        builder.setAutoCancel(true);
        if (clickIntent != null) {
            builder.setContentIntent(clickIntent);
        }
        if (dismissIntent != null) {
            builder.setDeleteIntent(dismissIntent);
        }
        Uri defaultSoundUri = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
        builder.setSound(defaultSoundUri);

        return builder;
    }

    public NotificationCompat.Builder getNotifPropertiesByType(Context context, IGameNotificationHelper helper, NotificationCompat.Builder builder) {
        String packageName = context.getPackageName();

        if (notificationType == NotificationStyle.BIGPICTURE) {
            builder.setStyle(getBigPictureNotification(packageName, context));
            builder.setContentTitle(title);
            builder.setContentText(message);
            builder.setLargeIcon(getBitmapFromImgFilePath(context, bigPictureIconName));
        }

        if (notificationType == NotificationStyle.BIGTEXT) {
            builder.setStyle(getBigTextNotification());
            builder.setContentTitle(title);
            builder.setContentText(message);
            builder.setLargeIcon(getBitmapFromImgFilePath(context, notifLargeIcon));
        }

        if (notificationType == NotificationStyle.CUSTOM) {
            builder.setCustomContentView(this.getCustomLayout(packageName, helper));
            builder.setStyle(new NotificationCompat.DecoratedCustomViewStyle());
        }

        return builder;
    }

    public Bitmap getBitmapFromImgFilePath(Context context, String imgFileName) {
        String packageName = context.getPackageName();
        Uri imageUri = Uri.parse("android.resource://" + packageName + "/raw/" + imgFileName);
        try {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
                return ImageDecoder.decodeBitmap(ImageDecoder.createSource(context.getContentResolver(), imageUri));
            } else {
                return MediaStore.Images.Media.getBitmap(context.getContentResolver(), imageUri);
            }
        } catch (Exception e) {
            Log.w("Error", "Unable to load file resource" + imgFileName);
            return null;
        }
    }

    public NotificationCompat.Style getBigPictureNotification(String packageName, Context context) {
        Bitmap bigLargeIconBitmap = getBitmapFromImgFilePath(context, bigPictureIconName);
        Bitmap bigPictureBitmap = getBitmapFromImgFilePath(context, expandablePictureName);

        return new NotificationCompat.BigPictureStyle()
                .setSummaryText(message)
                .bigLargeIcon(bigLargeIconBitmap)
                .bigPicture(bigPictureBitmap)
                .setBigContentTitle(title);
    }

    public NotificationCompat.Style getBigTextNotification() {
        return new NotificationCompat.BigTextStyle()
                .setBigContentTitle(title)
                .bigText(message);
    }


    public boolean isValid() {
        if (title == null || title.isEmpty()) {
            return false;
        }
        return message != null && !message.isEmpty();
    }

    private CustomNotification(Builder builder) {
        title = builder.title;
        message = builder.message;
        backgroundImage = builder.backgroundImage;
        foregroundImage = builder.foregroundImage;
        channel = builder.channel;
        notificationType = builder.notificationStyle;
        bigPictureIconName = builder.bigPictureIconName;
        expandablePictureName = builder.expandablePictureName;
        notifLargeIcon = builder.notifLargeIcon;
        clickIntent = builder.clickIntent;
        dismissIntent = builder.dismissIntent;
    }
    private RemoteViews getCustomLayout(String packageName, IGameNotificationHelper helper) {
        RemoteViews views = new RemoteViews(packageName, helper.getBGLayoutId());
        views.setTextViewText(helper.getNotifTitleId(), title);
        views.setTextViewText(helper.getNotifMessageId(), message);
        if (backgroundImage != null && backgroundImage.length() > 0) {
            Uri bgUri = Uri.parse("android.resource://"
                    + packageName + "/raw/" + backgroundImage);
            views.setImageViewUri(helper.getNotifBackgroundImageId(), bgUri);
        }
        if (foregroundImage != null && foregroundImage.length() > 0) {
            Uri fgUri = Uri.parse("android.resource://"
                    + packageName + "/raw/" + foregroundImage);
            views.setImageViewUri(helper.getNotifForegroundImageId(), fgUri);
        }
        return views;
    }

    public static final class Builder {
        private String title;
        private String message;
        private String backgroundImage;
        private String foregroundImage;
        private String channel;
        private String bigPictureIconName;
        private String expandablePictureName;
        private String notifLargeIcon;
        private NotificationStyle notificationStyle;
        private NotificationPriority notificationPriority;
        private PendingIntent clickIntent;
        private PendingIntent dismissIntent;

        public Builder() {
        }

        public Builder title(String val) {
            title = val;
            return this;
        }

        public Builder message(String val) {
            message = val;
            return this;
        }

        public Builder backgroundImage(String val) {
            backgroundImage = val;
            return this;
        }

        public Builder channel(String val) {
            channel = val;
            return this;
        }

        public Builder onClickIntent(PendingIntent val) {
            clickIntent = val;
            return this;
        }

        public Builder onDismissIntent(PendingIntent val) {
            dismissIntent = val;
            return this;
        }

        public CustomNotification build() {
            return new CustomNotification(this);
        }

        public Builder foregroundImage(String val) {
            this.foregroundImage = val;
            return this;
        }

        public Builder bigPictureIconName(String val) {
            this.bigPictureIconName = val;
            return this;
        }

        public Builder expandablePictureName(String val) {
            this.expandablePictureName = val;
            return this;
        }

        public Builder notifLargeIcon(String val) {
            this.notifLargeIcon = val;
            return this;
        }

        public Builder notificationStyle(NotificationStyle val) {
            this.notificationStyle = val;
            return this;
        }

        public Builder notificationPriority(NotificationPriority val) {
            this.notificationPriority = val;
            return this;
        }

    }
}

enum NotificationStyle {BIGPICTURE, BIGTEXT, CUSTOM}

enum NotificationPriority {P0, P1, P2, P3, P4, P5, P6, P7, P8}
