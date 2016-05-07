#ifndef __SWAT_H__
#define __SWAT_H__

#include "IItem.h"

class SpecialForce : public IItem{
public:
	// TODO : change int -> const int&
	SpecialForce(cocos2d::Layer *layer, const cocos2d::Point&  point, const int& idBomb);
	void hitTarget();
	void hitLand();
	void shootBangBang();
private:
	bool _isGoodHit;
	//Sprite* _bgNight;
	bool _isShow;
};

#endif // __B52BOOM_H__