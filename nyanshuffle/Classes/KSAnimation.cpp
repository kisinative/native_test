#include "KSAnimation.h"

#define WIN_WIDTH  Director::sharedDirector()->getWinSize().width
#define WIN_HEIGHT Director::sharedDirector()->getWinSize().height

#define BOX_LOC_LEFT   ccp(WIN_WIDTH * 0.2, WIN_HEIGHT * 0.5)
#define BOX_LOC_CENTER ccp(WIN_WIDTH * 0.5, WIN_HEIGHT * 0.5)
#define BOX_LOC_RIGHT  ccp(WIN_WIDTH * 0.8, WIN_HEIGHT * 0.5)

#define CONTROL_POINT_X1 WIN_WIDTH * 0.25
#define CONTROL_POINT_X2 WIN_WIDTH * 0.45
#define CONTROL_POINT_X3 WIN_WIDTH * 0.55
#define CONTROL_POINT_X4 WIN_WIDTH * 0.75

#define CONTROL_POINT_Y1 WIN_HEIGHT * 0.8
#define CONTROL_POINT_Y2 WIN_HEIGHT * 0.2
#define CONTROL_POINT_Y3 WIN_HEIGHT * 0.65
#define CONTROL_POINT_Y4 WIN_HEIGHT * 0.35

FiniteTimeAction* KSAnimation::catStartAction()
{
    SkewTo* skew1 = SkewTo::create(0.2,  1, 0);
    SkewTo* skew2 = SkewTo::create(0.2, -1, 0);
    Sequence* seq = Sequence::createWithTwoActions(skew1, skew2);
    Repeat* repeat = Repeat::create(seq, 10);
    Hide* hide = Hide::create();
    
    return Sequence::createWithTwoActions(repeat, hide);;
}

FiniteTimeAction* KSAnimation::vibrationAnimation()
{
    MoveBy* move1 = MoveBy::create(0.03, ccp( -5, 0));
    MoveBy* move2 = MoveBy::create(0.06, ccp( 10, 0));
    MoveBy* move3 = MoveBy::create(0.03, ccp( -5, 0));
    Sequence* moves = Sequence::create(move1, move2, move3, NULL);
    
    return Repeat::create(moves, 2);
}

FiniteTimeAction* KSAnimation::boxesStartAction(Object* target, SEL_CallFunc selector)
{
    Size size = Director::sharedDirector()->getWinSize();
    
    int randum = rand();
    
    float delayTime = 1;
    
    switch (randum % 5)
    {
        case 0:  delayTime = delayTime * 0.90; break;
        case 1:  delayTime = delayTime * 0.95; break;
        case 2:  delayTime = delayTime * 1.05; break;
        case 3:  delayTime = delayTime * 1.10; break;
        default: break;
    }
    
    DelayTime* delay1 = DelayTime::create(delayTime);
    MoveBy* move1 = MoveBy::create(1, ccp(0, - size.height));
    EaseIn* ease1 = EaseIn::create(move1, 10);
    
    DelayTime* delay2 = DelayTime::create(0.9);
    CallFunc* func = CallFunc::create(target, selector);
    FiniteTimeAction* seq = Sequence::createWithTwoActions(delay2, func);
    
    Spawn* spawn = Spawn::createWithTwoActions(ease1, seq);
    
    return Sequence::createWithTwoActions(delay1, spawn);
}

FiniteTimeAction* KSAnimation::boxesStartActionWithVibration(Object* target, SEL_CallFunc selector)
{
    FiniteTimeAction* action1 = boxesStartAction(target, selector);
    FiniteTimeAction* action2 = KSAnimation::vibrationAnimation();
    
    return Sequence::createWithTwoActions(action1, action2);
}

FiniteTimeAction* KSAnimation::num3Animation()
{
    DelayTime* delay1  = DelayTime::create(0.5);
    ScaleTo* scaleUp   = ScaleTo::create(0.1, 1);
    DelayTime* delay2  = DelayTime::create(0.3);
    ScaleTo* scaleDown = ScaleTo::create(0.1, 0);
    
    return Sequence::create(delay1, scaleUp, delay2, scaleDown, NULL);
}

FiniteTimeAction* KSAnimation::num2Animation()
{
    DelayTime* delay = DelayTime::create(1);
    
    return Sequence::create(delay, KSAnimation::num3Animation(), NULL);
}

FiniteTimeAction* KSAnimation::num1Animation()
{
    DelayTime* delay = DelayTime::create(2);
    
    return Sequence::create(delay, KSAnimation::num3Animation(), NULL);
}

FiniteTimeAction* KSAnimation::num0Animation(Object* target, SEL_CallFunc selector)
{
    DelayTime* delay = DelayTime::create(3);
    CallFunc* func = CallFunc::create(target, selector);
    
    return Sequence::create(delay, KSAnimation::num3Animation(), func, NULL);
}

FiniteTimeAction* KSAnimation::moveFromLeftToCenter(float time)
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(CONTROL_POINT_X1, CONTROL_POINT_Y1);
    bezier.controlPoint_2 = ccp(CONTROL_POINT_X2, CONTROL_POINT_Y1);
    bezier.endPosition = BOX_LOC_CENTER;
    
    FiniteTimeAction* action = BezierTo::create(time, bezier);
    action->setTag(TAG_ACTION);
    
    return action;
}

FiniteTimeAction* KSAnimation::moveFromLeftToRight(float time)
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(CONTROL_POINT_X1, CONTROL_POINT_Y1);
    bezier.controlPoint_2 = ccp(CONTROL_POINT_X4, CONTROL_POINT_Y1);
    bezier.endPosition = BOX_LOC_RIGHT;
    
    FiniteTimeAction* action = BezierTo::create(time, bezier);
    action->setTag(TAG_ACTION);
    
    return action;
}

FiniteTimeAction* KSAnimation::moveFromCenterToLeft(float time)
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(CONTROL_POINT_X2, CONTROL_POINT_Y2);
    bezier.controlPoint_2 = ccp(CONTROL_POINT_X1, CONTROL_POINT_Y2);
    bezier.endPosition = BOX_LOC_LEFT;
    
    FiniteTimeAction* action = BezierTo::create(time, bezier);
    action->setTag(TAG_ACTION);
    
    return action;
}

FiniteTimeAction* KSAnimation::moveFromCenterToRight(float time)
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(CONTROL_POINT_X3, CONTROL_POINT_Y1);
    bezier.controlPoint_2 = ccp(CONTROL_POINT_X4, CONTROL_POINT_Y1);
    bezier.endPosition = BOX_LOC_RIGHT;
    
    FiniteTimeAction* action = BezierTo::create(time, bezier);
    action->setTag(TAG_ACTION);
    
    return action;
}

FiniteTimeAction* KSAnimation::moveFromRightToLeft(float time)
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(CONTROL_POINT_X4, CONTROL_POINT_Y2);
    bezier.controlPoint_2 = ccp(CONTROL_POINT_X1, CONTROL_POINT_Y2);
    bezier.endPosition = BOX_LOC_LEFT;
    
    FiniteTimeAction* action = BezierTo::create(time, bezier);
    action->setTag(TAG_ACTION);
    
    return action;
}

FiniteTimeAction* KSAnimation::moveFromRightToCenter(float time)
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(CONTROL_POINT_X4, CONTROL_POINT_Y2);
    bezier.controlPoint_2 = ccp(CONTROL_POINT_X3, CONTROL_POINT_Y2);
    bezier.endPosition = BOX_LOC_CENTER;
    
    FiniteTimeAction* action = BezierTo::create(time, bezier);
    action->setTag(TAG_ACTION);
    
    return action;
}

FiniteTimeAction* KSAnimation::catEndAction()
{
    Show* show = Show::create();
    SkewTo* skew1 = SkewTo::create(0.2,  1, 0);
    SkewTo* skew2 = SkewTo::create(0.2, -1, 0);
    Sequence* seq = Sequence::createWithTwoActions(skew1, skew2);
    Repeat* repeat = Repeat::create(seq, 10000);
    
    return Sequence::createWithTwoActions(show, repeat);
}

FiniteTimeAction* KSAnimation::resultAnimation(Object* target, SEL_CallFunc selector)
{
    ScaleTo* scaleUp = ScaleTo::create(0.5, 1);
    DelayTime* delay = DelayTime::create(1);
    CallFunc* func = CallFunc::create(target, selector);
    
    return Sequence::create(scaleUp, delay, func, NULL);
}
