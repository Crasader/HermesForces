#include "ISVictim_Cage.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"
#include "../Target.h"
//#define TARGET_IS_IRAQ 1
IsCageVictim::IsCageVictim(const int& idTag, const cocos2d::Point& p) : IUnit(idTag,p)
{
	_targetUnit = Sprite::createWithSpriteFrameName("victim_cage.png");
	_targetUnit->setPosition(Point( p.x ,  (p.y  * 0.5 )  + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	setPhysicsBody(_targetUnit->getContentSize() * 1.5);
}

const int& IsCageVictim::die()
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

