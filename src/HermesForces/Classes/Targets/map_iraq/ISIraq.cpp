#include "ISIraq.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"
#include "../Target.h"
//#define TARGET_IS_IRAQ 1
IsIraq::IsIraq(const int&   idTag, const cocos2d::Point& p) : IUnit(idTag, p)
{
	int rand = cocos2d::random(0, 1);
	if (rand == 0){
		_targetUnit = Sprite::createWithSpriteFrameName("is_iraq_1.png");
		_indexAnime = 0;
	}
	else if (rand == 1){
		_targetUnit = Sprite::createWithSpriteFrameName("is_iraq_gun_1.png");
		_indexAnime = 1;
	}

	_targetUnit->setPosition(Point(p.x, (p.y  * 0.5) + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	setPhysicsBody(_targetUnit->getContentSize() * 1.5);
	_isDead = false;
}

const int& IsIraq::die()
{
	MapProcessor::Instance()->playSoundEffectTargetDie();
	//ScreenManager::Instance()->playSoundEffect("Sounds/ahcut.mp3");
	this->disable();
	//_targetUnit->stopAllActions();
	
	_isDead = true;
	//Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(2); // die = 2 1,2 :targets
	Animation* animation = Animation::createWithSpriteFrames(MapProcessor::Instance()->getTargetAnimeFramesByIndex(2), 0.1);
	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(IsIraq::disapeare, this)), nullptr);
	_targetUnit->runAction(seq);
	return DESTROY_ENEMY_GOODKILL;
}

void IsIraq::startMoving()
{
	Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(_indexAnime);
	float delay = cocos2d::random(0.3f, 0.4f);
	Animation* animation = Animation::createWithSpriteFrames(frames, delay);
	Animate* animate = Animate::create(animation);
	_targetUnit->runAction(RepeatForever::create(animate));
}

