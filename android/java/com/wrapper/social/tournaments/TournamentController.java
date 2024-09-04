package com.wrapper.social.tournaments;

import android.app.Activity;
import android.media.Image;
import android.util.Log;

import com.wrapper.social.facebook.ErrorMessage;
import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.bolts.Task;
import com.facebook.gamingservices.Tournament;
import com.facebook.gamingservices.TournamentConfig;
import com.facebook.gamingservices.TournamentFetcher;
import com.facebook.gamingservices.TournamentShareDialog;
import com.facebook.gamingservices.TournamentUpdater;
import com.facebook.gamingservices.internal.TournamentScoreType;
import com.facebook.gamingservices.internal.TournamentSortOrder;
import com.google.gson.Gson;

import java.time.Instant;
import java.util.List;

public class TournamentController {
    private static String TAG = "TournamentController";
    private static Activity sActivity;
    private static TournamentFetcher tournamentFetcher;
    private static TournamentUpdater tournamentUpdater;
    private static CallbackManager mCallbackManager;
    private static TournamentController sInstance;

    public static void init(Activity activity, CallbackManager callbackManager) {
        sActivity = activity;
        mCallbackManager = callbackManager;
        sInstance = new TournamentController();
        tournamentFetcher = new TournamentFetcher();
        tournamentUpdater = new TournamentUpdater();
    }

    public static void createTournament(int score, String title, int endTime, String scoreType, String image, String sortOrder, String payload) {
        Instant tEndTime = Instant.ofEpochSecond(endTime);
        TournamentScoreType tScoreType;
        TournamentSortOrder tSortOrder;
//        Image tImage;
        if (scoreType.equals(TournamentScoreType.TIME.toString())) {
            tScoreType = TournamentScoreType.TIME;
        } else {
            tScoreType = TournamentScoreType.NUMERIC;
        }
        if (sortOrder.equals(TournamentSortOrder.LowerIsBetter.toString())) {
            tSortOrder = TournamentSortOrder.LowerIsBetter;
        } else {
            tSortOrder = TournamentSortOrder.HigherIsBetter;
        }
        TournamentConfig newTournamentConfig = getTournamentConfig(title, tEndTime, tScoreType, tSortOrder, payload);
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                try {
                    TournamentShareDialog shareDialog = new TournamentShareDialog(sActivity);
                    shareDialog.registerCallback(
                            getCallbackManager(),
                            new FacebookCallback<TournamentShareDialog.Result>() {
                                @Override
                                public void onSuccess(TournamentShareDialog.Result result) {
                                    //result.getTournamentID // Will return the newly created Tournament's ID
                                    Log.e(TAG, "Tournament Creation Complete" + result.getTournamentID());
                                    sInstance.onTournamentCreateSuccess(result.getTournamentID());
                                }

                                @Override
                                public void onCancel() {
                                    // The user cancelled the dialog without creating and sharing the Tournament
                                    Log.e(TAG, "Tournament Creation Cancelled");
                                    sInstance.onTournamentCreatefailed(ErrorMessage.USER_CANCEL.toString());
                                }

                                @Override
                                public void onError(FacebookException error) {
                                    Log.e(TAG, "Tournament Creation failed" + error);
                                    // Handle any dialog errors
                                    Gson gson = new Gson();
                                    final String errorString = gson.toJson(error);
                                    sInstance.onTournamentCreatefailed(errorString);
                                }
                            });

                    shareDialog.show(score, newTournamentConfig);
                } catch (Exception e) {
                    sInstance.onTournamentCreatefailed(e.toString());
                }
            }
        });
    }

    public static void shareTournament(int score, String tournamentId) {
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                try {
                    TournamentShareDialog shareDialog = new TournamentShareDialog(sActivity);
                    shareDialog.registerCallback(getCallbackManager(),
                            new FacebookCallback<TournamentShareDialog.Result>() {
                                @Override
                                public void onSuccess(TournamentShareDialog.Result result) {
                                    Log.e(TAG, "Tournament Share Complete" + result);
                                    sInstance.onTournamentShareSuccess(result.getTournamentID());
                                }

                                @Override
                                public void onCancel() {
                                    Log.e(TAG, "Tournament Share Cancelled");

                                    sInstance.onTournamentSharefailed(ErrorMessage.USER_CANCEL.toString());
                                }

                                @Override
                                public void onError(FacebookException error) {
                                    Log.e(TAG, "Tournament Share failed" + error);
                                    Gson gson = new Gson();
                                    final String errorString = gson.toJson(error);
                                    sInstance.onTournamentSharefailed(errorString);
                                }
                            });
                    shareDialog.show(score, new Tournament(tournamentId, null, null, null));
                } catch (Exception e) {
                    sInstance.onTournamentSharefailed(e.toString());
                }
            }
        });
    }

    public static void postTournamentScore(int score, String tournamentId) {
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                try {
                    Tournament selectedTournament = new Tournament(tournamentId, null, null, null);
                    TournamentPostScoreCallback tournamentScoreUpdater = new TournamentPostScoreCallback() {
                        @Override
                        public void onPostScoreComplete(Boolean status) {
                            if (status) {
                                sInstance.onPostTournamentScoreSuccess(selectedTournament.identifier);
                            } else {
                                sInstance.onPostTournamentScorefailed("POST_SCORE_FAILED");
                            }
                        }
                    };
                    tournamentScoreUpdater.postTournamentScore(score, selectedTournament);
                } catch (Exception e) {
                    sInstance.onPostTournamentScorefailed(e.toString());
                }
            }
        });
    }

    public static void getTournaments() {
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                try {
                    TournamentFetchCallback tournamentFetcher = new TournamentFetchCallback() {
                        @Override
                        public void onFetchComplete(List<Tournament> tournaments) {
                            Gson gson = new Gson();
                            sInstance.onTournamentsFetchComplete(gson.toJson(tournaments));
                        }
                    };
                    tournamentFetcher.fetchTournaments();
                } catch (Exception e) {
                    sInstance.onTournamentsFetchComplete("[]");
                }
            }
        });
    }

    public static void getTournament() {
        sInstance.onTournamentFetchComplete("");
    }

    private static CallbackManager getCallbackManager() {
        return mCallbackManager;
    }

    private static TournamentConfig getTournamentConfig(String title, Instant endTime, TournamentScoreType scoreType, TournamentSortOrder sortOrder, String payload) {
        return new TournamentConfig.Builder()
                .setTournamentTitle(title)
                .setTournamentEndTime(endTime)
                .setTournamentScoreType(scoreType)
                .setTournamentSortOrder(sortOrder)
                .setTournamentPayload(payload)
//                .setTournamentImage(image)
                .build();
    }

    public static class TournamentFetchCallback {
        public void onFetchComplete(List<Tournament> tournaments) {
            throw new RuntimeException("ERROR!");
        }

        public void fetchTournaments() {
            Task<List<Tournament>> tournaments = tournamentFetcher.fetchTournaments().getTask();
            tournaments.onSuccess((tournamentList) -> {
                onFetchComplete(tournamentList.getResult());
                return true;
            });
        }
    }

    public static class TournamentPostScoreCallback {
        public void onPostScoreComplete(Boolean status) {
            throw new RuntimeException("ERROR!");
        }

        public void postTournamentScore(int score, Tournament selectedTournament) {
            tournamentUpdater.update(selectedTournament, score).getTask().onSuccess((booleanTask) -> {
                onPostScoreComplete(booleanTask.getResult());
                return true;
            });
        }
    }

    private native void onTournamentCreateSuccess(String tournamentId);

    private native void onTournamentCreatefailed(String error);

    private native void onTournamentShareSuccess(String tournamentId);

    private native void onTournamentSharefailed(String error);

    private native void onPostTournamentScoreSuccess(String tournamentId);

    private native void onPostTournamentScorefailed(String error);

    private native void onTournamentsFetchComplete(String tournaments);

    private native void onTournamentFetchComplete(String tournament);
}