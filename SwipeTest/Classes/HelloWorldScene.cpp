#include "HelloWorldScene.h"
#include "KSAnimation.h"

USING_NS_CC;
//String arrowArray[] = {"右", "左", "上", "下"};
String arrowArray[] = {"0", "1", "2", "3","02","03","12","13","20","21","30","31"};

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);

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
    targetGesture = "99";
    enemyStrongLv = 1;
    enemypowerLv = 1;
    enemySpeedLv = 1;
    nowStage = 1;
    nowGesture = "";

//	//画面サイズを取得する
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Point origin = Director::getInstance()->getVisibleOrigin();
	//矢印ラベルを生成する
    LabelTTF* arrowLabel = LabelTTF::create("れでぃ", "Arial", 90.0);
	arrowLabel->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	arrowLabel->setTag(tagArrowLabel);
	this->addChild(arrowLabel,2);

	//敵初期ステータス設定
    setup();

    return true;
}

void HelloWorld::setup()
{
    Size winSize = Director::sharedDirector()->getWinSize();
    //HP表示
	createLabel(String::createWithFormat("残りHP:%d", NowHp)->getCString(),
				50.0,
				winSize.width * 0.15,
				winSize.height * 0.95,
				tagHp);
	//敵HP表示
	NowEnemyHp = defaultEnemyStrong + (5 * enemyStrongLv);
	createLabel(String::createWithFormat("敵残りHP:%d", NowEnemyHp)->getCString(),
				50.0,
				winSize.width * 0.8,
				winSize.height * 0.95,
				tagEnemyHp);
	//敵LV表示
	createLabel(String::createWithFormat("タフネスLV:%d", enemyStrongLv)->getCString(),
				50.0,
				winSize.width * 0.8,
				winSize.height * 0.90,
				tagEnemyStrong);
	createLabel(String::createWithFormat("パワーLV:%d", enemypowerLv)->getCString(),
				50.0,
				winSize.width * 0.8,
				winSize.height * 0.85,
				tagEnemyPower);
	createLabel(String::createWithFormat("スピードLV:%d", enemySpeedLv)->getCString(),
				50.0,
				winSize.width * 0.8,
				winSize.height * 0.80,
				tagEnemySpeed);

    this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 2);

}

void HelloWorld::createLabel(std::string labelString, float labelSize, float labelWidth, float labelHeight, int labelTag)
{
	LabelTTF* wkLabel = (LabelTTF*)this->getChildByTag(labelTag);
	if (wkLabel)
	{
		wkLabel->setString(labelString);
	} else {
		wkLabel = LabelTTF::create(labelString, "Arial", labelSize);
		wkLabel->setPosition(ccp(labelWidth, labelHeight));
		wkLabel->setTag(labelTag);
		this->addChild(wkLabel,2);
	}
}


//****************************************************************************************
//スケジュール系
//****************************************************************************************
// 矢印表示
//void HelloWorld::showArrow()
void HelloWorld::showArrow(float time)
{
	//ジェスチャー抽選
    int randum = rand() % 12;
    targetGesture = arrowArray[randum].getCString();

//	//矢印ラベルを取得
//	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(tagArrowLabel);
//	//矢印ラベルを更新する
//	arrowLabel->setString(arrowArray[randum].getCString());

	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(tagArrowLabel);
	arrowLabel->setString("");

    Node* pArrow = this->getChildByTag(tagArrowImg);
    if (pArrow)
    {
    	pArrow->removeFromParentAndCleanup(true);
    }
	Size size = Director::sharedDirector()->getWinSize();
//	Sprite* pArrow = Sprite::create(String::createWithFormat("%d.png",randum)->getCString());
	pArrow = Sprite::create(String::createWithFormat("%s.png",arrowArray[randum].getCString())->getCString());
	pArrow->setPosition(ccp(size.width * 0.50, size.height * 0.60));
	pArrow->setTag(tagArrowImg);
	this->addChild(pArrow);
	pArrow->runAction(KSAnimation::vibrationAnimation((float)defaultEnemySpeed - enemySpeedLv / 10.0));

	this->scheduleOnce(schedule_selector(HelloWorld::timeOver), (float)defaultEnemySpeed - enemySpeedLv / 10.0);

}

/*
 * 次ステージ
 */
void HelloWorld::nextStage(float time)
{
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(tagArrowLabel);
	arrowLabel->setString(String::createWithFormat("%dステージれでぃ！",++nowStage)->getCString());
	setup();
}


/*
 * タイムオーバー
 */
void HelloWorld::timeOver(float time)
{
	targetGesture = "99";
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	arrowLabel->setString("timeOut");

	//HP更新
	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagHp);
	NowHp = NowHp - (defaultEnemyPower + 5 * enemypowerLv);
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

//****************************************************************************************
// タッチ系
//****************************************************************************************
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    Point point = touch->getLocation();
//    CCLOG("X = %f, y = %f", point.x, point.y);
    this->xtGestureStartPoint= point;
    return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
//    Point point = touch->getLocation();
//    CCLOG("X = %f, y = %f", point.x, point.y);

//	if (targetGesture.size() > 1) {
		Point point = touch->getLocation();
		this->xtGestureEndPoint= point;

		float deltaX = this->xtGestureStartPoint.x - this->xtGestureEndPoint.x;
		float deltaY = this->xtGestureStartPoint.y - this->xtGestureEndPoint.y;

//		std::string subGesture = targetGesture.substr(0,1);

//		CCLOG("--------------");
//		CCLOG("X = %d", subGesture.size());
//		CCLOG("targetGesture = %s", targetGesture.c_str());
//		CCLOG("subGesture = %s", subGesture.c_str());
		int wkLen = 0;
		if (nowGesture.size() > 0)
		{
			wkLen = nowGesture.size() - 1;
			if ((nowGesture.substr(wkLen,1) == "2") || (nowGesture.substr(wkLen,1) == "3")) {
				if (deltaX + 100 < 0)
				{
					nowGesture += migi;
					this->xtGestureStartPoint= point;
				}
				if (deltaX - 100 > 0)
				{
					nowGesture += hidari;
					this->xtGestureStartPoint= point;
				}
			} else {
				if (deltaY + 100 < 0)
				{
					nowGesture += ue;
					this->xtGestureStartPoint= point;
				}
				if (deltaY - 100 > 0)
				{
					nowGesture += sita;
					this->xtGestureStartPoint= point;
				}
			}
		} else {
			if (fabs(deltaX) > fabs(deltaY)) {
				CCLOG("X = %s", nowGesture.substr(wkLen,1).c_str());
				if (nowGesture == "")
				{
	//				if ((deltaX + 100 < 0 && subGesture == "0") || (deltaX - 100 > 0 && subGesture == "1"))
					if (deltaX + 100 < 0)
					{
						CCLOG("aaaaaaaaaaaaaaaaaaaa");
						nowGesture += migi;
						this->xtGestureStartPoint= point;
					}
					if (deltaX - 100 > 0)
					{
						CCLOG("aaaaaaaaaaaaaaaaaaaa");
	//					targetGesture = targetGesture.substr(1);
						nowGesture += hidari;
						this->xtGestureStartPoint= point;
					}
					CCLOG("--------------");
					CCLOG("X = %f, y = %f", deltaX, deltaY);
					CCLOG("targetGesture = %s", targetGesture.c_str());
					CCLOG("nowGesture = %s", nowGesture.c_str());
				}
				CCLOG("cccccc");
			} else {
				CCLOG("Y = %s", nowGesture.substr(wkLen,1).c_str());
				if (nowGesture == "")
				{
	//				if ((deltaY + 100 < 0 && subGesture == "2") || (deltaY - 100 > 0 && subGesture == "3"))
					if (deltaY + 100 < 0)
					{
						CCLOG("aaaaaaaaaaaaaaaaaaaa");
						nowGesture += ue;
						this->xtGestureStartPoint= point;
					}
					if (deltaY - 100 > 0)
					{
	//					targetGesture = targetGesture.substr(1);
						CCLOG("aaaaaaaaaaaaaaaaaaaa");
						nowGesture += sita;
						this->xtGestureStartPoint= point;
					}
					CCLOG("--------------");
					CCLOG("X = %f, y = %f", deltaX, deltaY);
					CCLOG("targetGesture = %s", targetGesture.c_str());
					CCLOG("nowGesture = %s", nowGesture.c_str());
				}
				CCLOG("ddddddddddd");
			}
		}
//		CCLOG("targetGesture = %s", targetGesture.c_str());
//	}
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	if (targetGesture < "99"){
		//タイムアウトチェックタイマーを停止する
		this->unschedule(schedule_selector(HelloWorld::timeOver));

//		Point point = touch->getLocation();
//		this->xtGestureEndPoint= point;
//
//		float deltaX = this->xtGestureStartPoint.x - this->xtGestureEndPoint.x;
//		float deltaY = this->xtGestureStartPoint.y - this->xtGestureEndPoint.y;
//
		bool wkGesture = false;
//		if (fabs(deltaX) > fabs(deltaY)) {
//			if ((deltaX + 50 < 0 && targetGesture == "0") || (deltaX - 50 > 0 && targetGesture == "1")) wkGesture = true;
//		} else {
//			if ((deltaY + 50 < 0 && targetGesture == "2") || (deltaY - 50 > 0 && targetGesture == "3")) wkGesture = true;
//		}
		CCLOG("-------end-------");
		CCLOG("targetGesture = %s", targetGesture.c_str());
		CCLOG("nowGesture = %s", nowGesture.c_str());
//		CCLOG("X = %f, y = %f", deltaX, deltaY);
//		CCLOG("X = %f, y = %f", point.x, point.y);

		if (nowGesture == targetGesture)
		{
			wkGesture = true;
		}

		targetGesture = "99";
		if (wkGesture){
			attack();
		} else {
			miss();
		}
	}
	nowGesture = "";
}

//****************************************************************************************
//攻撃成否系
//****************************************************************************************
/*
 *	攻撃成功
 */
void HelloWorld::attack()
{
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	arrowLabel->setString("ぬこぱーんち");

	//HP更新
	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagEnemyHp);
	hpLabel->setString(String::createWithFormat("敵残りHP:%d", --NowEnemyHp)->getCString());
	if (NowEnemyHp < 1){
	    Node* pArrow = this->getChildByTag(tagArrowImg);
    	pArrow->removeFromParentAndCleanup(true);

		arrowLabel->setString(String::createWithFormat("%dステージクリア！！ ",nowStage)->getCString());
	    int randum = rand() % 3;
	    switch (randum){
	    	case 0:
	    	    enemyStrongLv++;
	    		break;
	    	case 1:
	    	    enemypowerLv++;
	    		break;
	    	case 2:
	    	    enemySpeedLv++;
	    		break;
	    }
	    //HP回復
	    NowHp += 20;
		this->scheduleOnce(schedule_selector(HelloWorld::nextStage), 1.3);
	} else {
		this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 0.2);
	}
}

/*
 *	攻撃失敗
 */
void HelloWorld::miss()
{
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	arrowLabel->setString("ミス！");

	//HP更新
	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagHp);
	NowHp = NowHp - (defaultEnemyPower + 5 * enemypowerLv);
	hpLabel->setString(String::createWithFormat("残りHP:%d", NowHp)->getCString());
	if (NowHp < 1){
		arrowLabel->setString("GameOver");
		makeRetryButton();
	} else {
		this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 1);
	}
}

//****************************************************************************************
//再挑戦
//****************************************************************************************
/*
 * 再挑戦系ボタン作成
 */
void HelloWorld::makeRetryButton()
{
	//画面サイズを取得する
	Size winSize = Director::sharedDirector()->getWinSize();

	//リトライボタンを作成する
	LabelTTF* retryLabel = LabelTTF::create("Retry?", "Arial", 80.0);
    MenuItemLabel* retryItem = MenuItemLabel::create(retryLabel, [&](Object *sender) {
			//ゲームのシーンを新しく用意する
			Scene* gameScene = (Scene*)HelloWorld::create();
			Director::sharedDirector()->replaceScene(gameScene);
    	});


	retryItem->setPosition(ccp(winSize.width * 0.5,winSize.height *0.4));

	//メニューを作成する
	Menu* menu = Menu::create(retryItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu,3);
}

//リトライボタンタップ時の処理
void HelloWorld::tapRetryButton(Node *node)
{
	//ゲームのシーンを新しく用意する
	Scene* gameScene = (Scene*)HelloWorld::create();
	Director::sharedDirector()->replaceScene(gameScene);
}



