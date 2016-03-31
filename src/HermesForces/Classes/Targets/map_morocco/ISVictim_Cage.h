#ifndef __IS_VICTIM_CAGE_H__
#define __IS_VICTIM_CAGE_H__

#include "../IUnit.h"

class IsCageVictim : public IUnit
{
public:
	IsCageVictim(const int& idTag, const cocos2d::Point& p);
	const int& die();
};

#endif