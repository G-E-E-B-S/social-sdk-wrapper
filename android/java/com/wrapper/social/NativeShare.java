package com.wrapper.social;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;

import androidx.core.app.ShareCompat;
import androidx.core.content.FileProvider;

import java.io.File;

public class NativeShare {
    private static String TAG = "NativeShare";
    private static String SHARE_RECEIVE_ACTION = "com.wrapper.social.NativeShare.SHARE_RECEIVE_ACTION";
    private static NativeShare sInstance;
    private static Activity sActivity;
    private static String sAuthority;
    private static Class sReceiverClass;

    public static void init(Activity activity, Class receiverClass, String authority) {
        sActivity = activity;
        sAuthority = authority;
        sInstance = new NativeShare();
        sReceiverClass = receiverClass;
    }

    public static void shareImage(String imageFileFullPath, String shareMsg, String titleMsg) throws InterruptedException {
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                try {
                    File fileToShare = new File(imageFileFullPath);
                    Uri uriToImage = FileProvider.getUriForFile(sActivity,
                            sAuthority,
                            fileToShare);
                    Log.d(TAG, "NativeShare shareImage uri:" + uriToImage);
                    Intent shareIntent = ShareCompat.IntentBuilder.from(sActivity)
                            .setType("image/*")
                            .addStream(uriToImage)
                            .setText(shareMsg)
                            .setSubject(titleMsg)
                            .getIntent();
                    shareIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_DOCUMENT);
                    shareIntent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
                    sActivity.startActivity(Intent.createChooser(shareIntent, titleMsg));
                    sInstance.onShareComplete(true);
                } catch (Exception e) {
                    Log.d(TAG, "exception in share: " + e);
                    sInstance.onShareFailed(e.toString());
                }
            }
        });
    }

    public static void shareLink(String linkStr) {
        if (linkStr == null) {
            return;
        }
        try {
            Log.d(TAG, "shareLink:" + linkStr);
            Intent shareIntent = ShareCompat.IntentBuilder.from(sActivity)
                    .setType("text/plain")
                    .setText(linkStr).getIntent();
            Intent shareReceiveIntent = new Intent(sActivity, sReceiverClass);
            shareReceiveIntent.setAction(SHARE_RECEIVE_ACTION);
            PendingIntent pi = PendingIntent.getBroadcast(sActivity,
                    100,
                    shareReceiveIntent,
                    PendingIntent.FLAG_UPDATE_CURRENT|PendingIntent.FLAG_MUTABLE);
            sActivity.startActivity(Intent.createChooser(shareIntent, null, pi.getIntentSender()));
            sInstance.onShareComplete(true);
        } catch (Exception e) {
            Log.d(TAG, "exception in share: " + e);
            sInstance.onShareFailed(e.toString());
        }
    }
    private native void onShareComplete(boolean status);
    private native void onShareFailed(String error);
}
