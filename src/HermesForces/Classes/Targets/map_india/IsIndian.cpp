#include "IsIndian.h"
#include "../../Missions/Land.h"
#include "../Target.h"
#include "../../Missions/MapProccessor.h"

//#define TARGET_IS_IRAQ 1
IsIndian::IsIndian(const int& idTag, const cocos2d::Point& p) : IUnit( idTag, p)
{
	_targetUnit = Sprite::createWithSpriteFrameName("ene.png");
	_targetUnit->setPosition(Point(p.x, (p.y  * 0.5) + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	//setPhysicsBody(Size(_targetUnit->getContentSize().width * 4, _targetUnit->getContentSize().height * 1.5));
	_targetBody = PhysicsBody::createBox(Size(40, 1));// ,PHYSICSBODY_MATERIAL_DEFAULT,vec);
	_targetBody->setCollisionBitmask(POINT_TARGET_BITMASK);
	_targetBody->setContactTestBitmask(true);
	_targetBody->setTag(idTag);
	_targetUnit->setPhysicsBody(_targetBody);
	_targetUnit->setTag(idTag);
	_targetUnit->setScale(Land::deltaScale);

	_targetUnit->setOpacity(0);
	_isDead = false;
}

const int& IsIndian::die()
{
	MapProcessor::Instance()->playSoundEffectTargetDie();
	this->disable();
	//_targetBody->setEnabled(false);
	_targetUnit->setOpacity(0);
	//_targetUnit->stopAllActions();
	_isDead = true;
	
	return DESTROY_ENEMY_GOODKILL;
}

const int& IsIndian::beDetected()
{
	if (_isDisable)
		return BE_DEAD_NO_DETECT;
	auto actionFadeIn = FadeTo::create(0.2, 255);
	auto actionFadeOut = FadeTo::create(0.2, 0);
	auto sequenceFade = Sequence::create(actionFadeIn, actionFadeOut, nullptr);
	_targetUnit->runAction(sequenceFade);

	return BE_DETECTED;
}

