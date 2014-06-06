#include "WinnerScene.h"
#include "TitleScene.h"
#include "HelloWorldScene.h"
#include <unistd.h>
#include "SimpleAudioEngine.h"
#include "Android/AdViewManager.h"

using namespace CocosDenshion;

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

	//背景色
//	if (!LayerColor::initWithColor(ccc4(240, 200, 150, 255))) {
//		return false;;
//	}
    //サイズ取得を行う
    origin			= Director::getInstance()->getVisibleOrigin();		//使用端末の(0,0)地点
	visibleSize		= Director::getInstance()->getVisibleSize();		//使用端末の画面サイズ

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Winner::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

//	if (!LayerColor::initWithColor(ccc4(247, 250, 191, 255))) {
//		return false;
//	}
//    cell = new TableViewCell();
//    cell->autorelease();
    Sprite* bg = Sprite::create();
    bg->setAnchorPoint(Point(0, 0));
    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
    bg->setColor(Color3B(247, 250, 191));
    bg->setTag(100);
    this->addChild(bg);
//    cell->addChild(bg);


	MenuItemImage* pWinner;
	Menu* pMenu;
	Node* pTarget;
	LabelTTF* wkLabel;

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("mp3/winner.mp3", true);

	pTarget = Sprite::create("winner.png");
	pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 800));
	pTarget->setTag(kTag_Winner);
	this->addChild(pTarget,2);

	// 経験値追加
	pTarget = Sprite::create("board.png");
	pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 520));
	pTarget->setTag(kTag_Cat);
	this->addChild(pTarget,2);
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	enemyLv		= userDefault->getIntegerForKey(key_enemyLv, 1);
	playEnemyLv	= userDefault->getIntegerForKey(key_playEnemyLv, 1);
	playerExp	= userDefault->getIntegerForKey(key_playerExp, 0);
	maxCombo	= userDefault->getIntegerForKey(key_maxComboCount, 1) / 5;
	noMissFlag	= userDefault->getBoolForKey(key_noMissFlag, false);
	bossFlag	= userDefault->getBoolForKey(key_bossFlag, false);

//	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(kTag_Exp_Label);
//	arrowLabel->setString(String::createWithFormat("ステージクリア！！\n%dポイント獲得 %d　→　%d",playEnemyLv, playerExp, wk_enemyExp)->getCString());

//    wkLabel = LabelTTF::create(String::createWithFormat("ステージクリア！！\n%dポイントGET!\n%d　→　%d",playEnemyLv, playerExp, wk_enemyExp)->getCString(), MISAKI_FONT, 40.0);

	this->schedule(schedule_selector(Winner::showScore), 0.4);

	if (noMissFlag) {
		if (bossFlag) {
			wk_enemyExp	= playerExp + ((playEnemyLv + maxCombo + 20) * 2);
		} else {
			wk_enemyExp	= playEnemyLv + playerExp + maxCombo + 20;
		}
	} else {
		if (bossFlag) {
			wk_enemyExp	= playerExp + ((playEnemyLv + maxCombo) * 2);
		} else {
			wk_enemyExp	= playEnemyLv + playerExp + maxCombo;
		}
	}


	userDefault->setIntegerForKey(key_playerExp, wk_enemyExp);
	if (enemyLv == playEnemyLv) {
		//相手レベル記録
		userDefault->setIntegerForKey(key_enemyLv, ++enemyLv);
	}


	// リトライボタン
	pWinner = MenuItemImage::create("button_next.png",
										 "button_next.png",
										 CC_CALLBACK_1(Winner::tapRetry, this));
	pWinner->setPosition(Point(origin.y + 150, origin.y + 180));
	pMenu = Menu::create(pWinner, NULL);
	pMenu->setPosition(Point::ZERO);
	pMenu->setTag(kTag_Retry);
	this->addChild(pMenu,2);

	// リトライボタン
	pWinner = MenuItemImage::create("button_title.png",
										 "button_title.png",
										 CC_CALLBACK_1(Winner::tapReturnMenu, this));
	pWinner->setPosition(Point(origin.y + 390, origin.y + 180));
	pMenu = Menu::create(pWinner, NULL);
	pMenu->setPosition(Point::ZERO);
	pMenu->setTag(kTag_Menu);
	this->addChild(pMenu,2);

//	ParticleSystemQuad* fire = ParticleSystemQuad::create("plist/winner.plist");
//	this->addChild(fire,1);

    return true;
}

// TOPページへ
void Winner::tapReturnMenu(Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	Scene* gameScene = (Scene*)TitleScene::create();
	Director::getInstance()->replaceScene(gameScene);
}

// TOPページへ
void Winner::tapRetry(Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	//相手レベル記録
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	enemyLv = userDefault->getIntegerForKey(key_playEnemyLv, 1);
	userDefault->setIntegerForKey(key_playEnemyLv, enemyLv+1);


	Scene* gameScene = (Scene*)HelloWorld::create();
	Director::getInstance()->replaceScene(gameScene);
}

void Winner::showScore(float time)
{
	LabelTTF* wkLabel;

	switch (showCount){
	case 0:
	    wkLabel = LabelTTF::create(String::createWithFormat("きほんボーナス　%dポイント",playEnemyLv)->getCString(), MISAKI_FONT, 30.0);
		wkLabel->setPosition(Point(visibleSize.width * 0.5, origin.y + 570));
		wkLabel->setColor(ccc3(0, 0, 0));
		wkLabel->setTag(kTag_Exp_Label);
		wkLabel->setAnchorPoint(Point(0.5,1));
		this->addChild(wkLabel,3);
		break;
	case 1:
		wkLabel = (LabelTTF*)this->getChildByTag(kTag_Exp_Label);
		wkLabel->setString(String::createWithFormat("きほんボーナス　%dポイント\nMAXコンボボーナス　%dポイント",playEnemyLv, maxCombo)->getCString());
		wkLabel->setColor(ccc3(0, 0, 0));
		break;
	case 2:
		wkLabel = (LabelTTF*)this->getChildByTag(kTag_Exp_Label);
		wkLabel->setColor(ccc3(0, 0, 0));
		if (noMissFlag) {
			wkLabel->setString(String::createWithFormat("きほんボーナス　%dポイント\nMAXコンボボーナス　%dポイント\nノーミスボーナス　%d",playEnemyLv, maxCombo, 20)->getCString());
		} else {
			if (bossFlag) {
				wkLabel->setString(String::createWithFormat("きほんボーナス　%dポイント\nMAXコンボボーナス　%dポイント\nボスねこボーナス ｘ 2\n%d　→　%d",playEnemyLv, maxCombo, playerExp, wk_enemyExp)->getCString());
			} else {
				wkLabel->setString(String::createWithFormat("きほんボーナス　%dポイント\nMAXコンボボーナス　%dポイント\n%d　→　%d",playEnemyLv, maxCombo, playerExp, wk_enemyExp)->getCString());
			}
			this->unschedule(schedule_selector(Winner::showScore));
		}
		break;
	case 3:
		wkLabel = (LabelTTF*)this->getChildByTag(kTag_Exp_Label);
		if (bossFlag) {
			wkLabel->setString(String::createWithFormat("きほんボーナス　%dポイント\nMAXコンボボーナス　%dポイント\nノーミスボーナス　%d\nボスねこボーナス ｘ 2\n%d　→　%d",playEnemyLv, maxCombo, 20, playerExp, wk_enemyExp)->getCString());
		} else {
			wkLabel->setString(String::createWithFormat("きほんボーナス　%dポイント\nMAXコンボボーナス　%dポイント\nノーミスボーナス　%d\n%d　→　%d",playEnemyLv, maxCombo, 20, playerExp, wk_enemyExp)->getCString());
		}
		wkLabel->setColor(ccc3(0, 0, 0));
		this->unschedule(schedule_selector(Winner::showScore));
		break;
	}
	showCount++;

}
//バックキー処理
void Winner::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE )
	{
		//AIDの広告表示
		AdViewManager::setAidAdImgView();
	}
}

