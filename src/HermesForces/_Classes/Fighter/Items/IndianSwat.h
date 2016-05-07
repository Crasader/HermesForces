#ifndef __INDIA_SWAT_H__
#define __INDIA_SWAT_H__

#include "IItem.h"

class IndianSwat : public IItem{
public:
	IndianSwat(cocos2d::Layer *layer, const cocos2d::Point&  point, const int& idBomb);
	void hitTarget();
	void hitLand();
private:
	bool _isGoodHit;
};

#endif // __INDIA_SWAT_H__