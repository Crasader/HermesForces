#ifndef __CIVI_EGYPT_H__
#define __CIVI_EGYPT_H__

#include "../IUnit.h"

class CiviEgypt : public IUnit
{
public:
	CiviEgypt(const int& idTag, const cocos2d::Point& p);
	const int& die();
	const int& beDetected() override;
};

#endif