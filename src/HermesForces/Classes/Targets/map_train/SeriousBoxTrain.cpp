#include "SeriousBoxTrain.h"
#include "../../Missions/Land.h"
#include "../Target.h"
#include "../../Missions/MapProccessor.h"
//#define TARGET_IS_IRAQ 1
SeriousBoxTrain::SeriousBoxTrain(int idTag,cocos2d::Point p, int distanceNumber) : IUnit(idTag,p)
{
	//std::string test = MapProcessor::Instance()->getPathRandomItemNotLoop(false);
	_targetUnit = Sprite::createWithSpriteFrameName(MapProcessor::Instance()->getPathRandomItemNotLoop(true));
	_targetUnit->setPosition(Point( p.x , -distanceNumber  * Land::deltaScale + (p.y  * 0.5 )  + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));

	Vec2 vec = Vec2(0 , distanceNumber + 1 - _targetUnit->getContentSize().height * 0.5);
	_targetBody = PhysicsBody::createBox( Size(100,1) ,PHYSICSBODY_MATERIAL_DEFAULT,vec);
	_targetBody->setCollisionBitmask( POINT_TARGET_BITMASK );
	_targetBody->setContactTestBitmask( true );
	_targetBody->setTag(idTag);	
	_targetUnit->setPhysicsBody( _targetBody );	
	_targetUnit->setTag(idTag);
	_targetUnit->setScale(Land::deltaScale);
	_isDead = false;

	//_targetUnit->setOpacity(100);
}

const int& SeriousBoxTrain::die()
{
	this->disable();
	MapProcessor::Instance()->playSoundEffectTargetDie();
    //_targetBody->setEnabled(false);
	_isDead = true;
	return DESTROY_ENEMY_GOODKILL;
}



