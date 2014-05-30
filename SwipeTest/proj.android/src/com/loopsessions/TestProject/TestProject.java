package com.loopsessions.TestProject;

import org.cocos2dx.cpp.Cocos2dxActivity;

import jp.live_aid.aid.AdController;
import android.app.Activity;
import android.app.NativeActivity;
import android.os.Bundle;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.view.ViewGroup;
import android.util.Log;

// The name of .so is specified in AndroidMenifest.xml. NativityActivity will load it automatically for you.
// You can use "System.loadLibrary()" to load other .so files.

public class TestProject extends NativeActivity{

	public static TestProject myActivity;
	static final int WC = ViewGroup.LayoutParams.WRAP_CONTENT;

	static final int MC = LinearLayout.LayoutParams.MATCH_PARENT;

	public static LinearLayout linearLayout;

	public static PopupWindow popUpWindow;
	private static AdController mAidAdController = null;

    public static void setAidAdView() {
        final Activity activity = (Activity)Cocos2dxActivity.getContext();

        activity.runOnUiThread(new Runnable() {
            public void run() {
                if (mAidAdController == null) {
                    String MEDIA_CODE = "jp.nyanko.puncho";
                    mAidAdController = new AdController(MEDIA_CODE, activity);
                }
                mAidAdController.startPreloading();
                mAidAdController.showDialog(AdController.DialogType.ON_EXIT);
            }
        });
    }





}

