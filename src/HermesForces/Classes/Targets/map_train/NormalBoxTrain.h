#ifndef __NORMAL_BOX_H__
#define __NORMAL_BOX_H__

#include "../IUnit.h"

class NormalBoxTrain : public IUnit
{
public:
	NormalBoxTrain(int idTag,cocos2d::Point p , int distanceNumber);
	const int& die();
};

#endif