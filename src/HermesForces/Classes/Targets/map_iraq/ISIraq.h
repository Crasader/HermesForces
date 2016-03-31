#ifndef __IS_IRAQ_H__
#define __IS_IRAQ_H__

#include "../IUnit.h"

class IsIraq : public IUnit
{
public:
	IsIraq(const int&  idTag, const cocos2d::Point& p);
	const int& die();
	void startMoving() override;
};

#endif