#ifndef __BOMB_WARNING_H__
#define __BOMB_WARNING_H__

#include "../IUnit.h"

class BombWarning : public IUnit
{
public:
	BombWarning(const int& idTag, const cocos2d::Point& p);
	const int& die();
	const int& beDetected() override;
};

#endif