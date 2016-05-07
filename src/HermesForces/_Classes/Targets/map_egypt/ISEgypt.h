#ifndef __IS_EGYPT_H__
#define __IS_EGYPT_H__

#include "../IUnit.h"

class IsEgypt : public IUnit
{
public:
	IsEgypt(const int& idTag, const cocos2d::Point& p);
	const int& die();
	const int& beDetected() override;
};

#endif