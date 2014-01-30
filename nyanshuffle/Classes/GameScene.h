#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
protected:
    Sprite* m_pCat;
    MenuItemImage* m_pBox1;
    MenuItemImage* m_pBox2;
    MenuItemImage* m_pBox3;
    
    // Chapter 6.4で説明した内容
    void playDroppingSound();
    
    // Chapter 6.5で追記する内容
    void showCountdown(float time);
    void playCountdownSound(float time);
    void startShuffle();
    
    // Chapter 6.6で追記する内容
    enum kBoxLocation
    {
        kBoxLocation_Left = 101,
        kBoxLocation_Center,
        kBoxLocation_Right,
    };
    float m_totalShuffleTime;
    MenuItemImage* getLeftBox();
    MenuItemImage* getCenterBox();
    MenuItemImage* getRightBox();
    void shufflePattern1(float time);
    void shufflePattern2(float time);
    void shufflePattern3(float time);
    void shufflePattern4(float time);
    void shufflePattern5(float time);
    void boxesShuffle(float time);
    void afterShuffle(float time);

    // Chapter 6.8で追記する内容
    void selectBox(Object* sender);
//    void selectBox(Node* target);
    void boxVibration(float time);
    void correctAnswer();
    void incorrectAnswer();
    
    // Chapter 6.9で追記する内容
    int m_level;
    void showLevel();
    
    // Chapter 6.10で追記する内容
    virtual void onEnterTransitionDidFinish();
    
public:
    static cocos2d::Scene* scene();

    // Chapter 6.9で追記する内容
    virtual bool initWithLevel(int level);
    static cocos2d::Scene* sceneWithLevel(int level);
    static GameScene* createWithLevel(int level);
};

#endif // __GAME_SCENE_H__
