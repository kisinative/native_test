package jp.GameFeat.GameFeatModule;

//import org.cocos2dx.cpp.Cocos2dxActivity;

//import com.loopsessions.TestProject.TestProject;
import org.cocos2dx.cpp.Cocos2dxActivity;

import jp.GameFeat.GameFeatModule.GameFeat;

import jp.basicinc.gamefeat.android.sdk.controller.GameFeatAppController;

import android.os.Bundle;
//import android.util.Log;
import android.app.Activity;
import android.app.NativeActivity;
//import android.content.Context;
//import android.content.Intent;
//import android.content.SharedPreferences;
//import android.content.SharedPreferences.Editor;
//import android.content.pm.PackageManager;
//import android.content.pm.PackageManager.NameNotFoundException;
//import android.net.Uri;
//import android.os.Bundle;
//import android.os.Handler;
//import android.provider.Settings;
//import android.text.TextUtils;
//import android.util.Log;
//import android.view.Gravity;
//import android.view.View;
//import android.view.ViewGroup;
//import android.view.WindowManager;
//import android.view.ViewGroup.MarginLayoutParams;
import android.widget.LinearLayout;
//import android.widget.PopupWindow;
//import android.widget.RelativeLayout;
public class GameFeat extends NativeActivity{

	private static LinearLayout container;
	private static GameFeat me = null;
	static GameFeatAppController gfAppController;

	/////////////////////////////////
	// GAMEFEAT ICON
	/////////////////////////////////
	GFIcons gfIcons = null;

	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		me = this;
		container = new LinearLayout(me);
		me.addContentView(container, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT));

		gfAppController = new GameFeatAppController();
	}

    static {
         System.loadLibrary("game");
    }

    @Override
    public void onStart() {
    	super.onStart();
    	// 広告設定初期化
    	gfAppController.activateGF(me, true, true, true);
    }

    //================================================================================
  	// GAMEFEAT オファーウォール表示・非表示
  	//================================================================================
    public static void showGameFeatJNI()
    {
		System.out.println("-----------------koukokuaaaaaa--------------------");
        gfAppController.show(me);
    }

    //================================================================================
  	// GAMEFEAT 全画面表示・非表示
  	//================================================================================
    public static void showAllGameFeatJNI()
    {
		me.runOnUiThread(new Runnable(){
			@Override
			public void run() {
				gfAppController.showPopupAdDialog(me);
			}
		});
    }

    public static void hideAllGameFeatJNI()
    {
    }


    public void onStop() {
        super.onStop();
    }
}