package com.wrapper.payload;

import android.content.Intent;
import android.app.Activity;
import android.net.Uri;
import androidx.core.app.ShareCompat;
import android.util.Log;

public class FirebaseDynamicLinks {
    private static String TAG = "FirebaseDynamicLinks";
    private static Activity sActivity;
    private static int REQUEST_INVITE = 25;

    public static void setActivity(Activity activity) {
        sActivity = activity;
    }

    public static void shareLink(String linkStr) {
        if (linkStr == null) {
            return;
        }
        Log.d(TAG, "shareLink:" + linkStr);
        Intent shareIntent = ShareCompat.IntentBuilder.from(sActivity)
                                                    .setType("text/plain")
                                                    .setText(linkStr).getIntent();
        sActivity.startActivity(shareIntent);
    }
}
