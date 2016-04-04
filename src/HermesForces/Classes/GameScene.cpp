#include "ScreenManager.h"
#include "Missions/MapProccessor.h"
#include <iostream>
#include <chrono>

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics( );
    //scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    scene->getPhysicsWorld( )->setGravity( Vect( 0, 0 ) );
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld( ) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	layer->setKeypadEnabled(true);
#endif
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	if (gettimeofday(&_oldTimer, nullptr) == 0)
	{
		_oldTimer.tv_sec = 0;
		_oldTimer.tv_usec = 0;
	}

    //background.mp3
    //actionAudio = SimpleAudioEngine::getInstance();
    //backgroundAudio = SimpleAudioEngine::getInstance();
    _testCallerUpdater = -1;
	_clickPause = false;
	//_isWelcome = true;

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	//map 13 , 14 have special game play
	_isSpecialMap = false;
	//_isUnlimitedGun = false;
	_isMap14 = false;
	_isMap15 = false;
    _isGameOver = false;
	_isEmptyWeapons = false;
	//_isWelcome = true;
	_isMapRandom3 = false;
	_isMapRandom6 = false;
    //backgroundAudio->playEffect("Sounds/background.mp3", true, 1.0f, 1.0f, 1.0f);
    // map -> 1.1
    //_land = new Land(this , ScreenManager::Instance()->CurrentMap());
	ScreenManager::Instance()->setUpNewLand(this);
	//
	//Director::getInstance()->getEventDispatcher()->setEnabled(false);
	_contactListener = EventListenerPhysicsContact::create();
	_contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_contactListener, this);

	_touchListener = EventListenerTouchOneByOne::create();
	_touchListener->setSwallowTouches(true);
	_touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
    
    //auto actionFadeIn = FadeTo::create(2,255);
    //auto sequenceStart = Sequence::create(actionFadeIn,CallFunc::create(CC_CALLBACK_0(GameScene::start,this)),nullptr);
    //scoreLabel->runAction(sequenceStart);

	_lastTimeClicked = 0;
	this->setupUI();
	this->setupDialogUI();
	//tm.start = get_timestamp();
	//Director::getInstance()->getEventDispatcher()->setEnabled(false);

	//_testLabel = Label::createWithTTF(_szWeaponTotalStr, "fonts/SAF.otf", 18 * Land::deltaScale);
	//_testLabel->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	//_testLabel->setColor(Color3B::BLACK);
	//this->addChild(_testLabel, 14102);
	_disTime = DELTA_TIME / ScreenManager::Instance()->getDelayTimeDevice();

    return true;
}

void GameScene::onPause()
{
	if (!_clickPause)
	{
		_clickPause = true;
		_blackBg->setOpacity(OPACITY_BACKGROUND_BLACK);
		_boardNoti->setOpacity(255);

		_resumeBtt->setOpacity(255);
		_reloadBtt->setOpacity(255);
		_homeBtt->setOpacity(255);
		_musicBtt->setOpacity(255);
		_soundBtt->setOpacity(255);

		_resumeBtt->setTouchEnabled(true);
		_reloadBtt->setTouchEnabled(true);
		_homeBtt->setTouchEnabled(true);
		_musicBtt->setTouchEnabled(true);
		_soundBtt->setTouchEnabled(true);

	}
}

void GameScene::touchPauseEvent(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		onPause();
	}
}

void GameScene::touchResumeEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		_clickPause = false;
		_blackBg->setOpacity(0);
		_boardNoti->setOpacity(0);
		_resumeBtt->setOpacity(0);
		_reloadBtt->setOpacity(0);
		_homeBtt->setOpacity(0);
		_musicBtt->setOpacity(0);
		_soundBtt->setOpacity(0);

		_resumeBtt->setTouchEnabled(false);
		_reloadBtt->setTouchEnabled(false);
		_homeBtt->setTouchEnabled(false);
		_musicBtt->setTouchEnabled(false);
		_soundBtt->setTouchEnabled(false);
	}
}

void GameScene::touchReloadEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		this->stopGame();
		ScreenManager::Instance()->gotoGameOver(false, ScreenManager::Instance()->GetLand()->getPathMap());
	}
}

void GameScene::touchHomeEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	this->unscheduleUpdate();
	ScreenManager::Instance()->gotoMainMenu();
}

void GameScene::touchOnOffMusicEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->turnOnOffMusic();
		if (ScreenManager::Instance()->isOnMusic()){
			ScreenManager::Instance()->playMusicGameScene();
			_musicBtt->loadTextures("mini/scene/musicbtt.png", "mini/scene/musicbtt.png", "");
		}
		else
			_musicBtt->loadTextures("mini/scene/musicbtt_no.png", "mini/scene/musicbtt_no.png", "");
	}
}

void GameScene::touchOnOffSoundEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->turnOnOffSound();
		if (ScreenManager::Instance()->isOnSound())
			_soundBtt->loadTextures("mini/scene/soundbtt.png", "mini/scene/soundbtt.png", "");
		else
			_soundBtt->loadTextures("mini/scene/soundbtt_no.png", "mini/scene/soundbtt_no.png", "");
	}
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
    PhysicsBody *a = contact.getShapeA( )->getBody();
    PhysicsBody *b = contact.getShapeB( )->getBody();
    
	if (!_isMap15)
    {
			// items to land
			if (POINT_FIGHTER_ITEMS_BITMASK == a->getCollisionBitmask( )
				&& POINT_LAND_BITMASK == b->getCollisionBitmask() )
			{
				//if(!_isGameOver)
				ScreenManager::Instance()->GetFighter()->hitLand(a->getTag());
				//ScreenManager::Instance()->GetFighter()
			}
			else if( POINT_FIGHTER_ITEMS_BITMASK == b->getCollisionBitmask( )
					&& POINT_LAND_BITMASK == a->getCollisionBitmask() )
			{
				// land : a
				//actionAudio->playEffect("Sounds/fail.mp3", false, 1.0f, 1.0f, 1.0f);
				//if(!_isGameOver)
				ScreenManager::Instance()->GetFighter()->hitLand(b->getTag());
			}

    
		// items to enemies
		if(POINT_TARGET_BITMASK == a->getCollisionBitmask( )
		   && POINT_FIGHTER_ITEMS_BITMASK == b->getCollisionBitmask())
		{
			//if (!_isMap15)  
			ScreenManager::Instance()->GetFighter()->hitTarget(b->getTag());
			_rs = ScreenManager::Instance()->GetLand()->destroyEnemies(a->getTag());
				switch (_rs)
				{
				case DESTROY_ENEMY_BADKILL:
					_isGameOver = true;
					ScreenManager::Instance()->GetFighter()->hitLand(b->getTag());
					ScreenManager::Instance()->GetFighter()->gameOver(b->getTag());
					this->returnScoreScreen(false);
					break;
				case DESTROY_ENEMY_GOODKILL:
					if (--_itargetTotal <= 0)
						returnScoreScreen(true);
					sprintf(_szTargetTotalStr, " x %d ", _itargetTotal);
					_targetLabel->setString(_szTargetTotalStr);
					break;
				}
		}
		else if(POINT_TARGET_BITMASK == b->getCollisionBitmask( )
				&& POINT_FIGHTER_ITEMS_BITMASK == a->getCollisionBitmask())
		{
			//if (!_isMap15)
			ScreenManager::Instance()->GetFighter()->hitTarget(a->getTag());
			_rs = ScreenManager::Instance()->GetLand()->destroyEnemies(b->getTag());
				switch (_rs)
				{
				case DESTROY_ENEMY_BADKILL:
					_isGameOver = true;
					ScreenManager::Instance()->GetFighter()->hitLand(a->getTag());
					ScreenManager::Instance()->GetFighter()->gameOver(a->getTag());
					this->returnScoreScreen(false);
					break;
				case DESTROY_ENEMY_GOODKILL:
					if (--_itargetTotal <= 0)
						returnScoreScreen(true);
					sprintf(_szTargetTotalStr, " x %d ", _itargetTotal);
					_targetLabel->setString(_szTargetTotalStr);
					break;
				}
        
		}
	}
    // with special map
	//int al = (int)a->getCollisionBitmask();
	//int bl = (int)b->getCollisionBitmask();
	if (_isSpecialMap){
		if (POINT_FIGHTER_BITMASK == b->getCollisionBitmask()
			&& POINT_TARGET_ROCKET_BITMASK == a->getCollisionBitmask())
		{
			ScreenManager::Instance()->GetFighter()->eatRocket();
			ScreenManager::Instance()->GetLand()->hitWeaponEnemies(a->getTag());
				returnScoreScreen(false);
		}
		else if (POINT_TARGET_ROCKET_BITMASK == b->getCollisionBitmask()
			&& POINT_FIGHTER_BITMASK == a->getCollisionBitmask())
		{
			ScreenManager::Instance()->GetFighter()->eatRocket();
			ScreenManager::Instance()->GetLand()->hitWeaponEnemies(b->getTag());
				returnScoreScreen(false);
		}

		/////////

		if (_isMap14)
		{
			// antirocket and rocket !!
			if (POINT_ANTI_ROCKET_FIGHTER == b->getCollisionBitmask()
				&& POINT_TARGET_ROCKET_BITMASK == a->getCollisionBitmask())
			{
				ScreenManager::Instance()->GetLand()->hitWeaponEnemies(a->getTag());
			}
			else if (POINT_TARGET_ROCKET_BITMASK == b->getCollisionBitmask()
				&& POINT_ANTI_ROCKET_FIGHTER == a->getCollisionBitmask())
			{
				ScreenManager::Instance()->GetLand()->hitWeaponEnemies(b->getTag());
			}
		}
		else // 15!!
		{
			// gun and target !!
			if (POINT_TARGET_BITMASK == a->getCollisionBitmask()
				&& POINT_VIEWER_ITEMS_BITMASK == b->getCollisionBitmask())
			{
				_rs = ScreenManager::Instance()->GetLand()->destroyEnemies(a->getTag());
				if (_rs == DESTROY_ENEMY_BADKILL)
					returnScoreScreen(false);
				else if (_rs == DESTROY_ENEMY_GOODKILL)
				{
					if (--_itargetTotal <= 0)
						returnScoreScreen(true);
					sprintf(_szTargetTotalStr, " x %d ", _itargetTotal);
					_targetLabel->setString(_szTargetTotalStr);
				}
				//_fighter->hitRocket(b->getTag());
			}
			else if (POINT_VIEWER_ITEMS_BITMASK == a->getCollisionBitmask()
				&& POINT_TARGET_BITMASK == b->getCollisionBitmask())
			{
				_rs = ScreenManager::Instance()->GetLand()->destroyEnemies(b->getTag());
				if (_rs == DESTROY_ENEMY_BADKILL)
					returnScoreScreen(false);
				else if (_rs == DESTROY_ENEMY_GOODKILL)
				{
					if (--_itargetTotal <= 0)
						returnScoreScreen(true);
					sprintf(_szTargetTotalStr, " x %d ", _itargetTotal);
					_targetLabel->setString(_szTargetTotalStr);
				}
				//_fighter->hitRocket(a->getTag());
			}


			// rocket - viewer
			if (POINT_TARGET_ROCKET_BITMASK == a->getCollisionBitmask()
				&& POINT_VIEWER_ITEMS_BITMASK == b->getCollisionBitmask())
			{
				ScreenManager::Instance()->GetLand()->hitWeaponEnemies(a->getTag());
			}
			else if (POINT_VIEWER_ITEMS_BITMASK == a->getCollisionBitmask()
				&& POINT_TARGET_ROCKET_BITMASK == b->getCollisionBitmask())
			{
				ScreenManager::Instance()->GetLand()->hitWeaponEnemies(b->getTag());
			}
		}
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
const bool& GameScene::checkDeltaTime()
{
	//struct timeval now;
	if (gettimeofday(&_currTimer, nullptr) != 0)
	{
		//CCLOG("error in gettimeofday");
		return true; // bomb anyway
	}

	if (_currTimer.tv_sec == _oldTimer.tv_sec) // same second
	{
		if (_currTimer.tv_usec < _oldTimer.tv_usec + _disTime)
			return false;
	} // 
//	else if (_currTimer.tv_sec == _oldTimer.tv_sec + 1)
//	{
//		if (_currTimer.tv_usec >= _oldTimer.tv_usec - _disTime)
//		{
//			return true;
//		}
//		else
//			return false;
//	}
	//else
		return true;
	//_currTimer = (now.tv_sec) * 100 + (now.tv_usec) / 10000;
	//sprintf(_szTest, "s:%d|ms:%d|rs:%d|,", now.tv_sec, now.tv_usec, _currTimer);
	//_testLabel->setString(_szTest);
}
//inline long long getCurrentTime()
//{
//	struct timeval now;
//	if (gettimeofday(&now, nullptr) != 0)
//	{
//		CCLOG("error in gettimeofday");
//		return 0;
//	}
//	//long long test = (now.tv_sec) * 100 + (now.tv_usec) / 10000.0f;
//	return (now.tv_sec) + (now.tv_usec) / 1000.0f;
//}

//double getCurMillisecond()
//{
//	cocos2d::timeval now_time;
//	cocos2d::CCTime::gettimeofdayCocos2d(&now_time, NULL);
//	double millisecond = ((double)now_time.tv_sec) * 1000 + now_time.tv_usec / 1000;
//	return millisecond;
//}

bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event )
{
	if (_clickPause)
		return false;
	//if (_isWelcome)
	//	return false;

	//if (_isWelcome)
	//{
	//	_isWelcome = !_isWelcome;
	//	_desciptContent->stopAllActions();
	//	_desciptContent->setOpacity(0);
	//	_blackBg->setOpacity(0);
	//	this->start();
	//	return false;
	//}
	//
	//else
	//{
	//	_desciptContent->stopAllActions();
	//	_desciptContent->setOpacity(0);
	//	_blackBg->setOpacity(0);
	//	this->start();
	//}

    //return false;
    if(!_isGameOver)
    {
		if(Land::isMoving == true){
            if(_isMap15)
            {
				ScreenManager::Instance()->GetFighter()->Shoot(touch->getLocation());
            }
            else
            {
				if (this->checkDeltaTime())
				{
					if (_iweaponTotal-- > 0){
						ScreenManager::Instance()->GetFighter()->Drop();
						sprintf(_szWeaponTotalStr, " x %d ", _iweaponTotal);
						_weaponLabel->setString(_szWeaponTotalStr);
					}
					_oldTimer = _currTimer;
				}

				//cocos2d::ProfilingEndTimingBlock("aa");

				//_currentTime = getCurrentTime();
				//if (_currentTime > _lastTimeClicked + 50)
				//{
				//	_lastTimeClicked = _currentTime;
				//	if (!_fighter->Drop())
				//	{
				//		scoreLabel->setString("Empty weapons");
				//		returnScoreScreen();
				//	}
				//}

            //scoreLabel->setString( "Drop!!" );
            }
        }
    }
    return true;
}

void GameScene::update( float dt )
{
	ScreenManager::Instance()->GetLand()->updateLandPositionToTheLeft();
	if (!_isMap15)
		ScreenManager::Instance()->GetFighter()->updateBombs();
    // update position of land and enemies
    // try to put enemies in land => moving with land 
}

void GameScene::stopGame()
{
	_isGameOver = true;
	this->unscheduleUpdate();
	Land::isMoving = false;
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	//delete _land;
}
void GameScene::returnScoreScreen(const bool& _isCompleted)
{
	this->stopGame();
	ScreenManager::Instance()->gotoGameOver(_isCompleted, ScreenManager::Instance()->GetLand()->getPathMap());
}

void GameScene::start()
{
	//ScreenManager::Instance()->cleanUpMainMenu();
	//ScreenManager::Instance()->cleanUpGameOver();
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sounds/heli_long.mp3", true);

	if (_isMapRandom3)
	{
		Enemy1->removeFromParent();
		Enemy2->removeFromParent();
		Enemy3->removeFromParentAndCleanup(true);
	}
	if (_isMapRandom6)
	{
		Enemy1->removeFromParent();
		Enemy2->removeFromParent();
		Enemy3->removeFromParent();
		Enemy4->removeFromParent();
		Enemy5->removeFromParent();
		Enemy6->removeFromParentAndCleanup(true);
	}

	
	ScreenManager::Instance()->GetLand()->startMoving();
    this->scheduleUpdate( );
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	ScreenManager::Instance()->playMusicGameScene();

	//*_pauseButton, *_resumeBtt, *_reloadBtt, *_homeBtt, *_musicBtt, *_soundBtt;
	_pauseButton->setTouchEnabled(true);
//    this->schedule(schedule_selector(GameScene::updateFPS), 0);
    Land::isMoving = true;
	//Director::getInstance()->getEventDispatcher()->setEnabled(true);
}

void GameScene::setupUI()
{
	// htop 1
	float xblank_top = 0.05 * visibleSize.height + origin.y;
	float ytop1 = visibleSize.height * 0.95 + origin.y - SIZE_AHALF_BTT_SPEC * Land::deltaScale;
	float xSpec = xblank_top + SIZE_AHALF_BTT_SPEC * Land::deltaScale;
	float xfighter = xblank_top + SIZE_BTT_SPEC * Land::deltaScale + xblank_top;

	//// add fighter
	if (ScreenManager::Instance()->CurrentMap() == MAP_14){
		//_fighter = ScreenManager::Instance()->getNewFighter(this, Point(xfighter, ytop1), MAP_14);//new Fighter(this, Point(xfighter, ytop1), MAP_14);
		ScreenManager::Instance()->setUpNewFighter(this, Point(xfighter, ytop1), MAP_14);
		_isSpecialMap = true;
		_isMap14 = true;
	}
	else if (ScreenManager::Instance()->CurrentMap() == MAP_15)
	{
		ScreenManager::Instance()->setUpNewFighter(this, Point(xfighter, ytop1), MAP_15);
		//_fighter = ScreenManager::Instance()->getNewFighter(this, Point(xfighter, ytop1), MAP_15);//new Fighter(this, Point(xfighter, ytop1), MAP_15);
		_isMap15 = true;
		_isSpecialMap = true;
		//_isUnlimitedGun = true;
	}
	else{
		ScreenManager::Instance()->setUpNewFighter(this, Point(xfighter, ytop1));
		//_fighter = ScreenManager::Instance()->getNewFighter(this, Point(xfighter, ytop1));;//new Fighter(this, Point(xfighter, ytop1));
	}
		
		
	////// weapon totals
	
	ScreenManager::Instance()->GetLand()->getWeaponsAndTarget(_iweaponTotal, _itargetTotal);
	if (!_isMap14)
		ScreenManager::Instance()->GetLand()->setPositionSpecialBtt(Point(xSpec, ytop1));
	else
		ScreenManager::Instance()->GetFighter()->setAntiRocketMap14(Point(xSpec, ytop1));

	if (!_isMap15)
	{
		sprintf(_szWeaponTotalStr, " x %d", _iweaponTotal);
		_weaponLabel = Label::createWithTTF(_szWeaponTotalStr, "fonts/SAF.otf", 20 * Land::deltaScale);
		_weaponLabel->setColor(Color3B::WHITE);
		this->addChild(_weaponLabel, 4102);

		auto weaponIco = Sprite::create(MapProcessor::Instance()->getWeaponsSpriteFrameName());
		weaponIco->setScale(Land::deltaScale);
		if (ScreenManager::Instance()->GetLand()->isSpecialButtonExist())
		{
			float ytop2 = visibleSize.height * 0.947 + origin.y - SIZE_BTT_SPEC * Land::deltaScale - weaponIco->getContentSize().height * 0.5 * Land::deltaScale;
			weaponIco->setPosition(Point(xblank_top + SIZE_AHALF_BTT_SPEC * Land::deltaScale * 0.25, ytop2));
		}
		else
		{
			// set up total bomb
			weaponIco->setPosition(Point(xSpec, ytop1));
		}
		this->addChild(weaponIco, 4103);
		_weaponLabel->setPosition(Point(weaponIco->getPositionX() + 
			weaponIco->getContentSize().width * 0.5 * Land::deltaScale
			+ _weaponLabel->getContentSize().width * 0.5, weaponIco->getPositionY()));
	}
	
	////// target totals

	_pauseButton = cocos2d::ui::Button::create();
	_pauseButton->setTouchEnabled(false);
	_pauseButton->loadTextures("mini/scene/pausebtt.png", "mini/scene/pausebtt.png", "");
	_pauseButton->setScale(Land::deltaScale);
	_pauseButton->setPosition(Point(visibleSize.width * 0.95 + origin.x - _pauseButton->getContentSize().width * 0.5 * Land::deltaScale, ytop1));
	_pauseButton->addTouchEventListener(CC_CALLBACK_2(GameScene::touchPauseEvent, this));
	
	this->addChild(_pauseButton, 4200);

	sprintf(_szTargetTotalStr, " x %d ", _itargetTotal);
	_targetLabel = Label::createWithTTF(_szTargetTotalStr, "fonts/SAF.otf", 20 * Land::deltaScale);
	_targetLabel->setColor(Color3B::WHITE);
	_targetLabel->setPosition(Point(_pauseButton->getPositionX() - _pauseButton->getContentSize().width * 0.5 * Land::deltaScale - _targetLabel->getContentSize().width 
		, ytop1));
	this->addChild(_targetLabel, 4201);

	auto deadHeadIco = Sprite::create("mini/scene/headdead.png");
	deadHeadIco->setScale(Land::deltaScale);
	deadHeadIco->setPosition(Point(_targetLabel->getPositionX() - _targetLabel->getContentSize().width * 0.5 - deadHeadIco->getContentSize().width * Land::deltaScale * 0.5, ytop1));
	this->addChild(deadHeadIco, 4205);
}

void GameScene::setupDialogUI()
{
	_blackBg = Sprite::create("mini/land/bg_nothing.jpg");
	_blackBg->setScale(visibleSize.width / 10);
	_blackBg->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(_blackBg, 8000);
	_blackBg->setOpacity(OPACITY_BACKGROUND_BLACK);

	_boardNoti = Sprite::create("mini/scene/board.jpg");
	_boardNoti->setScale(Land::deltaScale);
	_boardNoti->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(_boardNoti, 8100);
	_boardNoti->setOpacity(0);

	_homeBtt = cocos2d::ui::Button::create();
	_homeBtt->setTouchEnabled(false);
	_homeBtt->loadTextures("mini/scene/homebtt.png", "mini/scene/homebtt.png", "");
	_homeBtt->setScale(Land::deltaScale);
	_homeBtt->setPosition(Point(_boardNoti->getPositionX() - 0.36 * _boardNoti->getContentSize().width * Land::deltaScale, _boardNoti->getPositionY()));
	_homeBtt->addTouchEventListener(CC_CALLBACK_2(GameScene::touchHomeEvent, this));
	this->addChild(_homeBtt, 8130);

	_reloadBtt = cocos2d::ui::Button::create();
	_reloadBtt->setTouchEnabled(false);
	_reloadBtt->loadTextures("mini/scene/reloadbtt.png", "mini/scene/reloadbtt.png", "");
	_reloadBtt->setScale(Land::deltaScale);
	_reloadBtt->setPosition(Point(_boardNoti->getPositionX() - 0.18 * _boardNoti->getContentSize().width * Land::deltaScale, _boardNoti->getPositionY()));
	_reloadBtt->addTouchEventListener(CC_CALLBACK_2(GameScene::touchReloadEvent, this));
	this->addChild(_reloadBtt, 8120);

	_resumeBtt = cocos2d::ui::Button::create();
	_resumeBtt->setTouchEnabled(false);
	_resumeBtt->loadTextures("mini/scene/resumebtt.png", "mini/scene/resumebtt.png", "");
	_resumeBtt->setScale(Land::deltaScale);
	_resumeBtt->setPosition(Point(_boardNoti->getPositionX() , _boardNoti->getPositionY()));
	_resumeBtt->addTouchEventListener(CC_CALLBACK_2(GameScene::touchResumeEvent, this));
	this->addChild(_resumeBtt, 8110);

	_musicBtt = cocos2d::ui::Button::create();
	_musicBtt->setTouchEnabled(false);
	//ScreenManager::Instance()->turnOnOffMusic();
	if (ScreenManager::Instance()->isOnMusic())
		_musicBtt->loadTextures("mini/scene/musicbtt.png", "mini/scene/musicbtt.png", "");
	else
		_musicBtt->loadTextures("mini/scene/musicbtt_no.png", "mini/scene/musicbtt_no.png", "");
	_musicBtt->addTouchEventListener(CC_CALLBACK_2(GameScene::touchOnOffMusicEvent, this));
	_musicBtt->setScale(Land::deltaScale);
	_musicBtt->setPosition(Point(_boardNoti->getPositionX() + 0.18 * _boardNoti->getContentSize().width * Land::deltaScale, _boardNoti->getPositionY()));
	this->addChild(_musicBtt, 8140);

	_soundBtt = cocos2d::ui::Button::create();
	_soundBtt->setTouchEnabled(false);
	//ScreenManager::Instance()->turnOnOffMusic();
	if (ScreenManager::Instance()->isOnSound())
		_soundBtt->loadTextures("mini/scene/soundbtt.png", "mini/scene/soundbtt.png", "");
	else
		_soundBtt->loadTextures("mini/scene/soundbtt_no.png", "mini/scene/soundbtt_no.png", "");
	_soundBtt->addTouchEventListener(CC_CALLBACK_2(GameScene::touchOnOffSoundEvent, this));
	_soundBtt->setScale(Land::deltaScale);
	_soundBtt->setPosition(Point(_boardNoti->getPositionX() + 0.36 * _boardNoti->getContentSize().width * Land::deltaScale, _boardNoti->getPositionY()));
	this->addChild(_soundBtt, 8150);

	_boardNoti->setOpacity(0);
	_resumeBtt->setOpacity(0);
	_reloadBtt->setOpacity(0);
	_homeBtt->setOpacity(0);
	_musicBtt->setOpacity(0);
	_soundBtt->setOpacity(0);

	//////////////////////////////////////////////////////////////////////////
	if (ScreenManager::Instance()->IsWelcome3s())
	{	
		char szPath[25] = { 0 };
		sprintf(szPath, "mini/scene/ctn/%d.png", ScreenManager::Instance()->CurrentMap());
		_desciptContent = Sprite::create(szPath);
		float scaleY = visibleSize.height * 0.5 / _desciptContent->getContentSize().height;
		_desciptContent->setScale(visibleSize.width * 0.8 / _desciptContent->getContentSize().width,
			scaleY);
		_desciptContent->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.7 + origin.y));
		this->addChild(_desciptContent, 8900);

		auto delay = DelayTime::create(3.0f);
		auto actionFadeOut = FadeOut::create(1.0f);
		auto sequenceStart = Sequence::create(delay, actionFadeOut, CallFunc::create(CC_CALLBACK_0(GameScene::runTutorial, this)), nullptr);
		_desciptContent->runAction(sequenceStart);

		std::vector<std::string> listEnemiesTexture = MapProcessor::Instance()->getListEnemies();
		std::random_shuffle(listEnemiesTexture.begin(), listEnemiesTexture.end());
		float scaleTargetShow = Land::deltaScale * 1.25;
		if (ScreenManager::Instance()->CurrentMap() == MAP_9 || ScreenManager::Instance()->CurrentMap() == MAP_13)
			scaleTargetShow *= 1.6;
		if (listEnemiesTexture.size() == 3) // map 3
		{
			_isMapRandom3 = true;
			Enemy1 = Sprite::createWithSpriteFrameName(listEnemiesTexture[0]);

			float yTargetShow = _desciptContent->getPositionY()
				- _desciptContent->getContentSize().height * scaleY * 0.5
				- Enemy1->getContentSize().height * 1.5 * scaleTargetShow;
			
			Enemy1->setPosition(Point(_desciptContent->getPositionX(), yTargetShow));
			Enemy1->setScale(scaleTargetShow);
			this->addChild(Enemy1, 8911);

			Enemy2 = Sprite::createWithSpriteFrameName(listEnemiesTexture[1]);
			Enemy2->setPosition(Point(_desciptContent->getPositionX() - Enemy1->getContentSize().width * scaleTargetShow * 0.5
				- Enemy2->getContentSize().width  * scaleTargetShow, yTargetShow));
			Enemy2->setScale(scaleTargetShow);
			this->addChild(Enemy2, 8912);

			Enemy3 = Sprite::createWithSpriteFrameName(listEnemiesTexture[2]);
			Enemy3->setPosition(Point(_desciptContent->getPositionX() + Enemy1->getContentSize().width * scaleTargetShow * 0.5
				+ Enemy3->getContentSize().width  * scaleTargetShow, yTargetShow));
			Enemy3->setScale(scaleTargetShow);
			this->addChild(Enemy3, 8912);
		}
		else if (listEnemiesTexture.size() == 6) // map 6
		{
			_isMapRandom6 = true;

			Enemy1 = Sprite::createWithSpriteFrameName(listEnemiesTexture[0]);

			float yTargetShow = _desciptContent->getPositionY()
				- _desciptContent->getContentSize().height * scaleY * 0.5
				- Enemy1->getContentSize().height * 1.5 * Land::deltaScale;

			Enemy1->setPosition(Point(_desciptContent->getPositionX(), yTargetShow));
			Enemy1->setScale(scaleTargetShow);
			this->addChild(Enemy1, 8911);

			Enemy2 = Sprite::createWithSpriteFrameName(listEnemiesTexture[1]);
			Enemy2->setPosition(Point(_desciptContent->getPositionX() - Enemy1->getContentSize().width * scaleTargetShow * 0.5
				- Enemy2->getContentSize().width  * scaleTargetShow, yTargetShow));
			Enemy2->setScale(scaleTargetShow);
			this->addChild(Enemy2, 8912);

			Enemy3 = Sprite::createWithSpriteFrameName(listEnemiesTexture[2]);
			Enemy3->setPosition(Point(_desciptContent->getPositionX() + Enemy1->getContentSize().width * scaleTargetShow * 0.5
				+ Enemy3->getContentSize().width  * scaleTargetShow, yTargetShow));
			Enemy3->setScale(scaleTargetShow);
			this->addChild(Enemy3, 8912);

			//////////////////////////////////////////////////////////////////////////

			Enemy4 = Sprite::createWithSpriteFrameName(listEnemiesTexture[3]);
			float yTargetShowUnder = yTargetShow - Enemy4->getContentSize().height * 1.5 * scaleTargetShow;
			Enemy4->setPosition(Point(_desciptContent->getPositionX(), yTargetShowUnder));
			Enemy4->setScale(scaleTargetShow);
			this->addChild(Enemy4, 8913);
			
			Enemy5 = Sprite::createWithSpriteFrameName(listEnemiesTexture[4]);
			Enemy5->setPosition(Point(_desciptContent->getPositionX() - Enemy4->getContentSize().width * scaleTargetShow * 0.5
				- Enemy5->getContentSize().width  * scaleTargetShow, yTargetShowUnder));
			Enemy5->setScale(scaleTargetShow);
			this->addChild(Enemy5, 8914);

			Enemy6 = Sprite::createWithSpriteFrameName(listEnemiesTexture[5]);
			Enemy6->setPosition(Point(_desciptContent->getPositionX() + Enemy4->getContentSize().width * scaleTargetShow * 0.5
				+ Enemy6->getContentSize().width  * scaleTargetShow, yTargetShowUnder));
			Enemy6->setScale(scaleTargetShow);
			this->addChild(Enemy6, 8915);
		}

	}
	else
	{

		this->scheduleOnce(schedule_selector(GameScene::NoDesciptStart), 0.5f);
	}
}

void GameScene::runTutorial()
{
	_blackBg->setOpacity(0);
	Sprite* tut;
	if (ScreenManager::Instance()->CurrentMap() == MAP_1)
	{
		 tut = Sprite::create("mini/scene/ctn/tut_map1.png");
	}
	else if (ScreenManager::Instance()->CurrentMap() == MAP_2)
	{
		tut = Sprite::create("mini/scene/ctn/tut_map2.png");
	}
	else if (ScreenManager::Instance()->CurrentMap() == MAP_4)
	{
		tut = Sprite::create("mini/scene/ctn/tut_map4.png");
	}
	else if (ScreenManager::Instance()->CurrentMap() == MAP_14)
	{
		tut = Sprite::create("mini/scene/ctn/tut_map14.png");
	}
	else{
		this->start();
		return;
	}
		
	tut->setPosition(visibleSize.width / 2 + origin.x / 2, visibleSize.height / 2 + origin.y / 2);
	tut->setScale(visibleSize.width / tut->getContentSize().width, visibleSize.height / tut->getContentSize().height);
	this->addChild(tut,2890);

	tut->setOpacity(255);
	auto delay = DelayTime::create(2.0f);
	auto fadeout = FadeOut::create(0.5f);
	auto seqTut = Sequence::create(delay,fadeout, CallFunc::create(CC_CALLBACK_0(GameScene::start, this)), nullptr);
	tut->runAction(seqTut);
}

void GameScene::NoDesciptStart(float dt)
{
	_blackBg->setOpacity(0);
	this->start();
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if(Land::isMoving)
		onPause();
}
#endif






