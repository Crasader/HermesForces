#ifndef __VIEW_FINDER_H__
#define __VIEW_FINDER_H__

#include "cocos2d.h"
USING_NS_CC;

class ViewFinder{
public:
	ViewFinder( cocos2d::Layer *layer, const cocos2d::Point&  pStart);
	void Shoot(const cocos2d::Point& pTo);
	void disable();
protected:
	cocos2d::Sprite* _viewer;
	cocos2d::Sprite* _bullet;
	FadeOut* _bulletAppeare;
	PhysicsBody* _bulletPb;
	Sequence* _sequenceDisapeared;
};

#endif // __VIEW_FINDER_H__