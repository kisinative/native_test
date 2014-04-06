package net.nend.NendModule;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.FrameLayout;
import net.nend.android.NendAdListener;
import net.nend.android.NendAdView;

public class NendModule {

	private static NendAdView nendAdView;

	// 広告の初期化
	public static void createAdView(final String apiKey, final String spotID, final float x, final float y) {
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (nendAdView == null) {
					int intsSpotID = Integer.parseInt(spotID);

					nendAdView = new NendAdView(activity.getApplicationContext(), intsSpotID, apiKey);
					nendAdView.setListener(sAdListener);
			
					FrameLayout.LayoutParams adLayoutParams = new FrameLayout.LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT);
					//座標を指定する場合
					adLayoutParams.setMargins((int)x, (int)y, 0, 0);
					adLayoutParams.gravity = Gravity.TOP | Gravity.LEFT;
					activity.addContentView(nendAdView, adLayoutParams);

					nendAdView.loadAd();
				}
			}
		});
	}

	// 広告の初期化
	public static void createAdViewBottom(final String apiKey, final String spotID) {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (nendAdView == null) {
				int intsSpotID = Integer.parseInt(spotID);

				nendAdView = new NendAdView(activity.getApplicationContext(), intsSpotID, apiKey);
				nendAdView.setListener(sAdListener);

				FrameLayout.LayoutParams adParams = new FrameLayout.LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT);
				//下に表示する場合
				adParams.gravity = (Gravity.BOTTOM|Gravity.CENTER);
			
				activity.addContentView(nendAdView, adParams);
				nendAdView.loadAd();
				}
			}
		});

	}

	// 広告の初期化
	public static void createAdViewTop(final String apiKey, final String spotID) {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView == null) {
					int intsSpotID = Integer.parseInt(spotID);

					nendAdView = new NendAdView(activity.getApplicationContext(), intsSpotID, apiKey);
					nendAdView.setListener(sAdListener);

					FrameLayout.LayoutParams adParams = new FrameLayout.LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT);
					//下に表示する場合
					adParams.gravity = (Gravity.TOP|Gravity.CENTER);
			
					activity.addContentView(nendAdView, adParams);
					nendAdView.loadAd();
				}
			}
		});
	}

	// 広告の非表示
	public static void hideAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView != null) {
					nendAdView.setVisibility(View.INVISIBLE);
				}
			}
		});
	}

	// 広告の再表示
	public static void showAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView != null) {
					nendAdView.setVisibility(View.VISIBLE);
				}
			}
		});
	}
	
	// 広告の一時停止
	public static void pauseAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView != null) {
					nendAdView.pause();
				}
			}
		});
	}

	// 広告の再開
	public static void resumeAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView != null) {
					nendAdView.resume();
				}
			}
		});
	}
	
	private static NendAdListener sAdListener = new NendAdListener() {
		
		@Override
		public void onReceiveAd(NendAdView arg0) {
			NendModule.onReceiveAd();
		}
		
		@Override
		public void onFailedToReceiveAd(NendAdView arg0) {
			NendModule.onFailedToReceiveAd();
		}
		
		@Override
		public void onDismissScreen(NendAdView arg0) {
			NendModule.onDismissScreen();
		}
		
		@Override
		public void onClick(NendAdView arg0) {
			NendModule.onClick();
		}
	};
	
	public static native void onReceiveAd();
	public static native void onFailedToReceiveAd();
	public static native void onDismissScreen();
	public static native void onClick();
}
