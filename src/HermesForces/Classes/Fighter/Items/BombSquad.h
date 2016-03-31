#ifndef __BOMB_SQUAD_H__
#define __BOMB_SQUAD_H__

#include "IItem.h"

class BombSquad : public IItem{
public:
	BombSquad(cocos2d::Layer *layer, const cocos2d::Point&  point, const int& idBomb);
	void hitTarget();
	void hitLand();
private:
	bool _isGoodHit;
};

#endif // __B52BOOM_H__