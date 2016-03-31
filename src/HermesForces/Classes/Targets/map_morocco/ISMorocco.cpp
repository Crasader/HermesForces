#include "IsMorocco.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"
#include "../Target.h"
#include "../../ScreenManager.h"

//#define TARGET_IS_IRAQ 1
IsMorocco::IsMorocco(const int& idTag, const cocos2d::Point& p) : IUnit(idTag,p)
{
	_targetUnit = Sprite::createWithSpriteFrameName("is_shoot_gun_1.png");
	_indexAnime = 2;
	// TODO : not appeare ??
	_targetUnit->setPosition(Point(p.x, (p.y  * 0.5) + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	setPhysicsBody(_targetUnit->getContentSize() * 1.5);
	_isDead = false;
	_isShouldShoot = false;
}

const int& IsMorocco::die()
{
	MapProcessor::Instance()->playSoundEffectTargetDie();
	this->disable();
	//_targetUnit->stopAllActions();
	_isDead = true;
	// TODO : change frames into MapProcessor::Instance()->getTargetAnimeFramesByIndex(3)
	Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(3); // die = 2 1,2 :targets
	Animation* animation = Animation::createWithSpriteFrames(frames, 0.1);
	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(IsIraq::disapeare, this)), nullptr);
	_targetUnit->runAction(seq);

	return DESTROY_ENEMY_GOODKILL;
}

void IsMorocco::startMoving()
{
	Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(_indexAnime);
	Animation* animation = Animation::createWithSpriteFrames(frames, 0.1);
	Animate* animate = Animate::create(animation);
	float radTime = cocos2d::random(0.1f, 0.5f);
	auto delay = DelayTime::create(radTime);
	auto seq = Sequence::create(animate, /*CallFunc::create(CC_CALLBACK_0(IsMorocco::shoot, this)), */delay, nullptr);
	_targetUnit->runAction(RepeatForever::create(seq));
}

//void IsMorocco::shoot()
//{
//	if (_isShouldShoot)
//		ScreenManager::Instance()->playSoundEffect("Sounds/machinegun.mp3");
//}

const bool& IsMorocco::updatePositionToTheLeft()
{
	if (!_isShouldShoot && _targetUnit->getPositionX()  < 1000)
		_isShouldShoot = true;

	_targetUnit->setPositionX(_targetUnit->getPositionX() - Land::pixelOfTargetMoving);
	if (_targetUnit->getPositionX() < Land::OutOfLeftWidth){
		if (_isEnemies){
			if (!_isDead)
				Land::thisPointer->stopMoveLand();
		}
		else
			this->disable();
		return false;
	}
	return true;
}

