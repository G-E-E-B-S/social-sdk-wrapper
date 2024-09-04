package com.wrapper.social;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;

abstract public class ShareReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        ComponentName clickedComponent = intent.getParcelableExtra(Intent.EXTRA_CHOSEN_COMPONENT);
        trackSharer(context, clickedComponent);
    }
    abstract public void trackSharer(Context context, ComponentName componentName);
}
