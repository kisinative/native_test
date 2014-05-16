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
	void tapRetryButton(Object* pSender);
	void arrowRefresh();
	void meDamage();
	void rushPoint(bool flag);
	void menuStartRush();
	void firstRandomTarget(float time);
	void randomTarget();
	void rushEnd(float time);
	void tapReturnMenu(Object* pSender);
	void tapNextLv(Object* pSender);
	void catChenge(int flag);
	void catChenge0();
	void catChenge1();
	void catChenge2();
	void enemyAtk();
	void enemyDef(bool flag);
	void moveGameOver();
	void moveWinner();

	// tag
	const int tagHp				= 10;		//HPタグ
	const int tagHpImg			= 11;		//HPタグ
	const int tagEnemyHp		= 20;		//敵HPタグ
	const int tagEnemyHpImg		= 21;		//敵HPタグ
	const int tagEnemyStrong	= 22;		//敵体力タグ
	const int tagEnemyPower		= 24;		//敵攻撃力タグ
	const int tagEnemySpeed		= 26;		//敵スピードタグ
	const int tagEnemyTechnique	= 28;		//敵テクニックタグ

	const int tagThumbnailImg		= 30;	//自キャラサムネイル
	const int tagEnemyThumbnail	= 31;   //敵キャラサムネイル
	const int tagEnemyImg		= 50;		//敵戦闘画像

	const int tagTargetImg	 	= 80;		//ターゲットタグ
	const int tagTargetImgSub1	= 85;		//ターゲットタグ
	const int tagTargetImgSub2	= 86;		//ターゲットタグ
	const int tagArrowLabel 	= 100;		//矢印タグ
	const int tagRetry		 	= 110;		//リトライタグ
	const int tagRushButton 	= 120;		//ラッシュボタンタグ
	const int tagRushMenu	 	= 125;		//ラッシュボタンタグ
	const int tagRushTarget	= 130;		//ラッシュターゲットタグ
	const int tagRushCutin		= 140;		//ラッシュカットインタグ
	const int tagNextButton	= 150;		//NEXTステージボタン
	const int tagMenutButton	= 160;		//メニューボタン
	const int tagArrowImg	 	= 1000;		//矢印タグ
	const int tagComboCount	= 170;		//コンボ数タグ

	//敵基本能力
	const int defaultEnemyStrong = 40;		//体力
	const int defaultEnemyPower  = 10;		//攻撃力
	const float defaultEnemySpeed  = 3.1;	//スピード
	const int defaultEnemyTechnique  = 20;	//テクニック

	//攻撃力
	const int normalAtk 			= 3;	//通常攻撃
	const int justAtk				= 5;	//ジャストヒット
	const int rushAtk				= 1;	//ラッシュ攻撃

	//プレイヤーレベル
	int playerStrongLv;
	int playerPowerLv;
	int playerSpeedLv;
	int playerTechniqueLv;

	//敵レベル
	int enemyLv;
	int enemyType;
	int enemyStrongLv;
	int enemypowerLv;
	int enemySpeedLv;
	int enemyTechniqueLv;

	//HP関連
	const int MaxHp			= 100;          //最大HP
	int NowHp;                              //現在HP
	int NowRush;							//現在ラッシュポイント
	int NowEnemyHp;                         //敵現在HP
	int MaxEnemyHp;                         //敵最大HP
	int NowEnemyRush;						//現在ラッシュポイント

	//フラグ類
	std::string migi = "0";                 //入力中ジェスチャ
	std::string hidari = "1";				//入力中ジェスチャ
	std::string ue = "2";                   //入力中ジェスチャ
	std::string sita = "3";                 //入力中ジェスチャ
	const int startRushConst = 7;			//自ラッシュ開始ポイント
	int		startRush;						//自ラッシュ開始ポイント
	int		startEnemyRush = 20;			//敵ラッシュ開始ポイント
	bool	rushStack = false;				//ラッシュ開始可能状況判定フラグ
	bool	rush_flag = false;				//ラッシュ判定フラグ
	float	rushTime  = 6.0;				//ラッシュ時間
	bool	noMissFlag  = true;				//ノーミスフラグ
	int		conboCount = 0;					//コンボカウント
	int		maxConboCount = 0;				//MAXコンボカウント

	std::string targetGesture;              //現在ジェスチャ
	std::string nowGesture;                 //入力中ジェスチャ
	bool atkDefFlag;                        //攻撃防御フラグ
	int nowStage;                           //現在ステージ
    std::vector<std::string> moveArrow;		//移動中矢印
    std::vector<int> moveAtkDef;			//移動中矢印
	int atkCount;                          //攻撃数
	int frontArrowTag;                     //先頭矢印タグ
	int rushCount;							//残りラッシュ数

	//配置
	cocos2d::Point	origin;										//使用端末の(0,0)地点
	cocos2d::Size	visibleSize;								//使用端末の画面サイズ
	float			rushButton_y		= -100.0;				//ラッシュボタン
	float			nextLvButton_y		= 250.0;				//ネクストレベルボタン
	float			returnMenuButton_y	= 250.0;				//メニューボタン


	//プリファレンス
	const char* key_enemyLv			= "EnemyLv";			//敵レベル
	const char* key_playEnemyLv		= "PlayEnemyLv";		//対戦中敵レベル
	const char* key_playerExp			= "PlayerExp";			//プレイヤー経験値
	const char* key_playerStrongLv		= "PlayerStrong";		//プレイヤー体力
	const char* key_playerPowerLv		= "PlayerPower";		//プレイヤー攻撃力
	const char* key_playerSpeedLv		= "PlayerSpeed";		//プレイヤースピード
	const char* key_playerTechniqueLv	= "PlayerTechnique";	//プレイヤーテクニック
	const char* key_maxComboCount		= "MaxConboCount";		//MAXコンボ数
	const char* key_noMissFlag			= "NoMissFlag";			//ノーミスフラグ


//	int enemyStrongLv;
//	int enemypowerLv;
//	int enemySpeedLv;
//	int enemyTechniqueLv;

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
