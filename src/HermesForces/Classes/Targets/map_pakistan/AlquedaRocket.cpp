#include "AlQuedaRocket.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"
#include "../../ScreenManager.h"
AlQuedaRocket::AlQuedaRocket(const int& idTag, const cocos2d::Point& p)  : IUnit(idTag,p)
{
	//int rand = cocos2d::random(0,4);
	//if(rand == 0)
	_targetUnit = Sprite::createWithSpriteFrameName( "is_shoot_air_1.png" );

	_targetUnit->setPosition(Point( p.x ,  (p.y  * 0.5 )  + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	//setPhysicsBody(_targetUnit->getContentSize() * 0.8);
	_targetBody = PhysicsBody::createBox(_targetUnit->getContentSize() * 0.8);
	_targetBody->setCollisionBitmask(POINT_TARGET_BITMASK);
	_targetBody->setContactTestBitmask(true);
	_targetBody->setTag(_idTag);
	_targetUnit->setPhysicsBody(_targetBody);
	_targetUnit->setTag(_idTag);
	_targetUnit->setScale(Land::deltaScale);

	this->_deathHit = 1;
	this->_expBombHit = 5;
	_rocket = Sprite::createWithSpriteFrameName( "rocket_attack.png" );
	_rocket->setPositionY((p.y  * 0.5) + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale) + (_rocket->getContentSize().height * Land::deltaScale));
	_rocket->setOpacity(0);
	Land::parentLayer->addChild(_rocket);
	// TO DO : change this code layer 
	_isFireRocket = false;
	_isDead = false;
}

const int& AlQuedaRocket::die()
{
	if(this->_deathHit <= 0)
	{
		MapProcessor::Instance()->playSoundEffectTargetDie();
		this->disable();
		//_targetUnit->stopAllActions();
		_isDead = true;
		Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(3); // die = 2 1,2 :targets
		Animation* animation = Animation::createWithSpriteFrames(frames, 0.1);
		Animate* animate = Animate::create(animation);
		auto seq = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(AlQuedaRocket::disapeare, this)), nullptr);
		_targetUnit->runAction(seq);

		return DESTROY_ENEMY_GOODKILL;
	}
	else
		this->_deathHit--;
	return DESTROY_ENEMY_DONOTHING;
}

void AlQuedaRocket::hitMainCharacter()
{
	if(this->_expBombHit <= 0)
	{
		_rocket->stopAllActions();
		bodyRocket->setEnabled(false);
		Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getTargetAnimeFramesByIndex(4); // 4 - hit rocket
		Animation* animation = Animation::createWithSpriteFrames(frames, 0.1);
		Animate* animate = Animate::create(animation);
		Sequence* sequenceMoveAndEnd = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(AlQuedaRocket::disableRocket, this)), nullptr);
		_rocket->runAction(sequenceMoveAndEnd);
		//_rocket->setOpacity(0);
		//_rocket->removeFromParentAndCleanup(true);
	}
	else
		this->_expBombHit--;
}

const bool& AlQuedaRocket::updatePositionToTheLeft()
{
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
	// check rocket
	if(!_isFireRocket)
	{
		// fire
		// TO DO : change and::visibleSize.width * 0.6
		if(_targetUnit->getPositionX() < Land::PosRocket)
		{
			_rocket->setPositionX(_targetUnit->getPositionX() );
			// Move to Land::FighterPos
			_rocket->runAction(CallFunc::create(CC_CALLBACK_0(AlQuedaRocket::attackMainCharacter,this)));
			_isFireRocket = true;
		}
	}
	return true;
}

void AlQuedaRocket::attackMainCharacter()
{
    //return;
	if(_isDisable)
		return;
	//rocket_launch
	ScreenManager::Instance()->playSoundEffect("Sounds/rocket_launch.mp3");

	Animation* animation = Animation::createWithSpriteFrames(MapProcessor::Instance()->getTargetAnimeFramesByIndex(2), 0.05);
	Animate* animate = Animate::create(animation);
	_targetUnit->runAction(animate);


	bodyRocket = PhysicsBody::createBox( Size(60,60));// ,PHYSICSBODY_MATERIAL_DEFAULT,vec);
	bodyRocket->setCollisionBitmask(POINT_TARGET_ROCKET_BITMASK);
	bodyRocket->setContactTestBitmask( true );
	bodyRocket->setTag(_idTag);	

	_rocket->setPhysicsBody( bodyRocket );	
	_rocket->setTag(_idTag);
	_rocket->setScale(Land::deltaScale);

	// do everything here
	float rad = cocos2d::random(1.5f, 3.0f);
	auto actionMove = MoveTo::create(rad, Land::FighterPos);
	Sequence* sequenceMoveAndEnd = Sequence::create(actionMove,CallFunc::create(CC_CALLBACK_0(AlQuedaRocket::disableRocket,this)),nullptr);
	_rocket->runAction(actionMove);

	_rocket->setOpacity(255);
}

void AlQuedaRocket::disableRocket()
{
	_rocket->stopAllActions();
	_rocket->setOpacity(0);
	_rocket->removeFromParentAndCleanup(true);
}