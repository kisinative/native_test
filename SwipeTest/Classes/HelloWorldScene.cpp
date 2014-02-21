#include "HelloWorldScene.h"
#include "KSAnimation.h"

USING_NS_CC;
//String arrowArray[] = {"右", "左", "上", "下"};
String arrowArray[] = {"0", "1", "2", "3","02","03","12","13","20","21","30","31"};

#define WINSIZE CCDirector::sharedDirector()->getWinSize()
#define TEXT_SCALE WINSIZE.width/1080

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
    
    EGLView::sharedOpenGLView()->setDesignResolutionSize(640, 1136, kResolutionNoBorder);
//    EGLView::sharedOpenGLView()->setDesignResolutionSize(1080, 1776, kResolutionNoBorder);
//    EGLView::sharedOpenGLView()->setDesignResolutionSize(320, 480, kResolutionNoBorder);

    // シングルタッチモードにする
    this->setTouchMode(kCCTouchesOneByOne);
    // タッチを有効にする（内部的にEventDispatcherに登録される）
    this->setTouchEnabled(true);

    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Size visibleSize = Director::sharedDirector()->getWinSize();
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
    enemyTechniqueLv = 1;
    nowStage = 1;
    nowGesture = "";

    // 背景を生成
//    Sprite* pBG = Sprite::create("testbackimg.png");
//    pBG->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.5));
//    this->addChild(pBG);
//    Sprite* pBG = Sprite::create("masu.png");
//    pBG->setPosition(Point(origin.x, origin.y));
//    this->addChild(pBG);
    CCLOG("visible = %f,visible = %f",origin.x,origin.y);


//    CCLOG("visible = %f,visible = %f",visibleSize.width,visibleSize.height);
	//矢印ラベルを生成する
    LabelTTF* arrowLabel = LabelTTF::create("れでぃ", "Arial", 90.0*TEXT_SCALE);
	arrowLabel->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	arrowLabel->setTag(tagArrowLabel);
	this->addChild(arrowLabel,2);
//    CCLOG("aaaaaaa = %f,bbbbbbb = %f",origin.x,origin.y);

	Node* pTarget = Sprite::create("target.png");
//	pTarget->setPosition(ccp(visibleSize.width * 0.05, visibleSize.height * 0.80));
	pTarget->setPosition(Point(pTarget->getContentSize().width+50.0, visibleSize.height * 0.80));
	pTarget->setTag(tagTargetImg);
	this->addChild(pTarget);

			Node* pTarget1 = Sprite::create("target.png");
			pTarget1->setPosition(Point(pTarget->getContentSize().width+50.0 - 5.0, visibleSize.height * 0.75));
			pTarget1->setTag(200);
			this->addChild(pTarget1);
			Node* pTarget2 = Sprite::create("target.png");
			pTarget2->setPosition(Point(pTarget->getContentSize().width+50.0 + 5.0, visibleSize.height * 0.75));
			pTarget2->setTag(201);
			this->addChild(pTarget2);
			Node* pTarget3 = Sprite::create("target.png");
			pTarget3->setPosition(Point(pTarget->getContentSize().width+50.0 - 50.0, visibleSize.height * 0.70));
			pTarget3->setTag(202);
			this->addChild(pTarget3);
			Node* pTarget4 = Sprite::create("target.png");
			pTarget4->setPosition(Point(pTarget->getContentSize().width+50.0 + 50.0, visibleSize.height * 0.70));
			pTarget4->setTag(203);
			this->addChild(pTarget4);

	Node* pHp = Sprite::create("gauge_blue.png");
	pHp->setPosition(Point(visibleSize.width * 0.1, visibleSize.height * 0.95));
	pHp->setAnchorPoint(CCPointZero);
	pHp->setTag(tagHpImg);
	this->addChild(pHp);

	Node* pHpEnemy = Sprite::create("gauge_red.png");
	pHpEnemy->setPosition(Point(visibleSize.width * 0.9, visibleSize.height * 0.90));
	pHpEnemy->setAnchorPoint(Point(1,0));
	pHpEnemy->setTag(tagEnemyHpImg);
	this->addChild(pHpEnemy);

	//敵初期ステータス設定
    setup();

    return true;
}

void HelloWorld::setup()
{
//    Size winSize = Director::sharedDirector()->getWinSize();
    Size winSize = Director::getInstance()->getVisibleSize();
    //HP表示
	createLabel(String::createWithFormat("残りHP:%d", NowHp)->getCString(),
				50.0*TEXT_SCALE,
				winSize.width * 0.15,
				winSize.height * 0.95,
				tagHp);


	//敵HP表示
	NowEnemyHp = defaultEnemyStrong + (5 * enemyStrongLv);
	MaxEnemyHp = NowEnemyHp;
	createLabel(String::createWithFormat("敵残りHP:%d", NowEnemyHp)->getCString(),
				50.0*TEXT_SCALE,
				winSize.width * 0.8,
				winSize.height * 0.95,
				tagEnemyHp);

	//敵LV表示
	createLabel(String::createWithFormat("タフネスLV:%d", enemyStrongLv)->getCString(),
				50.0*TEXT_SCALE,
				winSize.width * 0.8,
				winSize.height * 0.90,
				tagEnemyStrong);
	createLabel(String::createWithFormat("パワーLV:%d", enemypowerLv)->getCString(),
				50.0*TEXT_SCALE,
				winSize.width * 0.8,
				winSize.height * 0.85,
				tagEnemyPower);
	createLabel(String::createWithFormat("スピードLV:%d", enemySpeedLv)->getCString(),
				50.0*TEXT_SCALE,
				winSize.width * 0.8,
				winSize.height * 0.80,
				tagEnemySpeed);
	createLabel(String::createWithFormat("テクニックLV:%d", enemyTechniqueLv)->getCString(),
				50.0*TEXT_SCALE,
				winSize.width * 0.8,
				winSize.height * 0.75,
				tagEnemyTechnique);

	//攻撃数を初期化
	atkCount = tagArrowImg;
    frontArrowTag = tagArrowImg;
    NowEnemyRush = 0;
    rushCount = 0;

	Node* pHpImg = this->getChildByTag(tagEnemyHpImg);
	pHpImg->runAction(KSAnimation::hpAction(1.0));

//    this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 2);
    this->schedule(schedule_selector(HelloWorld::showArrow), 2);

}

void HelloWorld::createLabel(std::string labelString, float labelSize, float labelWidth, float labelHeight, int labelTag)
{
	LabelTTF* wkLabel = (LabelTTF*)this->getChildByTag(labelTag);
	if (wkLabel)
	{
		wkLabel->setString(labelString);
	} else {
		wkLabel = LabelTTF::create(labelString, "Arial", labelSize);
		wkLabel->setPosition(Point(labelWidth, labelHeight));
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
    int randum = arc4random() % 12;
    targetGesture = arrowArray[randum].getCString();
    moveArrow.push_back(arrowArray[randum].getCString());
    
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(tagArrowLabel);
	arrowLabel->setString("");

    Node* pArrow = this->getChildByTag(atkCount);
    if (pArrow)
    {
    	pArrow->removeFromParentAndCleanup(true);
    }
    Size size = Director::getInstance()->getVisibleSize();
//	Size size = Director::sharedDirector()->getWinSize();
//	Sprite* pArrow = Sprite::create(String::createWithFormat("%d.png",randum)->getCString());
    
    //攻防判定
    int atkDefFlag = arc4random() % (50 + defaultEnemyTechnique +enemyTechniqueLv);
    if ((atkDefFlag < (defaultEnemyTechnique +enemyTechniqueLv)) || (rushCount > 0))
    {
        //防御
        pArrow = Sprite::create("back_red.png");
        moveAtkDef.push_back(1);
    } else {
        //攻撃
        pArrow = Sprite::create("back_blue.png");
        moveAtkDef.push_back(0);
    }
 	
	pArrow->setPosition(Point(size.width, size.height * 0.80));
	pArrow->setTag(atkCount++);
	this->addChild(pArrow);
	Node* pArrow1 = Sprite::create(String::createWithFormat("%s.png",arrowArray[randum].getCString())->getCString());
	Size bgSize = pArrow->getContentSize();
	pArrow1->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.5));
	pArrow->addChild(pArrow1);

	CallFunc* callFunction = CallFunc::create(this, callfunc_selector(HelloWorld::timeOver));
    Sequence* callAction = Sequence::create(KSAnimation::vibrationAnimation((float)defaultEnemySpeed - enemySpeedLv / 10.0), callFunction, RemoveSelf::create(true), NULL);

	pArrow->runAction(callAction);

	//ラッシュ処理
	if (rushCount > 0)
	{
		if (--rushCount == 0)
		{
			NowEnemyRush = 0;
			this->unschedule(schedule_selector(HelloWorld::showArrow));
			this->schedule(schedule_selector(HelloWorld::showArrow), 2);
		}
	}


//	this->scheduleOnce(schedule_selector(HelloWorld::timeOver), (float)defaultEnemySpeed - enemySpeedLv / 10.0);

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
void HelloWorld::timeOver()
{
    frontArrowTag++;
//	targetGesture = "99";
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	arrowLabel->setString("timeOut");

	//HP更新
	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagHp);
	NowHp = NowHp - (defaultEnemyPower + 2 * enemypowerLv);
	hpLabel->setString(String::createWithFormat("残りHP:%d", NowHp)->getCString());
//    for (int i = 1;i < moveArrow.size();i++)
//    {
//        moveArrow[i-1] = moveArrow[i];
//    }
//    moveArrow.pop_back();

	if (moveAtkDef[0] == 1)
	{
		//ガード失敗連続攻撃
		Node* pArrow = this->getChildByTag(frontArrowTag);
		if (pArrow) {
			Animation *animation = Animation::create();
			animation->addSpriteFrameWithFileName("back_red.png");
			animation->setDelayPerUnit( 0.1f );
			animation->setRestoreOriginalFrame(false);
			moveAtkDef[0] = 1;
			RepeatForever *action = RepeatForever::create( Animate::create(animation) );
			pArrow->runAction(action);
		}
	}

    moveArrow.erase(moveArrow.begin());
    moveAtkDef.erase(moveAtkDef.begin());

	Node* pHpImg = this->getChildByTag(tagHpImg);
	float wk_a = (float)NowHp / MaxHp;
	pHpImg->runAction(KSAnimation::hpAction(wk_a));

	if (NowHp < 1){
		hpLabel->setString(String::createWithFormat("残りHP:%d", 0)->getCString());
		arrowLabel->setString("GameOver");
        makeRetryButton();
//	} else {
//		this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 1);
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
//				CCLOG("X = %s", nowGesture.substr(wkLen,1).c_str());
				if (nowGesture == "")
				{
	//				if ((deltaX + 100 < 0 && subGesture == "0") || (deltaX - 100 > 0 && subGesture == "1"))
					if (deltaX + 100 < 0)
					{
						nowGesture += migi;
						this->xtGestureStartPoint= point;
					}
					if (deltaX - 100 > 0)
					{
	//					targetGesture = targetGesture.substr(1);
						nowGesture += hidari;
						this->xtGestureStartPoint= point;
					}
				}
			} else {
				if (nowGesture == "")
				{
	//				if ((deltaY + 100 < 0 && subGesture == "2") || (deltaY - 100 > 0 && subGesture == "3"))
					if (deltaY + 100 < 0)
					{
						nowGesture += ue;
						this->xtGestureStartPoint= point;
					}
					if (deltaY - 100 > 0)
					{
	//					targetGesture = targetGesture.substr(1);
						nowGesture += sita;
						this->xtGestureStartPoint= point;
					}
//					CCLOG("--------------");
//					CCLOG("X = %f, y = %f", deltaX, deltaY);
//					CCLOG("targetGesture = %s", targetGesture.c_str());
//					CCLOG("nowGesture = %s", nowGesture.c_str());
				}
			}
		}
//		CCLOG("targetGesture = %s", targetGesture.c_str());
//	}
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	if (moveArrow.size() > 0){

		//矢印削除
		Node* pArrow = this->getChildByTag(frontArrowTag++);
		auto arrowPoint = pArrow->getPosition();
		pArrow->removeFromParentAndCleanup(true);

		Node* pTarget = this->getChildByTag(tagTargetImg);
		auto targetPoint = pTarget->getPosition();

		Size visibleSize = Director::getInstance()->getVisibleSize();
//        Size visibleSize = Director::sharedDirector()->getWinSize();


//		//タイムアウトチェックタイマーを停止する
//		this->unschedule(schedule_selector(HelloWorld::timeOver));

//		Point point = touch->getLocation();
//		this->xtGestureEndPoint= point;
//
//		float deltaX = this->xtGestureStartPoint.x - this->xtGestureEndPoint.x;
//		float deltaY = this->xtGestureStartPoint.y - this->xtGestureEndPoint.y;
//
		bool wkGesture = false;
		//攻防判定
		bool wkAtkDef  = false;
		if (moveAtkDef[0] == 0) wkAtkDef = true;

//		if (fabs(deltaX) > fabs(deltaY)) {
//			if ((deltaX + 50 < 0 && targetGesture == "0") || (deltaX - 50 > 0 && targetGesture == "1")) wkGesture = true;
//		} else {
//			if ((deltaY + 50 < 0 && targetGesture == "2") || (deltaY - 50 > 0 && targetGesture == "3")) wkGesture = true;
//		}
//		CCLOG("-------end-------");
//		CCLOG("targetGesture = %s", targetGesture.c_str());
//		CCLOG("nowGesture = %s", nowGesture.c_str());
//		CCLOG("X = %f, y = %f", deltaX, deltaY);
//		CCLOG("X = %f, y = %f", point.x, point.y);

		int flag = 0;
//		if (nowGesture == targetGesture)
        
		if (nowGesture == moveArrow[0])
		{
			if ((targetPoint.x - 50.0 <= arrowPoint.x) && (targetPoint.x + 50.0 >= arrowPoint.x))
			{
				wkGesture = true;
				if ((targetPoint.x - 5.0 <= arrowPoint.x) && (targetPoint.x + 5.0 >= arrowPoint.x))
				{
					flag = 1;
				}
			}
		}

//		targetGesture = "99";
//		moveArrow->removeObjectAtIndex(0);
        
//        for (int i = 1;i < moveArrow.size();i++)
//        {
//            moveArrow[i-1] = moveArrow[i];
//        }
//		moveArrow.pop_back();
        moveArrow.erase(moveArrow.begin());
        moveAtkDef.erase(moveAtkDef.begin());
        
		if (wkGesture){
			if (wkAtkDef){
				attack(flag);
			} else {
				defense(flag);
			}
			NowEnemyRush += 1;
		} else {
			miss(wkAtkDef);
			NowEnemyRush += 5;
		}

		if (NowEnemyRush >= 20 && rushCount == 0)
		{
			rushCount = 5;
			this->unschedule(schedule_selector(HelloWorld::showArrow));
			this->schedule(schedule_selector(HelloWorld::showArrow), 1);
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
void HelloWorld::attack(int flag)
{
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	if (flag == 0)
	{
		arrowLabel->setString("ぬこぱーんち");
		--NowEnemyHp;
	} else {
		arrowLabel->setString("すーぱー");
		NowEnemyHp -= 3;
		if (NowEnemyHp < 0) {
			NowEnemyHp = 0;
		}
	}

	Node* pHpImg = this->getChildByTag(tagEnemyHpImg);
	float wk_a = (float)NowEnemyHp / MaxEnemyHp;
	pHpImg->runAction(KSAnimation::hpAction(wk_a));

	//HP更新
	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagEnemyHp);
	hpLabel->setString(String::createWithFormat("敵残りHP:%d", NowEnemyHp)->getCString());
	if (NowEnemyHp < 1){
        arrowRefresh();
		arrowLabel->setString(String::createWithFormat("%dステージクリア！！ ",nowStage)->getCString());
	    int randum = rand() % 4;
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
	    	case 3:
	    	    enemyTechniqueLv++;
	    		break;
	    }
	    //HP回復
	    NowHp += 20;
	    if (MaxHp < NowHp)
	    {
	    	NowHp = MaxHp;
	    }
		Node* pHpImg = this->getChildByTag(tagHpImg);
		float wk_a = (float)NowHp / MaxHp;
		pHpImg->runAction(KSAnimation::hpAction(wk_a));


		this->scheduleOnce(schedule_selector(HelloWorld::nextStage), 1.3);
//	} else {
//		this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 0.2);
	}
}

/*
 *	攻撃成功
 */
void HelloWorld::defense(int flag)
{

	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	arrowLabel->setString("ガード");

}

/*
 *	攻撃失敗
 */
void HelloWorld::miss(bool flag)
{
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	arrowLabel->setString("ミス！");

	if (!flag)
	{
		//ガード失敗連続攻撃
		Node* pArrow = this->getChildByTag(frontArrowTag);
		if (pArrow) {
			Animation *animation = Animation::create();
			animation->addSpriteFrameWithFileName("back_red.png");
			animation->setDelayPerUnit( 0.1f );
			animation->setRestoreOriginalFrame(false);
			moveAtkDef[0] = 1;
			RepeatForever *action = RepeatForever::create( Animate::create(animation) );
			pArrow->runAction(action);
		}
	}

	//HP更新
	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagHp);
	NowHp = NowHp - (defaultEnemyPower + 2 * enemypowerLv);

	Node* pHpImg = this->getChildByTag(tagHpImg);
	float wk_a = (float)NowHp / MaxHp;
	pHpImg->runAction(KSAnimation::hpAction(wk_a));

	hpLabel->setString(String::createWithFormat("残りHP:%d", NowHp)->getCString());
	if (NowHp < 1){
        hpLabel->setString(String::createWithFormat("残りHP:%d", 0)->getCString());
		arrowLabel->setString("GameOver");
		makeRetryButton();
//	} else {
//		this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 1);
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
    arrowRefresh();
    
	//画面サイズを取得する
//	Size winSize = Director::sharedDirector()->getWinSize();
    Size winSize = Director::getInstance()->getVisibleSize();

	//リトライボタンを作成する
	LabelTTF* retryLabel = LabelTTF::create("Retry?", "Arial", 80.0);
    MenuItemLabel* retryItem = MenuItemLabel::create(retryLabel, [&](Object *sender) {
			//ゲームのシーンを新しく用意する
			Scene* gameScene = (Scene*)HelloWorld::create();
            Director::getInstance()->replaceScene(gameScene);
    	});


	retryItem->setPosition(Point(winSize.width * 0.5,winSize.height *0.4));

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
//	Director::sharedDirector()->replaceScene(gameScene);
	Director::getInstance()->replaceScene(gameScene);
}

void HelloWorld::arrowRefresh()
{
    this->unschedule(schedule_selector(HelloWorld::showArrow));
    for (int i = frontArrowTag;i < atkCount; i++)
    {
        Node* pArrow = this->getChildByTag(i);
        pArrow->removeFromParentAndCleanup(true);
    }
    moveArrow.clear();
    moveAtkDef.clear();
}
 
 
