#include "WinnerScene.h"
#include "TitleScene.h"
#include "HelloWorldScene.h"
#include <unistd.h>

USING_NS_CC;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define MISAKI_FONT "fonts/mini-wakuwaku-maru.ttf"
#else
#define MISAKI_FONT "mini-wakuwaku-maru"
#endif

Scene* Winner::createScene()
{
    auto scene = Scene::create();
    auto layer = Winner::create();
    scene->addChild(layer,1);

    return scene;
}

// on "init" you need to initialize your instance
bool Winner::init()
{
    //サイズ取得を行う
    origin			= Director::getInstance()->getVisibleOrigin();		//使用端末の(0,0)地点
	visibleSize		= Director::getInstance()->getVisibleSize();		//使用端末の画面サイズ


	MenuItemImage* pWinner;
	Menu* pMenu;
	Node* pTarget;
	LabelTTF* wkLabel;

	pTarget = Sprite::create("winner.png");
	pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 800));
	pTarget->setTag(kTag_Winner);
	this->addChild(pTarget,1);

	// 経験値追加
	pTarget = Sprite::create("board.png");
	pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 520));
	pTarget->setTag(kTag_Cat);
	this->addChild(pTarget,1);
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	enemyLv		= userDefault->getIntegerForKey(key_enemyLv, 1);
	playEnemyLv	= userDefault->getIntegerForKey(key_playEnemyLv, 1);
	playerExp	= userDefault->getIntegerForKey(key_playerExp, 0);
	maxCombo	= userDefault->getIntegerForKey(key_maxComboCount, 1) / 5;
	noMissFlag	= userDefault->getBoolForKey(key_noMissFlag, false);

//	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(kTag_Exp_Label);
//	arrowLabel->setString(String::createWithFormat("ステージクリア！！\n%dポイント獲得 %d　→　%d",playEnemyLv, playerExp, wk_enemyExp)->getCString());

//    wkLabel = LabelTTF::create(String::createWithFormat("ステージクリア！！\n%dポイントGET!\n%d　→　%d",playEnemyLv, playerExp, wk_enemyExp)->getCString(), MISAKI_FONT, 40.0);

	this->schedule(schedule_selector(Winner::showScore), 0.4);

	if (noMissFlag) {
		wk_enemyExp	= playEnemyLv + playerExp + maxCombo + 20;
	} else {
		wk_enemyExp	= playEnemyLv + playerExp + maxCombo;
	}


	userDefault->setIntegerForKey(key_playerExp, wk_enemyExp);
	if (enemyLv == playEnemyLv) {
		//相手レベル記録
		userDefault->setIntegerForKey(key_enemyLv, ++enemyLv);
	}


	// リトライボタン
	pWinner = MenuItemImage::create("button_1.png",
										 "button_2.png",
										 CC_CALLBACK_1(Winner::tapRetry, this));
	pWinner->setPosition(Point(visibleSize.width * 0.5, origin.y + 290));
	pMenu = Menu::create(pWinner, NULL);
	pMenu->setPosition(Point::ZERO);
	pMenu->setTag(kTag_Retry);
	this->addChild(pMenu,1);
    wkLabel = LabelTTF::create("リトライ", MISAKI_FONT, 40.0);
	wkLabel->setPosition(Point(visibleSize.width * 0.5, origin.y + 290));
	wkLabel->setTag(kTag_Retry_Label);
	this->addChild(wkLabel,2);

	// リトライボタン
	pWinner = MenuItemImage::create("button_1.png",
										 "button_2.png",
										 CC_CALLBACK_1(Winner::tapReturnMenu, this));
	pWinner->setPosition(Point(visibleSize.width * 0.5, origin.y + 180));
	pMenu = Menu::create(pWinner, NULL);
	pMenu->setPosition(Point::ZERO);
	pMenu->setTag(kTag_Menu);
	this->addChild(pMenu,1);
    wkLabel = LabelTTF::create("タイトルにもどる", MISAKI_FONT, 40.0);
	wkLabel->setPosition(Point(visibleSize.width * 0.5, origin.y + 180));
	wkLabel->setTag(kTag_Menu_Label);
	this->addChild(wkLabel,2);

    return true;
}

// TOPページへ
void Winner::tapReturnMenu(Object* pSender)
{
	Scene* gameScene = (Scene*)TitleScene::create();
	Director::getInstance()->replaceScene(gameScene);
}

// TOPページへ
void Winner::tapRetry(Object* pSender)
{
	Scene* gameScene = (Scene*)HelloWorld::create();
	Director::getInstance()->replaceScene(gameScene);
}

void Winner::showScore(float time)
{
	LabelTTF* wkLabel;

	switch (showCount){
	case 0:
	    wkLabel = LabelTTF::create(String::createWithFormat("きほんボーナス　%dポイント",playEnemyLv)->getCString(), MISAKI_FONT, 30.0);
		wkLabel->setPosition(Point(visibleSize.width * 0.5, origin.y + 520));
		wkLabel->setTag(kTag_Exp_Label);
		this->addChild(wkLabel,2);
		break;
	case 1:
		wkLabel = (LabelTTF*)this->getChildByTag(kTag_Exp_Label);
		wkLabel->setString(String::createWithFormat("きほんボーナス　%dポイント\nMAXコンボボーナス　%dポイント",playEnemyLv, maxCombo)->getCString());
		break;
	case 2:
		wkLabel = (LabelTTF*)this->getChildByTag(kTag_Exp_Label);
		if (noMissFlag) {
			wkLabel->setString(String::createWithFormat("きほんボーナス　%dポイント\nMAXコンボボーナス　%dポイント\nノーミスボーナス　%d",playEnemyLv, maxCombo, 20)->getCString());
		} else {
			wkLabel->setString(String::createWithFormat("きほんボーナス　%dポイント\nMAXコンボボーナス　%dポイント\n%d　→　%d",playEnemyLv, maxCombo, playerExp, wk_enemyExp)->getCString());
			this->unschedule(schedule_selector(Winner::showScore));
		}
		break;
	case 3:
		wkLabel = (LabelTTF*)this->getChildByTag(kTag_Exp_Label);
		wkLabel->setString(String::createWithFormat("きほんボーナス　%dポイント\nMAXコンボボーナス　%dポイント\nノーミスボーナス　%d\n%d　→　%d",playEnemyLv, maxCombo, 20, playerExp, wk_enemyExp)->getCString());
		this->unschedule(schedule_selector(Winner::showScore));
		break;
	}
	showCount++;

}
