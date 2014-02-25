#include "TitleScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

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
    EGLView::sharedOpenGLView()->setDesignResolutionSize(640, 1136, kResolutionNoBorder);

    srand((unsigned int)time(NULL));

    Size size = Director::sharedDirector()->getWinSize();


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

    CCLOG("aaa = %d, bbb = %d", kTag_StartButton, kTag_Menu);
    return true;
}

void TitleScene::menuStartCallback(Object* sender)
{
    // ゲーム画面の表示
    Scene* scene = HelloWorld::createScene();
    TransitionJumpZoom* tran = TransitionJumpZoom::create(1, scene);
    Director::sharedDirector()->replaceScene(tran);
}
