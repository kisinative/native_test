#include "TutorialScene.h"
#include "TitleScene.h"
#include "HelloWorldScene.h"
#include "PowerUpScene.h"
#include <unistd.h>

USING_NS_CC;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define MISAKI_FONT "fonts/mini-wakuwaku-maru.ttf"
#else
#define MISAKI_FONT "mini-wakuwaku-maru"
#endif

Scene* Tutorial::createScene()
{
    auto scene = Scene::create();
    auto layer = Tutorial::create();
    scene->addChild(layer,1);

    return scene;
}

// on "init" you need to initialize your instance
bool Tutorial::init()
{
    //サイズ取得を行う
    origin			= Director::getInstance()->getVisibleOrigin();		//使用端末の(0,0)地点
	visibleSize		= Director::getInstance()->getVisibleSize();		//使用端末の画面サイズ

	this->setTouchMode(kCCTouchesOneByOne);								// シングルタッチモードにする
    this->setTouchEnabled(true);										// タッチを有効にする（内部的にEventDispatcherに登録される）

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Tutorial::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 背景を生成
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int wk_flag = userDefault->getIntegerForKey(key_tutorialFlag, 1);

	Sprite* pBG;
	if (wk_flag == 3) {
		pBG = Sprite::create("help_1.png");
	} else {
		pBG = Sprite::create("Tutorial.png");
	}
    pBG->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.5));
    this->addChild(pBG);


    return true;
}
void Tutorial::onTouchEnded(Touch* touch, Event* event)
{

	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int wk_flag = userDefault->getIntegerForKey(key_tutorialFlag, 1);

	if (wk_flag == 1) {
		Scene* gameScene = (Scene*)TitleScene::create();
		Director::getInstance()->replaceScene(gameScene);
	} else if (wk_flag == 2) {
		//相手レベル記録
		UserDefault* userDefault = UserDefault::sharedUserDefault();
		userDefault->setIntegerForKey(key_playEnemyLv, 1);

	    // ゲーム画面の表示
	    Scene* scene = HelloWorld::createScene();
	    TransitionFlipX* tran = TransitionFlipX::create(0.2, scene);
	    Director::sharedDirector()->replaceScene(tran);
	} else {
		if (wk_count > 3) {
		    Scene* scene = PowerUp::createScene();
		    TransitionFlipX* tran = TransitionFlipX::create(1, scene);
		    Director::sharedDirector()->replaceScene(tran);
		} else {
			wk_count = wk_count + 1;
			Sprite* pBG = Sprite::create(String::createWithFormat("help_%d.png", wk_count)->getCString());
		    pBG->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.5));
		    this->addChild(pBG);
		}
	}

}
//バックキー処理
void Tutorial::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE )
	{
		Scene* gameScene = (Scene*)TitleScene::create();
		Director::getInstance()->replaceScene(gameScene);
	}
}

