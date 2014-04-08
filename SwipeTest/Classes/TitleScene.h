#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
protected:
    enum kTag
    {
        kTag_Menu = 1,
        kTag_StartButton,
        kTag_HelpButton,
        kTag_Help,
    };

	//プリファレンス
	const char* key_enemyLv = "EnemyLv";

	bool debug_flag = true;

public:

    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(TitleScene);
    virtual void menuStartCallback(Object* sender);

};

#endif // __TITLE_SCENE_H__
