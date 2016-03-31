#include "Fighter.h"
#include "../Missions/Land.h"
#include "../Utility/Utility.h"
#include "../ScreenManager.h"

USING_NS_CC;
#define FIGHTER_BOX_SQUARE 10
#define FIGHTER_POS_BOMB 0
// TODO: hit fighter -> explosive !!
Fighter::Fighter(cocos2d::Layer *layer, const cocos2d::Point& leftAlignPos, const int& specialMap)
{
	int map = ScreenManager::Instance()->CurrentMap();
	if (map != MAP_5 )
		_fighter = Sprite::createWithSpriteFrameName("apache_1.png");
	else
		_fighter = Sprite::createWithSpriteFrameName("china_zep.png");

	// TO DO : make less calculation
	Land::FighterPos = Point(leftAlignPos.x + _fighter->getContentSize().width * 0.5 * Land::deltaScale,leftAlignPos.y);/*Point((Land::visibleSize.width + Land::origin.x) * 0.25,
							(Land::visibleSize.height + Land::origin.y) * 0.8);*/
	_fighter->setPosition( Land::FighterPos );
	
	_fighter->setScale(Land::deltaScale);
	//_fighter->setTag(999);
	_layer = layer;
	_currentTime = 0;
 	layer->addChild( _fighter, 2000 );   
	
	if(specialMap > 0)
	{
		// special map
		_currentAntiRocketTime = 0;
		if(specialMap == MAP_14){ // map 14
			_antiRocketFromPos_1 = Land::FighterPos + Point((FIGHTER_BOX_SQUARE + 0.5 * Land::sizeBoom->width + FIGHTER_BOX_ANTI_ROCKET) * Land::deltaScale, 0);
			_antiRocketFromPos_2 = Land::FighterPos + Point((FIGHTER_BOX_SQUARE + 0.5 * Land::sizeBoom->width) * Land::deltaScale, (-1) * (1 + FIGHTER_BOX_ANTI_ROCKET * Land::deltaScale));
			_antiRocketFromPos_3 = Land::FighterPos + Point((FIGHTER_BOX_SQUARE + 0.5 * Land::sizeBoom->width + FIGHTER_BOX_ANTI_ROCKET) * Land::deltaScale, (-1) * (1 + FIGHTER_BOX_ANTI_ROCKET * Land::deltaScale));

			_antiRocketToPos_1 = Point(0.6 * Land::visibleSize.width, _antiRocketFromPos_1.y);
			_antiRocketToPos_2 = Point(_antiRocketFromPos_1.x, 0.4 * Land::visibleSize.height);
			_antiRocketToPos_3 = Point(Land::visibleSize.width * 0.6, Land::visibleSize.height * 0.5);

			_listAntiRocketItems = new AntiRocket*[15]; // 5 times
			_restAntiRocket = 14;
			_timeDelayAntiRocket = 1000;
			_specialButton = cocos2d::ui::Button::create();
			_specialButton->loadTextures("mini/land/special/btt_antirocket.png", "mini/land/special/btt_antirocket_clicked.png", "");
			_specialButton->addTouchEventListener(CC_CALLBACK_2(Fighter::antiRocket, this));
			_specialButton->setScale(Land::deltaScale);
			layer->addChild(_specialButton, 2895);
			//SpecialButton->setPosition(Point(50 , Land::visibleSize.height - 50));
			Land::PosRocket = cocos2d::random(0.8,0.95) * Land::visibleSize.width;

			auto fighterBody = PhysicsBody::createBox( cocos2d::Size(FIGHTER_BOX_SQUARE,FIGHTER_BOX_SQUARE));
			fighterBody->setCollisionBitmask(POINT_FIGHTER_BITMASK);
			fighterBody->setContactTestBitmask( true );
			fighterBody->setTag(999);
			_fighter->setPhysicsBody(fighterBody);

		}
		else if(specialMap == MAP_15) // map 15
		{
			_listAntiRocketItems = new AntiRocket*[30]; // 10 times
			_restAntiRocket = 30;
			_timeDelayAntiRocket = 800;
			_unlimitedWeapon = new ViewFinder(layer,Point(Land::visibleSize.width * 0.5, Land::visibleSize.height * 0.5));
			Land::PosRocket = 0.95 * Land::visibleSize.width;

			auto fighterBody = PhysicsBody::createBox( cocos2d::Size(FIGHTER_BOX_SQUARE,FIGHTER_BOX_SQUARE));
			fighterBody->setCollisionBitmask(POINT_FIGHTER_BITMASK);
			fighterBody->setContactTestBitmask( true );
			fighterBody->setTag(999);
			_fighter->setPhysicsBody(fighterBody);
			this->setAnimationFighterFly();
			return;
		}	
	}

	_bombBarrel = Point(Land::FighterPos.x, Land::FighterPos.y -  0.5 * Land::sizeBoom->height * Land::deltaScale - FIGHTER_POS_BOMB);
	_listFighterItems = new FighterItems*[Land::BombCount];
	restBomb = Land::BombCount; // by index
	for(int i=0; i<= Land::BombCount ; i++)
	{
		_listFighterItems[i] = new FighterItems(_layer, _bombBarrel , Land::TypeWeapon,i);
	}
	if (map != MAP_5)
	{
		this->setAnimationFighterFly();
	}
    _nextTimeShootGun = 1;
    _iGood = 6;
	//_fighter
}

void Fighter::Drop()
{
		//ScreenManager::Instance()->playSoundEffect("Sounds/bombdrop.wav", false);
	if (restBomb>=0)
		_listFighterItems[restBomb--]->Fall();
}

//Fighter::~Fighter()
//{
//	for(int i=0 ; i < Land::bombCount ; i++){
//		_listFighterItems[i]->removeBoom();
//		delete _listFighterItems[i];
//	}
//	_fighter->removeFromParentAndCleanup(true);
//}

void Fighter::hitTarget(const int&  idBoomTag)
{
	_listFighterItems[idBoomTag]->hitTarget();
}

void Fighter::hitLand(const int&  idBoomTag)
{
	_listFighterItems[idBoomTag]->hitLand();
}

void Fighter::updateBombs()
{
	for (int i = Land::BombCount; i > restBomb; i--)
	{
		_listFighterItems[i]->updatePosition();
	}
}

void Fighter::antiRocket(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	// throw protector
	// check time
	//_systemAntiRocketCrt = Utility::getCurrentTime();
	//if(_systemAntiRocketCrt - _currentAntiRocketTime > _timeDelayAntiRocket)
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		if(_restAntiRocket <= 1)
			return;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/antirocket.mp3");
		_listAntiRocketItems[_restAntiRocket] = new AntiRocket(_layer, _antiRocketFromPos_1  ,_restAntiRocket);
		_listAntiRocketItems[_restAntiRocket]->MoveToPos(_antiRocketToPos_1);
		_restAntiRocket--;

		_listAntiRocketItems[_restAntiRocket] = new AntiRocket(_layer, _antiRocketFromPos_2 ,_restAntiRocket);
		_listAntiRocketItems[_restAntiRocket]->MoveToPos(_antiRocketToPos_2);
		_restAntiRocket--;

		_listAntiRocketItems[_restAntiRocket] = new AntiRocket(_layer, _antiRocketFromPos_3 ,_restAntiRocket);
		_listAntiRocketItems[_restAntiRocket]->MoveToPos(_antiRocketToPos_3);
		_restAntiRocket--;

		_currentAntiRocketTime = _systemAntiRocketCrt;
	}
}

bool Fighter::hitRocket(const int& idAntiRocketTag)
{
		ScreenManager::Instance()->playSoundEffect("Sounds/rocketexp.mp3");
		_listAntiRocketItems[idAntiRocketTag]->hitRocket();
		return true;
}

void Fighter::gameOver(const int& indexFinal)
{
	if (restBomb < 0)
		return;
	for (int i = restBomb ; i < indexFinal; i++)
	{
		_listFighterItems[i]->disapeare();
	}
}

void Fighter::eatRocket()
{
	ScreenManager::Instance()->playSoundEffect("Sounds/fighter_exp.mp3");
	_fighter->stopAllActions();
	Vector<SpriteFrame*> frames_1;
	frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("apache_hit_1.png"));
	frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("apache_hit_2.png"));
	frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("apache_hit_3.png"));
	frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("apache_hit_4.png"));
	frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("apache_hit_5.png"));
	Animation* animation = Animation::createWithSpriteFrames(frames_1, 0.1);
	Animate* animate = Animate::create(animation);
	_fighter->runAction(animate);
}

void Fighter::setAntiRocketMap14(const Point& p)
{
	_specialButton->setPosition(p);
}

void Fighter::setAnimationFighterFly()
{
		Vector<SpriteFrame*> frames_1;
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("apache_2.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("apache_3.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("apache_4.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("apache_1.png"));
		Animation* animation = Animation::createWithSpriteFrames(frames_1, 0.05);
		Animate* animate = Animate::create(animation);
    if( ScreenManager::Instance()->CurrentMap() == MAP_3 ||
       ScreenManager::Instance()->CurrentMap() == MAP_15)
    {
        auto req = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(Fighter::soundGunMap415, this)), nullptr);
        _fighter->runAction(RepeatForever::create(req));
    }
    else
        _fighter->runAction(RepeatForever::create(animate));
}

const bool& Fighter::Shoot(const cocos2d::Point& pos)
{
	_unlimitedWeapon->Shoot(pos);
	return true;
}

void Fighter::soundGunMap415()
{
    if(_nextTimeShootGun++ % _iGood == 0){
        _nextTimeShootGun = 1;
        _iGood = cocos2d::random(5,9);
        ScreenManager::Instance()->playSoundEffect("Sounds/machinegun.mp3");
    }
}
//void Fighter::stopFly()
//{
//	for(int i=0 ; i < Land::bombCount ; i++){
//		_listFighterItems[i]->removeBoom();
//		delete _listFighterItems[i];
//	}
//}
