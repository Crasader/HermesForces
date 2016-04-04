#include "SubMarine.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"
#include "../Target.h"
#include "../../ScreenManager.h"

//#define TARGET_IS_IRAQ 1
SubMarine::SubMarine(int idTag,cocos2d::Point p) : IUnit(idTag,p)
{
	_targetUnit = Sprite::createWithSpriteFrameName( "water_4.png" );
	_targetUnit->setPosition(Point( p.x , /*-100  * Land::deltaScale  + */ (p.y  * 0.5 )  + ( 2 * Land::deltaScale)));
	// TO DO : +1 => idiot
	//Vec2 vec = Vec2(0 , 0);//100 + 1 - _targetUnit->getContentSize().height * 0.5);
	_targetBody = PhysicsBody::createBox( Size(120,1));// ,PHYSICSBODY_MATERIAL_DEFAULT,vec);
	_targetBody->setCollisionBitmask( POINT_TARGET_BITMASK );
	_targetBody->setContactTestBitmask( true );
	_targetBody->setTag(idTag);	
	_targetUnit->setPhysicsBody( _targetBody );	
	_targetUnit->setTag(idTag);
	_targetUnit->setScale(Land::deltaScale);

	_rocket = Sprite::createWithSpriteFrameName( "rocket_attack.png" );
	_rocket->setPositionY((p.y  * 0.5 )  + (_rocket->getContentSize().height * 0.5 * Land::deltaScale) + 30 * Land::deltaScale);
	_rocket->setOpacity(0);
	_targetUnit->setOpacity(0);
	Land::parentLayer->addChild(_rocket);

	_underMarine = Sprite::createWithSpriteFrameName("sub_mar_hit_0.png");
	_underMarine->setOpacity(0);
	_underMarine->setPosition(Point(p.x, (p.y  * 0.5) - (30 * Land::deltaScale))); // distance from drain and hole
	_underMarine->setScale(Land::deltaScale);

	
	Land::parentLayer->addChild(_underMarine,7811);
	// TO DO : change this code layer 
	_isFireRocket = false;
	_isDead = false;
}

const int& SubMarine::die()
{
	MapProcessor::Instance()->playSoundEffectTargetDie();
	this->disable();
	_underMarine->stopAllActions();
	_underMarine->setOpacity(255);
	_isDead = true;
	Animation* animation1 = Animation::createWithSpriteFrames(MapProcessor::Instance()->getTargetAnimeFramesByIndex(1), 0.1);
	Animate* animate1 = Animate::create(animation1);
	_underMarine->runAction(animate1);

	return DESTROY_ENEMY_GOODKILL;
}

void SubMarine::hitMainCharacter()
{
	_rocket->stopAllActions();
	bodyRocket->setEnabled(false);
	Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(2); // 2 - hit rocket
	Animation* animation = Animation::createWithSpriteFrames(frames, 0.1);
	Animate* animate = Animate::create(animation);
	Sequence* sequenceMoveAndEnd = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(SubMarine::disableRocket, this)), nullptr);
	_rocket->runAction(sequenceMoveAndEnd);
}

const bool& SubMarine::updatePositionToTheLeft()
{
	_targetUnit->setPositionX(_targetUnit->getPositionX() - Land::pixelOfTargetMoving);
	_underMarine->setPositionX(_targetUnit->getPositionX());
	//if (_isDisable)
	//	_underMarine->setPositionX(_targetUnit->getPositionX());
	//else
	//{
	if (!_isDisable)
	{
		if (_targetUnit->getPositionX() < Land::OutOfLeftWidth){
			if (_isEnemies){
				if (!_isDead)
					Land::thisPointer->stopMoveLand();
			}
			else
				this->disable();
			return false;
		}
	}

	//}

	// check rocket
	if(!_isFireRocket)
	{
		// fire
		if(_targetUnit->getPositionX() < Land::visibleSize.width * 0.9)
		{
			_isFireRocket = true;
			_targetUnit->setOpacity(255);
			_rocket->setPositionX(_targetUnit->getPositionX() );
			// Move to Land::FighterPos
			_rocket->runAction(CallFunc::create(CC_CALLBACK_0(SubMarine::attackMainCharacter,this)));	
		}
	}

	return true;
}

void SubMarine::attackMainCharacter()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	ScreenManager::Instance()->playSoundEffect("Sounds/waterbomb.ogg");
	ScreenManager::Instance()->playSoundEffect("Sounds/rocket_launch.ogg");
#else
	ScreenManager::Instance()->playSoundEffect("Sounds/waterbomb.mp3");
	ScreenManager::Instance()->playSoundEffect("Sounds/rocket_launch.mp3");
#endif


	Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(0);
	Animation* animation = Animation::createWithSpriteFrames(frames, 0.02);
	Animate* animate = Animate::create(animation);
	auto FadeOutWater = FadeOut::create(0.02);
	auto seq = Sequence::create(animate, FadeOutWater, nullptr);
	_targetUnit->runAction(seq);

	bodyRocket = PhysicsBody::createBox( Size(30,30));// ,PHYSICSBODY_MATERIAL_DEFAULT,vec);
	bodyRocket->setCollisionBitmask(POINT_TARGET_ROCKET_BITMASK);
	bodyRocket->setContactTestBitmask( true );
	bodyRocket->setTag(_idTag);	

	_rocket->setPhysicsBody( bodyRocket );	
	_rocket->setTag(_idTag);
	_rocket->setScale(Land::deltaScale);

	// do everything here
	float rad = cocos2d::random(1.0f, 3.0f);
	auto actionMove = MoveTo::create(rad, Land::FighterPos);
	Sequence* sequenceMoveAndEnd = Sequence::create(actionMove,CallFunc::create(CC_CALLBACK_0(SubMarine::disableRocket,this)),nullptr);
	_rocket->runAction(actionMove);
	_rocket->setOpacity(255);

	//_underMarine->setOpacity(255);

	auto fadeIn = FadeTo::create(0.25f,255);
	auto fadeOut = FadeTo::create(0.25f, 0);
	float radApea = cocos2d::random(1.5f, 2.5f);
	auto delayAppreare = DelayTime::create(1.5f);
	auto seqSub = Sequence::create(fadeIn, fadeOut, delayAppreare, nullptr);
	_underMarine->runAction(RepeatForever::create(seqSub));
}

void SubMarine::disableRocket()
{
	_rocket->stopAllActions();
	_rocket->setOpacity(0);
	_rocket->removeFromParentAndCleanup(true);
}

//void SubMarine::disapeareSubMarine()
//{
//
//}

//void SubMarine::clean()
//{
//	_targetUnit->removeFromParentAndCleanup(true);
//	_rocket->removeFromParentAndCleanup(true);
//}
//
