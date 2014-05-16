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

    Size size = Director::sharedDirector()->getWinSize();
    Point origin			= Director::getInstance()->getVisibleOrigin();


    // 背景
    Sprite* pBG = Sprite::create("title_bg.png");
    pBG->setPosition(Point(size.width * 0.5, size.height * 0.5));
    this->addChild(pBG);

    Size bgSize = pBG->getContentSize();

    // スタートボタン
    MenuItemImage* pStartItem;
    pStartItem = MenuItemImage::create("start_1.png",
                                         "start_2.png",
                                         CC_CALLBACK_1(TitleScene::menuStartCallback, this));
    pStartItem->setPosition(Point(size.width * 0.5, size.height * 0.70));
    pStartItem->setTag(kTag_StartButton);

    Menu* pMenu = Menu::create(pStartItem, NULL);
    pMenu->setPosition(Point::ZERO);
    pMenu->setTag(kTag_Menu);
    this->addChild(pMenu);

    // パワーアップボタン
    MenuItemImage* pPowerUp;
    pPowerUp = MenuItemImage::create("powerup_1.png",
                                         "powerup_2.png",
                                         CC_CALLBACK_1(TitleScene::menuPowerUpCallback, this));
    pPowerUp->setPosition(Point(size.width * 0.5, size.height * 0.50));
    pMenu = Menu::create(pPowerUp, NULL);
    pMenu->setPosition(Point::ZERO);
    pMenu->setTag(kTag_PowerUpButton);
    this->addChild(pMenu);


    if (debug_flag){
    	MenuItemImage* pGameOver;
    	Menu* pMenu;
    	Node* pTarget;
    	LabelTTF* wkLabel;

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
    	pGameOver->setPosition(Point(size.width * 0.5, origin.y + 200));
    	pMenu = Menu::create(pGameOver, NULL);
    	pMenu->setPosition(Point::ZERO);
    	pMenu->setTag(800);
    	this->addChild(pMenu,1);
        wkLabel = LabelTTF::create("初期化", "Arial", 40.0);
    	wkLabel->setPosition(Point(size.width * 0.5, origin.y + 200));
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

	//相手レベル記録
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int enemyLv = userDefault->getIntegerForKey(key_enemyLv, 1);
	userDefault->setIntegerForKey(key_playEnemyLv, enemyLv);

    // ゲーム画面の表示
    Scene* scene = HelloWorld::createScene();
    TransitionFlipX* tran = TransitionFlipX::create(0.2, scene);
    Director::sharedDirector()->replaceScene(tran);
}
void TitleScene::menuPowerUpCallback(Object* sender)
{
    // パワーアップ画面の表示
    Scene* scene = PowerUp::createScene();
    TransitionFlipX* tran = TransitionFlipX::create(1, scene);
    Director::sharedDirector()->replaceScene(tran);
}
