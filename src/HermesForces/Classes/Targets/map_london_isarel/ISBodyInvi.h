#ifndef __IS_LONDON_H__
#define __IS_LONDON_H__

#include "../IUnit.h"

class ISBodyInvi : public IUnit
{
public:
	ISBodyInvi(const int& idTag, const cocos2d::Point& p);
	const int& die();
	const int& beDetected()  override;
};

#endif