#include "ISVictim.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"
#include "../Target.h"
//#define TARGET_IS_IRAQ 1
IsVictim::IsVictim(const int& idTag, const cocos2d::Point& p) : IUnit(idTag,p)
{
	int rand = cocos2d::random(0,1);
	if(rand == 0)
		_targetUnit = Sprite::createWithSpriteFrameName("is_victim_1.png");
	else
		_targetUnit = Sprite::createWithSpriteFrameName("is_victim_2.png");

	_targetUnit->setPosition(Point( p.x ,  (p.y  * 0.5 )  + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	setPhysicsBody(_targetUnit->getContentSize() * 1.5);
}

const int& IsVictim::die()
{
	MapProcessor::Instance()->playSoundEffectTargetDie();
	this->disable();
	//_targetUnit->stopAllActions();
	Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(3); // die = 2 1,2 :targets
	Animation* animation = Animation::createWithSpriteFrames(frames, 0.1);
	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(IsIraq::disapeare, this)), nullptr);
	_targetUnit->runAction(seq);
	return DESTROY_ENEMY_BADKILL;
}

