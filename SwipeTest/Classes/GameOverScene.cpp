#include "GameOverScene.h"
#include "TitleScene.h"
#include "HelloWorldScene.h"
#include "Android/AdViewManager.h"
#include <unistd.h>

USING_NS_CC;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define MISAKI_FONT "fonts/mini-wakuwaku-maru.ttf"
#else
#define MISAKI_FONT "mini-wakuwaku-maru"
#endif

Scene* GameOver::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOver::create();
    scene->addChild(layer,1);

    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //サイズ取得を行う
    origin			= Director::getInstance()->getVisibleOrigin();		//使用端末の(0,0)地点
	visibleSize		= Director::getInstance()->getVisibleSize();		//使用端末の画面サイズ

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(GameOver::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    Sprite* bg = Sprite::create();
    bg->setAnchorPoint(Point(0, 0));
    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
//    bg->setColor(Color3B(247, 250, 191));
    bg->setColor(Color3B(200, 220, 255));
    bg->setTag(100);
    this->addChild(bg);

	MenuItemImage* pGameOver;
	Menu* pMenu;
	Node* pTarget;
	LabelTTF* wkLabel;

	pTarget = Sprite::create("gameover.png");
	pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 850));
	pTarget->setTag(kTag_GameOver);
	this->addChild(pTarget,1);

	pTarget = Sprite::create("lose_cat.png");
	pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 550));
	pTarget->setTag(kTag_Cat);
	this->addChild(pTarget,1);

	pTarget = Sprite::create("tegami_mini3.png");
	pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 270));
	this->addChild(pTarget,2);

	// リトライボタン
	pGameOver = MenuItemImage::create("button_retry.png",
										 "button_retry.png",
										 CC_CALLBACK_1(GameOver::tapRetry, this));
	pGameOver->setPosition(Point(origin.y + 150, origin.y + 160));
	pMenu = Menu::create(pGameOver, NULL);
	pMenu->setPosition(Point::ZERO);
	pMenu->setTag(kTag_Retry);
	this->addChild(pMenu,1);
//    wkLabel = LabelTTF::create("リトライ", MISAKI_FONT, 40.0);
//	wkLabel->setPosition(Point(visibleSize.width * 0.5, origin.y + 350));
//	wkLabel->setTag(kTag_Retry_Label);
//	this->addChild(wkLabel,2);

	// リトライボタン
	pGameOver = MenuItemImage::create("button_title.png",
										 "button_title.png",
										 CC_CALLBACK_1(GameOver::tapReturnMenu, this));
	pGameOver->setPosition(Point(origin.y + 390, origin.y + 160));
	pMenu = Menu::create(pGameOver, NULL);
	pMenu->setPosition(Point::ZERO);
	pMenu->setTag(kTag_Menu);
	this->addChild(pMenu,1);
//    wkLabel = LabelTTF::create("タイトルにもどる", MISAKI_FONT, 40.0);
//	wkLabel->setPosition(Point(visibleSize.width * 0.5, origin.y + 200));
//	wkLabel->setTag(kTag_Menu_Label);
//	this->addChild(wkLabel,2);

    return true;
}

// TOPページへ
void GameOver::tapReturnMenu(Object* pSender)
{
	Scene* gameScene = (Scene*)TitleScene::create();
	Director::getInstance()->replaceScene(gameScene);
}

// TOPページへ
void GameOver::tapRetry(Object* pSender)
{
	Scene* gameScene = (Scene*)HelloWorld::create();
	Director::getInstance()->replaceScene(gameScene);
}

//バックキー処理
void GameOver::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE )
	{
		//AIDの広告表示
		AdViewManager::setAidAdImgView();
	}
}

