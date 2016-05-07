#include "ISBodyInvi.h"
#include "../../Missions/Land.h"
#include "../Target.h"
#include "../../Missions/MapProccessor.h"
//#define TARGET_IS_IRAQ 1
ISBodyInvi::ISBodyInvi(const int& idTag, const cocos2d::Point& p) : IUnit(idTag, p)
{
	int rand = cocos2d::random(0,2);
	if(rand == 0)
		_targetUnit = Sprite::createWithSpriteFrameName( "enemies_1.png" );
	else if(rand == 1)
		_targetUnit = Sprite::createWithSpriteFrameName("enemies_2.png");
	else 
		_targetUnit = Sprite::createWithSpriteFrameName("enemies_3.png");
	_targetUnit->setPosition(Point( p.x ,  (p.y  * 0.5 )  + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	_targetUnit->setOpacity(0);
	setPhysicsBody(_targetUnit->getContentSize() * 1.5);
	_isDead = false;
}

const int& ISBodyInvi::die()
{
	MapProcessor::Instance()->playSoundEffectTargetDie();
	this->disable();
	_targetUnit->setOpacity(255);
	//_targetUnit->stopAllActions();
	_isDead = true;
	Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(0); // die = 0 :targets
	Animation* animation = Animation::createWithSpriteFrames(frames, 0.2);
	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(IsIraq::disapeare, this)), nullptr);
	_targetUnit->runAction(seq);
	return DESTROY_ENEMY_GOODKILL;
}

const int& ISBodyInvi::beDetected()
{
	if(_isDisable)
		return BE_DEAD_NO_DETECT;
	auto actionFadeIn = FadeTo::create(0.2,255);
	auto actionFadeOut = FadeTo::create(0.2, 0);
	auto sequenceFade = Sequence::create(actionFadeIn,actionFadeOut,nullptr);
	_targetUnit->runAction(sequenceFade);
	return BE_DETECTED;
}


