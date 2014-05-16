#ifndef __POWERUP_SCENE_H__
#define __POWERUP_SCENE_H__

#include "cocos2d.h"

class PowerUp : public cocos2d::Layer
{
protected:

	void tapReturnMenu(Object* pSender);
	void tapStrongButton(Object* pSender);
	void tapPowerButton(Object* pSender);
	void tapSpeedButton(Object* pSender);
	void tapTechniqueButton(Object* pSender);
	int Calculation(int lv);
	void redisplay();

    enum kTag
    {
        kTag_Menu = 1,
        kTag_StrongButton,
        kTag_PowerButton,
        kTag_SpeedButton,
        kTag_TechniqueButton,
        kTag_StrongLabel,
        kTag_PowerLabel,
        kTag_SpeedLabel,
        kTag_TechniqueLabel,
        kTag_ExpLabel,
    };

	//配置
	cocos2d::Point	origin;										//使用端末の(0,0)地点
	cocos2d::Size	visibleSize;								//使用端末の画面サイズ

	//プリファレンス
	const char* key_enemyLv			= "EnemyLv";
	const char* key_playerExp			= "PlayerExp";			//プレイヤー経験値
	const char* key_playerStrongLv		= "PlayerStrong";		//プレイヤー体力
	const char* key_playerPowerLv		= "PlayerPower";		//プレイヤー攻撃力
	const char* key_playerSpeedLv		= "PlayerSpeed";		//プレイヤースピード
	const char* key_playerTechniqueLv	= "PlayerTechnique";	//プレイヤーテクニック

	bool debug_flag = true;

public:

	static cocos2d::Scene* createScene();
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(PowerUp);

};

#endif // __POWERUP_SCENE_H__
