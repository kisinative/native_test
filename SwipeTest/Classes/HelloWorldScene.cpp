#include "HelloWorldScene.h"

USING_NS_CC;
String arrowArray[] = {"右", "左", "上", "下"};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // シングルタッチモードにする
    this->setTouchMode(kCCTouchesOneByOne);
    // タッチを有効にする（内部的にEventDispatcherに登録される）
    this->setTouchEnabled(true);


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    //初期化
    NowHp = MaxHp;
    NowEnemyHp = defaultEnemyStrong;
    nowGesture = 99;
    enemyStrongLv = 1;
    enemypowerLv = 1;
    enemySpeedLv = 1;


    //HP表示
    Size winSize = Director::sharedDirector()->getWinSize();
    LabelTTF* Hp = LabelTTF::create(String::createWithFormat("残りHP:%d", NowHp)->getCString(), "Arial", 50.0);
    Hp->setPosition(ccp(winSize.width * 0.15,winSize.height * 0.95));
    Hp->setTag(tagHp);
	this->addChild(Hp,2);
	//敵HP表示
    LabelTTF* enemyHp = LabelTTF::create(String::createWithFormat("敵残りHP:%d", NowEnemyHp)->getCString(), "Arial", 50.0);
    enemyHp->setPosition(ccp(winSize.width * 0.8,winSize.height * 0.95));
    enemyHp->setTag(tagEnemyHp);
	this->addChild(enemyHp,2);

    this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 1);

    return true;
}
//****************************************************************************************
//スケジュール系
//****************************************************************************************
// 矢印表示
//void HelloWorld::showArrow()
void HelloWorld::showArrow(float time)
{
	//ジェスチャー抽選
    int randum = rand() % 4;
    nowGesture = randum;

	//矢印ラベルを取得
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(tagArrowLabel);
	if (arrowLabel)
	{
		//矢印ラベルを更新する
		arrowLabel->setString(arrowArray[randum].getCString());
	} else {
		//画面サイズを取得する
	    Size visibleSize = Director::getInstance()->getVisibleSize();
	    Point origin = Director::getInstance()->getVisibleOrigin();

		//矢印ラベルを生成する
		arrowLabel = LabelTTF::create(arrowArray[randum].getCString(), "Arial", 90.0);
		arrowLabel->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		arrowLabel->setTag(tagArrowLabel);
		this->addChild(arrowLabel,2);
	}
	this->scheduleOnce(schedule_selector(HelloWorld::timeOver), (float)defaultEnemySpeed - enemySpeedLv / 10.0);

}

void HelloWorld::timeOver(float time)
{
	nowGesture = 99;
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	arrowLabel->setString("timeOut");

	//HP更新
	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagHp);
	NowHp = NowHp - defaultEnemyPower * enemypowerLv;
	hpLabel->setString(String::createWithFormat("残りHP:%d", NowHp)->getCString());
	if (NowHp < 1){
		hpLabel->setString(String::createWithFormat("残りHP:%d", 0)->getCString());
		arrowLabel->setString("GameOver");
	} else {
		this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 1);
	}
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// タッチ系
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    Point point = touch->getLocation();
//    CCLOG("X = %f, y = %f", point.x, point.y);
    this->xtGestureStartPoint= point;
    return true;
}

//void HelloWorld::onTouchMoved(Touch* touch, Event* event)
//{
//    Point point = touch->getLocation();
//    CCLOG("X = %f, y = %f", point.x, point.y);
//}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	if (nowGesture < 99){
		//タイムアウトチェックタイマーを停止する
		this->unschedule(schedule_selector(HelloWorld::timeOver));

		Point point = touch->getLocation();
		this->xtGestureEndPoint= point;

		float deltaX = this->xtGestureStartPoint.x - this->xtGestureEndPoint.x;
		float deltaY = this->xtGestureStartPoint.y - this->xtGestureEndPoint.y;

		bool wkGesture = false;
		if (fabs(deltaX) > fabs(deltaY)) {
			if ((deltaX + 200 < 0 && nowGesture == 0) || (deltaX - 200 > 0 && nowGesture == 1)) wkGesture = true;
		} else {
			if ((deltaY + 200 < 0 && nowGesture == 2) || (deltaY - 200 > 0 && nowGesture == 3)) wkGesture = true;
		}

		nowGesture = 99;
		if (wkGesture){
			attack();
		} else {
			miss();
		}
	}
}

void HelloWorld::attack()
{
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	arrowLabel->setString("ぬこぱーんち");

	//HP更新
	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagEnemyHp);
	hpLabel->setString(String::createWithFormat("敵残りHP:%d", --NowEnemyHp)->getCString());
	if (NowEnemyHp < 1){
		arrowLabel->setString("クリア！！");
	} else {
		this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 0.2);
	}
}

void HelloWorld::miss()
{
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	arrowLabel->setString("ミス！");

	//HP更新
	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagHp);
	NowHp = NowHp - defaultEnemyPower * enemypowerLv;
	hpLabel->setString(String::createWithFormat("残りHP:%d", NowHp)->getCString());
	if (NowHp < 1){
		arrowLabel->setString("GameOver");
	} else {
		this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 0.2);
	}
}

