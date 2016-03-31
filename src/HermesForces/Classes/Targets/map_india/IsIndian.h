#ifndef __INDIAN_H__
#define __INDIAN_H__

#include "../IUnit.h"

class IsIndian : public IUnit
{
public:
	IsIndian(const int& idTag, const cocos2d::Point& p);
	const int& die();
	const int& beDetected() override;
};

#endif