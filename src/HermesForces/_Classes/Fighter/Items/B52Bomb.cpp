#include "B52Bomb.h"
#include "../../Missions/Land.h"
#include  "../../Missions/MapProccessor.h"

B52Bomb::B52Bomb(cocos2d::Layer *layer, const cocos2d::Point&  point, const  int& idBomb, const bool& isChina) : IItem(layer, point, idBomb)
{
	if (isChina)
		_fighterItems = Sprite::createWithSpriteFrameName("bom_china.png");
	else
		_fighterItems = Sprite::createWithSpriteFrameName("bomb_b52.png");
	_fighterItems->setPosition( point);
	_fighterItems->setOpacity(0);
	layer->addChild(_fighterItems, 4500);
	if (!Land::isCalculateEndPoint){
		Land::isCalculateEndPoint = true;
		Land::endPointFallingBomb = Point(point.x, Land::LandPosY + _fighterItems->getContentSize().height * Land::deltaScale * 0.33 );
	}
	//_isGoodHit = false;
	//_end_point = Point(point.x, Land::LandPosY + _fighterItems->getContentSize().height * Land::deltaScale * 0.5);
}

void B52Bomb::hitTarget()
{
	// do nothing
	//_isGoodHit = true;
}

void B52Bomb::hitLand()
{	
	MapProcessor::Instance()->playSoundEffectHitLand();

	_isHit = true;
    _fighterBody->setEnabled(false);
	_fighterItems->setPosition(Land::endPointFallingBomb);
	
	//Vector<SpriteFrame*>  frames = MapProcessor::Instance()->getFighterItemAnimeFrames(0);
	Animation* animation = Animation::createWithSpriteFrames(/*frames*/MapProcessor::Instance()->getFighterItemAnimeFrames(0), 0.05);
	Animate* animate = Animate::create(animation);
	Sequence* sequenceDisapeared = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(B52Bomb::removeBoom, this)), nullptr);
	_fighterItems->runAction(sequenceDisapeared);// sequenceDisapeared);
}
