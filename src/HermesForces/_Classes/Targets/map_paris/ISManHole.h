#ifndef __IS_PARIS_H__
#define __IS_PARIS_H__

#include "../IUnit.h"

class IsManHole : public IUnit
{
public:
	IsManHole(const int& idTag, const cocos2d::Point& p);
	const int& die();
	const int& beDetected() override;
	//void returnManHoleOnly();
	const bool& updatePositionToTheLeft() override;
	void endDetected();
private:
	Sprite* _underHole;
	bool _beingDetected;
};

#endif