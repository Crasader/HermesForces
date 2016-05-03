#include "IItem.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"

IItem::IItem(cocos2d::Layer *layer, const cocos2d::Point&  pStart, const  int& idTag)
{
	isFalling = false;
	_isDisable = false;
	_isHit = false;
	_pStart = pStart;
	_idTag = idTag;
}

IItem::~IItem()
{

}

void IItem::Fall()
{
	if(!isFalling)
	{
		isFalling = true;
		MapProcessor::Instance()->playSoundEffectBombFall();
		_fighterItems->setOpacity(255);
		//Vec2 vec = Vec2(0, (-0.45) * Land::sizeBoom->height);
		_fighterBody = PhysicsBody::createBox(Size(Land::sizeBoom->width, Land::sizeBoom->height * 0.1), PHYSICSBODY_MATERIAL_DEFAULT, Land::vec2Boom);

		//_fighterBody = PhysicsBody::createBox( *Land::sizeBoom );
		_fighterBody->setCollisionBitmask( POINT_FIGHTER_ITEMS_BITMASK );
		_fighterBody->setContactTestBitmask( true );
		_fighterBody->setTag(_idTag);
		_fighterItems->setPhysicsBody( _fighterBody );
		_fighterItems->setTag(_idTag);
		_fighterItems->setScale(Land::deltaScale);
	}
}

void IItem::removeBoom()
{
	if(!_isDisable)
	{
		_fighterItems->setOpacity(0);
		_isDisable = true;
	}
}

//void IItem::recycle()
//{
//	_fighterItems->setPosition( _pStart);
//	_fighterItems->stopAllActions();
//	_fighterItems->setOpacity(0);
//	isFalling = false;
//	isEndContact = false;
//	_isHit = false;
//}

void IItem::updatePos()
{	
	if (!_isDisable){
		if (_isHit){
			_fighterItems->setPositionX(_fighterItems->getPositionX() - Land::pixelOfLandMoving);
			if (_fighterItems->getPositionX() < 0)
			{
                _isDisable = true;
				_fighterItems->stopAllActions();
			}
		}
		else
			_fighterItems->setPositionY(_fighterItems->getPositionY() - Land::PixelPerFPSBoomFall);
	}
}

void IItem::disapeare()
{
	if (isFalling)
		_fighterItems->setOpacity(0);
}
