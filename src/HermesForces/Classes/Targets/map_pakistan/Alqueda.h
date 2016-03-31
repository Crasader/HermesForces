#ifndef __AL_QUEDA_H__
#define __AL_QUEDA_H__

#include "../IUnit.h"

class AlQueda : public IUnit
{
public:
	AlQueda(const int& idTag, const cocos2d::Point& p);
	const int& die();
	void startMoving() override;
	//void shootSound();
private:
	int _deathHit;
};

#endif