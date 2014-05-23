#include "TitleScene.h"
#include "HelloWorldScene.h"
#include "PowerUpScene.h"
#include "SimpleAudioEngine.h"
//#include "NendModule.h"
#include "NendIconModule.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
//#define  CLASS_NAME  "org/cocos2dx/cpp/Cocos2dxActivity"
//#define  METHOD_NAME "adViewOn"

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
    pBG->setPosition(Point(size.width * 0.5, size.height * 0.70));
    this->addChild(pBG);


    // スタートボタン
    MenuItemImage* pStart = MenuItemImage::create("button_1.png",
										 "button_2.png",
										 CC_CALLBACK_1(TitleScene::menuStartCallback, this));
    pStart->setPosition(Point(size.width * 0.5, origin.y + 270));
	Menu* pMenu = Menu::create(pStart, NULL);
	pMenu->setPosition(Point::ZERO);
	pMenu->setTag(kTag_StartButton);
	this->addChild(pMenu,1);
	LabelTTF* wkLabel = LabelTTF::create("スタート", MISAKI_FONT, 40.0);
	wkLabel->setPosition(Point(size.width * 0.5, origin.y + 270));
	wkLabel->setTag(kTag_StartButtonLabel);
	this->addChild(wkLabel,2);
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
    pPowerUp = MenuItemImage::create("powerup_1.png",
                                         "powerup_2.png",
                                         CC_CALLBACK_1(TitleScene::menuPowerUpCallback, this));
    pPowerUp->setPosition(Point(size.width * 0.5, size.height * 0.40));
    pMenu = Menu::create(pPowerUp, NULL);
    pMenu->setPosition(Point::ZERO);
    pMenu->setTag(kTag_PowerUpButton);
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
    	pGameOver->setPosition(Point(size.width * 0.5, origin.y + 100));
    	pMenu = Menu::create(pGameOver, NULL);
    	pMenu->setPosition(Point::ZERO);
    	pMenu->setTag(800);
    	this->addChild(pMenu,1);
        wkLabel = LabelTTF::create("初期化", "Arial", 40.0);
    	wkLabel->setPosition(Point(size.width * 0.5, origin.y + 100));
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


	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("harunopayapaya.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("harunopayapaya.mp3", true);

    return true;
}

void TitleScene::menuStartCallback(Object* sender)
{

	gameStart(1);
	return;

	Menu* pMenu;
	//相手レベル記録
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int enemyLv = userDefault->getIntegerForKey(key_enemyLv, 1);

	if (enemyLv == 1) {
		gameStart(1);
	} else {
		//難易度ボード
	    //タイトル
		Sprite* board = Sprite::create("levelBoard.png");
//		board->setPosition(Point(origin.x + 70, origin.y + 200));
		board->setPosition(Point(size.width * 0.5, origin.y + 500));
//		board->setAnchorPoint(Point(0,0));
	    this->addChild(board,5);
	    Size bgSize = board->getContentSize();
	    MenuItemImage* pMaxLevel = MenuItemImage::create("difficulty_button_1.png",
	                                         "difficulty_button_2.png",
	                                         [&](Object* sender){
	    											TitleScene::gameStart(enemyLv);
	    										}
	                                         );
//	                                         CC_CALLBACK_1(TitleScene::gameStart, enemyLv));

	    CCLOG("x = %f  y = %f",bgSize.width * 0.5 ,bgSize.height * 0.7);
	    CCLOG("x = %f  y = %f",bgSize.width ,bgSize.height);
	    if (enemyLv <= 5) {
	    	MenuItemImage* pMidLevel = MenuItemImage::create("difficulty_button_1.png",
	    		                                         "difficulty_button_2.png",
	    		                                         [&](Object* sender){
	    		    											TitleScene::gameStart(1);
	    		    										}
	    		                                         );
//	    		                                         CC_CALLBACK_1(TitleScene::gameStart, 1));

	    	pMaxLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.7));
	    	pMidLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.5));
//	    	pMaxLevel->setPosition(bgSize / 2);
//	    	pMidLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.5));

	    	pMenu = Menu::create(pMaxLevel, NULL);
	    	board->addChild(pMenu,6);
		    pMenu = Menu::create(pMidLevel, NULL);
		    board->addChild(pMenu,6);
	    } else if (enemyLv <= 10) {
	    	MenuItemImage* pMidLevel = MenuItemImage::create("difficulty_button_1.png",
	    		                                         "difficulty_button_2.png",
	    		                                         [&](Object* sender){
	    		    											TitleScene::gameStart(enemyLv - 5);
	    		    										}
	    		                                         );
//	    		                                         CC_CALLBACK_1(TitleScene::gameStart, enemyLv - 5));

//	    	pMaxLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.7));
//	    	pMidLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.5));
	    	pMaxLevel->setPosition(Point(0, 0));
	    	pMidLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.5));

	    	pMenu = Menu::create(pMaxLevel, NULL);
	    	board->addChild(pMenu,6);
		    pMenu = Menu::create(pMidLevel, NULL);
		    board->addChild(pMenu,6);
	    } else {
	    	MenuItemImage* pMidLevel = MenuItemImage::create("difficulty_button_1.png",
	    		                                         "difficulty_button_2.png",
	    		                                         [&](Object* sender){
	    		    											TitleScene::gameStart(enemyLv - 5);
	    		    										}
	    		                                         );
//	    		                                         CC_CALLBACK_1(TitleScene::gameStart, enemyLv - 5));
	    	MenuItemImage* plowLevel = MenuItemImage::create("difficulty_button_1.png",
	    		                                         "difficulty_button_2.png",
	    		                                         [&](Object* sender){
	    		    											TitleScene::gameStart(enemyLv - 10);
	    		    										}
	    		                                         );
//	    		                                         CC_CALLBACK_1(TitleScene::gameStart, enemyLv - 10));

	    	pMaxLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.8));
	    	pMidLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.6));
	    	plowLevel->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.4));

	    	pMenu = Menu::create(pMaxLevel, NULL);
	    	board->addChild(pMenu,6);
		    pMenu = Menu::create(pMidLevel, NULL);
		    board->addChild(pMenu,6);
		    pMenu = Menu::create(plowLevel, NULL);
		    board->addChild(pMenu,6);
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

void TitleScene::gameStart(int enemyLv)
{

	//相手レベル記録
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	userDefault->setIntegerForKey(key_playEnemyLv, enemyLv);

    // ゲーム画面の表示
    Scene* scene = HelloWorld::createScene();
    TransitionFlipX* tran = TransitionFlipX::create(0.2, scene);
    Director::sharedDirector()->replaceScene(tran);
}

