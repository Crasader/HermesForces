#ifndef __FIRE_BOOM_H__
#define __FIRE_BOOM_H__

#include "IItem.h"

class FireBomb : public IItem{
public:
	FireBomb(cocos2d::Layer *layer, const cocos2d::Point&  point, const  int& idBomb);
	void hitTarget();
	void hitLand();
};

#endif // __B52BOOM_H__