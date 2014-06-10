#include "TutorialScene.h"
#include "TitleScene.h"
#include "HelloWorldScene.h"
#include "PowerUpScene.h"
#include <unistd.h>

USING_NS_CC;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define MISAKI_FONT "fonts/mini-wakuwaku-maru.ttf"
#else
#define MISAKI_FONT "mini-wakuwaku-maru"
#endif

Scene* Tutorial::createScene()
{
    auto scene = Scene::create();
    auto layer = Tutorial::create();
    scene->addChild(layer,1);

    return scene;
}

// on "init" you need to initialize your instance
bool Tutorial::init()
{
    //サイズ取得を行う
    origin			= Director::getInstance()->getVisibleOrigin();		//使用端末の(0,0)地点
	visibleSize		= Director::getInstance()->getVisibleSize();		//使用端末の画面サイズ

	this->setTouchMode(kCCTouchesOneByOne);								// シングルタッチモードにする
    this->setTouchEnabled(true);										// タッチを有効にする（内部的にEventDispatcherに登録される）

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Tutorial::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 背景を生成
	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int wk_flag = userDefault->getIntegerForKey(key_tutorialFlag, 1);

	Sprite* pBG;
	if (wk_flag == 3) {
		pBG = Sprite::create("help_1.png");
	} else {

//	    // NEXTボタン
//	    MenuItemImage* pSaisei = MenuItemImage::create("button_saisei.png",
//											 "button_saisei.png",
//											 CC_CALLBACK_1(Tutorial::tapSaiseiMenu, this));
//	    pSaisei->setPosition(Point(visibleSize.width * 0.5, origin.y + 220));
//		Menu* pMenu = Menu::create(pSaisei, NULL);
//		pMenu->setPosition(Point::ZERO);
//		pMenu->setTag(kTag_Saisei);
//		this->addChild(pMenu,2);

		//ターゲット
		Node* pTarget = Sprite::create("target_0.png");
		pTarget->setPosition(Point(pTarget->getContentSize().width+50.0, visibleSize.height * 0.80));
		pTarget->setTag(tagTargetImg);
		this->addChild(pTarget,2);
		Node* pTarget1 = Sprite::create("target_1.png");
		pTarget1->setPosition(Point(pTarget->getContentSize().width+10.0, visibleSize.height * 0.80));
		pTarget1->setTag(tagTargetImgSub1);
		this->addChild(pTarget1,1);
		pTarget1 = Sprite::create("target_1.png");
		pTarget1->setPosition(Point(pTarget->getContentSize().width+90.0, visibleSize.height * 0.80));
		pTarget1->setRotation(180);
		pTarget1->setTag(tagTargetImgSub2);
		this->addChild(pTarget1,1);

		//矢印表示
		Node* pArrow = Sprite::create("back_blue.png");
		pArrow->setPosition(Point(visibleSize.width-80, visibleSize.height * 0.80));
		pArrow->setTag(tagArrow);
		this->addChild(pArrow,9);
		Node* pArrow1 = Sprite::create("13.png");
		Size bgSize = pArrow->getContentSize();
		pArrow1->setPosition(Point(bgSize.width * 0.5, bgSize.height * 0.5));
		pArrow->addChild(pArrow1,10);

		pArrow->runAction(CCRepeatForever::create(Blink::create(5,5)));

		//メッセージ
		Node* pMsg = Sprite::create("help_msg1.png");
		pMsg->setPosition(Point(visibleSize.width-150, visibleSize.height * 0.80-100));
		pMsg->setTag(tagMsg);
		this->addChild(pMsg,2);

		pMsg = Sprite::create("help_msg3.png");
		pMsg->setPosition(Point(visibleSize.width/2 , origin.y + 200));
		pMsg->setTag(tagTap2);
		this->addChild(pMsg,2);

		LabelTTF* arrowLabel = LabelTTF::create("タップしてね", "Arial", 40);
		arrowLabel->setColor(ccc3(0, 0, 0));
		arrowLabel->setPosition(Point(visibleSize.width/2 , origin.y + 200));
		arrowLabel->setTag(tagTap);
		this->addChild(arrowLabel,3);
		arrowLabel->runAction(CCRepeatForever::create(Blink::create(5,7)));


		pBG = Sprite::create("Tutorial.png");
	}
    pBG->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.5));
    this->addChild(pBG);


    return true;
}
void Tutorial::onTouchEnded(Touch* touch, Event* event)
{

	UserDefault* userDefault = UserDefault::sharedUserDefault();
	int wk_flag = userDefault->getIntegerForKey(key_tutorialFlag, 1);

	if (wk_flag < 3) {


		Node* pArrow = this->getChildByTag(tagArrow);
		Node* pYubi;
		Node* pMsg;
		LabelTTF* arrowLabel;
		switch (scene_flag){
		case 0:
			//アニメーション停止
			pArrow->stopAllActions();
			pArrow->runAction(Show::create());
			pArrow->runAction(MoveTo::create(2, ccp(120.0, visibleSize.height * 0.80)));

			// 	メッセージ削除
			pMsg = this->getChildByTag(tagMsg);
			pMsg->removeFromParentAndCleanup(true);
			pMsg = this->getChildByTag(tagTap);
			pMsg->removeFromParentAndCleanup(true);
			pMsg = this->getChildByTag(tagTap2);
			pMsg->removeFromParentAndCleanup(true);

			//スワイプアニメーション追加
			pYubi = Sprite::create("yubi.png");
			pYubi->setPosition(Point(visibleSize.width-120, visibleSize.height * 0.80-200));
			pYubi->setRotation(120);
			pYubi->setTag(tagYubi);
			this->addChild(pYubi,2);
			pYubi->runAction(Sequence::create(MoveTo::create(1, ccp(120.0, visibleSize.height * 0.80-200)),MoveTo::create(0.7, ccp(120.0, visibleSize.height * 0.4)),NULL));

			scene_flag++;

			this->scheduleOnce(schedule_selector(Tutorial::msg2), 2);

			break;
		case 1:
			//アニメーションキャンセル
			this->unschedule(schedule_selector(Tutorial::msg2));

			//矢印を所定の位置へ移動
			pArrow->stopAllActions();
			pArrow->setPosition(Point(120.0, visibleSize.height * 0.80));

			//ｙｕｂｉを所定の位置へ移動
			pYubi  = this->getChildByTag(tagYubi);
			pYubi->stopAllActions();
			pYubi->setPosition(Point(120.0, visibleSize.height * 0.4));
			pYubi->runAction(RotateBy::create(0.5f, -90.0f));

			//メッセージ表示
			pMsg = Sprite::create("help_msg2.png");
			pMsg->setPosition(Point(280, visibleSize.height * 0.80-150));
			pMsg->setTag(tagMsg);
			this->addChild(pMsg,2);

			pMsg = Sprite::create("help_msg3.png");
			pMsg->setPosition(Point(visibleSize.width/2 , origin.y + 200));
			pMsg->setTag(tagTap2);
			this->addChild(pMsg,2);

			arrowLabel = LabelTTF::create("タップしてね", "Arial", 40);
			arrowLabel->setColor(ccc3(0, 0, 0));
			arrowLabel->setPosition(Point(visibleSize.width/2 , origin.y + 200));
			arrowLabel->setTag(tagTap);
			this->addChild(arrowLabel,3);
			arrowLabel->runAction(CCRepeatForever::create(Blink::create(5,7)));

			scene_flag++;

			break;
		case 2:
			if (wk_flag == 1) {
				Scene* gameScene = (Scene*)TitleScene::create();
				Director::getInstance()->replaceScene(gameScene);
			} else if (wk_flag == 2) {
				//相手レベル記録
				UserDefault* userDefault = UserDefault::sharedUserDefault();
				userDefault->setIntegerForKey(key_playEnemyLv, 1);

				// ゲーム画面の表示
				Scene* scene = HelloWorld::createScene();
				TransitionFlipX* tran = TransitionFlipX::create(0.2, scene);
				Director::sharedDirector()->replaceScene(tran);
			}
		}

	} else {
		if (wk_count > 3) {
		    Scene* scene = PowerUp::createScene();
		    TransitionFlipX* tran = TransitionFlipX::create(1, scene);
		    Director::sharedDirector()->replaceScene(tran);
		} else {
			wk_count = wk_count + 1;
			Sprite* pBG = Sprite::create(String::createWithFormat("help_%d.png", wk_count)->getCString());
		    pBG->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.5));
		    this->addChild(pBG);
		}
	}

}
//バックキー処理
void Tutorial::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE )
	{
		Scene* gameScene = (Scene*)TitleScene::create();
		Director::getInstance()->replaceScene(gameScene);
	}
}

// 次へボタン押下
void Tutorial::tapSaiseiMenu(Object* pSender)
{

	Node* pArrow = this->getChildByTag(tagArrow);
	Node* pYubi;
	Node* pMsg;
	switch (scene_flag){
	case 0:
		//アニメーション停止
		pArrow->stopAllActions();
		pArrow->runAction(Show::create());
		pArrow->runAction(MoveTo::create(2, ccp(120.0, visibleSize.height * 0.80)));

		// 	メッセージ削除
		pMsg = this->getChildByTag(tagMsg);
		pMsg->removeFromParentAndCleanup(true);

		//スワイプアニメーション追加
		pYubi = Sprite::create("yubi.png");
		pYubi->setPosition(Point(visibleSize.width-120, visibleSize.height * 0.80-200));
		pYubi->setRotation(120);
		pYubi->setTag(tagYubi);
		this->addChild(pYubi,2);
		pYubi->runAction(Sequence::create(MoveTo::create(0.7, ccp(120.0, visibleSize.height * 0.80-200)),MoveTo::create(0.7, ccp(120.0, visibleSize.height * 0.4)),NULL));

		scene_flag++;

		this->scheduleOnce(schedule_selector(Tutorial::msg2), 2);

		break;
	case 1:
		//アニメーションキャンセル
		this->unschedule(schedule_selector(Tutorial::msg2));

		//矢印を所定の位置へ移動
		pArrow->stopAllActions();
		pArrow->setPosition(Point(120.0, visibleSize.height * 0.80));

		//ｙｕｂｉを所定の位置へ移動
		pYubi  = this->getChildByTag(tagYubi);
		pYubi->stopAllActions();
		pYubi->setPosition(Point(120.0, visibleSize.height * 0.4));
		pYubi->runAction(RotateBy::create(0.5f, -90.0f));

		//メッセージ表示
		pMsg = Sprite::create("help_msg2.png");
		pMsg->setPosition(Point(280, visibleSize.height * 0.80-150));
		pMsg->setTag(tagMsg);
		this->addChild(pMsg,2);

		scene_flag++;

		break;
	}


}

void Tutorial::msg2(float time)
{

	Node* pMsg = Sprite::create("help_msg2.png");
	pMsg->setPosition(Point(280, visibleSize.height * 0.80-150));
	pMsg->setTag(tagMsg);
	this->addChild(pMsg,2);

	Node* pYubi  = this->getChildByTag(tagYubi);
	pYubi->runAction(RotateBy::create(0.5f, -90.0f));

	pMsg = Sprite::create("help_msg3.png");
	pMsg->setPosition(Point(visibleSize.width/2 , origin.y + 200));
	pMsg->setTag(tagTap2);
	this->addChild(pMsg,2);

	LabelTTF* arrowLabel = LabelTTF::create("タップしてね", "Arial", 40);
	arrowLabel->setColor(ccc3(0, 0, 0));
	arrowLabel->setPosition(Point(visibleSize.width/2 , origin.y + 200));
	arrowLabel->setTag(tagTap);
	this->addChild(arrowLabel,3);
	arrowLabel->runAction(CCRepeatForever::create(Blink::create(5,7)));

	scene_flag++;

}
