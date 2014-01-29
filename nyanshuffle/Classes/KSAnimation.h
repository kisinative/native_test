#ifndef __KSANIMATION_H__
#define __KSANIMATION_H__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_ACTION 1001

class KSAnimation
{
public:
    // Chapter 6.3で説明した内容
    static FiniteTimeAction* catStartAction();

    // Chapter 6.4で説明した内容
    static FiniteTimeAction* vibrationAnimation();
    static FiniteTimeAction* boxesStartAction(Object* target, SEL_CallFunc selector);
    static FiniteTimeAction* boxesStartActionWithVibration(Object* target, SEL_CallFunc selector);

    // Chapter 6.5で追記する内容
    static FiniteTimeAction* num3Animation();
    static FiniteTimeAction* num2Animation();
    static FiniteTimeAction* num1Animation();
    static FiniteTimeAction* num0Animation(Object* target, SEL_CallFunc selector);

    // Chapter 6.6で追記する内容
    static FiniteTimeAction* moveFromLeftToCenter(float time);
    static FiniteTimeAction* moveFromLeftToRight(float time);
    static FiniteTimeAction* moveFromCenterToLeft(float time);
    static FiniteTimeAction* moveFromCenterToRight(float time);
    static FiniteTimeAction* moveFromRightToLeft(float time);
    static FiniteTimeAction* moveFromRightToCenter(float time);

    // Chapter 6.7で追記する内容
    static FiniteTimeAction* catEndAction();

    // Chapter 6.8で追記する内容
    static FiniteTimeAction* resultAnimation(Object* target, SEL_CallFunc selector);
};

#endif // __KSANIMATION_H__
