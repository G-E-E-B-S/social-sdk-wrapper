package com.wrapper.social.facebook;
import android.content.Intent;

import com.facebook.gamingservices.GamingPayload;

public class GamingPayloadDelegate {
    private static GamingPayloadDelegate sInstance = new GamingPayloadDelegate();
    public static void init(Intent intent) {
        GamingPayload.loadPayloadFromIntent(intent);
        String payload = GamingPayload.getPayload();
        if (payload != null) {
            sInstance.setPayload(payload);
        }
    }

    private native void setPayload(String payload);
}
