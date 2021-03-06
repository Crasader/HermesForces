#include "IsKnife.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"
#include "../Target.h"
//TARGET_IRAQ_CIVILIANS 333
IsKnife::IsKnife(const int& idTag, const cocos2d::Point& p) : IUnit(idTag,p)
{
	_targetUnit = Sprite::createWithSpriteFrameName("is_knife_0.png");
	_indexAnime = 1;
	// TODO : not appeare ??
	_targetUnit->setPosition(Point(p.x, (p.y  * 0.5) + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	setPhysicsBody(_targetUnit->getContentSize() * 1.5);
	_isDead = false;
}

const int& IsKnife::die()
{
	MapProcessor::Instance()->playSoundEffectTargetDie();
	this->disable();
	//_targetUnit->stopAllActions();
	_isDead = true;
	Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(3); // die = 2 1,2 :targets
	Animation* animation = Animation::createWithSpriteFrames(frames, 0.1);
	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(IsIraq::disapeare, this)), nullptr);
	_targetUnit->runAction(seq);

	return DESTROY_ENEMY_GOODKILL;
}

void IsKnife::startMoving()
{
	Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(_indexAnime);
	Animation* animation = Animation::createWithSpriteFrames(frames, 0.3);
	Animate* animate = Animate::create(animation);
	float radTime = cocos2d::random(0.1f, 0.4f);
	auto delay = DelayTime::create(radTime);
	auto seq = Sequence::create(animate, delay, nullptr);
	_targetUnit->runAction(RepeatForever::create(seq));
}

