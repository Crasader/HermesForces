#ifndef __IITEM_H__
#define __IITEM_H__

#include "define.h"

USING_NS_CC;

class IItem{
public:
	IItem(cocos2d::Layer *layer, const cocos2d::Point&  pStart, const  int& idTag);
	~IItem();
	void Fall();
	void removeBoom();
	virtual void hitTarget() = 0;
	virtual void hitLand() = 0;
	//void recycle();
	virtual void updatePos();
	void disapeare();
protected:
	cocos2d::Sprite *_fighterItems;
    cocos2d::PhysicsBody* _fighterBody;
	bool isFalling;
	bool _isDisable;
	bool _isHit;
    bool _isHitTarget;
	cocos2d::Point  _pStart;
	int _idTag;
};

#endif // __IITEM_H__