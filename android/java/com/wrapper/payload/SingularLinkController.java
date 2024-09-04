package com.wrapper.payload;
import android.content.Intent;
import android.util.Log;

import com.singular.sdk.SingularConfig;
import com.singular.sdk.SingularLinkHandler;
import com.singular.sdk.SingularLinkParams;


public class SingularLinkController {
    private static String TAG = "SingularLinkController";
    private static String linkPayLoad = "";
    private static String deeplink = "";
    private static SingularLinkController sInstance;

    private SingularLinkController() {}
    public static void init() {
        sInstance = new SingularLinkController();
    }

    public static SingularConfig attachHandlerForDeepLink(SingularConfig singularConfig, Intent intent) {
        singularConfig.withSingularLink(intent, new SingularLinkHandler() {
            @Override
            public void onResolved(SingularLinkParams params) {
                // The deep link destination, as configured in the Manage Links page
                SingularLinkController.deeplink = params.getDeeplink();
                // The passthrough parameters added to the link, if any.
                SingularLinkController.linkPayLoad = params.getPassthrough();
                Log.d("Payload","attachHandlerForDeepLink deepLink = "+params.getDeeplink() + " passthrough = "+params.getPassthrough());
            }
        });
        return singularConfig;
    }

    public static void getLinkPayLoad() {
        sInstance.onInviteLinkFetchComplete(SingularLinkController.linkPayLoad);
    }

    public static String getDeeplink() {
        return SingularLinkController.deeplink;
    }

    private native void onInviteLinkFetchComplete(String linkPayLoad);

    private native void onInviteLinkFetchError(String error);

}
