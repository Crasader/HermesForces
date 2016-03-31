#ifndef __AL_QUEDA_ROCKET_H__
#define __AL_QUEDA_ROCKET_H__

#include "../IUnit.h"

class AlQuedaRocket : public IUnit
{
public:
	AlQuedaRocket(const int& idTag, const cocos2d::Point& p);
	const int& die();
	void hitMainCharacter() override;
	//int updatePositionToTheLeft(float deltaMoving) override;
	//int checkPosIsGood();
	const bool& updatePositionToTheLeft() override;

	void attackMainCharacter();
	void disableRocket();

private:
	int _deathHit,_expBombHit;
	cocos2d::Sprite* _rocket;
	cocos2d::PhysicsBody* bodyRocket;
	bool _isFireRocket;
};

#endif