#ifndef __IS_MOROCCO_H__
#define __IS_MOROCCO_H__

#include "../IUnit.h"

class IsMorocco : public IUnit
{
public:
	IsMorocco(const int& idTag, const cocos2d::Point& p);
	const int& die();
	void startMoving() override;
	//void shoot();
	const bool& updatePositionToTheLeft();
private:
	bool _isShouldShoot;
};

#endif