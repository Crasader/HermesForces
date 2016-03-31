#include "BombWarning.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"
#include "../Target.h"
//TARGET_EGYPT_CIVILIANS 437
BombWarning::BombWarning(const int& idTag,const cocos2d::Point& p) : IUnit(idTag,p)
{
	_targetUnit = Sprite::create( "mini/army/plist/map_berlin/warning_bomb_mini.png" );
	_targetUnit->setPosition(Point( p.x ,  (p.y  * 0.5 )  + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	_targetUnit->setOpacity(0);
	setPhysicsBody(_targetUnit->getContentSize() * 1.5);
	_isDead = false;
}

const int& BombWarning::die()
{
	MapProcessor::Instance()->playSoundEffectTargetDie();
	this->disable();
	_targetUnit->setOpacity(0);
	_isDead = true;
	return DESTROY_ENEMY_GOODKILL;
}

const int& BombWarning::beDetected()
{
	if(_isDisable)
		return BE_DEAD_NO_DETECT;
	auto actionFadeIn = FadeTo::create(0.2,255);
	auto actionFadeOut = FadeTo::create(0.2, 0);
	auto sequenceFade = Sequence::create(actionFadeIn,actionFadeOut,nullptr);
	_targetUnit->runAction(sequenceFade);

	return BE_DETECTED;
}


