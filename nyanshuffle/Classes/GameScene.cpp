#include "GameScene.h"
#include "KSAnimation.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "TitleScene.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

Scene* GameScene::scene()
{
    return GameScene::sceneWithLevel(1);
}

Scene* GameScene::sceneWithLevel(int level)
{
    Scene* scene = Scene::create();
    GameScene* layer = GameScene::createWithLevel(level);
    scene->addChild(layer);
    
    return scene;
}

GameScene* GameScene::createWithLevel(int level)
{
    GameScene *pRet = new GameScene();
    if (pRet && pRet->initWithLevel(level))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool GameScene::initWithLevel(int level)
{
    if (!Layer::init())
    {
        return false;
    }
    
    m_level = level;
    
    srand((unsigned int)time(NULL));
    int randum = rand();
    
    Size size = Director::sharedDirector()->getWinSize();
    
    // 背景の表示
    Sprite* pBG = Sprite::create("game_bg.png");
    pBG->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(pBG);
    
    Size bgSize = pBG->getContentSize();
    
    // 雲のアクション作成
    MoveBy* cloud1Action = MoveBy::create(80, ccp(bgSize.width, 0));
    MoveBy* cloud2Action = MoveBy::create(160, ccp(bgSize.width, 0));
    
    // 雲の表示
    Sprite* pCloud1 = Sprite::create("cloud.png");
    pCloud1->setPosition(ccp(bgSize.width * 0.4, bgSize.height * 0.83));
    pCloud1->runAction(cloud1Action);
    pBG->addChild(pCloud1);
    
    Sprite* pCloud2 = Sprite::create("cloud.png");
    pCloud2->setPosition(ccp(bgSize.width * 0.2, bgSize.height * 0.9));
    pCloud2->setScale(0.6);
    pCloud2->runAction(cloud2Action);
    pBG->addChild(pCloud2);
    
    // ネコの表示
    String* catImagePath = String::createWithFormat("cat%d.png", randum % 5 + 1);
    m_pCat = Sprite::create(catImagePath->getCString());
    m_pCat->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(m_pCat, 0);
    
    // Levelを表示する
    showLevel();
    
    return true;
}

void GameScene::onEnterTransitionDidFinish()
{
    int randum = rand();
    Size size = Director::sharedDirector()->getWinSize();
    
    // ネコのアクションを開始する
    m_pCat->runAction(KSAnimation::catStartAction());
    
    // 箱を表示する
    String* boxFileName = String::createWithFormat("box%d.png", randum % 2 + 1);
    m_pBox1 = MenuItemImage::create(boxFileName->getCString(), boxFileName->getCString(), NULL, NULL);
    CCLOG("box1=%p",m_pBox1);
    m_pBox1->setPosition(ccp(size.width * 0.2, size.height * 0.5 + size.height));
    m_pBox1->runAction(KSAnimation::boxesStartAction(this, callfunc_selector(GameScene::playDroppingSound)));
    m_pBox1->setTag(kBoxLocation_Left);
    
    m_pBox2 = MenuItemImage::create(boxFileName->getCString(), boxFileName->getCString(), NULL, NULL);
    m_pBox2->setPosition(ccp(size.width * 0.5, size.height * 0.5 + size.height));
    m_pBox2->runAction(KSAnimation::boxesStartActionWithVibration(this, callfunc_selector(GameScene::playDroppingSound)));
    m_pBox2->setTag(kBoxLocation_Center);
    
    m_pBox3 = MenuItemImage::create(boxFileName->getCString(), boxFileName->getCString(), NULL, NULL);
    m_pBox3->setPosition(ccp(size.width * 0.8, size.height * 0.5 + size.height));
    m_pBox3->runAction(KSAnimation::boxesStartAction(this, callfunc_selector(GameScene::playDroppingSound)));
    m_pBox3->setTag(kBoxLocation_Right);
    
    Menu* menu = Menu::create(m_pBox1, m_pBox2, m_pBox3, NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    // カウントダウンを開始する
    this->scheduleOnce(schedule_selector(GameScene::showCountdown), 1);
}

void GameScene::playDroppingSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("rakka.mp3");
}
void GameScene::showCountdown(float time)
{
    this->scheduleOnce(schedule_selector(GameScene::playCountdownSound), 0.5);
    
    Size size = Director::sharedDirector()->getWinSize();
    
    // 「3」の表示
    Sprite* pNum3 = Sprite::create("3.png");
    pNum3->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    pNum3->setScale(0);
    pNum3->runAction(KSAnimation::num3Animation());
    this->addChild(pNum3, 1);
    
    // 「2」の表示
    Sprite* pNum2 = Sprite::create("2.png");
    pNum2->setPosition(pNum3->getPosition());
    pNum2->setScale(0);
    pNum2->runAction(KSAnimation::num2Animation());
    this->addChild(pNum2, 1);
    
    // 「1」の表示
    Sprite* pNum1 = Sprite::create("1.png");
    pNum1->setPosition(pNum3->getPosition());
    pNum1->setScale(0);
    pNum1->runAction(KSAnimation::num1Animation());
    this->addChild(pNum1, 1);
    
    // 「GO」の表示
    Sprite* pGo = Sprite::create("go.png");
    pGo->setPosition(pNum3->getPosition());
    pGo->setScale(0);
    pGo->runAction(KSAnimation::num0Animation(this, callfunc_selector(GameScene::startShuffle)));
    this->addChild(pGo, 1);
}

void GameScene::playCountdownSound(float time)
{
    SimpleAudioEngine::sharedEngine()->playEffect("countdown.mp3");
}

void GameScene::startShuffle()
{
    m_totalShuffleTime = 0;
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameBgm.mp3", true);
    this->schedule(schedule_selector(GameScene::boxesShuffle));
}

MenuItemImage* GameScene::getLeftBox()
{
    if (m_pBox1->getTag() == kBoxLocation_Left)
        return m_pBox1;
    else if (m_pBox2->getTag() == kBoxLocation_Left)
        return m_pBox2;
    else
        return m_pBox3;
}

MenuItemImage* GameScene::getCenterBox()
{
    if (m_pBox1->getTag() == kBoxLocation_Center)
        return m_pBox1;
    else if (m_pBox2->getTag() == kBoxLocation_Center)
        return m_pBox2;
    else
        return m_pBox3;
}

MenuItemImage* GameScene::getRightBox()
{
    if (m_pBox1->getTag() == kBoxLocation_Right)
        return m_pBox1;
    else if (m_pBox2->getTag() == kBoxLocation_Right)
        return m_pBox2;
    else
        return m_pBox3;
}

void GameScene::shufflePattern1(float time)
{
    // 左から中央へ
    MenuItemSprite* leftBox = getLeftBox();
    leftBox->runAction(KSAnimation::moveFromLeftToCenter(time));
    
    // 中央から左へ
    MenuItemSprite* centerBox = getCenterBox();
    centerBox->runAction(KSAnimation::moveFromCenterToLeft(time));
    
    leftBox->setTag(kBoxLocation_Center);
    centerBox->setTag(kBoxLocation_Left);
}

void GameScene::shufflePattern2(float time)
{
    // 左から右へ
    MenuItemSprite* leftBox = getLeftBox();
    leftBox->runAction(KSAnimation::moveFromLeftToRight(time));
    
    // 右から左へ
    MenuItemSprite* rightBox = getRightBox();
    rightBox->runAction(KSAnimation::moveFromRightToLeft(time));
    
    leftBox->setTag(kBoxLocation_Right);
    rightBox->setTag(kBoxLocation_Left);
}

void GameScene::shufflePattern3(float time)
{
    // 中央から右へ
    MenuItemSprite* centerBox = getCenterBox();
    centerBox->runAction(KSAnimation::moveFromCenterToRight(time));
    
    // 右から中央へ
    MenuItemSprite* rightBox = getRightBox();
    rightBox->runAction(KSAnimation::moveFromRightToCenter(time));
    
    centerBox->setTag(kBoxLocation_Right);
    rightBox->setTag(kBoxLocation_Center);
}

void GameScene::shufflePattern4(float time)
{
    // 左から右へ
    MenuItemSprite* leftBox = getLeftBox();
    leftBox->runAction(KSAnimation::moveFromLeftToRight(time));
    
    // 中央から左へ
    MenuItemSprite* centerBox = getCenterBox();
    centerBox->runAction(KSAnimation::moveFromCenterToLeft(time));
    
    // 右から中央へ
    MenuItemSprite* rightBox = getRightBox();
    rightBox->runAction(KSAnimation::moveFromRightToCenter(time));
    
    leftBox->setTag(kBoxLocation_Right);
    centerBox->setTag(kBoxLocation_Left);
    rightBox->setTag(kBoxLocation_Center);
}

void GameScene::shufflePattern5(float time)
{
    // 左から中央へ
    MenuItemSprite* leftBox = getLeftBox();
    leftBox->runAction(KSAnimation::moveFromLeftToCenter(time));
    
    // 中央から右へ
    MenuItemSprite* centerBox = getCenterBox();
    centerBox->runAction(KSAnimation::moveFromCenterToRight(time));
    
    // 右から左へ
    MenuItemSprite* rightBox = getRightBox();
    rightBox->runAction(KSAnimation::moveFromRightToLeft(time));
    
    leftBox->setTag(kBoxLocation_Center);
    centerBox->setTag(kBoxLocation_Right);
    rightBox->setTag(kBoxLocation_Left);
}

void GameScene::boxesShuffle(float time)
{
    m_totalShuffleTime += time;
    
    // 箱がアクション中は、処理を抜ける
    if (m_pBox1->getActionByTag(TAG_ACTION) ||
        m_pBox2->getActionByTag(TAG_ACTION) ||
        m_pBox3->getActionByTag(TAG_ACTION))
        return;
    
    // 5秒経過した場合は、シャッフル終了
    if (m_totalShuffleTime > 5)
    {
        this->unschedule(schedule_selector(GameScene::boxesShuffle));
        this->scheduleOnce(schedule_selector(GameScene::afterShuffle), 0.2);
        
        return;
    }
    
    float shuffleTime = 0.5 - 0.01 * m_level;
    if (shuffleTime < 0.3) {
        shuffleTime = 0.3;
    }
    float activeShufflingTime;
    
    // シャッフル時間の指定
    switch (rand() % 5)
    {
        case 0:  activeShufflingTime = shuffleTime * 0.90; break;
        case 1:  activeShufflingTime = shuffleTime * 0.95; break;
        case 2:  activeShufflingTime = shuffleTime * 1.00; break;
        case 3:  activeShufflingTime = shuffleTime * 1.05; break;
        default: activeShufflingTime = shuffleTime * 1.10; break;
    }
    
    // シャッフルパターンの指定
    switch (rand() % 5)
    {
        case 0:  shufflePattern1(activeShufflingTime); break;
        case 1:  shufflePattern2(activeShufflingTime); break;
        case 2:  shufflePattern3(activeShufflingTime); break;
        case 3:  shufflePattern4(activeShufflingTime); break;
        default: shufflePattern5(activeShufflingTime); break;
    }
}

void GameScene::afterShuffle(float time)
{
    // ネコの表示
    m_pCat->setPosition(m_pBox2->getPosition());
    m_pCat->runAction(KSAnimation::catEndAction());
    // 箱をタップ可能にする
//    m_pBox1->setTarget(this, menu_selector(GameScene::selectBox));
//    m_pBox2->setTarget(this, menu_selector(GameScene::selectBox));
//    m_pBox3->setTarget(this, menu_selector(GameScene::selectBox));
    m_pBox1->setCallback(CC_CALLBACK_1(GameScene::selectBox, this));
    m_pBox2->setCallback(CC_CALLBACK_1(GameScene::selectBox, this));
    m_pBox3->setCallback(CC_CALLBACK_1(GameScene::selectBox, this));
//    m_pBox2->setCallback(CC_CALLBACK_1(GameScene::selectBox,this));
//    m_pBox3->setCallback(CC_CALLBACK_1(GameScene::selectBox,this));
    this->schedule(schedule_selector(GameScene::boxVibration), 1);
}

void GameScene::boxVibration(float time)
{
    if (rand() % 10 == 0)
        m_pBox1->runAction(KSAnimation::vibrationAnimation());
    
    if (rand() % 10 == 0)
        m_pBox2->runAction(KSAnimation::vibrationAnimation());
    
    if (rand() % 10 == 0)
        m_pBox3->runAction(KSAnimation::vibrationAnimation());
}

//void GameScene::backCallback(Object* sender)
//{
//	log("override back!");
//}


//void GameScene::selectBox(Node* target)
void GameScene::selectBox(Object* sender)
{
	MenuItemImage* sender_Box = (MenuItemImage*)sender;

	CCLOG("tapped-1");
    // 箱のタップを無効とする
    m_pBox1->setEnabled(false);
    m_pBox2->setEnabled(false);
    m_pBox3->setEnabled(false);
    
    // 箱のアニメーションを停止する
    this->unschedule(schedule_selector(GameScene::boxVibration));
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCLOG("tapped0");
    
    Size size = Director::sharedDirector()->getWinSize();
    
    // 選択された箱のアニメーションを開始する
	CCLOG("tapped1");
    MoveBy* move = MoveBy::create(1, ccp(0, sender_Box->getContentSize().height * sender_Box->getScaleY()));
	CCLOG("tapped2");
	sender_Box->runAction(move);
	CCLOG("tapped3");
    
    string answerFilePath;
	CCLOG("tapped4");
    string seFileName;
	CCLOG("tapped5");
    SEL_CallFunc selector;
	CCLOG("tapped6");
    
    if (sender_Box == m_pBox2)
    {
        // 正解の場合の処理
        answerFilePath = "success.png";
        seFileName = "correctAnswer.mp3";
        selector = callfunc_selector(GameScene::correctAnswer);
    }
    else
    {
        // 不正解の場合の処理
        answerFilePath = "failure.png";
        seFileName = "incorrectAnswer.mp3";
        selector = callfunc_selector(GameScene::incorrectAnswer);
    }
    
    SimpleAudioEngine::sharedEngine()->playEffect(seFileName.c_str());
    
    // 正解あるいは不正解と表示する
    Sprite* answer = Sprite::create(answerFilePath.c_str());
    answer->setPosition(ccp(size.width / 2, size.height * 7.5 / 10));
    answer->setScale(0);
    answer->runAction(KSAnimation::resultAnimation(this, selector));
    this->addChild(answer);
}

//void GameScene::correctAnswer(Node* target)
void GameScene::correctAnswer()
{
    // 正解時の画面遷移
    Scene* scene = GameScene::sceneWithLevel(m_level + 1);
    TransitionJumpZoom* tran = TransitionJumpZoom::create(1, scene);
    Director::sharedDirector()->replaceScene(tran);
}

//void GameScene::incorrectAnswer(Node* target)
void GameScene::incorrectAnswer()
{
    // 不正解時の画面遷移
    Scene* scene = TitleScene::scene();
    TransitionProgressRadialCCW* tran = TransitionProgressRadialCCW::create(1, scene);
    Director::sharedDirector()->replaceScene(tran);
}

void GameScene::showLevel()
{
    Size size = Director::sharedDirector()->getWinSize();
    
    // Levelの表示
    String* levelString = String::createWithFormat("Level %d", m_level);
    LabelTTF* pLevel = LabelTTF::create(levelString->getCString(), "", LEVEL_FONT_SIZE);
    pLevel->setPosition(ccp(size.width * 0.5, size.height * 0.2));
    this->addChild(pLevel);
}

