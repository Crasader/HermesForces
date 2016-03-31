#ifndef __FAKED_CAR_H__
#define __FAKED_CAR_H__

#include "../IUnit.h"

class FakedCar : public IUnit
{
public:
	FakedCar(const int&  idTag, const cocos2d::Point& p);
	const int& die();
	void startMoving() override;
};

#endif