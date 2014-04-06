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

FiniteTimeAction* KSAnimation::hpAction(float pointScale)
{
    MoveBy* move1 = MoveBy::create(0.03, ccp( 0, -5));
    MoveBy* move2 = MoveBy::create(0.06, ccp( 0, 10));
    MoveBy* move3 = MoveBy::create(0.03, ccp( 0, -5));
//    ActionInterval* move4  = ScaleTo::create(0.5, pointScale);

//    Sequence* moves = Sequence::create(move1, move2, move3, move4, NULL);
    Sequence* moves = Sequence::create(move1, move2, move3, NULL);

    return Repeat::create(moves, 2);
}

FiniteTimeAction* KSAnimation::rushCutin()
{

	Point origin			= Director::getInstance()->getVisibleOrigin();
	Size  visibleSize		= Director::getInstance()->getVisibleSize();

//	EaseInOut* move1 = EaseInOut::create(MoveTo::create(0.2, ccp( origin.x, visibleSize.height * 0.45)), 2);
	MoveTo* move1 = MoveTo::create(0.2, ccp( origin.x, visibleSize.height * 0.45));
    DelayTime* move2 = DelayTime::create(0.6f);
    MoveTo* move3 = MoveTo::create(0.2, ccp( -800, visibleSize.height * 0.45));

    Sequence* moves = Sequence::create(move1, move2, move3, NULL);

    return Repeat::create(moves, 1);
}

