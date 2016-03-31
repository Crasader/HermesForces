#ifndef __SERIOUS_BOX_H__
#define __SERIOUS_BOX_H__

#include "../IUnit.h"

class SeriousBoxTrain : public IUnit
{
public:
	SeriousBoxTrain(int idTag,cocos2d::Point p, int distanceNumber);
	const int& die();
};

#endif