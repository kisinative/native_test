#ifndef __KSANIMATION_H__
#define __KSANIMATION_H__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_ACTION 1001

class KSAnimation
{
public:
    static FiniteTimeAction* vibrationAnimation(float time);
};

#endif // __KSANIMATION_H__
