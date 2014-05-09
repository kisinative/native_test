#include "PowerUpScene.h"
#include "TitleScene.h"
#include <unistd.h>

USING_NS_CC;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define MISAKI_FONT "fonts/mini-wakuwaku-maru.ttf"
#else
#define MISAKI_FONT "mini-wakuwaku-maru"
#endif

Scene* PowerUp::createScene()
{
    auto scene = Scene::create();
    auto layer = PowerUp::create();
    scene->addChild(layer,1);

    return scene;
}

// on "init" you need to initialize your instance
bool PowerUp::init()
{
    //サイズ取得を行う
    origin			= Director::getInstance()->getVisibleOrigin();		//使用端末の(0,0)地点
	visibleSize		= Director::getInstance()->getVisibleSize();		//使用端末の画面サイズ

	// 現在の経験値やレベル取得
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int playerExp = userDefault->getIntegerForKey(key_playerExp, 0);
	int playerStr = userDefault->getIntegerForKey(key_playerStrongLv, 1);
	int playerPow = userDefault->getIntegerForKey(key_playerPowerLv, 1);
	int playerSpd = userDefault->getIntegerForKey(key_playerSpeedLv, 1);
	int playerTec = userDefault->getIntegerForKey(key_playerTechniqueLv, 1);

	MenuItemImage* pPowerUp;
	Menu* pMenu;
	Node* pTarget;
	LabelTTF* wkLabel;
    // 体力
	if (playerExp >= Calculation(playerStr)) {
		pPowerUp = MenuItemImage::create("levelup_1.png",
											 "levelup_2.png",
											 CC_CALLBACK_1(PowerUp::tapStrongButton, this));
	//    pPowerUp->setPosition(Point(visibleSize.width * 0.5 - 10, visibleSize.height * 0.50 + 10));
		pPowerUp->setPosition(Point(visibleSize.width * 0.5, origin.y + 720));
		Menu* pMenu = Menu::create(pPowerUp, NULL);
		pMenu->setPosition(Point::ZERO);
	//    pMenu->setAnchorPoint(Point(1,0));
		pMenu->setTag(kTag_StrongButton);
		this->addChild(pMenu,1);
	} else {
		pTarget = Sprite::create("levelup_2.png");
		pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 720));
		pTarget->setTag(kTag_StrongButton);
		this->addChild(pTarget,1);
	}
    wkLabel = LabelTTF::create(String::createWithFormat("タフネス LV%d\n必要ポイント：%d", playerStr, Calculation(playerStr))->getCString(), MISAKI_FONT, 40.0);
	wkLabel->setPosition(Point(visibleSize.width * 0.5, origin.y + 720));
	wkLabel->setTag(kTag_StrongLabel);
	this->addChild(wkLabel,2);


    // 攻撃力
	if (playerExp >= Calculation(playerPow)) {
		pPowerUp = MenuItemImage::create("levelup_1.png",
											 "levelup_2.png",
											 CC_CALLBACK_1(PowerUp::tapPowerButton, this));
	//    pPowerUp->setPosition(Point(visibleSize.width * 0.5 + 10, visibleSize.height * 0.50 + 10));
		pPowerUp->setPosition(Point(visibleSize.width * 0.5, origin.y + 570));
		pMenu = Menu::create(pPowerUp, NULL);
		pMenu->setPosition(Point::ZERO);
	//    pMenu->setAnchorPoint(Point(0,0));
		pMenu->setTag(kTag_PowerButton);
		this->addChild(pMenu,1);
	} else {
		pTarget = Sprite::create("levelup_2.png");
		pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 570));
		pTarget->setTag(kTag_PowerButton);
		this->addChild(pTarget,1);
	}
    wkLabel = LabelTTF::create(String::createWithFormat("パワー LV%d\n必要ポイント：%d", playerPow, Calculation(playerPow))->getCString(), MISAKI_FONT, 40.0);
	wkLabel->setPosition(Point(visibleSize.width * 0.5, origin.y + 570));
	wkLabel->setTag(kTag_PowerLabel);
	this->addChild(wkLabel,2);


    // スピード
	if (playerExp >= Calculation(playerSpd)) {
		pPowerUp = MenuItemImage::create("levelup_1.png",
											 "levelup_2.png",
											 CC_CALLBACK_1(PowerUp::tapSpeedButton, this));
	//    pPowerUp->setPosition(Point(visibleSize.width * 0.5 - 10, visibleSize.height * 0.50 - 10));
		pPowerUp->setPosition(Point(visibleSize.width * 0.5, origin.y + 420));
		pMenu = Menu::create(pPowerUp, NULL);
		pMenu->setPosition(Point::ZERO);
	//    pMenu->setAnchorPoint(Point(1,1));
		pMenu->setTag(kTag_SpeedButton);
		this->addChild(pMenu,1);
	} else {
		pTarget = Sprite::create("levelup_2.png");
		pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 420));
		pTarget->setTag(kTag_SpeedButton);
		this->addChild(pTarget,1);
	}
    wkLabel = LabelTTF::create(String::createWithFormat("スピード LV%d\n必要ポイント：%d", playerSpd, Calculation(playerSpd))->getCString(), MISAKI_FONT, 40.0);
	wkLabel->setPosition(Point(visibleSize.width * 0.5, origin.y + 420));
	wkLabel->setTag(kTag_SpeedLabel);
	this->addChild(wkLabel,2);


    // テクニック
	if (playerExp >= Calculation(playerTec)) {
		pPowerUp = MenuItemImage::create("levelup_1.png",
											 "levelup_2.png",
											 CC_CALLBACK_1(PowerUp::tapTechniqueButton, this));
	//    pPowerUp->setPosition(Point(visibleSize.width * 0.5 + 10, visibleSize.height * 0.50 - 10));
		pPowerUp->setPosition(Point(visibleSize.width * 0.5, origin.y + 270));
		pMenu = Menu::create(pPowerUp, NULL);
		pMenu->setPosition(Point::ZERO);
	//    pMenu->setAnchorPoint(Point(0,1));
		pMenu->setTag(kTag_TechniqueButton);
		this->addChild(pMenu,1);
	} else {
		pTarget = Sprite::create("levelup_2.png");
		pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 270));
		pTarget->setTag(kTag_TechniqueButton);
		this->addChild(pTarget,1);
	}
    wkLabel = LabelTTF::create(String::createWithFormat("テクニック LV%d\n必要ポイント：%d", playerTec, Calculation(playerTec))->getCString(), MISAKI_FONT, 40.0);
	wkLabel->setPosition(Point(visibleSize.width * 0.5, origin.y + 270));
	wkLabel->setTag(kTag_TechniqueLabel);
	this->addChild(wkLabel,2);


    // 戻るボタン
    pPowerUp = MenuItemImage::create("backhome_1.png",
                                         "backhome_2.png",
                                         CC_CALLBACK_1(PowerUp::tapReturnMenu, this));
//    pPowerUp->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.30));
    pPowerUp->setPosition(Point(origin.x + 480, origin.y + 150));
    pMenu = Menu::create(pPowerUp, NULL);
    pMenu->setPosition(Point::ZERO);
    pMenu->setTag(kTag_Menu);
    this->addChild(pMenu,1);

    //現在経験値
    wkLabel = LabelTTF::create(String::createWithFormat("ポイント：%d",playerExp)->getCString(), MISAKI_FONT, 40.0);
	wkLabel->setPosition(Point(visibleSize.width * 0.1, origin.y + 900));
	wkLabel->setColor(ccc3(255, 0, 50));
	wkLabel->setAnchorPoint(Point(0,0));
	wkLabel->setTag(kTag_ExpLabel);
	this->addChild(wkLabel,2);

    return true;
}

// TOPページへ
void PowerUp::tapReturnMenu(Object* pSender)
{
	Scene* gameScene = (Scene*)TitleScene::create();
	Director::getInstance()->replaceScene(gameScene);
}

int PowerUp::Calculation(int lv)
{
	return lv * 5;
}

void PowerUp::tapStrongButton(Object* pSender)
{
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int wk_lv = userDefault->getIntegerForKey(key_playerStrongLv, 0) + 1;
	int wk_exp = userDefault->getIntegerForKey(key_playerExp, 0) - Calculation(wk_lv-1);
	userDefault->setIntegerForKey(key_playerStrongLv, wk_lv);
	userDefault->setIntegerForKey(key_playerExp, wk_exp);
}
void PowerUp::tapPowerButton(Object* pSender)
{
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int wk_lv = userDefault->getIntegerForKey(key_playerPowerLv, 0) + 1;
	int wk_exp = userDefault->getIntegerForKey(key_playerExp, 0) - Calculation(wk_lv-1);
	userDefault->setIntegerForKey(key_playerPowerLv, wk_lv);
	userDefault->setIntegerForKey(key_playerExp, wk_exp);
}
void PowerUp::tapSpeedButton(Object* pSender)
{
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int wk_lv = userDefault->getIntegerForKey(key_playerSpeedLv, 0) + 1;
	int wk_exp = userDefault->getIntegerForKey(key_playerExp, 0) - Calculation(wk_lv-1);
	userDefault->setIntegerForKey(key_playerSpeedLv, wk_lv);
	userDefault->setIntegerForKey(key_playerExp, wk_exp);
}
void PowerUp::tapTechniqueButton(Object* pSender)
{
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int wk_lv = userDefault->getIntegerForKey(key_playerTechniqueLv, 0) + 1;
	int wk_exp = userDefault->getIntegerForKey(key_playerExp, 0) - Calculation(wk_lv-1);
	userDefault->setIntegerForKey(key_playerTechniqueLv, wk_lv);
	userDefault->setIntegerForKey(key_playerExp, wk_exp);
}
