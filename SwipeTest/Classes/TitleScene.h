#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
protected:

	void menuPowerUpCallback(Object* sender);
	void menuClose(Object* sender);
	void menuTutorial(Object* sender);
	void gameStart(int enemyLv);

    enum kTag
    {
        kTag_Menu = 1,
        kTag_StartButton,
        kTag_StartButtonLabel,
        kTag_HelpButton,
        kTag_Help,
        kTag_Title,
        kTag_PowerUpButton,
        kTag_OsusumeButton,
    };

	//プリファレンス
	const char* key_enemyLv = "EnemyLv";
	const char* key_playEnemyLv		= "PlayEnemyLv";		//対戦中敵レベル
	const char* key_playerExp			= "PlayerExp";			//プレイヤー経験値
	const char* key_playerStrongLv		= "PlayerStrong";		//プレイヤー体力
	const char* key_playerPowerLv		= "PlayerPower";		//プレイヤー攻撃力
	const char* key_playerSpeedLv		= "PlayerSpeed";		//プレイヤースピード
	const char* key_playerTechniqueLv	= "PlayerTechnique";	//プレイヤーテクニック
	const char* key_tutorialFlag 		= "TutorialFlag";

	bool debug_flag = false;
	cocos2d::Point	origin;										//使用端末の(0,0)地点
	cocos2d::Size	size;										//使用端末の画面サイズ

public:

    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(TitleScene);
    virtual void menuStartCallback(Object* sender);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);

};

#endif // __TITLE_SCENE_H__
