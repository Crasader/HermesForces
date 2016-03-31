#ifndef __AL_QUEDA_FIRE_H__
#define __AL_QUEDA_FIRE_H__

#include "../IUnit.h"

class AlQuedaFire : public IUnit
{
public:
	AlQuedaFire(const int& idTag, const cocos2d::Point& p);
	const int& die();
	void startMoving() override;
private:
	int _deathHit;
};

#endif