#include "TitleScene.h"
#include "GameScene.h"
#include "KSAnimation.h"
#include "SimpleAudioEngine.h"
#include "ScrollLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

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
    
    srand((unsigned int)time(NULL));
    
    Size size = Director::sharedDirector()->getWinSize();
    
    // BGM再生
    if (!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("titleBgm.mp3", true);
    
    // 背景
    Sprite* pBG = Sprite::create("title_bg.png");
    pBG->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(pBG);
    
    Size bgSize = pBG->getContentSize();
    
    // ネコの目
    Sprite* pLeftEye = Sprite::create("cateye.png");
    pLeftEye->setPosition(ccp(bgSize.width * 0.43, bgSize.height * 0.28));
    pLeftEye->runAction(RepeatForever::create(RotateBy::create(1, 360)));
    pBG->addChild(pLeftEye);
    
    Sprite* pRightEye = Sprite::create("cateye.png");
    pRightEye->setPosition(ccp(bgSize.width * 0.54, bgSize.height * 0.28));
    pRightEye->runAction(RepeatForever::create(RotateBy::create(1, 360)));
    pBG->addChild(pRightEye);
    
    // タイトル
    Sprite* pTitle = Sprite::create("title.png");
    pTitle->setPosition(ccp(size.width * 0.50, size.height * 0.60));
    this->addChild(pTitle);
    
    // スタートボタン
    MenuItemImage* pStartItem;
    pStartItem = MenuItemImage::create("start_1.png",
                                         "start_2.png",
                                         this,
                                         menu_selector(TitleScene::menuStartCallback));
    pStartItem->setPosition(ccp(size.width * 0.25, size.height * 0.20));
    pStartItem->setTag(kTag_StartButton);
    
    // ヘルプボタン
    MenuItemImage* pHelpItem;
    pHelpItem = MenuItemImage::create("help_1.png",
                                        "help_2.png",
                                        this,
                                        menu_selector(TitleScene::menuOpenHelpCallback));
    pHelpItem->setPosition(ccp(size.width * 0.60, size.height * 0.30));
    pHelpItem->setAnchorPoint(ccp(0.5, 0));
    pHelpItem->setRotation(30);
    pHelpItem->setTag(kTag_HelpButton);
    
    Menu* pMenu = Menu::create(pStartItem, pHelpItem, NULL);
    pMenu->setPosition(Point::ZERO);
    pMenu->setTag(kTag_Menu);
    this->addChild(pMenu);
    
    // ボタンアニメーション開始
    this->schedule(schedule_selector(TitleScene::itemVibration), 1);
    
    // 初回起動時はヘルプを表示する
    if (!UserDefault::sharedUserDefault()->getBoolForKey("shownHelp", false))
    {
        menuOpenHelpCallback(NULL);
        UserDefault::sharedUserDefault()->setBoolForKey("shownHelp", true);
        UserDefault::sharedUserDefault()->flush();
    }

    return true;
}

void TitleScene::itemVibration(float time)
{
    int randum = rand();
    
    if ((randum % 2) == 0)
    {
        // スタートボタンのアニメーション
        Node* pMenu = this->getChildByTag(kTag_Menu);
        if (pMenu)
        {
            Node* pStartButton = pMenu->getChildByTag(kTag_StartButton);
            if (pStartButton)
                pStartButton->runAction(KSAnimation::vibrationAnimation());
        }
    }

    if ((randum % 3) == 0)
    {
        // ヘルプボタンのアニメーション
        Node* pMenu = this->getChildByTag(kTag_Menu);
        if (pMenu)
        {
            Node* pHelpButton = pMenu->getChildByTag(kTag_HelpButton);
            if (pHelpButton)
            {
                RotateBy* rotate1 = RotateBy::create(0.05,   5);
                RotateBy* rotate2 = RotateBy::create(0.10, -10);
                RotateBy* rotate3 = RotateBy::create(0.05,   5);
                Sequence* rotations = Sequence::create(rotate1, rotate2, rotate3, NULL);
                Repeat* repeat = Repeat::create(rotations, 3);
                
                pHelpButton->runAction(repeat);
            }
        }
    }
}

void TitleScene::menuStartCallback(Object* pSender)
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
    
    // ゲーム画面の表示
    Scene* scene = GameScene::scene();
    TransitionJumpZoom* tran = TransitionJumpZoom::create(1, scene);
    Director::sharedDirector()->replaceScene(tran);
}

void TitleScene::setButtonEnabled(bool enabled)
{
    Node* pMenu = this->getChildByTag(kTag_Menu);
    if (pMenu)
    {
        Node* pStartButton = pMenu->getChildByTag(kTag_StartButton);
        if (pStartButton)
            ((MenuItemImage*)pStartButton)->setEnabled(enabled);
        
        Node* pHelpButton = pMenu->getChildByTag(kTag_HelpButton);
        if (pHelpButton)
            ((MenuItemImage*)pHelpButton)->setEnabled(enabled);
    }
}

void TitleScene::menuOpenHelpCallback(Object* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
    
    // ヘルプ表示時は、ボタンを無効とする
    setButtonEnabled(false);
    
    // ヘルプの背景（ベースとなるレイヤー）
    LayerColor* pHelpBackLayer = LayerColor::create(ccc4(255, 255, 255, 223));
    pHelpBackLayer->setTag(kTag_Help);
    this->addChild(pHelpBackLayer);
    
    Size size = Director::sharedDirector()->getWinSize();
    
    // ヘルプに表示する画像の配列を生成
    Array* pHelpLayers = Array::create();
    for (int i = 1; i <= 3; i++)
    {
        LayerColor* pHelpLayer = LayerColor::create(ccc4(0, 0, 0, 0));
        
        String* fileName = String::createWithFormat("howtoplay%d.png", i);
        Sprite* pHelpSprite = Sprite::create(fileName->getCString());
        pHelpSprite->setPosition(ccp(size.width * 0.5, size.height * 0.5));
        pHelpLayer->addChild(pHelpSprite);
        pHelpLayer->setContentSize(pHelpSprite->getContentSize());
        pHelpLayers->addObject(pHelpLayer);
    }
    
    // ヘルプ画像の表示
    ScrollLayer* pHelp = ScrollLayer::createWithLayers(pHelpLayers, size.width * 0.40);
    pHelpBackLayer->addChild(pHelp);
    
    // 戻るボタンの表示
    MenuItemImage* pBackItem;
    pBackItem = MenuItemImage::create("back_1.png",
                                        "back_2.png",
                                        this,
                                        menu_selector(TitleScene::menuCloseHelpCallback));
    pBackItem->setPosition(ccp(size.width * 0.1, size.height * 0.8));
    
    Menu* pMenu = Menu::create(pBackItem, NULL);
    pMenu->setPosition(Point::ZERO);
    pHelpBackLayer->addChild(pMenu);
}

void TitleScene::menuCloseHelpCallback(Object* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
    
    // ヘルプを閉じると、ボタンを有効とする
    setButtonEnabled(true);
    
    // ヘルプレイヤーの削除
    this->removeChildByTag(kTag_Help, true);
}

