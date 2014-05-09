#ifndef __WINNER_SCENE_H__
#define __WINNER_SCENE_H__

#include "cocos2d.h"

class Winner : public cocos2d::Layer
{
protected:

	void tapReturnMenu(Object* pSender);
	void tapRetry(Object* pSender);
	void showScore(float time);

    enum kTag
    {
        kTag_Menu = 1,
        kTag_Winner,
        kTag_Cat,
        kTag_Retry,
        kTag_Menu_Label,
        kTag_Retry_Label,
        kTag_Exp_Label,
    };

	//プリファレンス
	const char* key_enemyLv			= "EnemyLv";
	const char* key_playEnemyLv		= "PlayEnemyLv";		//対戦中敵レベル
	const char* key_playerExp			= "PlayerExp";			//プレイヤー経験値
	const char* key_playerStrongLv		= "PlayerStrong";		//プレイヤー体力
	const char* key_playerPowerLv		= "PlayerPower";		//プレイヤー攻撃力
	const char* key_playerSpeedLv		= "PlayerSpeed";		//プレイヤースピード
	const char* key_playerTechniqueLv	= "PlayerTechnique";	//プレイヤーテクニック
	const char* key_maxComboCount		= "MaxConboCount";		//MAXコンボ数
	const char* key_noMissFlag			= "NoMissFlag";			//ノーミスフラグ


	//配置
	cocos2d::Point	origin;										//使用端末の(0,0)地点
	cocos2d::Size	visibleSize;								//使用端末の画面サイズ

	bool debug_flag = true;
	int enemyLv;
	int playEnemyLv;
	int playerExp;
	int maxCombo;
	bool noMissFlag;
	int wk_enemyExp;
	int showCount = 0;

public:

	static cocos2d::Scene* createScene();
    static cocos2d::Scene* scene();
    virtual bool init();
    CREATE_FUNC(Winner);

};

#endif // __WINNER_SCENE_H__
