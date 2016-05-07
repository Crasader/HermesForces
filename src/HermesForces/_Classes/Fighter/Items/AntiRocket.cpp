#include "AntiRocket.h"
#include "../../Missions/Land.h"

AntiRocket::AntiRocket( cocos2d::Layer *layer, const cocos2d::Point&  pStart, const int& idTag)
{
	_antiRocketItem = Sprite::create( "mini/army/Weapons/anti_rocket/anti_rocket.png" );
	_antiRocketItem->setPosition(pStart);

	_antiRocketBody = PhysicsBody::createBox( cocos2d::Size(FIGHTER_BOX_ANTI_ROCKET,FIGHTER_BOX_ANTI_ROCKET) );
	_antiRocketBody->setCollisionBitmask( POINT_ANTI_ROCKET_FIGHTER );
	_antiRocketBody->setContactTestBitmask( true );
	_antiRocketBody->setTag(idTag);

	_antiRocketItem->setPhysicsBody(_antiRocketBody);
	_antiRocketItem->setScale(Land::deltaScale);

	_antiRocketItem->setTag(idTag);

	layer->addChild(_antiRocketItem);
}

void AntiRocket::MoveToPos(const cocos2d::Point&  pTo)
{
	auto actionMove = MoveTo::create(3,pTo);
	Sequence* sequenceMoveAndEnd = Sequence::create(actionMove,CallFunc::create(CC_CALLBACK_0(AntiRocket::removeAntiRocket,this)),nullptr);
	_antiRocketItem->runAction(sequenceMoveAndEnd);
}

void AntiRocket::removeAntiRocket()
{
	//_antiRocketItem->removeFromPhysicsWorld();
    _antiRocketBody->setEnabled(false);  
	//_antiRocketItem->stopAllActions();
	_antiRocketItem->setOpacity(0);
	//_antiRocketItem->removeFromParentAndCleanup(true);
}

void AntiRocket::hitRocket()
{
	this->removeAntiRocket();
}

