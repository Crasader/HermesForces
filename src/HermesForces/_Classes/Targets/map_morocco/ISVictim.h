#ifndef __IS_VICTIM_H__
#define __IS_VICTIM_H__

#include "../IUnit.h"

class IsVictim : public IUnit
{
public:
	IsVictim(const int& idTag, const cocos2d::Point& p);
	const int& die();
};

#endif