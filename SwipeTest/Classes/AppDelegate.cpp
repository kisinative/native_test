#include "AppDelegate.h"
#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "Android/AdViewManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto eglView = EGLView::getInstance();

    director->setOpenGLView(eglView);

    // turn on display FPS
//    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
//    auto scene = HelloWorld::createScene();
    auto scene = TitleScene::scene();

    // run
    director->runWithScene(scene);

	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int enemyLv = userDefault->getIntegerForKey(key_enemyLv, 1);

	if (enemyLv > 4) {
		//AIDの広告表示
		AdViewManager::setAidAdView();
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("mp3/harunopayapaya.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("mp3/winner.mp3");

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
