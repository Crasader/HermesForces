#include "FakedCar.h"
#include "../../Missions/Land.h"
#include "../Target.h"
#include "../../Missions/MapProccessor.h"
//#define TARGET_IS_IRAQ 1
FakedCar::FakedCar(const int& idTag,const cocos2d::Point& p) : IUnit(idTag,p)
{
	_targetUnit = Sprite::createWithSpriteFrameName(MapProcessor::Instance()->getPathRandomItemNotLoopWithIndex(true, _indexAnime));
	_targetUnit->setPosition(Point( p.x ,  (p.y  * 0.5 )  + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	//_targetUnit->setOpacity(50);
	setPhysicsBody(_targetUnit->getContentSize() * 1.2);
	_isDead = false;
}

const int& FakedCar::die()
{
	MapProcessor::Instance()->playSoundEffectTargetDie();
	this->disable();
	_targetUnit->stopAllActions();
	_isDead = true;
	//Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(0); // die = 0
	Animation* animation = Animation::createWithSpriteFrames(MapProcessor::Instance()->getTargetAnimeFramesByIndex(0), 0.1);
	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(IsIraq::disapeare, this)), nullptr);
	_targetUnit->runAction(seq);
	return DESTROY_ENEMY_GOODKILL;
}

void FakedCar::startMoving()
{
	float delay = cocos2d::random(0.28f, 0.4f);
	Animation* animation = Animation::createWithSpriteFrames(MapProcessor::Instance()->getTargetAnimeFramesByIndex(_indexAnime), 0.25f);
	Animate* animate = Animate::create(animation);
	_targetUnit->runAction(RepeatForever::create(animate));
}

