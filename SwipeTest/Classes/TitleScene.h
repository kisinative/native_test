#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
protected:

	void menuPowerUpCallback(Object* sender);

    enum kTag
    {
        kTag_Menu = 1,
        kTag_StartButton,
        kTag_HelpButton,
        kTag_Help,
        kTag_PowerUpButton,
    };

	//プリファレンス
	const char* key_enemyLv = "EnemyLv";
	const char* key_playEnemyLv		= "PlayEnemyLv";		//対戦中敵レベル
	const char* key_playerExp			= "PlayerExp";			//プレイヤー経験値
	const char* key_playerStrongLv		= "PlayerStrong";		//プレイヤー体力
	const char* key_playerPowerLv		= "PlayerPower";		//プレイヤー攻撃力
	const char* key_playerSpeedLv		= "PlayerSpeed";		//プレイヤースピード
	const char* key_playerTechniqueLv	= "PlayerTechnique";	//プレイヤーテクニック

	bool debug_flag = true;

public:

    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(TitleScene);
    virtual void menuStartCallback(Object* sender);


};

#endif // __TITLE_SCENE_H__
