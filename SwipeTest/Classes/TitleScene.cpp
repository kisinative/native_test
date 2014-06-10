#include "TitleScene.h"
#include "HelloWorldScene.h"
#include "PowerUpScene.h"
#include "SimpleAudioEngine.h"
#include "TutorialScene.h"
//#include "NendModule.h"
#include "Android/AdViewManager.h"
#include "Android/AdGameFeat.h"
#include "NendIconModule.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
//#include "Define.h"
//#define  CLASS_NAME  "org/cocos2dx/cpp/Cocos2dxActivity"
//#define  METHOD_NAME "adViewOn"
//#define  CLASS_NAME  "com/loopsessions/TestProject/TestProject"
//#define  METHOD_NAME "setAidAdView"
using namespace CocosDenshion;

USING_NS_CC;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define MISAKI_FONT "fonts/mini-wakuwaku-maru.ttf"
#else
#define MISAKI_FONT "mini-wakuwaku-maru"
#endif

Scene* TitleScene::scene()
{
    Scene* scene = Scene::create();
    TitleScene* layer = TitleScene::create();
    scene->addChild(layer);

    return scene;
}

bool TitleScene::init()
{
    if (!Layer::init())
        return false;

//    EGLView::sharedOpenGLView()->setDesignResolutionSize(640, 1136, kResolutionNoBorder);
    Director* pDirector = Director::sharedDirector();
    EGLView* pEGLView = EGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
//    pEGLView->setDesignResolutionSize(320, 480, kResolutionShowAll);
    pEGLView->setDesignResolutionSize(540, 960, kResolutionShowAll);


    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(TitleScene::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    srand((unsigned int)time(NULL));

    size = Director::sharedDirector()->getWinSize();
    origin			= Director::getInstance()->getVisibleOrigin();


    // 背景
    Sprite* pBG = Sprite::create("background_0.png");
    pBG->setPosition(Point(size.width * 0.5, size.height * 0.5));
    this->addChild(pBG);

    Size bgSize = pBG->getContentSize();

    //タイトル
    pBG = Sprite::create("title.png");
//    pBG->setPosition(Point(size.width * 0.5, size.height * 0.70));
    pBG->setPosition(Point(size.width * 0.5, origin.y + 730));
    this->addChild(pBG,3);


    // スタートボタン
    MenuItemImage* pStart = MenuItemImage::create("button_start.png",
										 "button_start.png",
										 CC_CALLBACK_1(TitleScene::menuStartCallback, this));
    pStart->setPosition(Point(size.width * 0.5, origin.y + 465));
	Menu* pMenu = Menu::create(pStart, NULL);
	pMenu->setPosition(Point::ZERO);
	pMenu->setTag(kTag_StartButton);
	this->addChild(pMenu,2);
//	LabelTTF* wkLabel = LabelTTF::create("スタート", MISAKI_FONT, 40.0);
//	wkLabel->setPosition(Point(size.width * 0.5, origin.y + 420));
//	wkLabel->setTag(kTag_StartButtonLabel);
//	this->addChild(wkLabel,2);
//    MenuItemImage* pStartItem;
//    pStartItem = MenuItemImage::create("start_1.png",
//                                         "start_2.png",
//                                         CC_CALLBACK_1(TitleScene::menuStartCallback, this));
//    pStartItem->setPosition(Point(size.width * 0.5, size.height * 0.70));
//    pStartItem->setTag(kTag_StartButton);
//
//    Menu* pMenu = Menu::create(pStartItem, NULL);
//    pMenu->setPosition(Point::ZERO);
//    pMenu->setTag(kTag_Menu);
//    this->addChild(pMenu);

    // パワーアップボタン
    MenuItemImage* pPowerUp;
    pPowerUp = MenuItemImage::create("button_power.png",
                                         "button_power.png",
                                         CC_CALLBACK_1(TitleScene::menuPowerUpCallback, this));
//    pPowerUp->setPosition(Point(size.width * 0.5, size.height * 0.40));
    pPowerUp->setPosition(Point(origin.y + 150, origin.y + 285));
    pMenu = Menu::create(pPowerUp, NULL);
    pMenu->setPosition(Point::ZERO);
    pMenu->setTag(kTag_PowerUpButton);
    this->addChild(pMenu);

    // ヘルプボタン
    pPowerUp = MenuItemImage::create("button_play.png",
                                         "button_play.png",
                                         CC_CALLBACK_1(TitleScene::menuTutorial, this));
    pPowerUp->setPosition(Point(origin.y + 390, origin.y + 285));
    pMenu = Menu::create(pPowerUp, NULL);
    pMenu->setPosition(Point::ZERO);
    pMenu->setTag(kTag_HelpButton);
    this->addChild(pMenu);

    if (debug_flag){
    	MenuItemImage* pGameOver;
    	Menu* pMenu;
    	Node* pTarget;


    	// 初期化
    	pGameOver = MenuItemImage::create("button_1.png",
    										 "button_2.png",
    										 [&](Object *sender) {
    										 				UserDefault* userDefault = UserDefault::sharedUserDefault();
    										 				userDefault->setIntegerForKey(key_enemyLv, 1);
    										 				userDefault->setIntegerForKey(key_playerExp, 0);
    										 				userDefault->setIntegerForKey(key_playerStrongLv, 1);
    										 				userDefault->setIntegerForKey(key_playerPowerLv, 1);
    										 				userDefault->setIntegerForKey(key_playerSpeedLv, 1);
    										 				userDefault->setIntegerForKey(key_playerTechniqueLv, 1);
    										 			});
    	pGameOver->setPosition(Point(size.width * 0.5, origin.y + 900));
    	pMenu = Menu::create(pGameOver, NULL);
    	pMenu->setPosition(Point::ZERO);
    	pMenu->setTag(800);
    	this->addChild(pMenu,1);
    	LabelTTF* wkLabel = LabelTTF::create("初期化", "Arial", 40.0);
    	wkLabel->setPosition(Point(size.width * 0.5, origin.y + 900));
    	wkLabel->setTag(801);
    	this->addChild(wkLabel,2);


//		//初期化ボタンを作成する
//		LabelTTF* retryLabel = LabelTTF::create("初期化", "Arial", 80.0);
//		retryLabel->setColor(ccc3(255, 255, 255));
//		MenuItemLabel* retryItem = MenuItemLabel::create(retryLabel, [&](Object *sender) {
//				UserDefault* userDefault = UserDefault::sharedUserDefault();
//				userDefault->setIntegerForKey(key_enemyLv, 1);
//			});
//
//
//		retryItem->setPosition(Point(size.width * 0.5,size.height *0.4));
//
//		//メニューを作成する
//		Menu* menu = Menu::create(retryItem, NULL);
//		menu->setPosition(Point::ZERO);
//		this->addChild(menu,2);
    }

    //広告の表示
//    char apiKey[] = "3d3b135cbf2fedde5e1e214d67c55e9b62a9f677";
//    char spotID[] = "143994";
//    NendModule::createNADViewTop(apiKey, spotID);
//    char iconApiKey[] = "3d3b135cbf2fedde5e1e214d67c55e9b62a9f677";
//    char iconSpotID[] = "143994";
    char iconApiKey[] = "0c734134519f25412ae9a9bff94783b81048ffbe";
    char iconSpotID[] = "101282";
    NendIconModule::createNADIconLoader(iconApiKey, iconSpotID);
    NendIconModule::createNADIconViewBottom();
    NendIconModule::load();

//    cocos2d::JniMethodInfo methodInfo;
//    cocos2d::JniHelper::getStaticMethodInfo( methodInfo, "org/cocos2dx/cpp/Cocos2dxActivity",  "adViewOn", "()V" );
//    jstring jpath  = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
//    methodInfo.env->DeleteLocalRef(methodInfo.classID);

//        cocos2d::JniMethodInfo methodInfo;
//        cocos2d::JniHelper::getStaticMethodInfo( methodInfo, "com/loopsessions/TestProject/TestProject",  "setAidAdView", "()V" );
//        jstring jpath  = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
//        methodInfo.env->DeleteLocalRef(methodInfo.classID);

//    //AIDの広告表示
//	AdViewManager::setAidAdView();

    CCLOG("#############################################");

    // GameFeatオファーウォール型ボタン
    pPowerUp = MenuItemImage::create("button_osusume.png",
                                         "button_osusume.png",
                                         [&](Object *sender) {AdGameFeat::showGameFeat();});
    pPowerUp->setPosition(Point(size.width * 0.5, origin.y + 170));
    pMenu = Menu::create(pPowerUp, NULL);
    pMenu->setPosition(Point::ZERO);
    pMenu->setTag(kTag_HelpButton);
    this->addChild(pMenu);


//    		//初期化ボタンを作成する
//
//    		LabelTTF* retryLabel = LabelTTF::create("初期化", "Arial", 80.0);
//    		retryLabel->setColor(ccc3(255, 255, 255));
//    		MenuItemLabel* retryItem = MenuItemLabel::create(retryLabel, [&](Object *sender) {AdGameFeat::showGameFeat();});
//
//
//    		retryItem->setPosition(Point(size.width * 0.8,size.height *0.4));
//
//    		//メニューを作成する
//    		Menu* menu = Menu::create(retryItem, NULL);
//    		menu->setPosition(Point::ZERO);
//    		this->addChild(menu,2);
    CCLOG("#############################################");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/boss_cutin.mp3");

//    ParticleSystemQuad* fire = ParticleSystemQuad::create("mp3/Fire.plist");
//    this->addChild(fire);

    return true;
}

void TitleScene::menuStartCallback(Object* sender)
{

//	gameStart(1);
//	return;

	Menu* pMenu;

	//相手レベル記録
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int enemyLv = userDefault->getIntegerForKey(key_enemyLv, 1);

	CCLOG("Levelaaaaa = %d",enemyLv);

	if (enemyLv == 1) {
//		gameStart(1);

	    // チュートリアル画面の表示
		UserDefault* userDefault = UserDefault::sharedUserDefault();
		userDefault->setIntegerForKey(key_tutorialFlag, 2);
	    Scene* scene = Tutorial::createScene();
	    TransitionFlipX* tran = TransitionFlipX::create(0.2, scene);
	    Director::sharedDirector()->replaceScene(tran);

	} else {
		//難易度ボード
		Sprite* board = Sprite::create("levelBoard.png");
//		board->setPosition(Point(origin.x + 70, origin.y + 200));
		board->setPosition(Point(size.width * 0.5, origin.y + 500));
//		board->setAnchorPoint(Point(0,0));
		board->setTag(kTag_Menu);
	    this->addChild(board,5);
	    Size bgSize = board->getContentSize();

//	    MenuItemLabel *pMaxLevel = MenuItemFont::create(String::createWithFormat("レベル %d から",enemyLv)->getCString(), [&](Object* sender){TitleScene::gameStart(enemyLv);});
//	    MenuItemFont::setFontName( MISAKI_FONT );
//	    pMaxLevel->setColor(ccc3(0, 0, 0));

	    MenuItemImage* pMaxLevel = MenuItemImage::create("button_gold.png",
	                                         "button_gold.png",
	                                         [&](Object* sender){
	    											TitleScene::gameStart(4);
	    										}
	                                         );
		LabelTTF* wkLabel1 = LabelTTF::create(String::createWithFormat("レベル %d から",enemyLv)->getCString(), MISAKI_FONT, 30.0);

	    if (enemyLv <= 5) {
//		    MenuItemLabel *pMidLevel = MenuItemFont::create("レベル 1 から", [&](Object* sender){TitleScene::gameStart(1);});
//		    MenuItemFont::setFontName( MISAKI_FONT );
//		    pMidLevel->setColor(ccc3(0, 0, 0));
	    	MenuItemImage* pMidLevel = MenuItemImage::create("button_silver.png",
	    		                                         "button_silver.png",
	    		                                         [&](Object* sender){
	    		    											TitleScene::gameStart(1);
	    		    										}
	    		                                         );
			LabelTTF* wkLabel2 = LabelTTF::create("レベル 1 から", MISAKI_FONT, 30.0);

	    	MenuItemImage* pClose = MenuItemImage::create("button_tojiru.png",
	    		                                         "button_tojiru.png",
	    		                                         CC_CALLBACK_1(TitleScene::menuClose, this));

	    	pMaxLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.6));
			wkLabel1->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.6));
	    	pMidLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.35));
			wkLabel2->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.35));
	    	pClose->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.1));

	    	pMenu = Menu::create(pMaxLevel,pMidLevel, pClose, NULL);
	    	pMenu->setPosition(Point::ZERO);
	    	board->addChild(pMenu,6);
	    	board->addChild(wkLabel1,7);
	    	board->addChild(wkLabel2,7);

	    } else if (enemyLv <= 10) {
	    	MenuItemImage* pMidLevel = MenuItemImage::create("button_silver.png",
	    		                                         "button_silver.png",
	    		                                         [&](Object* sender){
	    		    											TitleScene::gameStart(2);
	    		    										}
	    		                                         );
	    	LabelTTF* wkLabel2 = LabelTTF::create(String::createWithFormat("レベル %d から",enemyLv - 5)->getCString(), MISAKI_FONT, 30.0);

	    	MenuItemImage* pClose = MenuItemImage::create("button_tojiru.png",
	    		                                         "button_tojiru.png",
	    		                                         CC_CALLBACK_1(TitleScene::menuClose, this));

	    	pMaxLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.6));
	    	wkLabel1->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.6));
	    	pMidLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.35));
	    	wkLabel2->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.35));
	    	pClose->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.1));

	    	pMenu = Menu::create(pMaxLevel,pMidLevel, pClose, NULL);
	    	pMenu->setPosition(Point::ZERO);
	    	board->addChild(pMenu,6);
	    	board->addChild(wkLabel1,7);
	    	board->addChild(wkLabel2,7);

	    } else {
	    	MenuItemImage* pMidLevel = MenuItemImage::create("button_silver.png",
	    		                                         "button_silver.png",
	    		                                         [&](Object* sender){
	    		    											TitleScene::gameStart(2);
	    		    										}
	    		                                         );
	    	LabelTTF* wkLabel2 = LabelTTF::create(String::createWithFormat("レベル %d から",enemyLv - 5)->getCString(), MISAKI_FONT, 30.0);

	    	MenuItemImage* pLowLevel = MenuItemImage::create("button_copper.png",
	    		                                         "button_copper.png",
	    		                                         [&](Object* sender){
	    		    											TitleScene::gameStart(3);
	    		    										}
	    		                                         );
	    	LabelTTF* wkLabel3 = LabelTTF::create(String::createWithFormat("レベル %d から",enemyLv - 10)->getCString(), MISAKI_FONT, 30.0);

	    	MenuItemImage* pClose = MenuItemImage::create("button_tojiru.png",
	    		                                         "button_tojiru.png",
	    		                                         CC_CALLBACK_1(TitleScene::menuClose, this));

	    	pMaxLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.65));
	    	wkLabel1->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.65));
	    	pMidLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.46));
	    	wkLabel2->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.46));
	    	pLowLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.27));
	    	wkLabel3->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.27));
	    	pClose->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.1));

	    	pMenu = Menu::create(pMaxLevel, pMidLevel, pLowLevel, pClose, NULL);
	    	pMenu->setPosition(Point::ZERO);
	    	board->addChild(pMenu,6);
	    	board->addChild(wkLabel1,7);
	    	board->addChild(wkLabel2,7);
	    	board->addChild(wkLabel3,7);
	    }

	}



}
void TitleScene::menuPowerUpCallback(Object* sender)
{
    // パワーアップ画面の表示
    Scene* scene = PowerUp::createScene();
    TransitionFlipX* tran = TransitionFlipX::create(1, scene);
    Director::sharedDirector()->replaceScene(tran);
}

void TitleScene::menuClose(Object* sender)
{

    Node* pMenu = this->getChildByTag(kTag_Menu);
    pMenu->removeFromParentAndCleanup(true);

}
void TitleScene::menuTutorial(Object* sender)
{

	UserDefault* userDefault = UserDefault::sharedUserDefault();
	userDefault->setIntegerForKey(key_tutorialFlag, 1);

    // ゲーム画面の表示
    Scene* scene = Tutorial::createScene();
    TransitionFlipX* tran = TransitionFlipX::create(0.2, scene);
    Director::sharedDirector()->replaceScene(tran);

}

void TitleScene::gameStart(int enemyLv)
{
	//相手レベル記録
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int wkEnemyLv = userDefault->getIntegerForKey(key_enemyLv, 1);
	switch (enemyLv){
	case 1:
		wkEnemyLv = 1;
		break;
	case 2:
		wkEnemyLv -= 5;
		break;
	case 3:
		wkEnemyLv -= 10;
		break;
	}
	userDefault->setIntegerForKey(key_playEnemyLv, wkEnemyLv);

    // ゲーム画面の表示
    Scene* scene = HelloWorld::createScene();
    TransitionFlipX* tran = TransitionFlipX::create(0.2, scene);
    Director::sharedDirector()->replaceScene(tran);
}

bool TitleScene::onTouchBegan(Touch* touch, Event* event)
{
    // can not touch on back layers
    return true;
}

//バックキー処理
void TitleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE )
	{
		//AIDの広告表示
		AdViewManager::setAidAdImgView();
	}
}

