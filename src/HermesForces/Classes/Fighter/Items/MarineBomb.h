#ifndef __MARINE_BOOM_H__
#define __MARINE_BOOM_H__

#include "IItem.h"

class MarineBomb : public IItem{
public:
	MarineBomb(cocos2d::Layer *layer, const cocos2d::Point&  point, const int& idBomb);
	void hitTarget();
	void hitLand();
};

#endif // __B52BOOM_H__