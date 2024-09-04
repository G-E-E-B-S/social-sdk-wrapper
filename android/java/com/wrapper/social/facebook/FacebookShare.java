package com.wrapper.social.facebook;


import android.app.Activity;
import android.net.Uri;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.core.content.FileProvider;

import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.FacebookRequestError;
import com.facebook.gamingservices.GamingImageUploader;
import com.facebook.share.Sharer;
import com.facebook.share.model.ShareLinkContent;
import com.facebook.share.widget.MessageDialog;
import com.facebook.share.widget.ShareDialog;

import java.io.File;
import java.io.FileNotFoundException;

public class FacebookShare {
    private static final String TAG = "FacebookShare";
    private static Activity sActivity;
    private static CallbackManager sCallbackManager;
    private static String sAuthority;
    private static FacebookShare sInstance;

    public static void init(Activity activity, CallbackManager callbackManager, String authority) {
        sActivity = activity;
        sCallbackManager = callbackManager;
        sAuthority = authority;
        sInstance = new FacebookShare();
    }

    public static void shareScoreImage(String imgstr) {
        GamingImageUploader imageUploader = new GamingImageUploader(sActivity);
        try {
            File fileToShare = new File(imgstr);
            Uri uriToImage = FileProvider.getUriForFile(sActivity, sAuthority, fileToShare);
            Log.d(TAG, "NativeShare shareImage uri:" + uriToImage);
            imageUploader.uploadToMediaLibrary(
                    "Beat Score Image", uriToImage, true, graphResponse -> {
                        if (graphResponse.getError() != null) {
                            FacebookRequestError error = graphResponse.getError();
                            sInstance.onShareFailed(error.getErrorMessage());
                            Log.e(FacebookShare.TAG, "Media Upload Failed: " + graphResponse.getError().toString());
                        } else {
                            Log.d(FacebookShare.TAG, "Media Upload Success: ");
                            sInstance.onShareComplete(true);
                        }
                    });
        } catch (FileNotFoundException e) {
            sInstance.onShareFailed(e.getLocalizedMessage());
            Log.e(FacebookShare.TAG, "FileException: " + e);
        }
    }

    public static void shareLink(String msg, String linkStr) {
        if (linkStr == null) {
            sInstance.onShareFailed("Empty params");
            return;
        }
        final ShareDialog shareDialog = new ShareDialog(sActivity);
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ShareLinkContent content = new ShareLinkContent.Builder()
                        .setContentUrl(Uri.parse(linkStr))
                        .setQuote(msg)
                        .build();
                shareDialog.registerCallback(sCallbackManager, new FacebookCallback<Sharer.Result>() {
                    @Override
                    public void onSuccess(Sharer.Result result) {
                        sInstance.onShareComplete(true);
                    }

                    @Override
                    public void onCancel() {
                        sInstance.onShareFailed(ErrorMessage.USER_CANCEL.toString());
                    }

                    @Override
                    public void onError(@NonNull FacebookException e) {
                        sInstance.onShareFailed(e.getLocalizedMessage());
                    }
                });
                shareDialog.show(sActivity, content);
            }
        });
    }

    public static void messageLink(String msg, String linkStr) {
        if (linkStr == null) {
            return;
        }
        final String fLinkStr = linkStr;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                final MessageDialog messageDialog = new MessageDialog(sActivity);
                messageDialog.registerCallback(sCallbackManager, new FacebookCallback<Sharer.Result>() {
                    @Override
                    public void onSuccess(Sharer.Result result) {
                        Log.v(TAG, "Facebook MessageDialog Success!!");
                        sInstance.onShareComplete(true);
                    }

                    @Override
                    public void onCancel() {
                        Log.v(TAG, "Facebook MessageDialog cancel!");
                        sInstance.onShareFailed(ErrorMessage.USER_CANCEL.toString());
                    }

                    @Override
                    public void onError(FacebookException error) {
                        Log.v(TAG, "Facebook MessageDialog error!!!:" + error.toString());
                        // NOTE: Fallback to share
                        shareLink(msg, fLinkStr);
                    }
                });
                ShareLinkContent content = new ShareLinkContent.Builder()
                        .setContentUrl(Uri.parse(fLinkStr))
                        .setQuote(msg)
                        .build();
                messageDialog.show(sActivity, content);
            }
        });
    }
    private native void onShareComplete(boolean status);
    private native void onShareFailed(String error);
}

