#include "ViewFinder.h"
#include "../../Missions/Land.h"
#include "../../ScreenManager.h"

ViewFinder::ViewFinder(cocos2d::Layer *layer, const cocos2d::Point& pStart)
{
	_viewer = Sprite::create("mini/army/Weapons/unlimited_weapons/viewer.png");
	_bullet = Sprite::create("mini/army/Weapons/unlimited_weapons/viewer_bullet.png");
	_viewer->setPosition(pStart);
	_bullet->setOpacity(0);
	_bulletPb = PhysicsBody::createBox( cocos2d::Size(1,1));
	_bulletPb->setCollisionBitmask( POINT_VIEWER_ITEMS_BITMASK );
	_bulletPb->setContactTestBitmask( true );
	_bulletPb->setEnabled(false);
	_viewer->setScale(Land::deltaScale);
	_bullet->setScale(Land::deltaScale);
	_bullet->setPhysicsBody(_bulletPb);
	layer->addChild(_viewer, 6100);
	layer->addChild(_bullet, 6200);
	
}

void ViewFinder::Shoot(const cocos2d::Point& pTo)
{	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	ScreenManager::Instance()->playSoundEffect("Sounds/gun.ogg");
#else
	ScreenManager::Instance()->playSoundEffect("Sounds/gun.mp3");
#endif
	_bullet->stopAllActions();
	_bulletPb->setEnabled(false);
	_bullet->setOpacity(255);
	_bulletAppeare = FadeOut::create(0.1);
	_sequenceDisapeared = Sequence::create(_bulletAppeare,CallFunc::create(CC_CALLBACK_0(ViewFinder::disable,this)),nullptr);
	
	_bulletPb->setEnabled(true);
	_bullet->setPosition(pTo);
	_bullet->runAction(_sequenceDisapeared);
	_viewer->setPosition(pTo);
	//_bulletPb->setEnable(false);
}

void ViewFinder::disable()
{
	_bulletPb->setEnabled(false);
}

