#ifndef __IS_SYRIA_H__
#define __IS_SYRIA_H__

#include "../IUnit.h"

class ISSyria : public IUnit
{
public:
	ISSyria(const int& idTag, const cocos2d::Point& p);
	const int& die();
	void startMoving() override;
};

#endif