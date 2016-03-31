//#include "CiviIraq.h"
//#include "../../Missions/Land.h"
//#include "../Target.h"
////TARGET_IRAQ_CIVILIANS 333
//CiviIraq::CiviIraq(int type, int idTag, cocos2d::Point p) : IUnit(type,idTag,p)
//{
//	int rand = cocos2d::random(0,3);
//	if(rand == 2)
//		_targetUnit = Sprite::create( "mini/army/plist/map_car/car_29.png" );
//	else if(rand == 1)
//		_targetUnit = Sprite::create( "mini/army/plist/map_car/car_30.png" );
//	else
//		_targetUnit = Sprite::create( "mini/army/plist/map_car/car_3.png" );
//
//	_targetUnit->setPosition(Point( p.x ,  (p.y  * 0.5 )  + (_targetUnit->getContentSize().height * 0.5 * Land::deltaScale)));
//	setPhysicsBody(_targetUnit->getContentSize() * 0.8);
//}
//
//int CiviIraq::die()
//{
//	////_targetUnit->removeFromPhysicsWorld();
// //   _targetBody->setEnabled(false);
// //   
//	//auto actionFade = FadeTo::create(0.1,200); 
//	////Animation *animation = Animation::createWithSpriteFrames(Target::diedFrames, 0.05);
//	////Animate *animateExplosived = Animate::create(animation);
//	//Sequence* sequenceDisapeared = Sequence::create(actionFade,/*animateExplosived,*/CallFunc::create(CC_CALLBACK_0(CiviIraq::disable,this)),nullptr);
//
//	////auto finalAction  = Spawn::create(sequenceDisapeared ,actionMove,nullptr);
//	//_targetUnit->runAction(sequenceDisapeared);
//	this->disable();
//	auto actionFade = FadeTo::create(1, 0);
//	_targetUnit->runAction(actionFade);
//	return DESTROY_ENEMY_BADKILL;
//}
//
//
