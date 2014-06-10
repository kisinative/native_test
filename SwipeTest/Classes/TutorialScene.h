#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "cocos2d.h"

class Tutorial : public cocos2d::Layer
{
protected:

	void tapSaiseiMenu(Object* pSender);
	void msg2(float time);

    enum kTag
    {
        kTag_Saisei = 1,
        tagTargetImg,
        tagTargetImgSub1,
        tagTargetImgSub2,
        tagArrow,
        tagMsg,
        tagYubi,
        tagTap,
        tagTap2,
    };

	//プリファレンス
	const char* key_tutorialFlag = "TutorialFlag";
	const char* key_playEnemyLv		= "PlayEnemyLv";		//対戦中敵レベル

	int wk_count = 1;
	int scene_flag = 0;

	bool debug_flag = true;
	cocos2d::Point	origin;										//使用端末の(0,0)地点
	cocos2d::Size	visibleSize;								//使用端末の画面サイズ

public:

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(Object* pSender);

    // タッチ関係のイベント
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);

    // implement the "static create()" method manually
    CREATE_FUNC(Tutorial);

};

#endif // __TITLE_SCENE_H__
