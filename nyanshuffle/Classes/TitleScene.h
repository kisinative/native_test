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
    
    // Chapter 6.11で追記する内容
    void itemVibration(float time);
    
    // Chapter 6.12で追記する内容
    void setButtonEnabled(bool enabled);
    
public:
    // Chapter 6.11で追記する内容
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(TitleScene);
    virtual void menuStartCallback(Object* pSender);
    
    // Chapter 6.12で追記する内容
    virtual void menuOpenHelpCallback(Object* pSender);
    virtual void menuCloseHelpCallback(Object* pSender);
};

#endif // __TITLE_SCENE_H__
