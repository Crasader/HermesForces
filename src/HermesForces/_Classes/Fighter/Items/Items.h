#ifndef __BOOM_H__
#define __BOOM_H__

#include "define.h"
#include "B52Bomb.h"
//#include "MachineGunBullet.h"
#include "FireBomb.h"
#include "BombSquad.h"
#include "SpecialForce.h"
#include "MarineBomb.h"
#include "IndianSwat.h"

class FighterItems
{
public:
	FighterItems(cocos2d::Layer *layer, const cocos2d::Point& p, const int& type, const  int& idBomb);
	~FighterItems();
	void Fall();
	void hitTarget();
	void hitLand();
	void removeBoom();
	void updatePosition();
	void disapeare();
private:
	IItem* _fighterItem;
};

#endif // __BOOM_H__
