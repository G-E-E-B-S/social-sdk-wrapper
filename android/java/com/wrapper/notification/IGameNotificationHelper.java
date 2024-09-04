package com.wrapper.notification;

import android.app.Activity;
import android.net.Uri;

import androidx.annotation.ColorInt;
import androidx.annotation.ColorRes;
import androidx.annotation.DrawableRes;
import androidx.annotation.IdRes;
import androidx.annotation.LayoutRes;
import androidx.annotation.StringRes;

public interface IGameNotificationHelper {
    @LayoutRes
    int getBGLayoutId();
    @DrawableRes
    int getSmallIconId();
    @ColorRes
    int getNotifColor();
    @IdRes
    int getNotifTitleId();
    @IdRes
    int getNotifMessageId();
    @IdRes
    int getNotifBackgroundImageId();
    @IdRes
    int getNotifForegroundImageId();
    Uri getSoundUri();
    @StringRes
    int getNotificationChannelId();
}
