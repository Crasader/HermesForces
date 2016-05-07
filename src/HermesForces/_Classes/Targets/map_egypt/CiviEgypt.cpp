#include "CiviEgypt.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"
#include "../Target.h"
//TARGET_EGYPT_CIVILIANS 437
CiviEgypt::CiviEgypt(const int& idTag, const cocos2d::Point& p) : IUnit( idTag, p)
{
	_targetUnit = Sprite::createWithSpriteFrameName( "civi.png" );
	_targetUnit->setPosition(Point( p.x ,  (p.y  * 0.5 )  + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	_targetUnit->setOpacity(0);
	setPhysicsBody(Size(_targetUnit->getContentSize().width * 8, _targetUnit->getContentSize().height * 1.5));
}

const int& CiviEgypt::die()
{
	MapProcessor::Instance()->playSoundEffectTargetDie();
	this->disable();
	//_targetUnit->stopAllActions();
	_targetUnit->setOpacity(255);
	//Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(0); // die = 0
	Animation* animation = Animation::createWithSpriteFrames(MapProcessor::Instance()->getTargetAnimeFramesByIndex(0), 0.1);
	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(IsIraq::disapeare, this)), nullptr);
	_targetUnit->runAction(seq);
	return DESTROY_ENEMY_BADKILL;
}

const int& CiviEgypt::beDetected()
{
	if(_isDisable)
		return BE_DEAD_NO_DETECT;
	auto actionFadeIn = FadeTo::create(0.2, 255);
	auto actionFadeOut = FadeTo::create(0.2, 0);
	auto sequenceFade = Sequence::create(actionFadeIn,actionFadeOut,nullptr);
	_targetUnit->runAction(sequenceFade);

	return BE_DETECTED;
}


