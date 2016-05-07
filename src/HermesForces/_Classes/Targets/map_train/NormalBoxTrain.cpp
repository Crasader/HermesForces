#include "NormalBoxTrain.h"
#include "../../Missions/Land.h"
#include "../Target.h"
#include "../../Missions/MapProccessor.h"
//#define TARGET_IS_IRAQ 1
NormalBoxTrain::NormalBoxTrain(int idTag,cocos2d::Point p, int distanceNumber) : IUnit(idTag,p)
{
	//std::string test = MapProcessor::Instance()->getPathRandomItemNotLoop(false);
	_targetUnit = Sprite::createWithSpriteFrameName( MapProcessor::Instance()->getPathRandomItemNotLoop(false));
	_targetUnit->setPosition(Point( p.x , -distanceNumber  * Land::deltaScale + (p.y  * 0.5 )  + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
	_targetBody = PhysicsBody::createBox(Size(0, 0));
	_targetBody->setEnabled(false);
	_targetUnit->setPhysicsBody(_targetBody);
	_targetUnit->setTag(idTag);
	_targetUnit->setScale(Land::deltaScale);

	//_targetUnit->setOpacity(100);
}

const int& NormalBoxTrain::die()
{
	return DESTROY_ENEMY_DONOTHING;
}
