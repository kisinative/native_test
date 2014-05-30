#include "KSAnimation.h"

FiniteTimeAction* KSAnimation::vibrationAnimation(float time)
{
//    MoveBy* move1 = MoveBy::create(0.03, ccp( -5, 0));
//    MoveBy* move2 = MoveBy::create(0.06, ccp( 10, 0));
//    MoveBy* move3 = MoveBy::create(0.03, ccp( -5, 0));
//    Sequence* moves = Sequence::create(move1, move2, move3, NULL);
//	Size size = Director::sharedDirector()->getWinSize();
    Size size = Director::getInstance()->getVisibleSize();

    MoveTo* move = MoveTo::create(time, ccp(0.0, size.height * 0.80));

    return move;
}

FiniteTimeAction* KSAnimation::move1(float time)
{

	int randum = arc4random() % 5;
	Sequence* moves;
	switch (randum){
		case 0:
			//拡大
			moves = Sequence::create(EaseIn::create(ScaleTo::create(1.0f, 2.0f), time / 4), EaseIn::create(ScaleTo::create(2.0f, 1.0f), time / 4), DelayTime::create(time / 2), NULL);
			break;
		case 1:
			//縮小
			moves = Sequence::create(EaseInOut::create(ScaleTo::create(1.0f, 0.1f), time / 4), EaseInOut::create(ScaleTo::create(0.1f, 1.0f), time / 2), DelayTime::create(time / 4), NULL);
			break;
		case 2:
			//一旦ゆっくりになり再進行
			moves = Sequence::create(MoveBy::create(time / 4, ccp( -100, 0 )), MoveBy::create(time / 4, ccp( 100, 0 )), NULL);
			break;
		case 3:
			//上下に移動
//			moves = RepeatForever::create(Sequence::create(MoveBy::create(time / 8, ccp( 0, -50 )), MoveBy::create(time / 8, ccp( 0, 50 )), NULL));
			moves = Sequence::create(MoveBy::create(time / 8, ccp( 0, -50 )), MoveBy::create(time / 8, ccp( 0, 50 )), NULL);
			break;
		case 4:
			//点滅
			moves = Sequence::create(Blink::create(time,6), NULL);
			break;
	}


    return Repeat::create(moves, 3);
}


FiniteTimeAction* KSAnimation::hpAction()
{
    MoveBy* move1 = MoveBy::create(0.04, ccp( 0, -5));
    MoveBy* move2 = MoveBy::create(0.08, ccp( 0, 10));
    MoveBy* move3 = MoveBy::create(0.04, ccp( 0, -5));
//    ActionInterval* move4  = ScaleTo::create(0.5, pointScale);

//    Sequence* moves = Sequence::create(move1, move2, move3, move4, NULL);
    Sequence* moves = Sequence::create(move1, move2, move3, NULL);

    return Repeat::create(moves, 2);
}
FiniteTimeAction* KSAnimation::bgAction()
{
    MoveBy* move1 = MoveBy::create(0.04, ccp( -10, -5));
    MoveBy* move2 = MoveBy::create(0.08, ccp(  20, 10));
    MoveBy* move3 = MoveBy::create(0.04, ccp( -10, -5));

    Sequence* moves = Sequence::create(move1, move2, move3, NULL);

    return Repeat::create(moves, 2);
}

FiniteTimeAction* KSAnimation::rushCutin()
{

	Point origin			= Director::getInstance()->getVisibleOrigin();
	Size  visibleSize		= Director::getInstance()->getVisibleSize();

//	EaseInOut* move1 = EaseInOut::create(MoveTo::create(0.2, ccp( origin.x, visibleSize.height * 0.45)), 2);
	MoveTo* move1 = MoveTo::create(0.3, ccp( origin.x, visibleSize.height * 0.45));
    DelayTime* move2 = DelayTime::create(1.0f);
    MoveTo* move3 = MoveTo::create(0.2, ccp( -800, visibleSize.height * 0.45));

    Sequence* moves = Sequence::create(move1, move2, move3, NULL);

    return Repeat::create(moves, 1);
}

FiniteTimeAction* KSAnimation::enemyJump(int enemyType)
{

	Sequence* moves;
	JumpBy* jump1;
	JumpBy* jump2;
	MoveBy* move1;
	MoveBy* move2;
	CCLOG("enemyType = %d",enemyType);
	switch (enemyType){
		case 0:			//ボス
			jump1 = JumpBy::create(0.7, ccp( 100, 0),50,2);
		    move1 = MoveBy::create(0.5, ccp(-100, 0));
		    moves = Sequence::create(jump1, move1, NULL);
			break;
		case 1:			//サビ
			jump1 = JumpBy::create(0.7, ccp( 100, 0),50,1);
			jump2 = JumpBy::create(0.7, ccp(-100, 0),50,1);
		    moves = Sequence::create(jump1, jump2, NULL);
			break;
		case 2:			//三毛
		    move1 = MoveBy::create(1, ccp( 50, 0));
		    move2 = MoveBy::create(1, ccp(-50, 0));
		    moves = Sequence::create(move1, move2, NULL);
			break;
		case 3:			//クロ
			jump1 = JumpBy::create(1, ccp( -60, 0),30,2);
			jump2 = JumpBy::create(1, ccp( 120, 0),40,3);
			jump1 = JumpBy::create(1, ccp( -60, 0),30,2);
		    moves = Sequence::create(jump1, jump2, NULL);
			break;
		case 4:			//シャム
		    move1 = MoveBy::create(0.5, ccp( 90, 0));
			jump1 = JumpBy::create(0.7, ccp(-90, 0),30,3);
		    moves = Sequence::create(move1, jump1, NULL);
			break;
	}

    return RepeatForever::create(moves);
}
