package com.lsm1987.egsnsplugin;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;

import com.epicgames.ue4.GameActivity;

import java.util.ArrayList;
import java.util.List;

/**
 * 플러그인 로직과 GameActivity 를 연결
 */

public class EGSnsGameActivityUtil
{
    public interface ActivityResultHandler
    {
        void onActivityResult(int requestCode, int resultCode, Intent data);
    }

    private static List<ActivityResultHandler> activityResultHandlers = new ArrayList<ActivityResultHandler>();

    public static Activity getActivity()
    {
        return GameActivity.Get();
    }

    public static void addActivityResultHandler(ActivityResultHandler handler)
    {
        if (activityResultHandlers.contains(handler))
        {
            Log.d("EGSnsGameActivityUtil", "Already added ActivityResultHandler");
            return;
        }

        activityResultHandlers.add(handler);
    }

    public static void removeActivityResultHandler(ActivityResultHandler handler)
    {
        boolean isRemoved = activityResultHandlers.remove(handler);

        if (!isRemoved)
        {
            Log.d("EGSnsGameActivityUtil", "Remove ActivityResultHandler failed. Not exist in handlers");
        }
    }

    public static void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        for (ActivityResultHandler handler : activityResultHandlers)
        {
            handler.onActivityResult(requestCode, resultCode, data);
        }
    }
}
