#include "FireBomb.h"
#include "../../Missions/Land.h"
#include  "../../Missions/MapProccessor.h"

FireBomb::FireBomb(cocos2d::Layer *layer, const cocos2d::Point&  point, const int& idBomb) : IItem(layer, point, idBomb)
{
	_fighterItems = Sprite::createWithSpriteFrameName( "fire_bomb_ori.png" );
	_fighterItems->setPosition(point);
	_fighterItems->setOpacity(0);
	layer->addChild(_fighterItems);
	if (!Land::isCalculateEndPoint){
		Land::isCalculateEndPoint = true;
		Land::endPointFallingBomb = Point(point.x, Land::LandPosY + _fighterItems->getContentSize().height * Land::deltaScale * 0.45);
	}
}

void FireBomb::hitTarget()
{
	// do nothing
    _isHitTarget = true;
}

void FireBomb::hitLand()
{
	MapProcessor::Instance()->playSoundEffectHitLand();
	_fighterBody->setEnabled(false);
	_fighterItems->setPosition(Land::endPointFallingBomb);
	Animation* animation = Animation::createWithSpriteFrames(MapProcessor::Instance()->getFighterItemAnimeFrames(0), 0.15);
	Animate* animate = Animate::create(animation);
	//Sequence* sequenceDisapeared = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(FireBomb::removeBoom, this)), nullptr);
	_fighterItems->runAction(RepeatForever::create(animate));
	_isHit = true;
}
