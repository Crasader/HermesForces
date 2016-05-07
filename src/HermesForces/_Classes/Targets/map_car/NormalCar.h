#ifndef __NORMAL_CAR_H__
#define __NORMAL_CAR_H__

#include "../IUnit.h"

class NormalCar : public IUnit
{
public:
	NormalCar(const int& idTag,const cocos2d::Point& p);
	const int& die();
	void startMoving() override;
};

#endif