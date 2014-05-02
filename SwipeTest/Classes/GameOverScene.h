#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
protected:


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
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(GameOver);

};

#endif // __GAMEOVER_SCENE_H__
