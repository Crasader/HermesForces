#ifndef __IS_FIRE_H__
#define __IS_FIRE_H__

#include "../IUnit.h"

class IsFire : public IUnit
{
public:
	IsFire(const int& idTag, const cocos2d::Point& p);
	const int& die();
	void startMoving() override;
};

#endif