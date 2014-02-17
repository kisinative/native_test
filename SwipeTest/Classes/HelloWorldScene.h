#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
protected:
	cocos2d::Point xtGestureStartPoint;
	cocos2d::Point xtGestureEndPoint;

	void showArrow(float time);
	void nextStage(float time);
	void timeOver();
	void attack(int flag);
	void miss();
	void setup();
	void createLabel(std::string labelString, float labelSize, float labelWidth, float labelHeight, int labelTag);
	void makeRetryButton();
	void tapRetryButton(Node *node);

	// tag
	const int tagHp				= 10;		//HPタグ
	const int tagEnemyHp		= 20;		//敵HPタグ
	const int tagEnemyStrong	= 22;		//敵体力タグ
	const int tagEnemyPower		= 24;		//敵攻撃力タグ
	const int tagEnemySpeed		= 26;		//敵スピードタグ
	const int tagTargetImg	 	= 80;		//ターゲットタグ
	const int tagArrowImg	 	= 90;		//矢印タグ
	const int tagArrowLabel 	= 100;		//矢印タグ
	const int tagRetry		 	= 110;		//リトライタグ

	//敵基本能力
	const int defaultEnemyStrong = 15;		//体力
	const int defaultEnemyPower  = 10;		//攻撃力
	const float defaultEnemySpeed  = 4.1;	//スピード

	//敵レベル
	int enemyStrongLv;
	int enemypowerLv;
	int enemySpeedLv;

	//HP関連
	const int MaxHp			= 100;		//最大HP
	int NowHp;							//現在HP
	int NowEnemyHp;						//敵現在HP

	//フラグ類
	std::string migi = "0";				//入力中ジェスチャ
	std::string hidari = "1";				//入力中ジェスチャ
	std::string ue = "2";				//入力中ジェスチャ
	std::string sita = "3";				//入力中ジェスチャ
	std::string targetGesture;			//現在ジェスチャ
	std::string nowGesture;				//入力中ジェスチャ
	bool atkDefFlag;					//攻撃防御フラグ
	int nowStage;						//現在ステージ



public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(Object* pSender);

    // タッチ関係のイベント
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
