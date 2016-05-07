#include "MarineBomb.h"
#include "../../Missions/Land.h"
#include "../../Missions/MapProccessor.h"

MarineBomb::MarineBomb(cocos2d::Layer *layer, const  cocos2d::Point&  point, const int& idBomb) : IItem(layer, point, idBomb)
{
	_fighterItems = Sprite::createWithSpriteFrameName( "bomb_marine.png" );
	_fighterItems->setPosition( point);
	_fighterItems->setOpacity(0);
	layer->addChild(_fighterItems);
	if (!Land::isCalculateEndPoint){
		Land::isCalculateEndPoint = true;
		Land::endPointFallingBomb = Point(point.x, Land::LandPosY);
	}
}

void MarineBomb::hitTarget()
{
	// do nothing
    _isHitTarget = true;
}

void MarineBomb::hitLand()
{
	MapProcessor::Instance()->playSoundEffectHitLand();

	_isHit = true;
	//_fighterItems->removeFromPhysicsWorld();
    _fighterBody->setEnabled(false);
	// TODO : remove all stopallaction if not neccessary
	//_fighterItems->stopAllActions();
	_fighterItems->setPosition(Land::endPointFallingBomb);
	_fighterItems->setOpacity(255);
	Animation* animation = Animation::createWithSpriteFrames(MapProcessor::Instance()->getTargetAnimeFramesByIndex(0), 0.1);
	Animate* animate = Animate::create(animation);
	auto FadeOutWater = FadeOut::create(0.2);
	auto seq = Sequence::create(animate, FadeOutWater, nullptr);
	_fighterItems->runAction(seq);

}
