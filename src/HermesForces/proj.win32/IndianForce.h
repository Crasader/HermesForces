#ifndef __INDIAN_FORCE_H__
#define __INDIAN_FORCE_H__

#include "IItem.h"

class BombSquad : public IItem{
public:
	BombSquad(cocos2d::Layer *layer, cocos2d::Point  point, int idBomb);
	void hitTarget();
	void hitLand();
};

#endif // __B52BOOM_H__