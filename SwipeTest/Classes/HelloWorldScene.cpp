#include "HelloWorldScene.h"

USING_NS_CC;

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

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
//    UILayer* pUILayer = UILayer::create();
//    pUILayer->addWidget(UIHELPER->createWidgetFromJsonFile("test_1.json"));
//    this->addChild(pUILayer, 100);

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

	String arrowArray[] = {"右", "左", "上", "下"};

	//矢印ラベル用タグ
	const int tagArrowLabel = 100;
    int randum = rand() % 4;

//	//ゲーム時間を文字列に変換する
//	String* timeString = String::createWithFormat("%8.1fs",gametime);
	String arrowString = arrowArray[randum];
//    cocos2d::String arrowString = "右";

	//ゲーム時間ラベルを取得
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(tagArrowLabel);
	if (arrowLabel)
	{
		//ゲーム時間を更新する
//		arrowLabel->setString(arrowArray[randum]->m_sString.c_str());
		arrowLabel->setString(arrowString.getCString());

	} else {
		//画面サイズを取得する
		Size winSize = Director::sharedDirector()->getWinSize();

		//ゲーム時間ラベルを生成する
		arrowLabel = LabelTTF::create(arrowString.getCString(), "Arial", 45.0);
		arrowLabel->setPosition(ccp(winSize.width * 0.9,
								    winSize.height * 0.9));
		arrowLabel->setTag(tagArrowLabel);
		this->addChild(arrowLabel,2);

	}

	this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 2);

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
    Point point = touch->getLocation();
    this->xtGestureEndPoint= point;

    float deltaX = this->xtGestureStartPoint.x - this->xtGestureEndPoint.x;
    float deltaY = this->xtGestureStartPoint.y - this->xtGestureEndPoint.y;

    if (fabs(deltaX) > fabs(deltaY)) {
        if (deltaX + 200 < 0) {
        	CCLOG("RIGHT");
        	return;
        }

        if (deltaX - 200 > 0){
        	CCLOG("LEFT");
        	return;
        }
        CCLOG("NG");
    } else {
        if (deltaY + 200 < 0){
        	CCLOG("UP");
        	return;
        }
        if (deltaY - 200 > 0){
        	CCLOG("DOWN");
        	return;
        }
        CCLOG("NG");
    }


//    CCLOG("X = %f, y = %f", point.x, point.y);
}


