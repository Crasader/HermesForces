#ifndef __AL_QUEDA_VICTIM_H__
#define __AL_QUEDA_VICTIM_H__

#include "../IUnit.h"

class AlQuedaVictim : public IUnit
{
public:
	AlQuedaVictim(const int& idTag, const cocos2d::Point& p);
	const int& die();
private:
	int _deathHit;
};

#endif