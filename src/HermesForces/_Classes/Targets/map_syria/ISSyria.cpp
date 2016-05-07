#include "ISSyria.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"
#include "../Target.h"
//#define TARGET_IS_SYRIA 2
ISSyria::ISSyria(const int& idTag, const cocos2d::Point& p) : IUnit(idTag,p)
{
	_targetUnit = Sprite::createWithSpriteFrameName("oil_carrier_0.png");
	_indexAnime = 0;

	_targetUnit->setPosition(Point( p.x ,  (p.y  * 0.5 )  + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	setPhysicsBody(_targetUnit->getContentSize()  * 1.2);
	_isDead = false;
}

const int& ISSyria::die()
{
	MapProcessor::Instance()->playSoundEffectTargetDie();
	this->disable();
	_isDead = true;
	//_targetUnit->stopAllActions();
	//Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(1); // die = 2 1,2 :targets
	Animation* animation = Animation::createWithSpriteFrames(MapProcessor::Instance()->getTargetAnimeFramesByIndex(1), 0.1);
	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(IsIraq::disapeare, this)), nullptr);
	_targetUnit->runAction(seq);
	return DESTROY_ENEMY_GOODKILL;
}

void ISSyria::startMoving()
{
	Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(_indexAnime);
	Animation* animation = Animation::createWithSpriteFrames(frames, 0.3);
	Animate* animate = Animate::create(animation);
	_targetUnit->runAction(RepeatForever::create(animate));
}

