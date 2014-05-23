#include "GameOverScene.h"
#include "TitleScene.h"
#include "HelloWorldScene.h"
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


	MenuItemImage* pGameOver;
	Menu* pMenu;
	Node* pTarget;
	LabelTTF* wkLabel;

	pTarget = Sprite::create("gameover.png");
	pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 850));
	pTarget->setTag(kTag_GameOver);
	this->addChild(pTarget,1);

	pTarget = Sprite::create("lose_cat.png");
	pTarget->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.5));
	pTarget->setTag(kTag_Cat);
	this->addChild(pTarget,1);

	// リトライボタン
	pGameOver = MenuItemImage::create("button_1.png",
										 "button_2.png",
										 CC_CALLBACK_1(GameOver::tapRetry, this));
	pGameOver->setPosition(Point(visibleSize.width * 0.5, origin.y + 350));
	pMenu = Menu::create(pGameOver, NULL);
	pMenu->setPosition(Point::ZERO);
	pMenu->setTag(kTag_Retry);
	this->addChild(pMenu,1);
    wkLabel = LabelTTF::create("リトライ", MISAKI_FONT, 40.0);
	wkLabel->setPosition(Point(visibleSize.width * 0.5, origin.y + 350));
	wkLabel->setTag(kTag_Retry_Label);
	this->addChild(wkLabel,2);

	// リトライボタン
	pGameOver = MenuItemImage::create("button_1.png",
										 "button_2.png",
										 CC_CALLBACK_1(GameOver::tapReturnMenu, this));
	pGameOver->setPosition(Point(visibleSize.width * 0.5, origin.y + 200));
	pMenu = Menu::create(pGameOver, NULL);
	pMenu->setPosition(Point::ZERO);
	pMenu->setTag(kTag_Menu);
	this->addChild(pMenu,1);
    wkLabel = LabelTTF::create("タイトルにもどる", MISAKI_FONT, 40.0);
	wkLabel->setPosition(Point(visibleSize.width * 0.5, origin.y + 200));
	wkLabel->setTag(kTag_Menu_Label);
	this->addChild(wkLabel,2);

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
