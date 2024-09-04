package com.wrapper.social.facebook;


import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.core.content.FileProvider;

import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.FacebookRequestError;
import com.facebook.GraphRequest;
import com.facebook.GraphResponse;
import com.facebook.gamingservices.CustomUpdate;
import com.facebook.gamingservices.GameRequestDialog;
import com.facebook.gamingservices.GamingContext;
import com.facebook.gamingservices.GamingImageUploader;
import com.facebook.gamingservices.ContextCreateDialog;
import com.facebook.gamingservices.ContextChooseDialog;
import com.facebook.gamingservices.ContextSwitchDialog;
import com.facebook.gamingservices.model.ContextChooseContent;
import com.facebook.gamingservices.model.ContextCreateContent;
import com.facebook.gamingservices.model.ContextSwitchContent;
import com.facebook.gamingservices.model.CustomUpdateContent;
import com.facebook.gamingservices.model.CustomUpdateLocalizedText;
import com.facebook.gamingservices.model.CustomUpdateMedia;
import com.facebook.share.Sharer;
import com.facebook.share.model.GameRequestContent;
import com.facebook.share.model.ShareLinkContent;
import com.facebook.share.widget.MessageDialog;
import com.facebook.share.widget.ShareDialog;

import com.facebook.gamingservices.FriendFinderDialog;
import com.google.gson.Gson;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;

enum ShareType {
    NEW_FRIEND,
    IN_GAME_FRIEND;
    public static ShareType fromInteger(int x) {
        switch(x) {
            case 0:
                return NEW_FRIEND;
            case 1:
                return IN_GAME_FRIEND;
        }
        return null;
    }
};

public class FacebookGamingShare {
    private static final String TAG = "FacebookGamingShare";
    // Named such to make it consistent with FB instant sdk.
    private static FacebookGamingShare sInstance;
    private static Activity sActivity;
    private static CallbackManager sCallbackManager;
    private static String sAuthority;

    public static void init(Activity activity, CallbackManager callbackManager, String authority) {
        sActivity = activity;
        sCallbackManager = callbackManager;
        sInstance = new FacebookGamingShare();
        sAuthority = authority;
    }

    public static void shareImage(String imgstr, String caption) {
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                GamingImageUploader imageUploader = new GamingImageUploader(sActivity);
                try {
                    File fileToShare = new File(imgstr);
                    Uri uriToImage = FileProvider.getUriForFile(sActivity, sAuthority, fileToShare);
                    Log.d(TAG, "NativeShare shareImage uri:" + uriToImage);
                    imageUploader.uploadToMediaLibrary(caption, uriToImage, true, graphResponse -> {
                        if (graphResponse.getError() != null) {
                            FacebookRequestError error = graphResponse.getError();
                            Log.e(FacebookGamingShare.TAG, "Media Upload Failed: " + error);
                            sInstance.onShareFailed(error.toString());
                        } else {
                            Log.d(FacebookGamingShare.TAG, "Media Upload Success: ");
                            sInstance.onShareComplete(true);
                        }
                    });
                } catch (FileNotFoundException error) {
                    Log.e(FacebookGamingShare.TAG, "FileException: " + error);
                    sInstance.onShareFailed(error.toString());
                }
            }
        });
    }
    public static void shareLink(int shareTypeInt, String msg, String linkStr) {
        shareCustomLinkToPost(msg, linkStr);

//        ShareType shareType = ShareType.fromInteger(shareTypeInt);
//        if (shareType == ShareType.IN_GAME_FRIEND) {
//            FacebookGamingShare.inviteToInGameFriends();
//        } else if (shareType == ShareType.NEW_FRIEND) {
//            FacebookGamingShare.inviteToNewFriend();
//        }
    }
    public static void chooseContext() {
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ContextChooseDialog dialog = new ContextChooseDialog(sActivity);
                ContextChooseContent content = new ContextChooseContent.Builder().build();
                if (!dialog.canShow(content)) {
                    sInstance.onContextChooseFailed("CLIENT_UNSUPPORTED_OPERATION");
                    return;
                }
                dialog.registerCallback(sCallbackManager, new FacebookCallback<ContextChooseDialog.Result>() {
                    @Override
                    public void onSuccess(ContextChooseDialog.Result result) {
                        sInstance.onContextChooseComplete(result.getContextID());
                    }

                    @Override
                    public void onCancel() {
                        sInstance.onContextChooseFailed(ErrorMessage.USER_CANCEL.toString());
                    }

                    @Override
                    public void onError(@NonNull FacebookException e) {
                        if (e.getMessage() == null) {
                            return;
                        }
                        if (e.getMessage().contains("The player dismissed the dialog")) {
                            sInstance.onContextChooseFailed(ErrorMessage.USER_CANCEL.toString());
                        } else {
                            sInstance.onContextChooseFailed(e.getMessage());
                        }

                    }
                });
                dialog.show(content);
            }
        });
    }
    public static void createContext(String playerId) {
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ContextCreateDialog dialog = new ContextCreateDialog(sActivity);
                ContextCreateContent content = new ContextCreateContent.Builder().setSuggestedPlayerID(playerId).build();
                if (!dialog.canShow(content)) {
                    sInstance.onContextCreateFailed("CLIENT_UNSUPPORTED_OPERATION");
                    return;
                }
                dialog.registerCallback(sCallbackManager, new FacebookCallback<ContextCreateDialog.Result>() {
                    @Override
                    public void onSuccess(ContextCreateDialog.Result result) {
                        sInstance.onContextCreateComplete(result.getContextID());
                    }

                    @Override
                    public void onCancel() {
                        sInstance.onContextCreateFailed(ErrorMessage.USER_CANCEL.toString());
                    }

                    @Override
                    public void onError(@NonNull FacebookException e) {
                        if (e.getMessage() == null) {
                            return;
                        }
                        if (e.getMessage().contains("The player dismissed the dialog")) {
                            sInstance.onContextCreateFailed(ErrorMessage.USER_CANCEL.toString());
                        } else {
                            sInstance.onContextCreateFailed(e.getMessage());
                        }
                    }
                });
                dialog.show(content);
            }
        });
    }
    public static void switchContext(String contextId) {
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ContextSwitchDialog dialog = new ContextSwitchDialog(sActivity);
                ContextSwitchContent content = new ContextSwitchContent.Builder().setContextID(contextId).build();
                if (!dialog.canShow(content)) {
                    sInstance.onContextSwitchFailed("CLIENT_UNSUPPORTED_OPERATION");
                    return;
                }
                dialog.registerCallback(sCallbackManager, new FacebookCallback<ContextSwitchDialog.Result>() {
                    @Override
                    public void onSuccess(ContextSwitchDialog.Result result) {
                        sInstance.onContextSwitchComplete();
                    }

                    @Override
                    public void onCancel() {
                        sInstance.onContextSwitchFailed(ErrorMessage.USER_CANCEL.toString());
                    }

                    @Override
                    public void onError(@NonNull FacebookException e) {
                        if (e.getMessage() == null) {
                            return;
                        }
                        if (e.getMessage().contains("The player dismissed the dialog")) {
                            sInstance.onContextSwitchFailed(ErrorMessage.USER_CANCEL.toString());
                        } else {
                            sInstance.onContextSwitchFailed(e.getMessage());
                        }
                    }
                });
                dialog.show(content);
            }
        });
    }
    public static void updateAsync(String text, String cta, String imagePath, String data) {
        CustomUpdateLocalizedText txt = new Gson().fromJson(text, CustomUpdateLocalizedText.class);
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                GamingContext context = GamingContext.getCurrentGamingContext();
                if (context == null) {
                    sInstance.onCustomUpdateFailed("CLIENT_UNSUPPORTED_OPERATION");
                    return;
                }
                Bitmap bitmap = BitmapFactory.decodeFile(imagePath);
                CustomUpdateContent content = new CustomUpdateContent.Builder(context, txt, bitmap)
                        .setData(data)
                        .setCta(new CustomUpdateLocalizedText(cta, new HashMap<>()))
                        .build();
                CustomUpdate.newCustomUpdateRequest(content, new GraphRequest.Callback() {
                    @Override
                    public void onCompleted(@NonNull GraphResponse graphResponse) {
                        if (graphResponse.getError() != null) {
                            sInstance.onCustomUpdateFailed(graphResponse.getError().getErrorMessage());
                        } else {
                            sInstance.onCustomUpdateSuccess();
                        }
                    }
                }).executeAsync();
            }
        });
    }

    private static void inviteToNewFriend() {
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                FriendFinderDialog dialog = new FriendFinderDialog(sActivity);
                // if we want to get notified when the dialog is closed
                // we can register a Callback
                dialog.registerCallback(
                        sCallbackManager,
                        new FacebookCallback<FriendFinderDialog.Result>() {
                            @Override
                            public void onSuccess(FriendFinderDialog.Result friendFinderResult) {
                                Log.v(TAG, "Player Finder Dialog Success!!");
                                sInstance.onShareComplete(true);
                            }

                            @Override
                            public void onCancel() {
                                Log.v(TAG, "Facebook FriendFinderDialog cancel!");
                                sInstance.onShareFailed(ErrorMessage.USER_CANCEL.toString());
                            }

                            @Override
                            public void onError(FacebookException exception) {
                                if (exception.getMessage() == null) {
                                    return;
                                }
                                Log.v(TAG, exception.toString());
                                sInstance.onShareFailed(exception.getLocalizedMessage());
                            }
                        });
                dialog.show();
            }
        });

    }

    private static void inviteToInGameFriends() {
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                GameRequestDialog requestDialog = new GameRequestDialog(sActivity);
                requestDialog.registerCallback(sCallbackManager, new FacebookCallback<GameRequestDialog.Result>() {
                    public void onSuccess(GameRequestDialog.Result result) {
                        Log.v(TAG, "Facebook GameRequestDialog Success!!");
                        sInstance.onShareComplete(true);
                    }

                    public void onCancel() {
                        Log.v(TAG, "Facebook GameRequestDialog cancel!");
                        sInstance.onShareFailed(ErrorMessage.USER_CANCEL.toString());
                    }

                    public void onError(FacebookException error) {
                        if (error.getMessage() == null) {
                            return;
                        }
                        Log.v(TAG, error.toString());
                        sInstance.onShareFailed(error.getLocalizedMessage());
                    }
                });
                GameRequestContent content = new GameRequestContent.Builder()
                        .setMessage("Come play this level with me")
                        .setActionType(GameRequestContent.ActionType.INVITE)
                        .setFilters(GameRequestContent.Filters.APP_USERS)
                        .build();
                Log.v(TAG,content.getFilters().toString());
                requestDialog.show(content);
            }
        });
    }

    private static void shareCustomLinkToPost(String msg, String linkStr){
        if (linkStr == null || msg == null) {
            sInstance.onShareFailed("empty params");
            return;
        }
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ShareLinkContent content = new ShareLinkContent.Builder()
                        .setContentUrl(Uri.parse(linkStr))
                        .setQuote(msg)
                        .build();
                ShareDialog shareDialog = new ShareDialog(sActivity);
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
                        if (e.getMessage() == null) {
                            return;
                        }
                        sInstance.onShareFailed(e.getLocalizedMessage());
                    }
                });
                shareDialog.show(content);
            }
        });
    }
    private native void onShareComplete(boolean status);
    private native void onShareFailed(String error);
    private native void onContextChooseComplete(String contextId);
    private native void onContextChooseFailed(String error);
    private native void onContextCreateComplete(String contextId);
    private native void onContextCreateFailed(String error);
    private native void onContextSwitchComplete();
    private native void onContextSwitchFailed(String error);
    private native void onCustomUpdateSuccess();
    private native void onCustomUpdateFailed(String error);
}

