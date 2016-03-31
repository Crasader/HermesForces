#include "Items.h"

FighterItems::FighterItems(cocos2d::Layer *layer, const  Point& p, const int& type, const  int& idBomb)
{
	switch (type)
	{
	case ITEM_BOMB_B52:
		_fighterItem = new B52Bomb(layer,p,idBomb);
		break;
	case ITEM_BOMB_CHINA:
		_fighterItem = new B52Bomb(layer, p, idBomb,true);
		break;
	//case ITEM_BULLET:
	//	_fighterItem = new MachineGunBullet(layer,p,idBomb);
	//	break;
	case ITEM_BOMB_FIRE:
		_fighterItem = new FireBomb(layer,p,idBomb);
		break;
	case ITEM_BOMB_SQUAD:
		_fighterItem = new BombSquad(layer,p,idBomb);
		break;
	case ITEM_TRAIN_SPECIAL_FORCE:
		_fighterItem = new SpecialForce(layer,p,idBomb);
		break;
	case ITEM_MARINE_BOMB:
		_fighterItem = new MarineBomb(layer,p,idBomb);
		break;
	case ITEM_INDIA_SPECIAL_FORCE:
		_fighterItem = new IndianSwat(layer, p, idBomb);
		break;
	default:
		break;
	}
}

void FighterItems::Fall()
{
	_fighterItem->Fall();
}

void FighterItems::removeBoom()
{
	_fighterItem->removeBoom();
}

void FighterItems::hitTarget()
{
	_fighterItem->hitTarget();
}

void FighterItems::hitLand()
{
	_fighterItem->hitLand();
}

FighterItems::~FighterItems()
{

}

void FighterItems::updatePosition()
{
	_fighterItem->updatePos();
}

void FighterItems::disapeare()
{
	_fighterItem->disapeare();
}
