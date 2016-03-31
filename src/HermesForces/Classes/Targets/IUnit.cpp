#include "IUnit.h"
#include "../Missions/Land.h"

IUnit::IUnit(const int& idTag, const cocos2d::Point& p)
{
	_idTag = idTag;
	_isDisable = false;
}

void IUnit::setScale(const float& k)
{
	_targetUnit->setScaleX(k);
}

void IUnit::setOpacity(const int& param)
{
	_targetUnit->setOpacity(param);
}

void IUnit::disable()
{
	_isDisable = true;
	_targetBody->setEnabled(false);
	_targetUnit->stopAllActions();
}

void IUnit::disapeare()
{
	_targetUnit->setOpacity(0);
}

const bool& IUnit::checkDisable()
{
	return _isDisable;
}


void IUnit::setPhysicsBody(const cocos2d::Size& sizeBody)
{
	Vec2 vec = Vec2(0, (-0.24) * sizeBody.height);
	_targetBody = PhysicsBody::createBox(Size(sizeBody.width, 0.01 * sizeBody.height), PHYSICSBODY_MATERIAL_DEFAULT, vec);
	_targetBody->setCollisionBitmask( POINT_TARGET_BITMASK );
	_targetBody->setContactTestBitmask( true );
	_targetBody->setTag(_idTag);
	_targetUnit->setPhysicsBody( _targetBody );
	_targetUnit->setTag(_idTag);
	_targetUnit->setScale(Land::deltaScale);
}

IUnit::~IUnit()
{

}
const bool& IUnit::updatePositionToTheLeft()
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
	return true;
}

//void IUnit::clean()
//{
//	_targetBody->setEnabled(false);
//	_targetUnit->stopAllActions();
//	_targetUnit->removeFromParent(); 
//}
