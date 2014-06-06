#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
protected:

	void tapReturnMenu(Object* pSender);
	void tapRetry(Object* pSender);

    enum kTag
    {
        kTag_Menu = 1,
        kTag_GameOver,
        kTag_Cat,
        kTag_Retry,
        kTag_Menu_Label,
        kTag_Retry_Label,
    };

	//配置
	cocos2d::Point	origin;										//使用端末の(0,0)地点
	cocos2d::Size	visibleSize;								//使用端末の画面サイズ

	bool debug_flag = true;

public:

	static cocos2d::Scene* createScene();
    static cocos2d::Scene* scene();
    virtual bool init();
    CREATE_FUNC(GameOver);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);

};

#endif // __GAMEOVER_SCENE_H__
