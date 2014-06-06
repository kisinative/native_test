#include "HelloWorldScene.h"
#include "KSAnimation.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "WinnerScene.h"
//#include "Define.h"
#include <unistd.h>
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;
//String arrowArray[] = {"右", "左", "上", "下"};
String arrowArray[] = {"0", "1", "2", "3","02","03","12","13","20","21","30","31"};

#define WINSIZE CCDirector::sharedDirector()->getWinSize()
#define TEXT_SCALE WINSIZE.width/1080

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define MISAKI_FONT "fonts/mini-wakuwaku-maru.ttf"
#else
#define MISAKI_FONT "mini-wakuwaku-maru"
#endif

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer,1);
//    CCLOG("X = %s", Define::key_enemyLv);
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
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//
//	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));

//    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Point::ZERO);
//    this->addChild(menu, 1);


	//効果音を読み込む
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/combat_enemy.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/combat_normal.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/combat_just.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/combat_rush.mp3");

    //プレイヤーの各種レベル取得
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	playerStrongLv 		= userDefault->getIntegerForKey(key_playerStrongLv, 1);
	playerPowerLv		= userDefault->getIntegerForKey(key_playerPowerLv, 1);
	playerSpeedLv		= userDefault->getIntegerForKey(key_playerSpeedLv, 1);
	playerTechniqueLv	= userDefault->getIntegerForKey(key_playerTechniqueLv, 1);

    //初期化
    NowHp = MaxHp + playerStrongLv * lvStrong;
    NowMaxHp = NowHp;
    targetGesture = "99";









//    enemyStrongLv = 1;
//    enemypowerLv = 1;
//    enemySpeedLv = 1;
//    enemyTechniqueLv = 1;
    nowStage = 1;
    nowGesture = "";

    // 背景を生成
    int bg_num = arc4random() % 3;
    Sprite* pBG = Sprite::create(String::createWithFormat("background_%d.png", bg_num)->getCString());
    pBG->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.5));
    pBG->setTag(tagBg);
    this->addChild(pBG);


//    Sprite* pBG = Sprite::create("testbackimg.png");
//    pBG->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.5));
//    this->addChild(pBG);
//    Sprite* pBG = Sprite::create("masu.png");
//    pBG->setPosition(Point(origin.x, origin.y));
//    this->addChild(pBG);
    CCLOG("visible = %f,visible = %f",origin.x,origin.y);
    CCLOG("visibleSize.width = %f, visibleSize.height = %f",visibleSize.width, visibleSize.height);


//    CCLOG("visible = %f,visible = %f",visibleSize.width,visibleSize.height);
//	//矢印ラベルを生成する
//    LabelTTF* arrowLabel = LabelTTF::create("れでぃ", "Arial", 90.0*TEXT_SCALE);
//	arrowLabel->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//	arrowLabel->setTag(tagArrowLabel);
//	this->addChild(arrowLabel,2);
//    CCLOG("aaaaaaa = %f,bbbbbbb = %f",origin.x,origin.y);

	Node* pTarget = Sprite::create("target_0.png");
//	pTarget->setPosition(ccp(visibleSize.width * 0.05, visibleSize.height * 0.80));
	pTarget->setPosition(Point(pTarget->getContentSize().width+50.0, visibleSize.height * 0.80));
	pTarget->setTag(tagTargetImg);
	this->addChild(pTarget,2);

	Node* pTarget1 = Sprite::create("target_1.png");
	pTarget1->setPosition(Point(pTarget->getContentSize().width+50.0, visibleSize.height * 0.80));
	pTarget1->setTag(tagTargetImgSub1);
	this->addChild(pTarget1,1);
	pTarget1 = Sprite::create("target_1.png");
	pTarget1->setPosition(Point(pTarget->getContentSize().width+50.0, visibleSize.height * 0.80));
//	pTarget1->setFlipX(true);
	pTarget1->setRotation(180);
	pTarget1->setTag(tagTargetImgSub2);
	this->addChild(pTarget1,1);
//			Node* pTarget2 = Sprite::create("target.png");
//			pTarget2->setPosition(Point(pTarget->getContentSize().width+50.0 + 5.0, visibleSize.height * 0.75));
//			pTarget2->setTag(201);
//			this->addChild(pTarget2,2);
//			Node* pTarget3 = Sprite::create("target.png");
//			pTarget3->setPosition(Point(pTarget->getContentSize().width+50.0 - 50.0, visibleSize.height * 0.70));
//			pTarget3->setTag(202);
//			this->addChild(pTarget3,2);
//			Node* pTarget4 = Sprite::create("target.png");
//			pTarget4->setPosition(Point(pTarget->getContentSize().width+50.0 + 50.0, visibleSize.height * 0.70));
//			pTarget4->setTag(203);
//			this->addChild(pTarget4,2);

	//自他HP画像
	Node* pHp = Sprite::create("gauge_cover.png");
	pHp->setPosition(Point(origin.x + 80, origin.y + 950));
	pHp->setAnchorPoint(Point(0,1));
	pHp->setTag(tagHpImg);
	this->addChild(pHp,3);
	Node* pHpEnemy = Sprite::create("gauge_cover.png");
	pHpEnemy->setPosition(Point(origin.x + 115, origin.y + 890));
	pHpEnemy->setAnchorPoint(Point(0,1));
	pHpEnemy->setTag(tagEnemyHpImg);
	this->addChild(pHpEnemy,3);

    // 描画用ノードの作成
    CCDrawNode* draw = CCDrawNode::create();
    draw->setPosition(ccp(origin.x + 80, origin.y + 950));
    draw->setAnchorPoint(Point(0,1));
//    draw->setPosition(ccp(0, 0));
//    draw->setAnchorPoint(Point(0,0));
    draw->setTag(tagHpImg+1);
    this->addChild(draw,2);
    static Point points[] = {ccp(0, 0),ccp(0, -50),ccp(350, -50),ccp(350, 0)};
    draw->drawPolygon(points,                  // 頂点の座標のデータ
                      4,                       // 角数
                      ccc4FFromccc3B(ccc3(0, 0, 255)), // 図形の色
                      1,                       // 枠線の太さ
                      ccc4FFromccc3B(ccBLACK)  // 枠線の色
                      );
    draw = CCDrawNode::create();
//    draw->setPosition(ccp(origin.x + 115, origin.y + 890));
    draw->setPosition(ccp(origin.x + 465, origin.y + 890));
    draw->setAnchorPoint(Point(1,1));
//    draw->setPosition(ccp(0, 0));
//    draw->setAnchorPoint(Point(0,0));
    draw->setTag(tagEnemyHpImg+1);
    this->addChild(draw,2);
    static Point points2[] = {ccp(0, 0),ccp(0, -50),ccp(-350, -50),ccp(-350, 0)};
    draw->drawPolygon(points2,                  // 頂点の座標のデータ
                      4,                       // 角数
                      ccc4FFromccc3B(ccc3(255, 0, 0)), // 図形の色
                      1,                       // 枠線の太さ
                      ccc4FFromccc3B(ccBLACK)  // 枠線の色
                      );





	//自サムネイル
	Node* pThumbnail = Sprite::create("mycat.png");
	pThumbnail->setPosition(Point(origin.x, visibleSize.height-10));
	pThumbnail->setAnchorPoint(Point(0,1));
	pThumbnail->setTag(tagThumbnailImg);
	this->addChild(pThumbnail,2);

	//敵初期ステータス設定
    setup();

    return true;
}

void HelloWorld::setup()
{

	//敵レベル取得
	UserDefault* userDefault = UserDefault::sharedUserDefault();
//	enemyLv = userDefault->getIntegerForKey(key_enemyLv, 1);
	enemyLv = userDefault->getIntegerForKey(key_playEnemyLv, 1);
	enemyStrongLv		= enemyLv;
	enemypowerLv		= enemyLv;
	enemySpeedLv		= enemyLv;
	enemyTechniqueLv	= enemyLv;
	enemyType = arc4random() % 9;
//	enemyType = 0;

	//低レベルの時はボス猫は出ない
	if (enemyLv < 6 && enemyType == 0){
		enemyType = 3;
	}

	switch (enemyType){
		case 0:			//ボス
			enemyStrongLv = enemyStrongLv + 4;
			enemypowerLv = enemypowerLv + 6;
			enemySpeedLv = enemySpeedLv + 4;
			enemyTechniqueLv = enemyTechniqueLv + 6;
			break;
		case 1:			//サビ
		case 2:
			enemyStrongLv = enemyStrongLv + 1;
			enemypowerLv = enemypowerLv + 2;
			enemySpeedLv = enemySpeedLv + 1;
			enemyTechniqueLv = enemyTechniqueLv + 2;
			enemyType = 1;
			break;
		case 3:			//三毛
		case 4:
			enemyStrongLv = enemyStrongLv + 2;
			enemypowerLv = enemypowerLv + 4;
			enemyType = 2;
			break;
		case 5:			//クロ
		case 6:
			enemySpeedLv = enemySpeedLv + 4;
			enemyTechniqueLv = enemyTechniqueLv + 2;
			enemyType = 3;
			break;
		case 7:			//シャム
		case 8:
			enemySpeedLv = enemySpeedLv + 2;
			enemyTechniqueLv = enemyTechniqueLv + 4;
			enemyType = 4;
			break;
	}
	catChenge(0);
	enemyCatChenge(0);

	Node* pEnemyImg = this->getChildByTag(tagEnemyImg);
	pEnemyImg->runAction(KSAnimation::enemyJump(enemyType));

	//敵サムネイル
	Node* pEnemyThumbnail = Sprite::create(String::createWithFormat("enemy_%d.png", enemyType)->getCString());
	pEnemyThumbnail->setPosition(Point(visibleSize.width, origin.y + 890));
	pEnemyThumbnail->setAnchorPoint(Point(1,1));
	pEnemyThumbnail->setTag(tagEnemyThumbnail);
	this->addChild(pEnemyThumbnail,2);

//    //HP表示
//	createLabel(String::createWithFormat("残りHP:%d", NowHp)->getCString(),
//				50.0*TEXT_SCALE,
//				visibleSize.width * 0.15,
//				visibleSize.height * 0.95,
//				tagHp);


	//敵HP表示
	NowEnemyHp = defaultEnemyStrong + (6 * enemyStrongLv);
	MaxEnemyHp = NowEnemyHp;
//	createLabel(String::createWithFormat("敵残りHP:%d", NowEnemyHp)->getCString(),
//				50.0*TEXT_SCALE,
//				visibleSize.width * 0.8,
//				visibleSize.height * 0.95,
//				tagEnemyHp);
//
//	//敵LV表示
//	createLabel(String::createWithFormat("タフネスLV:%d", enemyStrongLv)->getCString(),
//				50.0*TEXT_SCALE,
//				visibleSize.width * 0.8,
//				visibleSize.height * 0.90,
//				tagEnemyStrong);
//	createLabel(String::createWithFormat("パワーLV:%d", enemypowerLv)->getCString(),
//				50.0*TEXT_SCALE,
//				visibleSize.width * 0.8,
//				visibleSize.height * 0.85,
//				tagEnemyPower);
//	createLabel(String::createWithFormat("スピードLV:%d", enemySpeedLv)->getCString(),
//				50.0*TEXT_SCALE,
//				visibleSize.width * 0.8,
//				visibleSize.height * 0.80,
//				tagEnemySpeed);
//	createLabel(String::createWithFormat("テクニックLV:%d", enemyTechniqueLv)->getCString(),
//				50.0*TEXT_SCALE,
//				visibleSize.width * 0.8,
//				visibleSize.height * 0.75,
//				tagEnemyTechnique);

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

	//サブ攻撃ゲージ変動
	Node* pTarget = this->getChildByTag(tagTargetImgSub1);
	subTargetPoint =baseSubPoint + playerTechniqueLv - enemyTechniqueLv;
	if (subTargetPoint > 70) {
		subTargetPoint = 70;
	} else if (subTargetPoint < 1) {
		subTargetPoint = 1;
	}
	pTarget->runAction(MoveBy::create(0.7, ccp( 0 - subTargetPoint, 0)));
	pTarget = this->getChildByTag(tagTargetImgSub2);
	pTarget->runAction(MoveBy::create(0.7, ccp( subTargetPoint, 0)));


	//LV相殺
	enemySpeedLv	   -= playerSpeedLv / 2;
	enemyTechniqueLv   -= playerTechniqueLv / 2;
	enemySpeedLv		= enemySpeedLv		> 1 ? enemySpeedLv : 1;
	enemyTechniqueLv	= enemyTechniqueLv	> 1 ? enemyTechniqueLv : 1;

//	Node* pHpImg = this->getChildByTag(tagEnemyHpImg);
//	pHpImg->setScaleX(1.0);
//	pHpImg->runAction(KSAnimation::hpAction(1.0));

//    this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 2);
	if (enemyType == 0) {
		//カットイン作成
		Node* pCutin = Sprite::create("boss_cutin.png");
		pCutin->setPosition(Point(visibleSize.width, visibleSize.height * 0.5));
		pCutin->setTag(tagRushCutin);
		pCutin->setAnchorPoint(Point(0,0));
		this->addChild(pCutin,4);
		//カットインアニメーション
//		pCutin->runAction(KSAnimation::rushCutin());
		Sequence* callAction = Sequence::create(KSAnimation::rushCutin(), RemoveSelf::create(true), NULL);
		pCutin->runAction(callAction);

		this->scheduleOnce(schedule_selector(HelloWorld::bossSetup), 0.5);
	} else {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("mp3/harunopayapaya.mp3", true);

		this->schedule(schedule_selector(HelloWorld::showArrow), 2);
	}

}

void HelloWorld::bossSetup(float time)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.4);
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/boss_cutin.mp3");

	this->scheduleOnce(schedule_selector(HelloWorld::bossSetup1), 1.2);
    this->schedule(schedule_selector(HelloWorld::showArrow), 1.4);
}
void HelloWorld::bossSetup1(float time)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("mp3/boss.mp3", true);
}


void HelloWorld::createLabel(std::string labelString, float labelSize, float labelWidth, float labelHeight, int labelTag)
{
	LabelTTF* wkLabel = (LabelTTF*)this->getChildByTag(labelTag);
	if (wkLabel)
	{
		wkLabel->setColor(ccc3(0, 0, 0));
		wkLabel->setString(labelString);
	} else {
		wkLabel = LabelTTF::create(labelString, MISAKI_FONT, labelSize);
		wkLabel->setPosition(Point(labelWidth, labelHeight));
		wkLabel->setColor(ccc3(0, 0, 0));
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

//	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(tagArrowLabel);
//	arrowLabel->setString("");

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
	this->addChild(pArrow,9);
	Node* pArrow1 = Sprite::create(String::createWithFormat("%s.png",arrowArray[randum].getCString())->getCString());
	Size bgSize = pArrow->getContentSize();
	pArrow1->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.5));
	pArrow->addChild(pArrow1,10);

	CallFunc* callFunction = CallFunc::create(this, callfunc_selector(HelloWorld::timeOver));
//    Sequence* callAction = Sequence::create(KSAnimation::vibrationAnimation((float)defaultEnemySpeed - enemySpeedLv / 10.0), callFunction, RemoveSelf::create(true), NULL);
//
//	pArrow->runAction(callAction);




	switch (enemyType) {
	case 0:			//ボス
		randum = arc4random() % 5 + 3;
		break;
	case 1:			//サビ
		randum = arc4random() % 6;
		break;
	case 2:			//三毛
		randum = arc4random() % 5;
		break;
	case 3:			//クロ
		randum = arc4random() % 6;
		break;
	case 4:		//シャム
		randum = arc4random() % 5 + 2;
		break;
	}

	Spawn* spawn;
	float base_time = (float)defaultEnemySpeed - enemySpeedLv / 10.0;
	auto base_move = Sequence::create(KSAnimation::vibrationAnimation(base_time), callFunction, RemoveSelf::create(true), NULL);
	switch (randum){
		case 0:
			//通常
			pArrow->runAction(base_move);
			break;
		case 1:
			//拡大
			spawn = Spawn::createWithTwoActions(
					base_move,
					Sequence::create(EaseInOut::create(ScaleTo::create(1.0f, 1.5f), base_time / 4), EaseInOut::create(ScaleTo::create(1.5f, 1.0f), base_time / 4), NULL)
			);
			pArrow->runAction(spawn);
			break;
		case 2:
			//縮小
			spawn = Spawn::createWithTwoActions(
					base_move,
					Sequence::create(EaseInOut::create(ScaleTo::create(1.0f, 0.1f), base_time / 4), EaseInOut::create(ScaleTo::create(0.1f, 1.0f), base_time / 2), DelayTime::create(base_time / 4), NULL)
			);
			pArrow->runAction(spawn);
			break;
		case 3:
			//一旦ゆっくりになり再進行
			spawn = Spawn::createWithTwoActions(
					base_move,
					Sequence::create(MoveBy::create(base_time / 3, ccp( -100, 0 )), MoveBy::create(base_time / 4, ccp( 100, 0 )), NULL)
			);
			pArrow->runAction(spawn);
			break;
		case 4:
			//上下に移動
			spawn = Spawn::createWithTwoActions(
					base_move,
					Repeat::create(Sequence::create(MoveBy::create(base_time / 8, ccp( 0, -50 )), MoveBy::create(base_time / 8, ccp( 0, 50 )), NULL), 3)
			);
			pArrow->runAction(spawn);
			break;
		case 5:
			//点滅
			spawn = Spawn::createWithTwoActions(
					base_move,
					Sequence::create(Blink::create(base_time,6), NULL)
			);
			pArrow->runAction(spawn);
			break;
		case 6:
			//急発進＆バックして再進行
			pArrow->runAction(Sequence::create(EaseBackOut::create(MoveTo::create(base_time/3*2, ccp(300.0, visibleSize.height * 0.80))), MoveTo::create(base_time/3, ccp(0.0, visibleSize.height * 0.80)), callFunction, RemoveSelf::create(true), NULL));
			break;
		case 7:
			//ゴムゴムは連続で出さない（２回インターバルを置く
			if (actionNum1 == 7) {
				//上下に移動
				spawn = Spawn::createWithTwoActions(
						base_move,
						Repeat::create(Sequence::create(MoveBy::create(base_time / 8, ccp( 0, -50 )), MoveBy::create(base_time / 8, ccp( 0, 50 )), NULL), 3)
				);
				pArrow->runAction(spawn);
			} else if (actionNum2 == 7) {
				//一旦ゆっくりになり再進行
				spawn = Spawn::createWithTwoActions(
						base_move,
						Sequence::create(MoveBy::create(base_time / 3, ccp( -100, 0 )), MoveBy::create(base_time / 4, ccp( 100, 0 )), NULL)
				);
				pArrow->runAction(spawn);
			} else {
				//ゴムゴム
				pArrow->runAction(Sequence::create(EaseElasticOut::create(MoveTo::create(base_time/3*2, ccp(300.0, visibleSize.height * 0.80))), MoveTo::create(base_time/3, ccp(0.0, visibleSize.height * 0.80)), callFunction, RemoveSelf::create(true), NULL));
			}
			break;
	}
	actionNum2 = actionNum1;
	actionNum1 = randum;

//	Spawn* spawn = Spawn::createWithTwoActions(
//			Sequence::create(KSAnimation::vibrationAnimation((float)defaultEnemySpeed - enemySpeedLv / 10.0), callFunction, RemoveSelf::create(true), NULL),
//			KSAnimation::move1((float)defaultEnemySpeed - enemySpeedLv / 10.0)
//	);
//	pArrow->runAction(spawn);




















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
			if (enemyType == 0) {
				this->schedule(schedule_selector(HelloWorld::showArrow), 1.4);
			} else {
				this->schedule(schedule_selector(HelloWorld::showArrow), 2);
			}
		}
	}


//	this->scheduleOnce(schedule_selector(HelloWorld::timeOver), (float)defaultEnemySpeed - enemySpeedLv / 10.0);

}

/*
 * 次ステージ
 */
void HelloWorld::nextStage(float time)
{


	// 経験値追加
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int playerExp = userDefault->getIntegerForKey(key_playerExp, 0);
	int wk_enemyLv = nowStage+playerExp--;
	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(tagArrowLabel);
	arrowLabel->setString(String::createWithFormat("ステージクリア！！\n%dポイント獲得 %d　→　%d",wk_enemyLv, playerExp, wk_enemyLv+playerExp)->getCString());
//	arrowLabel->setString("ステージクリア！！ ");
	userDefault->setIntegerForKey(key_playerExp, wk_enemyLv+playerExp);

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
//	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
//	arrowLabel->setString("timeOut");
	createLabel("フリックしてね",
				40,
				visibleSize.width * 0.75,
				origin.y + 700,
				tagComboCount);

	//敵攻撃エフェクト
	enemyAtk(true);


	rushPoint(false);		//ラッシュポイント低下


	if (moveAtkDef[0] == 1)
	{
		//HP更新
		meDamage(true);

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
	} else {
		//HP更新
		meDamage(false);
	}

    moveArrow.erase(moveArrow.begin());
    moveAtkDef.erase(moveAtkDef.begin());

	if (NowHp < 1){
//		this->unschedule(schedule_selector(HelloWorld::showArrow));
//		arrowLabel->setString("GameOver");
//        makeRetryButton();

		this->scheduleOnce(schedule_selector(HelloWorld::moveGameOver), 0.3);


//	} else {
//		this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 1);
	}

	//コンボ表記削除
	noMissFlag = false;
	conboCount = 0;
//	Node* pConboTarget	= getChildByTag(tagComboCount);
//	if (pConboTarget){
//		pConboTarget->removeFromParentAndCleanup(true);
//	}


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
		if ((fabs(deltaX) <= 20.0 && fabs(deltaY) <= 20.0) || rushEndAtk_flag) {
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
//				if ((targetPoint.x - 50.0 <= arrowPoint.x) && (targetPoint.x + 50.0 >= arrowPoint.x))
				if ((targetPoint.x - subTargetPoint <= arrowPoint.x) && (targetPoint.x + subTargetPoint >= arrowPoint.x))
				{
					wkGesture = true;
//					if ((targetPoint.x - 5.0 <= arrowPoint.x) && (targetPoint.x + 5.0 >= arrowPoint.x))
					if ((targetPoint.x - subTargetPoint/10 <= arrowPoint.x) && (targetPoint.x + subTargetPoint/10 >= arrowPoint.x))
					{
						flag = 1;
					}
				} else {
					if (targetPoint.x - subTargetPoint <= arrowPoint.x) {
						createLabel("はやいよー",
									40,
									visibleSize.width * 0.75,
									origin.y + 700,
									tagComboCount);
					} else {
						createLabel("おそいよー",
									40,
									visibleSize.width * 0.75,
									origin.y + 700,
									tagComboCount);
					}
				}
			} else {
				createLabel("フリックミス",
							40,
							visibleSize.width * 0.75,
							origin.y + 700,
							tagComboCount);
//							tagMessage);
			}

			moveArrow.erase(moveArrow.begin());
			moveAtkDef.erase(moveAtkDef.begin());

			if (wkGesture){
				//コンボ数
				if (++conboCount > 1) {
					createLabel(String::createWithFormat("%dこんぼ", conboCount)->getCString(),
								40,
								visibleSize.width * 0.75,
								origin.y + 700,
								tagComboCount);

					Node* pHpImg = this->getChildByTag(tagComboCount);
					pHpImg->runAction(KSAnimation::hpAction());

				} else {
					createLabel(" ",
								40,
								visibleSize.width * 0.75,
								origin.y + 700,
								tagComboCount);
				}
				if (conboCount > maxConboCount) {
					maxConboCount = conboCount;
				}


				if (wkAtkDef){
					attack(flag);
				} else {
					defense(flag);
				}
				NowEnemyRush += 1;
			} else {
				//敵攻撃エフェクト
				enemyAtk(true);
				miss(wkAtkDef);
				NowEnemyRush += 5;

				//コンボ表記削除
				noMissFlag = false;
				conboCount = 0;
//				Node* pConboTarget	= getChildByTag(tagComboCount);
//				if (pConboTarget){
//					pConboTarget->removeFromParentAndCleanup(true);
//				}
			}

			if (NowEnemyRush >= startEnemyRush && rushCount == 0 && NowEnemyHp > 0)
			{
				rushCount = 5;
				this->unschedule(schedule_selector(HelloWorld::showArrow));
				if (enemyType == 0) {
					this->schedule(schedule_selector(HelloWorld::showArrow), 0.8);
				} else {
					this->schedule(schedule_selector(HelloWorld::showArrow), 1);
				}
			} else {
				if (!(rushCount >  5 && wkGesture)){
					rushPoint(wkGesture);
				}
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
		if (rush_crisis){
			NowEnemyHp -= crisisRushAtk;
		} else {
			NowEnemyHp -= rushAtk;
		}

		if (NowEnemyHp < 0) {
			NowEnemyHp = 0;
		}

//		Node* pHpImg = this->getChildByTag(tagEnemyHpImg);
//		float wk_a = (float)NowEnemyHp / MaxEnemyHp;
//		pHpImg->runAction(KSAnimation::hpAction());
//		pHpImg = this->getChildByTag(tagEnemyHpImg+1);
//		pHpImg->runAction(KSAnimation::hpAction());
//		pHpImg->setScaleX(wk_a);
		atk_num_flag = 2;
		this->scheduleOnce(schedule_selector(HelloWorld::enemyLifeAction), 0.1);

		//HP更新
//		LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagEnemyHp);
//		hpLabel->setString(String::createWithFormat("敵残りHP:%d", NowEnemyHp)->getCString());
		if (NowEnemyHp < 1){
			this->unschedule(schedule_selector(HelloWorld::rushEnd));
//			this->scheduleOnce(schedule_selector(HelloWorld::rushEnd), 0.0f);

			arrowRefresh();					// 攻防の矢印をリフレッシュ
			enemyDef(false);

			//現在のターゲットを消す
			Node* pRushTarget	= getChildByTag(tagRushTarget);
			pRushTarget->removeFromParentAndCleanup(true);

//			//HP回復
//			NowHp += 20;
//			if (MaxHp < NowHp)
//			{
//				NowHp = MaxHp + playerStrongLv * lvStrong;
//			}
//			Node* pHpImg = this->getChildByTag(tagHpImg);
//			float wk_a = (float)NowHp / (MaxHp + playerStrongLv * lvStrong);
//			pHpImg->runAction(KSAnimation::hpAction());
//			pHpImg = this->getChildByTag(tagHpImg+1);
//			pHpImg->setScaleX(wk_a);

//			this->scheduleOnce(schedule_selector(HelloWorld::nextStage), 0.1);
//			moveWinner();
		} else {
			enemyRushDef();
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

//	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
	if (flag == 0)
	{
//		arrowLabel->setString("ぬこぱーんち");
//		arrowLabel->setColor(ccc3(0, 0, 0));
		atk_num_flag = 0;
		NowEnemyHp -= normalAtk + playerPowerLv;
	} else {
//		arrowLabel->setString("ジャスト！！");
//		arrowLabel->setColor(ccc3(0, 0, 0));
		atk_num_flag = 1;

		CCLOG("playerPowerLv = %d",playerPowerLv);
		int aaa = (justAtk + (playerPowerLv / 2)) + playerPowerLv;
		CCLOG("aaaaaaaaaaaaa = %d",aaa);
		aaa = (justAtk + (1 / 2)) + 1;
		CCLOG("bbbbbbbbbbbbb = %d",aaa);
		aaa = (justAtk + (playerPowerLv / 4)) + playerPowerLv;
		CCLOG("ccccccccccccc = %d",aaa);

		NowEnemyHp -= (justAtk + (playerPowerLv / 2)) + playerPowerLv;
	}
	if (NowEnemyHp < 0) {
		NowEnemyHp = 0;
	}

//	Node* pHpImg = this->getChildByTag(tagEnemyHpImg);
//	float wk_a = (float)NowEnemyHp / MaxEnemyHp;
//	pHpImg->runAction(KSAnimation::hpAction());
//	pHpImg = this->getChildByTag(tagEnemyHpImg+1);
//	pHpImg->runAction(KSAnimation::hpAction());
//	pHpImg->setScaleX(wk_a);
	this->scheduleOnce(schedule_selector(HelloWorld::enemyLifeAction), 0.1);

	//HP更新
//	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagEnemyHp);
//	hpLabel->setString(String::createWithFormat("敵残りHP:%d", NowEnemyHp)->getCString());
	if (NowEnemyHp < 1){
        arrowRefresh();
		enemyDef(false);
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

//		//相手レベルUP
//		UserDefault* userDefault = UserDefault::sharedUserDefault();
//		enemyLv = userDefault->getIntegerForKey(key_enemyLv, 1) + 1;
//		userDefault->setIntegerForKey(key_enemyLv, enemyLv);

//	    //HP回復
//	    NowHp += 20;
//	    if (MaxHp < NowHp)
//	    {
//	    	NowHp = MaxHp;
//	    }
//		Node* pHpImg = this->getChildByTag(tagHpImg);
//		float wk_a = (float)NowHp / (MaxHp + playerStrongLv * lvStrong);
//		pHpImg->runAction(KSAnimation::hpAction());
//		pHpImg = this->getChildByTag(tagHpImg+1);
//		pHpImg->setScaleX(wk_a);

//		this->scheduleOnce(schedule_selector(HelloWorld::nextStage), 0.1);
//		moveWinner();
	} else {
		enemyDef(true);

//		this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 0.2);
	}
}

/*
 *	攻撃成功
 */
void HelloWorld::defense(int flag)
{

//	rushPoint(true);	//ラッシュポイント増加

//	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
//	arrowLabel->setString("ガード");

	//敵攻撃エフェクト
	enemyAtk(false);


}

/*
 *	攻撃失敗
 */
void HelloWorld::miss(bool flag)
{

//	rushPoint(false);	//ラッシュポイント初期化

//	LabelTTF* arrowLabel = (LabelTTF*)this->getChildByTag(100);
//	arrowLabel->setString("ミス！");

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
	meDamage(flag);

	if (NowHp < 1){
//		this->unschedule(schedule_selector(HelloWorld::showArrow));
//		arrowLabel->setString("GameOver");
//		makeRetryButton();

		this->scheduleOnce(schedule_selector(HelloWorld::moveGameOver), 0.3);




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
void HelloWorld::meDamage(bool flag)
{
//	LabelTTF* hpLabel = (LabelTTF*)this->getChildByTag(tagHp);

	if (flag){
		NowHp = NowHp - (defaultEnemyPower + enemypowerLv);
	} else {
		NowHp = NowHp - (defaultEnemyPower + 1.5 * enemypowerLv);
	}
	if (NowHp < 0){
		NowHp = 0;
	}
//	hpLabel->setString(String::createWithFormat("残りHP:%d", NowHp)->getCString());

	this->scheduleOnce(schedule_selector(HelloWorld::meLifeAction), 0.3);
}
void HelloWorld::meLifeAction(float time){
	Node* pHpImg = this->getChildByTag(tagHpImg);
	float wk_a = (float)NowHp / (MaxHp + playerStrongLv * lvStrong);
	pHpImg->runAction(KSAnimation::hpAction());
	pHpImg = this->getChildByTag(tagHpImg+1);
	pHpImg->runAction(KSAnimation::hpAction());
	pHpImg->setScaleX(wk_a);
	pHpImg = this->getChildByTag(tagBg);
	pHpImg->runAction(KSAnimation::bgAction());

	//効果音を鳴らす
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.4);
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/combat_enemy.mp3");

}
void HelloWorld::enemyLifeAction(float time){
	Node* pHpImg = this->getChildByTag(tagEnemyHpImg);
	float wk_a = (float)NowEnemyHp / MaxEnemyHp;
	pHpImg->runAction(KSAnimation::hpAction());
	pHpImg = this->getChildByTag(tagEnemyHpImg+1);
	pHpImg->runAction(KSAnimation::hpAction());
	pHpImg->setScaleX(wk_a);

	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.4);
	if (atk_num_flag == 0){
		SimpleAudioEngine::sharedEngine()->playEffect("mp3/combat_normal.mp3");
	} else if (atk_num_flag == 1){
		SimpleAudioEngine::sharedEngine()->playEffect("mp3/combat_just.mp3");
	} else {
		SimpleAudioEngine::sharedEngine()->playEffect("mp3/combat_rush.mp3");
	}
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
	arrowRefresh();					// 攻防の矢印をリフレッシュ
	rush_flag		= true;			// ラッシュフラグをtrueにする
	rushAtk_flag	= false;		// ラッシュ初回攻撃
	NowRush			= 0;			// ラッシュポイントを初期化

	if (NowHp <= NowMaxHp / 3) {
		rush_crisis = true;
	} else {
		rush_crisis = false;
	}

//	//ラッシュ開始ボタン削除
//	Node* pRushMenu   = this->getChildByTag(tagRushMenu);
//	pRushMenu->removeFromParentAndCleanup(true);

	//カットイン作成
	Node* pCutin;
	if (rush_crisis){
		pCutin = Sprite::create("rush_cutin_1.png");
	} else {
		pCutin = Sprite::create("rush_cutin_0.png");
	}
	pCutin->setPosition(Point(visibleSize.width, visibleSize.height * 0.45));
	pCutin->setTag(tagRushCutin);
	pCutin->setAnchorPoint(Point(0,0));
	this->addChild(pCutin,4);
	//カットインアニメーション
	pCutin->runAction(KSAnimation::rushCutin());
	//カットイン削除
//	pCutin->removeFromParentAndCleanup(true);

	rushEndAtk_flag = true;

	this->scheduleOnce(schedule_selector(HelloWorld::firstRandomTarget), 1.5);

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

	Node* pRushTarget;
	if (rush_crisis){
		pRushTarget = Sprite::create("rush_target_1.png");
	} else {
		pRushTarget = Sprite::create("rush_target_0.png");
	}
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

	//敵のステップ再開
	Node* pEnemyImg = this->getChildByTag(tagEnemyImg);
	pEnemyImg->runAction(KSAnimation::enemyJump(enemyType));

	//通常ゲーム再開
//	this->scheduleOnce(schedule_selector(HelloWorld::showArrow), 0.1);
	if (enemyType == 0) {
		this->schedule(schedule_selector(HelloWorld::showArrow), 1.4);
	} else {
		this->schedule(schedule_selector(HelloWorld::showArrow), 2);
	}

	this->scheduleOnce(schedule_selector(HelloWorld::rushEndFlag), 0.3);

	if (NowEnemyHp < 1){
		arrowRefresh();
	} else {
		showArrow(0.0);
	}
}
void HelloWorld::rushEndFlag(float time){
	rushEndAtk_flag = false;
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

/*
 * ゲームオーバーへ遷移
 */
void HelloWorld::moveGameOver(float time)
{

	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	//ゲームのシーンを新しく用意する
	Scene* gameScene = (Scene*)GameOver::create();
//	TransitionSlideInL* tran = TransitionSlideInL::create(1, gameScene);
//    TransitionSplitCols* tran = TransitionSplitCols::create(0.5, gameScene);
	TransitionMoveInT* tran = TransitionMoveInT::create(0.5, gameScene);
	Director::getInstance()->replaceScene(tran);

}

/*
 * 勝利画面へ遷移
 */
void HelloWorld::moveWinner(float time)
{

	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);


	UserDefault* userDefault = UserDefault::sharedUserDefault();
	userDefault->setIntegerForKey(key_maxComboCount, maxConboCount);
	userDefault->setBoolForKey(key_noMissFlag, noMissFlag);
	if (enemyType == 0){
		userDefault->setBoolForKey(key_bossFlag, true);
	} else {
		userDefault->setBoolForKey(key_bossFlag, false);
	}

	//ゲームのシーンを新しく用意する
	Scene* gameScene = (Scene*)Winner::create();
	TransitionMoveInT* tran = TransitionMoveInT::create(0.5, gameScene);
	Director::getInstance()->replaceScene(tran);

}



/*
 * 猫戦闘画像変更
 */
void HelloWorld::catChenge(int flag)
{

	String img_name = "";
	switch (flag){
		case 0:
			img_name = "myCatCombat.png";
			break;
		case 1:
			img_name = "myCatAtk.png";
			break;
		case 2:
			img_name = "myCatDown.png";
			break;
		case 3:
			img_name = "win_cat.png";
			break;
	}

	Node* pEnemyImg = this->getChildByTag(tagCatImg);
	if (pEnemyImg)
	{
		Animation *animation = Animation::create();
		animation->addSpriteFrameWithFileName(img_name.getCString());
		animation->setDelayPerUnit( 0.1f );
		animation->setRestoreOriginalFrame(false);
		pEnemyImg->runAction(Animate::create(animation));
	} else {
		Node* pTarget = Sprite::create(img_name.getCString());
		pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + pTarget->getContentSize().height/2));
		pTarget->setTag(tagCatImg);
		this->addChild(pTarget,2);
	}

}

void HelloWorld::enemyCatChenge(int flag)
{

	String img_name = "";
	switch (flag){
		case 0:
//			String* img_name = "cat_";String::createWithFormat(
			img_name = String::createWithFormat("cat_%d.png",enemyType)->getCString();
			break;
		case 1:
//			String* img_name = "catAtk_";
			img_name = String::createWithFormat("catAtk_%d.png",enemyType)->getCString();
			break;
		case 2:
//			String* img_name = "catDown_";
			img_name = String::createWithFormat("catDown_%d.png",enemyType)->getCString();
			break;
	}

	Node* pEnemyImg = this->getChildByTag(tagEnemyImg);
	if (pEnemyImg)
	{
		Animation *animation = Animation::create();
		animation->addSpriteFrameWithFileName(img_name.getCString());
		animation->setDelayPerUnit( 0.1f );
		animation->setRestoreOriginalFrame(false);
//		RepeatForever *action = RepeatForever::create( Animate::create(animation) );
		pEnemyImg->runAction(Animate::create(animation));
	} else {
		Node* pTarget = Sprite::create(img_name.getCString());
//		pTarget->setPosition(Point(pTarget->getContentSize().width * 0.5, origin.y + pTarget->getContentSize().height/2));
		pTarget->setPosition(Point(visibleSize.width * 0.5, origin.y + 400));
		pTarget->setTag(tagEnemyImg);
		this->addChild(pTarget,1);
	}

}

/*
 * 敵攻撃　flag：true 攻撃命中　False 攻撃回避
 */
void HelloWorld::enemyAtk(bool flag)
{
	//自攻撃エフェクト
	Node* pMyCatImg = this->getChildByTag(tagCatImg);
	String img_name = "myCatCombat.png";
	Animation *animation = Animation::create();
	animation->addSpriteFrameWithFileName(img_name.getCString());
	animation->setDelayPerUnit( 0.01f );
	animation->setRestoreOriginalFrame(false);

	img_name = "myCatDown.png";
	Animation *animation1 = Animation::create();
	animation1->addSpriteFrameWithFileName(img_name.getCString());
	animation1->setDelayPerUnit( 0.01f );
	animation1->setRestoreOriginalFrame(false);

	//敵攻撃エフェクト
	Node* pEnemyImg = this->getChildByTag(tagEnemyImg);
	img_name = String::createWithFormat("cat_%d.png",enemyType)->getCString();
	Animation *enemyAnimation = Animation::create();
	enemyAnimation->addSpriteFrameWithFileName(img_name.getCString());
	enemyAnimation->setDelayPerUnit( 0.01f );
	enemyAnimation->setRestoreOriginalFrame(false);

	img_name = String::createWithFormat("catAtk_%d.png",enemyType)->getCString();
	Animation *enemyAnimation1 = Animation::create();
	enemyAnimation1->addSpriteFrameWithFileName(img_name.getCString());
	enemyAnimation1->setDelayPerUnit( 0.01f );
	enemyAnimation1->setRestoreOriginalFrame(false);

	pEnemyImg->stopAllActions();
	pEnemyImg->runAction(
			Sequence::create(
				MoveBy::create(0.1, ccp( -30, 50)),
				Animate::create(enemyAnimation1),
				MoveTo::create(0.2, ccp( visibleSize.width * 0.5, origin.y + 250)),
				Animate::create(enemyAnimation),
				MoveTo::create(0.02, ccp( visibleSize.width * 0.5, origin.y + 400)),
				NULL
			)
	);

	if (flag) {
		pMyCatImg->runAction(
				Sequence::create(
					DelayTime::create(0.25f),
					Animate::create(animation1),
					EaseOut::create(MoveBy::create(0.3, ccp( 20, -35)),2),
					Animate::create(animation),
					MoveTo::create(0.02, ccp( visibleSize.width * 0.5, origin.y + pMyCatImg->getContentSize().height/2)),
					NULL
				)
		);
	} else {
		int move;
		if (arc4random() % 2 == 1) {
			move = 150;
		} else {
			move = -150;
		}
		pMyCatImg->runAction(
				Sequence::create(
					JumpBy::create(0.2, ccp( move, 0),150,1),
					JumpBy::create(0.2, ccp( 0 - move, 0),150,1),
					NULL
				)
		);
	}

	pEnemyImg->runAction(KSAnimation::enemyJump(enemyType));

}
void HelloWorld::enemyDef(bool flag)
{
	//自攻撃エフェクト
	Node* pMyCatImg = this->getChildByTag(tagCatImg);
	String img_name = "myCatCombat.png";
	Animation *animation = Animation::create();
	animation->addSpriteFrameWithFileName(img_name.getCString());
	animation->setDelayPerUnit( 0.01f );
	animation->setRestoreOriginalFrame(false);

	img_name = "myCatAtk.png";
	Animation *animation1 = Animation::create();
	animation1->addSpriteFrameWithFileName(img_name.getCString());
	animation1->setDelayPerUnit( 0.01f );
	animation1->setRestoreOriginalFrame(false);

	img_name = "win_cat.png";
	Animation *animation2 = Animation::create();
	animation2->addSpriteFrameWithFileName(img_name.getCString());
	animation2->setDelayPerUnit( 0.01f );
	animation2->setRestoreOriginalFrame(false);

	//敵攻撃エフェクト
	Node* pEnemyImg = this->getChildByTag(tagEnemyImg);
	img_name = String::createWithFormat("cat_%d.png",enemyType)->getCString();
	Animation *enemyAnimation = Animation::create();
	enemyAnimation->addSpriteFrameWithFileName(img_name.getCString());
	enemyAnimation->setDelayPerUnit( 0.01f );
	enemyAnimation->setRestoreOriginalFrame(false);

	img_name = String::createWithFormat("catDown_%d.png",enemyType)->getCString();
	Animation *enemyAnimation1 = Animation::create();
	enemyAnimation1->addSpriteFrameWithFileName(img_name.getCString());
	enemyAnimation1->setDelayPerUnit( 0.01f );
	enemyAnimation1->setRestoreOriginalFrame(false);

	pEnemyImg->stopAllActions();

	int move;
	if (arc4random() % 2 == 1) {
		move = 50;
	} else {
		move = -50;
	}

	if (flag) {
		pEnemyImg->runAction(
				Sequence::create(
					DelayTime::create(0.1f),
					MoveBy::create(0.15, ccp( 30, 50)),
					Animate::create(enemyAnimation1),
					DelayTime::create(0.3f),
					Animate::create(enemyAnimation),
					MoveTo::create(0.02, ccp( visibleSize.width * 0.5, origin.y + 400)),
					NULL
				)
		);

		pMyCatImg->runAction(
				Sequence::create(
					Animate::create(animation1),
					MoveBy::create(0.1, ccp( move, 150)),
					Animate::create(animation),
					MoveTo::create(0.1, ccp( visibleSize.width * 0.5, origin.y + pMyCatImg->getContentSize().height/2)),
					NULL
				)
		);
		pEnemyImg->runAction(KSAnimation::enemyJump(enemyType));
	} else {
		pEnemyImg->runAction(
				Sequence::create(
					MoveBy::create(0.15, ccp( 75, 100)),
					Animate::create(enemyAnimation1),
					NULL
				)
		);

		pMyCatImg->runAction(
				Sequence::create(
					Animate::create(animation1),
					MoveBy::create(0.1, ccp( move, 150)),
					Animate::create(animation2),
					NULL
				)
		);
		this->scheduleOnce(schedule_selector(HelloWorld::moveWinner), 1.5);

	}

}

void HelloWorld::enemyRushDef()
{
	//自攻撃エフェクト
	Node* pMyCatImg = this->getChildByTag(tagCatImg);
	String img_name = "myCatCombat.png";
	Animation *animation = Animation::create();
	animation->addSpriteFrameWithFileName(img_name.getCString());
	animation->setDelayPerUnit( 0.01f );
	animation->setRestoreOriginalFrame(false);

	img_name = "myCatAtk.png";
	Animation *animation1 = Animation::create();
	animation1->addSpriteFrameWithFileName(img_name.getCString());
	animation1->setDelayPerUnit( 0.01f );
	animation1->setRestoreOriginalFrame(false);

	//敵攻撃エフェクト
	Node* pEnemyImg = this->getChildByTag(tagEnemyImg);
	img_name = String::createWithFormat("cat_%d.png",enemyType)->getCString();
	Animation *enemyAnimation = Animation::create();
	enemyAnimation->addSpriteFrameWithFileName(img_name.getCString());
	enemyAnimation->setDelayPerUnit( 0.01f );
	enemyAnimation->setRestoreOriginalFrame(false);

	img_name = String::createWithFormat("catDown_%d.png",enemyType)->getCString();
	Animation *enemyAnimation1 = Animation::create();
	enemyAnimation1->addSpriteFrameWithFileName(img_name.getCString());
	enemyAnimation1->setDelayPerUnit( 0.01f );
	enemyAnimation1->setRestoreOriginalFrame(false);

	pEnemyImg->stopAllActions();

	int move;
	if (arc4random() % 2 == 1) {
		move = 50;
	} else {
		move = -50;
	}

	pMyCatImg->runAction(
			Sequence::create(
				Animate::create(animation1),
				MoveBy::create(0.1, ccp( move, 150)),
				Animate::create(animation),
				MoveTo::create(0.1, ccp( visibleSize.width * 0.5, origin.y + pMyCatImg->getContentSize().height/2)),
				NULL
			)
	);

	pEnemyImg->runAction(
			Sequence::create(
				DelayTime::create(0.1f),
				Animate::create(enemyAnimation1),
				MoveBy::create(0.03, ccp( -20, 0)),
				MoveBy::create(0.06, ccp( 40, 0)),
				MoveBy::create(0.03, ccp( -20, 0)),
				Animate::create(enemyAnimation),
				NULL
			)
	);

}
