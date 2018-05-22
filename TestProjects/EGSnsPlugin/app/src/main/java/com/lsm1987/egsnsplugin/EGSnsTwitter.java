package com.lsm1987.egsnsplugin;

import android.content.Intent;
import android.util.Log;

import java.io.File;

import egsnsplugin.com.twitter.sdk.android.core.Callback;
import egsnsplugin.com.twitter.sdk.android.core.DefaultLogger;
import egsnsplugin.com.twitter.sdk.android.core.Result;
import egsnsplugin.com.twitter.sdk.android.core.Twitter;
import egsnsplugin.com.twitter.sdk.android.core.TwitterApiClient;
import egsnsplugin.com.twitter.sdk.android.core.TwitterAuthConfig;
import egsnsplugin.com.twitter.sdk.android.core.TwitterConfig;
import egsnsplugin.com.twitter.sdk.android.core.TwitterCore;
import egsnsplugin.com.twitter.sdk.android.core.TwitterException;
import egsnsplugin.com.twitter.sdk.android.core.TwitterSession;
import egsnsplugin.com.twitter.sdk.android.core.identity.TwitterAuthClient;
import egsnsplugin.com.twitter.sdk.android.core.internal.CommonUtils;
import egsnsplugin.com.twitter.sdk.android.core.models.Media;
import egsnsplugin.com.twitter.sdk.android.core.models.Tweet;
import egsnsplugin.okhttp3.MediaType;
import egsnsplugin.okhttp3.RequestBody;

public class EGSnsTwitter implements EGSnsGameActivityUtil.ActivityResultHandler
{
    public enum ErrorCode {
        NO_ACTIVE_SESSION("TWITTER_NO_ACTIVE_SESSION"),
        MEDIA_FILE_NOT_EXIST("TWITTER_MEDIA_FILE_NOT_EXIST");

        private final String message;

        ErrorCode(final String message) {
            this.message = message;
        }

        @Override
        public String toString() {
            return message;
        }
    }

    volatile TwitterAuthClient authClient;
    Callback<TwitterSession> loginCallback;

    public void AndroidThunkJava_Initialize(String customerKey, String customerSecret)
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_Initialize()");
        Log.d("EGSnsPlugin", "customerKey: " + customerKey);
        Log.d("EGSnsPlugin", "customerSecret: " + customerSecret);

        TwitterConfig config = new TwitterConfig.Builder(EGSnsGameActivityUtil.getActivity())
                .logger(new DefaultLogger(Log.DEBUG))
                .twitterAuthConfig(new TwitterAuthConfig(customerKey, customerSecret))
                .debug(true)
                .build();
        Twitter.initialize(config);

        loginCallback = new Callback<TwitterSession>() {
            @Override
            public void success(Result<TwitterSession> result) {
                // Do something with result, which provides a TwitterSession for making API calls
                Log.d("EGSnsPlugin", "EGSnsTwitter loginCallback success");
                nativeOnLoggedIn(true);
            }

            @Override
            public void failure(TwitterException exception) {
                // Do something on failure
                Log.d("EGSnsPlugin", "EGSnsTwitter loginCallback failure. ex:" + exception.getMessage());
                nativeOnLoggedIn(false);
            }
        };

        EGSnsGameActivityUtil.addActivityResultHandler(this);
    }

    public void AndroidThunkJava_Finalize()
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_Finalize()");
        
        EGSnsGameActivityUtil.removeActivityResultHandler(this);
    }

    public void AndroidThunkJava_Login()
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_Login()");

        if (loginCallback == null)
        {
            CommonUtils.logOrThrowIllegalStateException(TwitterCore.TAG,
                    "Login callback must not be null, did you call Initialize?");
        }

        getTwitterAuthClient().authorize(EGSnsGameActivityUtil.getActivity(), loginCallback);
    }

    public void AndroidThunkJava_Logout()
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_Logout()");

        TwitterCore.getInstance().getSessionManager().clearActiveSession();
    }
    
    public boolean AndroidThunkJava_IsLoggedIn()
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_IsLoggedIn()");

        final TwitterSession activeSession = TwitterCore.getInstance().getSessionManager().getActiveSession();
        return (activeSession != null
            && activeSession.getAuthToken() != null
            && !activeSession.getAuthToken().isExpired());
    }

    public void AndroidThunkJava_ShareText(String text)
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_ShareText()");
        Log.d("EGSnsPlugin", "text: " + text);

        TwitterSession activeSession = TwitterCore.getInstance().getSessionManager().getActiveSession();
        if (activeSession == null)
        {
            onShareFail(ErrorCode.NO_ACTIVE_SESSION.toString());
            return;
        }

        uploadTweet(activeSession, text, null);
    }

    public void AndroidThunkJava_ShareImageFile(String text, String imageFilePath)
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_ShareImageFile()");
        Log.d("EGSnsPlugin", "text: " + text);
        Log.d("EGSnsPlugin", "imageFilePath: " + imageFilePath);

        TwitterSession activeSession = TwitterCore.getInstance().getSessionManager().getActiveSession();
        if (activeSession == null)
        {
            onShareFail(ErrorCode.NO_ACTIVE_SESSION.toString());
            return;
        }

        uploadTweet(activeSession, text, imageFilePath);
    }

    private TwitterAuthClient getTwitterAuthClient() {
        if (authClient == null) {
            synchronized (EGSnsTwitter.class) {
                if (authClient == null) {
                    authClient = new TwitterAuthClient();
                }
            }
        }
        return authClient;
    }

    private void uploadTweet(final TwitterSession session, final String text, final String mediaFilePath)
    {
        if (mediaFilePath != null) {
            uploadMedia(session, mediaFilePath, new Callback<Media>() {
                @Override
                public void success(Result<Media> result) {
                    uploadTweetWithMedia(session, text, result.data.mediaIdString);
                }

                @Override
                public void failure(TwitterException exception)
                {
                    onShareFail(exception.toString());
                }

            });
        } else {
            uploadTweetWithMedia(session, text, null);
        }
    }

    private void uploadMedia(TwitterSession session, String mediaFilePath, Callback<Media> callback)
    {
        final File file = new File(mediaFilePath);
        if (!file.isFile())
        {
            onShareFail(ErrorCode.MEDIA_FILE_NOT_EXIST.toString());
            return;
        }

        final TwitterApiClient client = TwitterCore.getInstance().getApiClient(session);
        final String mimeType = EGSnsFileUtils.getMimeType(file);
        final RequestBody media = RequestBody.create(MediaType.parse(mimeType), file);

        client.getMediaService().upload(media, null, null).enqueue(callback);
    }

    private void uploadTweetWithMedia(TwitterSession session, String text, String mediaId)
    {
        final TwitterApiClient client = TwitterCore.getInstance().getApiClient(session);

        client.getStatusesService().update(text, null, null, null, null, null, null, true, mediaId)
                .enqueue(
                        new Callback<Tweet>() {
                            @Override
                            public void success(Result<Tweet> result) {
                                onShareSuccess();
                            }

                            @Override
                            public void failure(TwitterException exception) {
                                onShareFail(exception.toString());
                            }
                        });
    }

    private void onShareSuccess()
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::onShareSuccess()");
    }

    private void onShareFail(String ErroeMessage)
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::onShareFailed()");
        Log.d("EGSnsPlugin", "ErroeMessage: " + ErroeMessage);
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == getTwitterAuthClient().getRequestCode()) {
            getTwitterAuthClient().onActivityResult(requestCode, resultCode, data);
        }
    }

    private native void nativeOnLoggedIn(boolean bSuccess);
}
