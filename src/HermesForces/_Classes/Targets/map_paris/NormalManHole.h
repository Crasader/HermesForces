#ifndef __NORMAL_MANHOLD_H__
#define __NORMAL_MANHOLD_H__

#include "../IUnit.h"

class NormalManHole : public IUnit
{
public:
	NormalManHole(const int& idTag, const cocos2d::Point& p);
	const int& die();
	//void returnManHoleOnly();
	const bool&  updatePositionToTheLeft() override;
private:
	Sprite* _underHole;
};

#endif