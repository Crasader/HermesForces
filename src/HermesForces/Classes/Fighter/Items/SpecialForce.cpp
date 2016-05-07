#include "SpecialForce.h"
#include "../../Missions/Land.h"
#include  "../../Missions/MapProccessor.h"
#include "../../ScreenManager.h"

SpecialForce::SpecialForce(cocos2d::Layer *layer, const cocos2d::Point&  point, const int& idBomb) : IItem(layer, point, idBomb)
{
	_fighterItems = Sprite::createWithSpriteFrameName( "swat_indo_jump.png" );
	_fighterItems->setPosition(point);
	_fighterItems->setOpacity(0);

	//if (Land::isNight)
	//{
	//	_bgNight = Sprite::create("mini/army/Weapons/train_special_force/land_swat.png");
	//	_bgNight->setOpacity(0);
	//	layer->addChild(_bgNight, 4300);
	//	_isShow = false;
	//}

	if (!Land::isCalculateEndPoint){
		Land::isCalculateEndPoint = true;
		Land::endPointFallingBomb = Point(point.x, Land::LandPosY + _fighterItems->getContentSize().height * Land::deltaScale * 0.5);
	}

	layer->addChild(_fighterItems,4500);
	_isGoodHit = false;
}

void SpecialForce::hitTarget()
{
	_isGoodHit = true;
    _isHitTarget = true;
	// do nothing
}

void SpecialForce::hitLand()
{
	MapProcessor::Instance()->playSoundEffectHitLand();
	_fighterBody->setEnabled(false);
	_isHit = true;
	_fighterItems->setPosition(Land::endPointFallingBomb);
	//_bgNight->setPosition(_fighterItems->getPosition());
	//if (Land::isNight)
	//{
	//	_bgNight->setOpacity(255);
	//	_bgNight->setScale(Land::deltaScale);
	//}
	if (_isGoodHit) // hit IS
	{
		//ScreenManager::Instance()->playSoundEffect("Sounds/gun.mp3", true);
		Animation* animation = Animation::createWithSpriteFrames(MapProcessor::Instance()->getFighterItemAnimeFrames(1), 0.25f);
		Animate* animate = Animate::create(animation);
		auto delay = DelayTime::create(1.0f);
		Sequence* sequenceArrest = Sequence::create(CallFunc::create(CC_CALLBACK_0(SpecialForce::shootBangBang, this)), animate, delay, nullptr);
		_fighterItems->runAction(RepeatForever::create(sequenceArrest));// sequenceDisapeared);
	}
	else
	{
		Animation* animation2 = Animation::createWithSpriteFrames(MapProcessor::Instance()->getFighterItemAnimeFrames(0), 0.2f);
		Animate* animate2 = Animate::create(animation2);
		auto delay = DelayTime::create(0.2f);
		Sequence* sequenceNoArrest = Sequence::create(animate2 , delay, nullptr);
		_fighterItems->runAction(RepeatForever::create(sequenceNoArrest));
	}
	
}


void SpecialForce::shootBangBang()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	ScreenManager::Instance()->playSoundEffect("Sounds/gun.ogg");
#else
	ScreenManager::Instance()->playSoundEffect("Sounds/gun.mp3");
#endif
}
