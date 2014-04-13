#include "HelloWorldScene.h"
#include "KSAnimation.h"
#include "TitleScene.h"
#include <unistd.h>

USING_NS_CC;
//String arrowArray[] = {"右", "左", "上", "下"};
String arrowArray[] = {"0", "1", "2", "3","02","03","12","13","20","21","30","31"};

#define WINSIZE CCDirector::sharedDirector()->getWinSize()
#define TEXT_SCALE WINSIZE.width/1080

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer,1);

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

//    EGLView::sharedOpenGLView()->setDesignResolutionSize(640, 1136, kResolutionNoBorder);

    //サイズ取得を行う
    origin			= Director::getInstance()->getVisibleOrigin();		//使用端末の(0,0)地点
	visibleSize		= Director::getInstance()->getVisibleSize();		//使用端末の画面サイズ

    // シングルタッチモードにする
    this->setTouchMode(kCCTouchesOneByOne);
    // タッチを有効にする（内部的にEventDispatcherに登録される）
    this->setTouchEnabled(true);

//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Point origin = Director::getInstance()->getVisibleOrigin();

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
    //プレイヤーの各種レベル取得
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	playerStrongLv 		= userDefault->getIntegerForKey(key_playerStrongLv, 1);
	playerPowerLv		= userDefault->getIntegerForKey(key_playerPowerLv, 1);
	playerSpeedLv		= userDefault->getIntegerForKey(key_playerSpeedLv, 1);
	playerTechniqueLv	= userDefault->getIntegerForKey(key_playerTechniqueLv, 1);
//    enemyStrongLv = 1;
//    enemypowerLv = 1;
//    enemySpeedLv = 1;
//    enemyTechniqueLv = 1;
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
	this->addChild(pTarget,2);

			Node* pTarget1 = Sprite::create("target.png");
			pTarget1->setPosition(Point(pTarget->getContentSize().width+50.0 - 5.0, visibleSize.height * 0.75));
			pTarget1->setTag(200);
			this->addChild(pTarget1,2);
			Node* pTarget2 = Sprite::create("target.png");
			pTarget2->setPosition(Point(pTarget->getContentSize().width+50.0 + 5.0, visibleSize.height * 0.75));
			pTarget2->setTag(201);
			this->addChild(pTarget2,2);
			Node* pTarget3 = Sprite::create("target.png");
			pTarget3->setPosition(Point(pTarget->getContentSize().width+50.0 - 50.0, visibleSize.height * 0.70));
			pTarget3->setTag(202);
			this->addChild(pTarget3,2);
			Node* pTarget4 = Sprite::create("target.png");
			pTarget4->setPosition(Point(pTarget->getContentSize().width+50.0 + 50.0, visibleSize.height * 0.70));
			pTarget4->setTag(203);
			this->addChild(pTarget4,2);

	//自他HP画像
	Node* pHp = Sprite::create("gauge_blue.png");
	pHp->setPosition(Point(visibleSize.width * 0.1, visibleSize.height * 0.95));
	pHp->setAnchorPoint(CCPointZero);
	pHp->setTag(tagHpImg);
	this->addChild(pHp,2);
	Node* pHpEnemy = Sprite::create("gauge_red.png");
	pHpEnemy->setPosition(Point(visibleSize.width * 0.9, visibleSize.height * 0.90));
	pHpEnemy->setAnchorPoint(Point(1,0));
	pHpEnemy->setTag(tagEnemyHpImg);
	this->addChild(pHpEnemy,2);
	//自他サムネイル
	Node* pThumbnail = Sprite::create("mycat.png");
	pThumbnail->setPosition(Point(origin.x, visibleSize.height));
	pThumbnail->setAnchorPoint(Point(0,1));
	pThumbnail->setTag(tagThumbnailImg);
	this->addChild(pThumbnail,2);
	Node* pEnemyThumbnail = Sprite::create("enemy.png");
	pEnemyThumbnail->setPosition(Point(visibleSize.width, visibleSize.height));
	pEnemyThumbnail->setAnchorPoint(Point(1,1));
	pEnemyThumbnail->setTag(tagEnemyThumbnail);
	this->addChild(pEnemyThumbnail,2);

	//自他サムネイル
	Node* pThumbnail1 = Sprite::create("mycat.png");
	pThumbnail1->setPosition(Point(visibleSize.width * 0.5, origin.y + 150));
	pThumbnail1->setAnchorPoint(Point(0,0));
	pThumbnail1->setTag(500);
	this->addChild(pThumbnail1,2);

	//敵初期ステータス設定
    setup();

    return true;
}

void HelloWorld::setup()
{

	//敵レベル取得
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	enemyLv = userDefault->getIntegerForKey(key_enemyLv, 1);
	enemyStrongLv		= enemyLv;
	enemypowerLv		= enemyLv;
	enemySpeedLv		= enemyLv;
	enemyTechniqueLv	= enemyLv;
	int randum = arc4random() % 4;
	switch (randum){
		case 0:
			enemyStrongLv = enemyStrongLv + 3;
			break;
		case 1:
			enemypowerLv = enemypowerLv + 3;
			break;
		case 2:
			enemySpeedLv = enemySpeedLv + 3;
			break;
		case 3:
			enemyTechniqueLv = enemyTechniqueLv + 3 ;
			break;
	}



    //HP表示
	createLabel(String::createWithFormat("残りHP:%d", NowHp)->getCString(),
				50.0*TEXT_SCALE,
				visibleSize.width * 0.15,
				visibleSize.height * 0.95,
				tagHp);


	//敵HP表示
	NowEnemyHp = defaultEnemyStrong + (6 * enemyStrongLv);
	MaxEnemyHp = NowEnemyHp;
	createLabel(String::createWithFormat("敵残りHP:%d", NowEnemyHp)->getCString(),
				50.0*TEXT_SCALE,
				visibleSize.width * 0.8,
				visibleSize.height * 0.95,
				tagEnemyHp);

	//敵LV表示
	createLabel(String::createWithFormat("タフネスLV:%d", enemyStrongLv)->getCString(),
				50.0*TEXT_SCALE,
				visibleSize.width * 0.8,
				visibleSize.height * 0.90,
				tagEnemyStrong);
	createLabel(String::createWithFormat("パワーLV:%d", enemypowerLv)->getCString(),
				50.0*TEXT_SCALE,
				visibleSize.width * 0.8,
				visibleSize.height * 0.85,
				tagEnemyPower);
	createLabel(String::createWithFormat("スピードLV:%d", enemySpeedLv)->getCString(),
				50.0*TEXT_SCALE,
				visibleSize.width * 0.8,
				visibleSize.height * 0.80,
				tagEnemySpeed);
	createLabel(String::createWithFormat("テクニックLV:%d", enemyTechniqueLv)->getCString(),
				50.0*TEXT_SCALE,
				visibleSize.width * 0.8,
				visibleSize.height * 0.75,
				tagEnemyTechnique);

	//攻撃数を初期化
	atkCount = tagArrowImg;
    frontArrowTag = tagArrowImg;
    NowRush = 0;
    NowEnemyRush = 0;
    rushCount = 0;

    //ラッシュ系初期化
    NowRush		= 0;
	rushStack	= false;
	rush_flag	= false;
	startRush	= startRushConst;

	//LV相殺
	enemySpeedLv	   -= playerSpeedLv / 2;
	enemyTechniqueLv   -= playerTechniqueLv / 2;
	enemySpeedLv		= enemySpeedLv		> 1 ? enemySpeedLv : 1;
	enemyTechniqueLv	= enemyTechniqueLv	> 1 ? enemyTechniqueLv : 1;
	CCLOG("enemySpeedLv = %d, enemyTechniqueLv = %d", enemySpeedLv, enemyTechniqueLv);
	CCLOG("test = %d", 5 / 2);

	Node* pHpImg = this->getChildByTag(tagEnemyHpImg);
	pHpImg->setScaleX(1.0);
//	pHpImg->runAction(KSAnimation::hpAction(1.0));

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

	pArrow->setPosition(Point(visibleSize.width, visibleSize.height * 0.80));
	pArrow->setTag(atkCount++);
	this->addChild(pArrow,2);
	Node* pArrow1 = Sprite::create(String::createWithFormat("%s.png",arrowArray[randum].getCString())->getCString());
	Size bgSize = pArrow->getContentSize();
	pArrow1->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.5));
	pArrow->addChild(pArrow1,3);

	CallFunc* callFunction = CallFunc::create(this, callfunc_selector(HelloWorld::timeOver));
//    Sequence* callAction = Sequence::create(KSAnimation::vibrationAnimation((float)defaultEnemySpeed - enemySpeedLv / 10.0), callFunction, RemoveSelf::create(true), NULL);
//
//	pArrow->runAction(callAction);

	Spawn* spawn = Spawn::createWithTwoActions(
			Sequence::create(KSAnimation::vibrationAnimation((float)defaultEnemySpeed - enemySpeedLv / 10.0), callFunction, RemoveSelf::create(true), NULL),
			KSAnimation::move1((float)defaultEnemySpeed - enemySpeedLv / 10.0)
	);
	pArrow->runAction(spawn);

//	pArrow->runAction(MoveTo::create(time, ccp(0.0, visibleSize.height * 0.80)));
//	pArrow->runAction(Sequence::create(MoveBy::create(0.8, ccp( -10, 0 )), MoveBy::create(0.8, ccp( 10, 0 )), NULL));

//	pArrow->runAction( MoveTo::create(1.0, ccp(0.0, visibleSize.height * 0.80)) );
//
//	//上下に50px移動を繰り返す
//	pArrow->runAction( RepeatForever::create(
//	Sequence::create( MoveBy::create(0.5, ccp( 0, -50 )),MoveBy::create(0.5, ccp( 0, 50 )),	NULL )));

//	pArrow->runAction(Spawn::createWithTwoActions(MoveTo::create(time, ccp(0.0, visibleSize.height * 0.80)),Sequence::create(MoveBy::create(0.5, ccp( 0, -50 )), MoveBy::create(0.5, ccp( 0, 50 )), NULL)));

//	pArrow->runAction(Spawn::createWithTwoActions(MoveTo::create(time, ccp(0.0, visibleSize.height * 0.80)),Sequence::create(MoveBy::create(0.5, ccp( -100, 0 )), MoveBy::create(0.5, ccp( 200, 0 )), NULL)));


//	pArrow->runAction(Spawn::createWithTwoActions(MoveTo::create(time, ccp(0.0, visibleSize.height * 0.80)),MoveTo::create(time, ccp(0.0, visibleSize.height * 0.80))));

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
//	arrowLabel->setString(String::createWithFormat("%dステージクリア！！ ",nowStage)->getCString());
	arrowLabel->setString("ステージクリア！！ ");

	// NEXTステージボタン設置
	MenuItemImage* pNext;
	pNext = MenuItemImage::create("next_1.png",
										 "next_2.png",
										 CC_CALLBACK_1(HelloWorld::tapNextLv, this));
	pNext->setPosition(Point(origin.x, origin.y + nextLvButton_y));
	pNext->setAnchorPoint(Point(0,0));

	Menu* pMenuNext = Menu::create(pNext, NULL);
	pMenuNext->setPosition(Point::ZERO);
	pMenuNext->setTag(tagNextButton);
	this->addChild(pMenuNext,10);

	// メニュー画面へ戻るボタン
	MenuItemImage* pRetrunMenu;
	pRetrunMenu = MenuItemImage::create("return_1.png",
										 "return_2.png",
										 CC_CALLBACK_1(HelloWorld::tapReturnMenu, this));
	pRetrunMenu->setPosition(Point(visibleSize.width, origin.y + returnMenuButton_y));
	pRetrunMenu->setAnchorPoint(Point(1,0));

	Menu* pMenuReturn = Menu::create(pRetrunMenu, NULL);
	pMenuReturn->setPosition(Point::ZERO);
	pMenuReturn->setTag(tagMenutButton);
	this->addChild(pMenuReturn,10);


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
	rushPoint(false);		//ラッシュポイント低下

	//HP更新
	meDamage();

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

	if (NowHp < 1){
		this->unschedule(schedule_selector(HelloWorld::showArrow));
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
	//ラッシュ中か？
	if (!rush_flag){
		Point point = touch->getLocation();
//    CCLOG("X = %f, y = %f", point.x, point.y);
		this->xtGestureStartPoint= point;
	}
	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
//    Point point = touch->getLocation();
//    CCLOG("X = %f, y = %f", point.x, point.y);

	//ラッシュ中か？
	if (!rush_flag){

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
	}
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	//ラッシュ中か？
	if (!rush_flag){

		//誤タッチ免除
		Point point = touch->getLocation();
		float deltaX = this->xtGestureStartPoint.x - point.x;
		float deltaY = this->xtGestureStartPoint.y - point.y;
		if (fabs(deltaX) <= 10.0 && fabs(deltaY) <= 10.0 ) {
			return;
		}

		if (moveArrow.size() > 0){

			//矢印削除
			Node* pArrow = this->getChildByTag(frontArrowTag++);
			auto arrowPoint = pArrow->getPosition();
			pArrow->removeFromParentAndCleanup(true);

			Node* pTarget = this->getChildByTag(tagTargetImg);
			auto targetPoint = pTarget->getPosition();

			bool wkGesture = false;
			//攻防判定
			bool wkAtkDef  = false;
			if (moveAtkDef[0] == 0) wkAtkDef = true;

			int flag = 0;

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

			if (NowEnemyRush >= startEnemyRush && rushCount == 0 && NowEnemyHp > 0)
			{
				rushCount = 5;
				this->unschedule(schedule_selector(HelloWorld::showArrow));
				this->schedule(schedule_selector(HelloWorld::showArrow), 1);
			} else {
				rushPoint(wkGesture);
			}
		}
		nowGesture = "";
	} else {
		Point point			= touch->getLocation();
		Node* pRushTarget	= getChildByTag(tagRushTarget);
		if (!pRushTarget){
			return;
		}
		Rect rushTarget		= pRushTarget->boundingBox();
		if (!rushTarget.containsPoint(point)) {
			return;
		}
		//現在のターゲットを消す
		pRushTarget->removeFromParentAndCleanup(true);

		randomTarget();			// ラッシュターゲット抽選


		//ダメージ処理
		NowEnemyHp -= rushAtk;
		if (NowEnemyHp < 0) {
			NowEnemyHp = 0;
		}

		Node* pHpImg = this->getChildByTag(tagEnemyHpImg);
		float wk_a = (float)NowEnemyHp / MaxEnemyHp;
		pHpImg->runAction(KSAnimation::hpAction(wk_a));
		pHpImg->setScaleX(wk_a);

		//HP更新
		LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagEnemyHp);
		hpLabel->setString(String::createWithFormat("敵残りHP:%d", NowEnemyHp)->getCString());
		if (NowEnemyHp < 1){
			this->unschedule(schedule_selector(HelloWorld::rushEnd));
			this->scheduleOnce(schedule_selector(HelloWorld::rushEnd), 0.0f);

//			LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
//			int randum = arc4random() % 4;
//			switch (randum){
//				case 0:
//					enemyStrongLv++;
//					break;
//				case 1:
//					enemypowerLv++;
//					break;
//				case 2:
//					enemySpeedLv++;
//					break;
//				case 3:
//					enemyTechniqueLv++;
//					break;
//			}

			//相手レベルUP
			UserDefault* userDefault = UserDefault::sharedUserDefault();
			enemyLv = userDefault->getIntegerForKey(key_enemyLv, 1) + 1;
			userDefault->setIntegerForKey(key_enemyLv, enemyLv);

			//HP回復
			NowHp += 20;
			if (MaxHp < NowHp)
			{
				NowHp = MaxHp;
			}
			Node* pHpImg = this->getChildByTag(tagHpImg);
			float wk_a = (float)NowHp / MaxHp;
			pHpImg->runAction(KSAnimation::hpAction(wk_a));
			pHpImg->setScaleX(wk_a);

			this->scheduleOnce(schedule_selector(HelloWorld::nextStage), 0.1);
		}

	}
}

//****************************************************************************************
//攻撃成否系
//****************************************************************************************
/*
 *	攻撃成功
 */
void HelloWorld::attack(int flag)
{

//	rushPoint(true);	//ラッシュポイント増加

	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	if (flag == 0)
	{
		arrowLabel->setString("ぬこぱーんち");
		NowEnemyHp -= normalAtk;
	} else {
		arrowLabel->setString("すーぱー");
		NowEnemyHp -= justAtk;
	}
	if (NowEnemyHp < 0) {
		NowEnemyHp = 0;
	}

	Node* pHpImg = this->getChildByTag(tagEnemyHpImg);
	float wk_a = (float)NowEnemyHp / MaxEnemyHp;
	pHpImg->runAction(KSAnimation::hpAction(wk_a));
	pHpImg->setScaleX(wk_a);

	//HP更新
	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagEnemyHp);
	hpLabel->setString(String::createWithFormat("敵残りHP:%d", NowEnemyHp)->getCString());
	if (NowEnemyHp < 1){
        arrowRefresh();
//	    int randum = arc4random() % 4;
//	    switch (randum){
//	    	case 0:
//	    	    enemyStrongLv++;
//	    		break;
//	    	case 1:
//	    	    enemypowerLv++;
//	    		break;
//	    	case 2:
//	    	    enemySpeedLv++;
//	    		break;
//	    	case 3:
//	    	    enemyTechniqueLv++;
//	    		break;
//	    }

		//相手レベルUP
		UserDefault* userDefault = UserDefault::sharedUserDefault();
		enemyLv = userDefault->getIntegerForKey(key_enemyLv, 1) + 1;
		userDefault->setIntegerForKey(key_enemyLv, enemyLv);

	    //HP回復
	    NowHp += 20;
	    if (MaxHp < NowHp)
	    {
	    	NowHp = MaxHp;
	    }
		Node* pHpImg = this->getChildByTag(tagHpImg);
		float wk_a = (float)NowHp / MaxHp;
		pHpImg->runAction(KSAnimation::hpAction(wk_a));
		pHpImg->setScaleX(wk_a);

		this->scheduleOnce(schedule_selector(HelloWorld::nextStage), 0.1);
//	} else {
//		this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 0.2);
	}
}

/*
 *	攻撃成功
 */
void HelloWorld::defense(int flag)
{

//	rushPoint(true);	//ラッシュポイント増加

	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	arrowLabel->setString("ガード");

}

/*
 *	攻撃失敗
 */
void HelloWorld::miss(bool flag)
{

//	rushPoint(false);	//ラッシュポイント初期化

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
	meDamage();

	if (NowHp < 1){
		this->unschedule(schedule_selector(HelloWorld::showArrow));
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

	//リトライボタンを作成する
	LabelTTF* retryLabel = LabelTTF::create("Retry?", "Arial", 80.0);
    MenuItemLabel* retryItem = MenuItemLabel::create(retryLabel, [&](Object *sender) {
			//ゲームのシーンを新しく用意する
			Scene* gameScene = (Scene*)HelloWorld::create();
            Director::getInstance()->replaceScene(gameScene);
    	});


	retryItem->setPosition(Point(visibleSize.width * 0.5,visibleSize.height *0.4));

	//メニューを作成する
	Menu* menu = Menu::create(retryItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu,2);
}


/*
 * 攻防処理リフレッシュ
 */
void HelloWorld::arrowRefresh()
{
    this->unschedule(schedule_selector(HelloWorld::showArrow));
    for (int i = frontArrowTag;i < atkCount; i++)
    {
        Node* pArrow = this->getChildByTag(i);
        pArrow->removeFromParentAndCleanup(true);
    }

	atkCount = tagArrowImg;
    frontArrowTag = tagArrowImg;

    moveArrow.clear();
    moveAtkDef.clear();
}


//****************************************************************************************
// 自ダメージ
//****************************************************************************************
void HelloWorld::meDamage()
{
	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagHp);
	NowHp = NowHp - (defaultEnemyPower + 2 * enemypowerLv);
	if (NowHp < 0){
		NowHp = 0;
	}
	hpLabel->setString(String::createWithFormat("残りHP:%d", NowHp)->getCString());

	Node* pHpImg = this->getChildByTag(tagHpImg);
	float wk_a = (float)NowHp / MaxHp;
	pHpImg->runAction(KSAnimation::hpAction(wk_a));
	pHpImg->setScaleX(wk_a);
}

/*****************************************************************************************
 *  ラッシュ関連
 *****************************************************************************************/
/*
 * 　ラッシュ開始処理
 */
//void HelloWorld::menuStartRush(Object* sender)
void HelloWorld::menuStartRush()
{
	arrowRefresh();			// 攻防の矢印をリフレッシュ
	rush_flag = true;		// ラッシュフラグをtrueにする
	NowRush = 0;			// ラッシュポイントを初期化

//	//ラッシュ開始ボタン削除
//	Node* pRushMenu   = this->getChildByTag(tagRushMenu);
//	pRushMenu->removeFromParentAndCleanup(true);

	//カットイン作成
	Node* pCutin = Sprite::create("rush_cutin.png");
	pCutin->setPosition(Point(visibleSize.width, visibleSize.height * 0.45));
	pCutin->setTag(tagRushCutin);
	pCutin->setAnchorPoint(Point(0,0));
	this->addChild(pCutin,4);
	//カットインアニメーション
	pCutin->runAction(KSAnimation::rushCutin());
	//カットイン削除
//	pCutin->removeFromParentAndCleanup(true);

	this->scheduleOnce(schedule_selector(HelloWorld::firstRandomTarget), 1);

	this->scheduleOnce(schedule_selector(HelloWorld::rushEnd), rushTime);

}

/*
 * ラッシュターゲット表示位置抽選
 */
void HelloWorld::firstRandomTarget(float time){
	randomTarget();
}
/*
 * ラッシュターゲット表示位置抽選
 */
void HelloWorld::randomTarget(){
	//visibleSize.width * 0.5, visibleSize.height
	int x_point  = (int)origin.x + 50;
	int y_point  = (int)origin.y + 200;
	float randum_x = arc4random() % ((int)visibleSize.width  -  50 - x_point) + x_point;
	float randum_y = arc4random() % ((int)visibleSize.height - 300 - y_point) + y_point;

	Node* pRushTarget = Sprite::create("rush_target.png");
	pRushTarget->setPosition(Point(randum_x, randum_y));
	pRushTarget->setTag(tagRushTarget);
	this->addChild(pRushTarget,2);
}

/*
 * 自ラッシュ増減処理
 * flag: true = 攻撃 | false = 防御
 */
void HelloWorld::rushPoint(bool flag)
{
	if (!rushStack){
		NowRush = flag ? NowRush + 1: 0;

		CCLOG("startRush = %d,NowRush = %d", startRush, NowRush);
		if (startRush <= NowRush) {
//		    // ラッシュボタン設置
//		    MenuItemImage* pStartRush;
//		    pStartRush = MenuItemImage::create("rush_1.png",
//		                                         "rush_2.png",
//		                                         CC_CALLBACK_1(HelloWorld::menuStartRush, this));
//		    pStartRush->setPosition(Point(origin.x, visibleSize.height + rushButton_y));
//		    pStartRush->setAnchorPoint(Point(0,1));
//
//		    Menu* pMenu = Menu::create(pStartRush, NULL);
//		    pMenu->setPosition(Point::ZERO);
//		    pMenu->setTag(tagRushMenu);
//		    this->addChild(pMenu,10);

			//ボタン表示せずポイントが溜まった瞬間ラッシュを開始する
			menuStartRush();

		    rushStack = true;

		}
	}
}


/*
 * ラッシュ終了
 */
void HelloWorld::rushEnd(float time){
	//現在のターゲットを消す
	Node* pRushTarget	= getChildByTag(tagRushTarget);
	pRushTarget->removeFromParentAndCleanup(true);

	//ラッシュフラグオフ
	rushStack = false;
	rush_flag = false;

	startRush++;			//ラッシュ発生必要コンボ数増加

	//カットイン削除
	Node* pHpImg = this->getChildByTag(tagRushCutin);
	pHpImg->removeFromParentAndCleanup(true);


	//通常ゲーム再開
//	this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 0.1);
	this->schedule(schedule_selector(HelloWorld::showArrow), 2);

	if (NowEnemyHp < 1){
		arrowRefresh();
	} else {
		showArrow(0.0);
	}
}


/********************************************************************************************
 * シーン変更
 ********************************************************************************************/
//リトライボタンタップ時の処理
void HelloWorld::tapRetryButton(Object* pSender)
{
	//ゲームのシーンを新しく用意する
	Scene* gameScene = (Scene*)HelloWorld::create();
	Director::getInstance()->replaceScene(gameScene);
}

//メニューへの処理
void HelloWorld::tapReturnMenu(Object* pSender)
{
	// ボタン削除
	Node* pNext = this->getChildByTag(tagNextButton);
	pNext->removeFromParentAndCleanup(true);
	Node* pMenu = this->getChildByTag(tagMenutButton);
	pMenu->removeFromParentAndCleanup(true);

	Scene* gameScene = (Scene*)TitleScene::create();
	Director::getInstance()->replaceScene(gameScene);
}
//次のレベルへの処理
void HelloWorld::tapNextLv(Object* pSender)
{

	// ボタン削除
	Node* pNext = this->getChildByTag(tagNextButton);
	pNext->removeFromParentAndCleanup(true);
	Node* pMenu = this->getChildByTag(tagMenutButton);
	pMenu->removeFromParentAndCleanup(true);


	setup();

}
