#include "NormalManHole.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"
#include "../Target.h"

NormalManHole::NormalManHole(const int& idTag, const cocos2d::Point& p) : IUnit(idTag,p)
{
	_targetUnit = Sprite::createWithSpriteFrameName("drain_cover.png");

	_targetUnit->setPosition(Point(p.x, (p.y  * 0.5) + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	setPhysicsBody(_targetUnit->getContentSize() * 1.2);

	//_targetUnit->setOpacity(0);
	//_targetBody->setEnabled(false);

	_underHole = Sprite::createWithSpriteFrameName("civi.png");
	_underHole->setScale(Land::deltaScale);
	_underHole->setPosition(Point(p.x, (p.y  * 0.5) - (78 * Land::deltaScale)));
	_underHole->setOpacity(0);
	Land::parentLayer->addChild(_underHole, 2954);

}

const int& NormalManHole::die()
{
	this->disable();
	_underHole->setOpacity(255);
	Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(1); // die = 0
	Animation* animation = Animation::createWithSpriteFrames(frames, 0.1);
	Animate* animate = Animate::create(animation);
	_underHole->runAction(RepeatForever::create(animate));
	return DESTROY_ENEMY_DONOTHING;
}

const bool& NormalManHole::updatePositionToTheLeft()
{
	_targetUnit->setPositionX(_targetUnit->getPositionX() - Land::pixelOfTargetMoving);
	if (_isDisable)
		_underHole->setPositionX(_targetUnit->getPositionX());
	if (_targetUnit->getPositionX() < 0){
		this->disable();
		return false;
	}
	return true;
}
