package com.epicgames.ue4;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.lsm1987.egsnsplugin.EGSnsTwitter;
import com.lsm1987.egsnsplugin.R;

public class GameActivity extends AppCompatActivity {

    static GameActivity _activity;

    private EGSnsTwitter twitter = new EGSnsTwitter();

    /** Access singleton activity for game. **/
    public static GameActivity Get()
    {
        return _activity;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);

        _activity = this;

        twitter.AndroidThunkJava_Initialize("TWITTER_CUSTOMER_KEY", "TWITTER_CUSTOMER_SECRET");
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        // Pass the activity result to the login button.
        twitter.onActivityResult(requestCode, resultCode, data);
    }

    public void onClickBtnLogin(View v) {
        Log.d("GameActivity", "onClickBtnLogin");
        twitter.AndroidThunkJava_Login();
    }
}
