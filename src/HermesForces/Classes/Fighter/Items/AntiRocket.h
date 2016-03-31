#ifndef __ANTI_ROCKET_H__
#define __ANTI_ROCKET_H__

#include "define.h"
#define FIGHTER_BOX_ANTI_ROCKET 20
USING_NS_CC;

class AntiRocket{
public:
	AntiRocket( cocos2d::Layer *layer, const cocos2d::Point&  pStart, const int& idTag);
	void MoveToPos(const cocos2d::Point& pTo);
	void removeAntiRocket();
	void hitRocket();
protected:
	cocos2d::Sprite* _antiRocketItem;
    cocos2d::PhysicsBody* _antiRocketBody;
};

#endif // __ANTI_ROCKET_H__