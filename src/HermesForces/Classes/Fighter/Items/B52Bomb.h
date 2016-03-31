#ifndef __B52BOOM_H__
#define __B52BOOM_H__

#include "IItem.h"

class B52Bomb : public IItem{
public:
	B52Bomb(cocos2d::Layer *layer, const cocos2d::Point&  point, const  int& idBomb, const bool& isChina = false);
	void hitTarget();
	void hitLand();
	/*private:
	bool _isGoodHit;*/
//	Point _end_point;
};

#endif // __B52BOOM_H__