package com.lsm1987.egsnsplugin;

import android.util.Log;

public class EGSnsTwitter
{
    public void AndroidThunkJava_Initialize(String customerKey, String customerSecret)
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_Initialize()");
        Log.d("EGSnsPlugin", "customerKey: " + customerKey);
        Log.d("EGSnsPlugin", "customerSecret: " + customerSecret);
    }

    public void AndroidThunkJava_Login()
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_Login()");
    }

    public boolean AndroidThunkJava_IsLoggedin()
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_IsLoggedin()");
        return false;
    }

    public void AndroidThunkJava_Logout()
    {
        Log.d("EGSnsPlugin", "EGSnsTwitter::AndroidThunkJava_Logout()");
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
}
