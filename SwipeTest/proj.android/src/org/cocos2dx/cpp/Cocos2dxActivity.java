package org.cocos2dx.cpp;

import net.nend.android.NendAdIconLayout;
//import com.MyCompany.AwesomeGame.R;
//import android.app.Activity;
import android.app.NativeActivity;
import android.os.Bundle;
//import android.util.Log;
//import android.widget.RelativeLayout;

import android.view.Gravity;
//import android.view.WindowManager;

import android.widget.LinearLayout;

import android.widget.PopupWindow;
import android.view.ViewGroup;

import android.view.ViewGroup.LayoutParams;

// The name of .so is specified in AndroidMenifest.xml. NativityActivity will load it automatically for you.
// You can use "System.loadLibrary()" to load other .so files.

public class Cocos2dxActivity extends NativeActivity{
//public class Cocos2dxActivity extends Activity{

	public static Cocos2dxActivity myActivity;
	static final int WC = ViewGroup.LayoutParams.WRAP_CONTENT;

	static final int MC = LinearLayout.LayoutParams.MATCH_PARENT;

	public static LinearLayout linearLayout;

	public static PopupWindow popUpWindow;


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);

		myActivity = this;

// XMLから実行
//		setContentView(R.layout.icon_layout);

//		setContentView(R.layout.icon_layout);
//		RelativeLayout rootLayout = (RelativeLayout)findViewById(R.id.root);
//		// ①spotIDとapiKey、アイコン数を指定して、NendAdIconLayoutを生成
//		NendAdIconLayout iconLayout = new NendAdIconLayout(getApplicationContext(),
//		143994, "3d3b135cbf2fedde5e1e214d67c55e9b62a9f677", 4);
//		Log.e("tag", ""+rootLayout);
//		Log.e("tag", ""+iconLayout);
//		// ②loadAdメソッドを実行し、広告取得を開始する
//		iconLayout.loadAd();
//		// ③レイアウトに追加する。
//		rootLayout.addView(iconLayout);

	}
	public static void adViewOn()

	{

		myActivity.runOnUiThread(new Runnable()  {

			@Override

			public void run()  {

				System.out.println("adViewOn()が実行されました。広告を表示します。");

				popUpWindow = new PopupWindow(myActivity);


				// ①spotIDとapiKey、アイコン数を指定して、NendAdIconLayoutを生成
				NendAdIconLayout iconLayout = new NendAdIconLayout(myActivity, 143994, "3d3b135cbf2fedde5e1e214d67c55e9b62a9f677", 4);

				// ②loadAdメソッドを実行し、広告取得を開始する
				iconLayout.loadAd();


				//広告サイズを変えたい場合は、以下を変更します。

				popUpWindow.setWidth(320);

				popUpWindow.setHeight(50);

				popUpWindow.setWindowLayoutMode(LayoutParams.WRAP_CONTENT,

				LayoutParams.WRAP_CONTENT);

				popUpWindow.setClippingEnabled(false);

				LinearLayout layout = new LinearLayout(myActivity);

				layout.addView(iconLayout, new LinearLayout.LayoutParams(WC, WC));

				popUpWindow.setContentView(layout);

				popUpWindow.showAtLocation(layout, Gravity.BOTTOM, 0, 0);

				popUpWindow.update();

			}

		});

	}//:adViewOn




}

