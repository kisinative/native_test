package net.nend.NendModule;

import java.util.ArrayList;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import net.nend.android.NendAdIconLoader;
import net.nend.android.NendAdIconLoader.OnClickListner;
import net.nend.android.NendAdIconLoader.OnFailedListner;
import net.nend.android.NendAdIconLoader.OnReceiveListner;
import net.nend.android.NendAdIconView;
import net.nend.android.NendIconError;

public class NendIconModule {

	//表示するアイコン個数
	public static final int ICON_DISPLAY_COUNT = 4;
	//IconLoader
	private static NendAdIconLoader mIconLoader;
	//IconView
	private static ArrayList<NendAdIconView> adIconViewArray;

	public static void createIconLoader(final String apiKey, final String spotID) {
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader == null){
					int intSpotID = Integer.parseInt(spotID);
					mIconLoader = new NendAdIconLoader(activity.getApplicationContext(), intSpotID, apiKey);
					mIconLoader.setOnReceiveLisner(sOnReceiveListner);
					mIconLoader.setOnFailedListner(sOnFailedListner);
					mIconLoader.setOnClickListner(sOnClickListner);
					adIconViewArray = new ArrayList<NendAdIconView>();
				}
			}
		});
	}
	
	public static void createIconView(final float x, final float y){

		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					
					//IconViewの生成
					NendAdIconView iconView = new NendAdIconView(activity.getApplicationContext());
			
					//レイアウト
					FrameLayout.LayoutParams adLayoutParams = new FrameLayout.LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT);
					//座標を指定
					adLayoutParams.setMargins((int)x, (int)y, 0, 0);
					adLayoutParams.gravity = Gravity.TOP | Gravity.LEFT;
					//IconViewの追加
					activity.addContentView(iconView, adLayoutParams);
					//IconLoaderへ設定
					mIconLoader.addIconView(iconView);
					//IconViewを保持する
					adIconViewArray.add(iconView);

			        //IconLoaderへ設定
					mIconLoader.addIconView(iconView);
					//IconViewを保持する
					adIconViewArray.add(iconView);
				}
			}
		});
	}

	public static void createIconViewBottom(){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {

				if(mIconLoader != null){

					//IconViewを設置するレイアウト
					LinearLayout baseLayout = new LinearLayout(activity);
					baseLayout.setGravity(Gravity.BOTTOM | Gravity.CENTER);
					
					for(int i = adIconViewArray.size() ; i < ICON_DISPLAY_COUNT ; i++){
						//iconの生成
						NendAdIconView iconView = new NendAdIconView(activity.getApplicationContext());
						baseLayout.addView(iconView);

						//loaderへiconを追加
						mIconLoader.addIconView(iconView);
						//制御用にiconを保持
						adIconViewArray.add(iconView);
					}
					View contentView = ((ViewGroup)activity.findViewById(android.R.id.content)).getChildAt(0);
			        ((ViewGroup)contentView).addView(baseLayout);
				}
			}
		});
	}

	public static void createIconViewTop(){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){

					//IconViewを設置するレイアウト
					LinearLayout baseLayout = new LinearLayout(activity);
					baseLayout.setGravity(Gravity.TOP | Gravity.CENTER);
					
					for(int i = adIconViewArray.size() ; i < ICON_DISPLAY_COUNT ; i++){
						//iconの生成
						NendAdIconView iconView = new NendAdIconView(activity.getApplicationContext());

						//iconのレイアウト
						baseLayout.addView(iconView);

						//loaderへiconを追加
						mIconLoader.addIconView(iconView);
						//制御用にiconを保持
						adIconViewArray.add(iconView);
					}
					View contentView = ((ViewGroup)activity.findViewById(android.R.id.content)).getChildAt(0);
			        ((ViewGroup)contentView).addView(baseLayout);
				}
			}
		});
	}

	public static void loadIconLoader() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					mIconLoader.loadAd();
				}	
			}
		});
	}
	
	public static void hideIconView(){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					for(int i =0 ; i < adIconViewArray.size() ; i++){
						NendAdIconView iconView = adIconViewArray.get(i);
						iconView.setVisibility(View.INVISIBLE);
					}
				}
			}
		});
	}

	public static void showIconView(){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					for(int i =0 ; i < adIconViewArray.size() ; i++){
						NendAdIconView iconView = adIconViewArray.get(i);
						iconView.setVisibility(View.VISIBLE);
					}
				}
			}
		});
	}

	public static void pauseIconView(){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					mIconLoader.pause();
				}
			}
		});
	}

	public static void resumeIconView(){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					mIconLoader.resume();
				}
			}
		});
	}

	private static OnReceiveListner sOnReceiveListner = new OnReceiveListner() {
		
		@Override
		public void onReceiveAd(NendAdIconView iconView) {
			NendIconModule.onReceiveIconAd();
		}
	};

	private static OnClickListner sOnClickListner = new OnClickListner() {
		
		@Override
		public void onClick(NendAdIconView iconView) {
			NendIconModule.onClickIconAd();
		}
	};

	private static OnFailedListner sOnFailedListner = new OnFailedListner() {
		
		@Override
		public void onFailedToReceiveAd(NendIconError iconError) {
			NendIconModule.onFailedIconAd();
		}
	};

	public static native void onReceiveIconAd();
	public static native void onFailedIconAd();
	public static native void onClickIconAd();
}
