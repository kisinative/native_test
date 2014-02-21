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
	void defense(int flag);
	void miss(bool flag);
	void setup();
	void createLabel(std::string labelString, float labelSize, float labelWidth, float labelHeight, int labelTag);
	void makeRetryButton();
	void tapRetryButton(Node *node);
	void arrowRefresh();

	// tag
	const int tagHp				= 10;		//HPタグ
	const int tagHpImg			= 11;		//HPタグ
	const int tagEnemyHp		= 20;		//敵HPタグ
	const int tagEnemyHpImg		= 21;		//敵HPタグ
	const int tagEnemyStrong	= 22;		//敵体力タグ
	const int tagEnemyPower		= 24;		//敵攻撃力タグ
	const int tagEnemySpeed		= 26;		//敵スピードタグ
	const int tagEnemyTechnique	= 28;		//敵テクニックタグ
	const int tagTargetImg	 	= 80;		//ターゲットタグ
	const int tagArrowLabel 	= 100;		//矢印タグ
	const int tagRetry		 	= 110;		//リトライタグ
	const int tagArrowImg	 	= 1000;		//矢印タグ

	//敵基本能力
	const int defaultEnemyStrong = 15;		//体力
	const int defaultEnemyPower  = 10;		//攻撃力
	const float defaultEnemySpeed  = 3.1;	//スピード
	const int defaultEnemyTechnique  = 20;	//テクニック

	//敵レベル
	int enemyStrongLv;
	int enemypowerLv;
	int enemySpeedLv;
	int enemyTechniqueLv;

	//HP関連
	const int MaxHp			= 100;          //最大HP
	int NowHp;                              //現在HP
	int NowEnemyHp;                         //敵現在HP
	int MaxEnemyHp;                         //敵最大HP
	int NowEnemyRush;						//現在ラッシュポイント

	//フラグ類
	std::string migi = "0";                 //入力中ジェスチャ
	std::string hidari = "1";				//入力中ジェスチャ
	std::string ue = "2";                   //入力中ジェスチャ
	std::string sita = "3";                 //入力中ジェスチャ
	std::string targetGesture;              //現在ジェスチャ
	std::string nowGesture;                 //入力中ジェスチャ
	bool atkDefFlag;                        //攻撃防御フラグ
	int nowStage;                           //現在ステージ
    std::vector<std::string> moveArrow;		//移動中矢印
    std::vector<int> moveAtkDef;			//移動中矢印
	int atkCount;                           //攻撃数
	int frontArrowTag;                      //先頭矢印タグ
	int rushCount;							//残りラッシュ数



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
