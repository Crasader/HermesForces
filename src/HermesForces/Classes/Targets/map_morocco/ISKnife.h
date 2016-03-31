#ifndef __IS_KNIFE_H__
#define __IS_KNIFE_H__

#include "../IUnit.h"

class IsKnife : public IUnit
{
public:
	IsKnife(const int& idTag, const cocos2d::Point& p);
	const int& die();
	void startMoving() override;
};

#endif