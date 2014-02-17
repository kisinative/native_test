#include "KSAnimation.h"

FiniteTimeAction* KSAnimation::vibrationAnimation(float time)
{
//    MoveBy* move1 = MoveBy::create(0.03, ccp( -5, 0));
//    MoveBy* move2 = MoveBy::create(0.06, ccp( 10, 0));
//    MoveBy* move3 = MoveBy::create(0.03, ccp( -5, 0));
//    Sequence* moves = Sequence::create(move1, move2, move3, NULL);
	Size size = Director::sharedDirector()->getWinSize();

    MoveTo* move = MoveTo::create(time, ccp(0.0, size.height * 0.80));

    return move;
}
