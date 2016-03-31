#include "AlQuedaFire.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"

AlQuedaFire::AlQuedaFire(const int& idTag, const cocos2d::Point& p) : IUnit(idTag, p)
{
	//int rand = cocos2d::random(0,4);
	//if(rand == 0)
	_targetUnit = Sprite::createWithSpriteFrameName("is_fire_1.png");

	_targetUnit->setPosition(Point(p.x, (p.y  * 0.5) + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	_targetBody = PhysicsBody::createBox(_targetUnit->getContentSize() * 0.8);
	_targetBody->setCollisionBitmask(POINT_TARGET_BITMASK);
	_targetBody->setContactTestBitmask(true);
	_targetBody->setTag(_idTag);
	_targetUnit->setPhysicsBody(_targetBody);
	_targetUnit->setTag(_idTag);
	_targetUnit->setScale(Land::deltaScale);
	_isDead = false;
	this->_deathHit = 1;
}

const int& AlQuedaFire::die()
{
	//int idtag = _idTag;
	if (this->_deathHit <= 0)
	{
		MapProcessor::Instance()->playSoundEffectTargetDie();
		this->disable();
		//_targetUnit->stopAllActions();
		_isDead = true;
		Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(3); // die = 2 1,2 :targets
		Animation* animation = Animation::createWithSpriteFrames(frames, 0.1);
		Animate* animate = Animate::create(animation);
		auto seq = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(AlQuedaFire::disapeare, this)), nullptr);
		_targetUnit->runAction(seq);

		return DESTROY_ENEMY_GOODKILL;
	}
	else
		this->_deathHit--;
	return DESTROY_ENEMY_DONOTHING;
}

void AlQuedaFire::startMoving()
{
	//Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(1);
	Animation* animation = Animation::createWithSpriteFrames(MapProcessor::Instance()->getTargetAnimeFramesByIndex(0), 0.1);
	Animate* animate = Animate::create(animation);
	float radTime = cocos2d::random(0.1f, 0.4f);
	auto delay = DelayTime::create(radTime);
	auto seq = Sequence::create(animate, delay, nullptr);
	_targetUnit->runAction(RepeatForever::create(seq));
}