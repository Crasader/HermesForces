#include "IsManHole.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"
#include "../Target.h"
//TARGET_EGYPT_CIVILIANS 437
IsManHole::IsManHole(const int& idTag, const cocos2d::Point& p) : IUnit(idTag,p)
{
	_targetUnit = Sprite::createWithSpriteFrameName( "drain_cover.png" );

	_targetUnit->setPosition(Point(p.x, (p.y  * 0.5) + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	
	setPhysicsBody(_targetUnit->getContentSize()  * 1.2);
	//_targetUnit->setOpacity(0);
	//_targetBody->setEnabled(false);
	
	_underHole = Sprite::createWithSpriteFrameName("ene.png");
	_underHole->setScale(Land::deltaScale);
	_underHole->setPosition(Point(p.x, (p.y  * 0.5) - (78 * Land::deltaScale))); // distance from drain and hole
	_underHole->setOpacity(0);
	Land::parentLayer->addChild(_underHole, 2954);
	_isDead = false;
	_beingDetected = false;
}

const int& IsManHole::die()
{
	MapProcessor::Instance()->playSoundEffectTargetDie();
	this->disable();
	_underHole->setOpacity(255);
	_isDead = true;
	Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(0); // die = 0
	Animation* animation = Animation::createWithSpriteFrames(frames, 0.1);
	Animate* animate = Animate::create(animation);
	_underHole->runAction(animate);

	return DESTROY_ENEMY_GOODKILL;
}

const int& IsManHole::beDetected()
{
	if (_isDisable)
		return BE_DEAD_NO_DETECT;

	_beingDetected = true;
	//auto fadeIn = FadeIn::create(0.25f);
	_underHole->setOpacity(255);
	auto fadeOut = FadeOut::create(0.5f);
	auto seq = Sequence::create(fadeOut, CallFunc::create(CC_CALLBACK_0(IsManHole::endDetected, this)), nullptr);
	//Sequence* sequenceDisapeared = Sequence::create(actionFade, CallFunc::create(CC_CALLBACK_0(IsIraq::disable, this)), nullptr);
	_underHole->runAction(seq);

	return BE_DETECTED;
}

const bool& IsManHole::updatePositionToTheLeft()
{
	_targetUnit->setPositionX(_targetUnit->getPositionX() - Land::pixelOfTargetMoving);
	_underHole->setPositionX(_targetUnit->getPositionX());
		
	if (_targetUnit->getPositionX() < 0){
		if (_isEnemies){
			if (!_isDead)
				Land::thisPointer->stopMoveLand();
		}
		else
			this->disable();
		return false;
	}
	return true;
}

void IsManHole::endDetected()
{
	_beingDetected = false;
}
