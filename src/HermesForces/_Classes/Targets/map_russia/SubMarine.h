#ifndef __IS_RUSSIA_H__
#define __IS_RUSSIA_H__

#include "../IUnit.h"

class SubMarine : public IUnit
{
public:
	SubMarine(int idTag,cocos2d::Point p);
	const int& die();
	void hitMainCharacter() override;
	const bool& updatePositionToTheLeft() override;
	void attackMainCharacter();
	void disableRocket();
	//void disapeareSubMarine();

	//void clean() override;
private:
	cocos2d::Sprite* _rocket;
	cocos2d::Sprite* _underMarine;
	cocos2d::PhysicsBody* bodyRocket;
	bool _isFireRocket;

};

#endif