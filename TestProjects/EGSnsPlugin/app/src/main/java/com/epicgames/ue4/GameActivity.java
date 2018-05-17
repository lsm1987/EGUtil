package com.epicgames.ue4;

import android.content.Intent;
import android.content.res.AssetManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.lsm1987.egsnsplugin.EGSnsGameActivityUtil;
import com.lsm1987.egsnsplugin.EGSnsTwitter;
import com.lsm1987.egsnsplugin.R;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class GameActivity extends AppCompatActivity {

    private EGSnsTwitter twitter = new EGSnsTwitter();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);

        EGSnsGameActivityUtil.setActivity(this);

        Properties pluginProperties = LoadPluginProperties();

        String twitterCustomerKey = pluginProperties.getProperty("twitter.customerKey", "TWITTER_CUSTOMER_KEY");
        String twitterCustomerSecret = pluginProperties.getProperty("twitter.customerSecret", "TWITTER_CUSTOMER_SECRET");
        twitter.AndroidThunkJava_Initialize(twitterCustomerKey, twitterCustomerSecret);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        EGSnsGameActivityUtil.onActivityResult(requestCode, resultCode, data);
    }

    public void onClickBtnLogin(View v) {
        Log.d("GameActivity", "onClickBtnLogin");
        twitter.AndroidThunkJava_Login();
    }

    private Properties LoadPluginProperties()
    {
        Properties properties = new Properties();

        try
        {
            AssetManager assetManager = getApplicationContext().getAssets();
            InputStream inputStream = assetManager.open("egsnsplugin.properties");
            properties.load(inputStream);
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }

        return properties;
    }
}
