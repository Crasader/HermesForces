#include "IndianSwat.h"
#include "../../Missions/Land.h"
#include  "../../Missions/MapProccessor.h"

IndianSwat::IndianSwat(cocos2d::Layer *layer, const cocos2d::Point&  point, const int& idBomb) : IItem(layer, point, idBomb)
{
	_fighterItems = Sprite::createWithSpriteFrameName("poli_jum.png");
	_fighterItems->setPosition(point);
	_fighterItems->setOpacity(0);
	layer->addChild(_fighterItems);
	_isGoodHit = false;
	if (!Land::isCalculateEndPoint){
		Land::isCalculateEndPoint = true;
		Land::endPointFallingBomb = Point(point.x, Land::LandPosY + _fighterItems->getContentSize().height * Land::deltaScale * 0.5);
	}
}

void IndianSwat::hitTarget()
{
	// do nothing
	_isGoodHit = true;
    _isHitTarget = true;
}

void IndianSwat::hitLand()
{
	MapProcessor::Instance()->playSoundEffectHitLand();
	_isHit = true;
	_fighterBody->setEnabled(false);
	_fighterItems->setPosition(Land::endPointFallingBomb);

	if (_isGoodHit) // hit IS
	{
		//Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getFighterItemAnimeFrames();
		Animation* animation = Animation::createWithSpriteFrames(/*frames*/MapProcessor::Instance()->getFighterItemAnimeFrames(0), 0.1f);
		Animate* animate = Animate::create(animation);
		Sequence* sequenceArrest = Sequence::create(animate, nullptr);
		_fighterItems->runAction(sequenceArrest);// sequenceDisapeared);
	}
	else
	{
		Animation* animation = Animation::createWithSpriteFrames(/*frames*/MapProcessor::Instance()->getFighterItemAnimeFrames(1), 0.2f);
		Animate* animate = Animate::create(animation);
		auto delay = DelayTime::create(0.2f);
		Sequence* sequenceNoArrest = Sequence::create(animate, delay, nullptr);
		_fighterItems->runAction(RepeatForever::create(sequenceNoArrest));
	}
}
