package com.lsm1987.egsnsplugin;

import android.content.Intent;
import android.util.Log;

import egsnsplugin.com.twitter.sdk.android.core.Callback;
import egsnsplugin.com.twitter.sdk.android.core.DefaultLogger;
import egsnsplugin.com.twitter.sdk.android.core.Result;
import egsnsplugin.com.twitter.sdk.android.core.Twitter;
import egsnsplugin.com.twitter.sdk.android.core.TwitterAuthConfig;
import egsnsplugin.com.twitter.sdk.android.core.TwitterConfig;
import egsnsplugin.com.twitter.sdk.android.core.TwitterCore;
import egsnsplugin.com.twitter.sdk.android.core.TwitterException;
import egsnsplugin.com.twitter.sdk.android.core.TwitterSession;
import egsnsplugin.com.twitter.sdk.android.core.identity.TwitterAuthClient;
import egsnsplugin.com.twitter.sdk.android.core.internal.CommonUtils;

public class EGSnsTwitter implements EGSnsGameActivityUtil.ActivityResultHandler
{
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
            }

            @Override
            public void failure(TwitterException exception) {
                // Do something on failure
                Log.d("EGSnsPlugin", "EGSnsTwitter loginCallback failure. ex:" + exception.getMessage());
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
    }
    
    public boolean AndroidThunkJava_IsLoggedIn()
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_IsLoggedIn()");
        return false;
    }

    public void AndroidThunkJava_ShareText(String text)
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_ShareText()");
        Log.d("EGSnsPlugin", "text: " + text);
    }

    public void AndroidThunkJava_ShareImageFile(String text, String imageFilePath)
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_ShareImageFile()");
        Log.d("EGSnsPlugin", "text: " + text);
        Log.d("EGSnsPlugin", "imageFilePath: " + imageFilePath);
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

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == getTwitterAuthClient().getRequestCode()) {
            getTwitterAuthClient().onActivityResult(requestCode, resultCode, data);
        }
    }
}
