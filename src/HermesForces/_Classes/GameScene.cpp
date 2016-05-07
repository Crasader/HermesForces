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
    
	_isTut1 = _isTut2 = _isTut3 = _isTut4 = /*_isTut5 = _isTut14 = */false;

	_isSpecialTutorial = false;
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

	_isFinishBombMeet = false;

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


	_lastTimeClicked = 0;
	this->setupUI();
	this->setupDialogUI();
	this->setupHelloUI();

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

		this->unscheduleUpdate();
		Land::isMoving = false;
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
		this->hideOptionBoard();
		this->scheduleUpdate();
		Land::isMoving = true;
	}
}

void GameScene::touchReloadEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		this->returnScoreScreen(false);
		this->hideOptionBoard();
		//this->stopGame();
		//ScreenManager::Instance()->gotoGameOver(false, ScreenManager::Instance()->GetLand()->getPathMap());
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
					ScreenManager::Instance()->GetFighter()->hitLand(b->getTag());
					ScreenManager::Instance()->GetFighter()->gameOver(b->getTag());
					this->returnScoreScreen(false);
					break;
				case DESTROY_ENEMY_GOODKILL:
					if (_isFinishBombMeet){
						_isFinishBombMeet = false;
						this->finishBombMeetMap1();
					}
					else
					{
						if (--_itargetTotal <= 0)
							returnScoreScreen(true);
						sprintf(_szTargetTotalStr, " x %d ", _itargetTotal);
						_targetLabel->setString(_szTargetTotalStr);

						auto fadeIn = FadeIn::create(0.25f);
						auto fadeOut = FadeOut::create(1.5f);
						auto seq = Sequence::create(fadeIn, fadeOut, nullptr);
						_focusLightNoTut->runAction(seq);
					}
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
					ScreenManager::Instance()->GetFighter()->hitLand(a->getTag());
					ScreenManager::Instance()->GetFighter()->gameOver(a->getTag());
					this->returnScoreScreen(false);
					break;
				case DESTROY_ENEMY_GOODKILL:
					if (_isFinishBombMeet){
						_isFinishBombMeet = false;
						this->finishBombMeetMap1();
					}
					else
					{
						if (--_itargetTotal <= 0)
							returnScoreScreen(true);
						sprintf(_szTargetTotalStr, " x %d ", _itargetTotal);
						_targetLabel->setString(_szTargetTotalStr);
						
						auto fadeIn = FadeIn::create(0.25f);
						auto fadeOut = FadeOut::create(1.5f);
						auto seq = Sequence::create(fadeIn, fadeOut, nullptr);
						_focusLightNoTut->runAction(seq);
					}
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
	return true;
}
bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event )
{
	if (_clickPause)
		return false;

	// for tut 1
	if (_isTut1)
	{
		_tutSprite->setOpacity(0);

		_focusLightBg = Sprite::create("mini/land/bg_nothing.jpg");
		_focusLightBg->setScale(visibleSize.width / 10);
		_focusLightBg->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		_focusLightBg->setOpacity(OPACITY_BACKGROUND_BLACK);
		this->addChild(_focusLightBg, 4297);
		
		_focusLight = Sprite::create("mini/scene/focus_light_white.png");
		_focusLight->setPosition(_weaponLabel->getPosition());
		_focusLight->setScale(Land::deltaScale * 1.5);
		_focusLight->setOpacity(50);
		this->addChild(_focusLight, 4299);

		auto fadeInLight = FadeIn::create(0.5f);
		auto sq = Sequence::create(fadeInLight, CallFunc::create(CC_CALLBACK_0(GameScene::runTutMap1, this)), nullptr);
		_focusLight->runAction(sq);

		_isTut1 = false;
		//this->playMusic();
		//this->start();

		return true;
	}
	else if (_isTut2)
	{
		_isTut2 = false;
		return true;
	}

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
						if (_iweaponTotal < 3)
						{
							_focusLight = Sprite::create("mini/scene/focus_light_red.png");
							_focusLight->setPosition(_weaponLabel->getPosition());
							_focusLight->setScale(Land::deltaScale);
							_focusLight->setOpacity(50);
							this->addChild(_focusLight, 4299);

							auto fadeIn = FadeIn::create(0.25f);
							auto delay = DelayTime::create(0.5f);
							auto fadeOut = FadeOut::create(0.5f);
							auto seq = Sequence::create(fadeIn, delay, fadeOut, nullptr);
							_focusLight->runAction(seq);
						}
						ScreenManager::Instance()->GetFighter()->Drop();
						sprintf(_szWeaponTotalStr, " x %d ", _iweaponTotal);
						_weaponLabel->setString(_szWeaponTotalStr);
					}
					_oldTimer = _currTimer;
				}
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

void GameScene::stopGame(float dt)
{	
	this->unscheduleUpdate();	
	if (ScreenManager::Instance()->isCompleStatusMapOver())
		ScreenManager::Instance()->gotoGameOver(ScreenManager::Instance()->GetLand()->getPathMap());
	else
		ScreenManager::Instance()->reloadGameScene();

}
void GameScene::returnScoreScreen(const bool& _isCompleted)
{
	if (_isGameOver)
		return;
	
	_isGameOver = true;
	ScreenManager::Instance()->GetFighter()->stopAllBooms();
	ScreenManager::Instance()->setResultCurrentMap(_isCompleted);
	Land::isMoving = false;
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();


	if (!_isCompleted)
	{
		auto fadein = FadeIn::create(0.25f);

		//missionfail
		auto failBg = Sprite::create("mini/scene/mission_fail.png");
		failBg->setScale(Land::deltaScale);
		failBg->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		failBg->setOpacity(0);
		this->addChild(failBg, 18000);

		auto fadeto = FadeTo::create(0.25f, 200);
		_blackBg->setOpacity(120);
		_blackBg->runAction(fadeto);

		failBg->runAction(fadein);
	}
	
	this->scheduleOnce(schedule_selector(GameScene::stopGame), 1.0f);
}

void GameScene::start()
{
	Land::isMoving = true;

	//ScreenManager::Instance()->cleanUpMainMenu();
	//ScreenManager::Instance()->cleanUpGameOver();
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sounds/heli_long.mp3", true);
	if (_isSpecialTutorial){
		if (ScreenManager::Instance()->CurrentMap() == MAP_14)
			ScreenManager::Instance()->GetFighter()->turnOffAntiRocketFading();
		else
			ScreenManager::Instance()->GetLand()->stopFadeInoutSpecBtt();
	}

	if (_isMapRandom3)
	{
		Enemy1->removeFromParent();
		bgEnemy1->removeFromParent();
		Enemy2->removeFromParent();
		bgEnemy2->removeFromParent();
		Enemy3->removeFromParent();
		bgEnemy3->removeFromParentAndCleanup(true);
	}
	if (_isMapRandom6)
	{
		Enemy1->removeFromParent();
		bgEnemy1->removeFromParent();
		Enemy2->removeFromParent();
		bgEnemy2->removeFromParent();
		Enemy3->removeFromParent();
		bgEnemy3->removeFromParent();
		Enemy4->removeFromParent();
		bgEnemy4->removeFromParent();
		Enemy5->removeFromParent();
		bgEnemy5->removeFromParent();
		Enemy6->removeFromParent();
		bgEnemy6->removeFromParentAndCleanup(true);
	}

	
	ScreenManager::Instance()->GetLand()->startMoving();
	ScreenManager::Instance()->GetFighter()->startMoving();
    this->scheduleUpdate( );
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	

	//*_pauseButton, *_resumeBtt, *_reloadBtt, *_homeBtt, *_musicBtt, *_soundBtt;
	_pauseButton->setTouchEnabled(true);
//    this->schedule(schedule_selector(GameScene::updateFPS), 0);
    
    //
    
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
		this->addChild(_weaponLabel, 4307);

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
		this->addChild(weaponIco, 4309);
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

	Sprite* deadHeadIco;
	if (ScreenManager::Instance()->CurrentMap() == MAP_7)
		deadHeadIco = Sprite::create("mini/scene/bomb.png");
	else
		deadHeadIco = Sprite::create("mini/scene/target.png");

	deadHeadIco->setScale(Land::deltaScale);
	deadHeadIco->setPosition(Point(_targetLabel->getPositionX() - _targetLabel->getContentSize().width * 0.5 - deadHeadIco->getContentSize().width * Land::deltaScale * 0.5, ytop1));
	this->addChild(deadHeadIco, 4205);
}

void GameScene::setupDialogUI()
{
	_blackBg = Sprite::create("mini/land/bg_nothing.jpg");
	_blackBg->setScale(visibleSize.width / 10);
	_blackBg->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(_blackBg, 2861);//2861
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

	_focusLightNoTut = Sprite::create("mini/scene/focus_light_white_no_tut.png");
	_focusLightNoTut->setPosition(_targetLabel->getPosition());
	_focusLightNoTut->setScale(Land::deltaScale * 1.5);
	_focusLightNoTut->setOpacity(50);
	this->addChild(_focusLightNoTut, 4199);
}


void GameScene::setupGuideUI()
{
	_desciptContent->setOpacity(0);
	_blackBg->setOpacity(0);

	if (ScreenManager::Instance()->CurrentMap() == MAP_1)
	{
		_isTut1 = true;

		//missionfail
		_tutSprite = Sprite::create("mini/scene/tut/guide_0.png");
		_tutSprite->setScale(visibleSize.width / _tutSprite->getContentSize().width, visibleSize.height / _tutSprite->getContentSize().height);
		_tutSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(_tutSprite, 2890);

	}
	else if (ScreenManager::Instance()->CurrentMap() == MAP_2)
	{
		_isTut2 = true;
		ScreenManager::Instance()->GetLand()->fadeInOutSpecBtt();
		_isSpecialTutorial = true;
		_blackBg->setOpacity(200);
		//auto fadeOut = FadeOut::create(1.0f);
		//auto sequenceStart = Sequence::create(fadeOut, CallFunc::create(CC_CALLBACK_0(GameScene::playMusic, this)),
		//	CallFunc::create(CC_CALLBACK_0(GameScene::start, this)), nullptr);
		//_blackBg->runAction(sequenceStart);
	}
	else if (ScreenManager::Instance()->CurrentMap() == MAP_3)
	{
		_focusLightBg = Sprite::create("mini/land/bg_nothing.jpg");
		_focusLightBg->setScale(visibleSize.width / 10);
		_focusLightBg->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		_focusLightBg->setOpacity(50);
		this->addChild(_focusLightBg, INDEX_LAYER_TARGET + 85);

		_focusLight = Sprite::create("mini/scene/focus_light_white.png");
		_focusLight->setPosition(ScreenManager::Instance()->GetLand()->focusLightPos);
		_focusLight->setScale(Land::deltaScale);
		_focusLight->setOpacity(50);
		this->addChild(_focusLight, INDEX_LAYER_TARGET + 87);

		//auto delay = DelayTime::create(1.0f);
		auto fadeInLight = FadeIn::create(0.25f);
		auto fadeInLightBg = FadeIn::create(0.25f);

		auto delayLight = DelayTime::create(1.0f);
		auto delayLightBg = DelayTime::create(1.0f);

		auto fadeOutLight = FadeOut::create(0.75f);
		auto fadeOutLightBg = FadeOut::create(0.5f);

		auto sqLightBg = Sequence::create(fadeInLightBg, delayLightBg, fadeOutLightBg,
			CallFunc::create(CC_CALLBACK_0(GameScene::playMusic, this)),
			CallFunc::create(CC_CALLBACK_0(GameScene::start, this)),
			nullptr);
		_focusLightBg->runAction(sqLightBg);

		auto sqLight = Sequence::create(fadeInLight, delayLight, fadeOutLight, nullptr);
		_focusLight->runAction(sqLight);

	}
	else if (ScreenManager::Instance()->CurrentMap() == MAP_4)
	{
		_isTut4 = true;
		_blackBg->setOpacity(200);
		ScreenManager::Instance()->GetLand()->fadeInOutSpecBtt();
		_isSpecialTutorial = true;
		//auto fadeOut = FadeOut::create(1.0f);
		//auto sequenceStart = Sequence::create(fadeOut, CallFunc::create(CC_CALLBACK_0(GameScene::playMusic, this)),
		//	CallFunc::create(CC_CALLBACK_0(GameScene::start, this)), nullptr);
		//_blackBg->runAction(sequenceStart);
	}
	else{
		auto fadeOut = FadeOut::create(0.25f);
		auto sequenceStart = Sequence::create(fadeOut, CallFunc::create(CC_CALLBACK_0(GameScene::playMusic, this)),
			CallFunc::create(CC_CALLBACK_0(GameScene::start, this)), nullptr);
		_blackBg->runAction(sequenceStart);
	}
}

void GameScene::setupHelloUI()
{
	//////////////////////////////////////////////////////////////////////////
	if (ScreenManager::Instance()->IsWelcome3s())
	{
		char szPath[60] = { 0 };
		sprintf(szPath, "mini/scene/tut/tut_%d.png", ScreenManager::Instance()->CurrentMap());	
		_desciptContent = Sprite::create(szPath);
		_desciptContent->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.6 + origin.y));
		_desciptContent->setOpacity(0);
		this->addChild(_desciptContent, 8900);
				
		float scaleY = Land::deltaScale;//visibleSize.height * 0.5 / _desciptContent->getContentSize().height;
		_desciptContent->setScale(Land::deltaScale);
		float delayFloat = 1.0f;
		if (ScreenManager::Instance()->isReloaded())
			delayFloat = 2.2f;
			
		auto delay = DelayTime::create(delayFloat);
		auto actionFadeIn = FadeIn::create(0.75f);
		auto actionFadeOut = FadeOut::create(0.25f);

		std::vector<std::string> listEnemiesTexture = MapProcessor::Instance()->getListEnemies();
		int sizeEnemies = listEnemiesTexture.size();
		if (sizeEnemies > 0)
		{
			std::random_shuffle(listEnemiesTexture.begin(), listEnemiesTexture.end());
			_blackBg->setOpacity(250);
			float scaleTargetShow = Land::deltaScale * 1.25;
			if (ScreenManager::Instance()->CurrentMap() == MAP_5){
				bgEnemy1 = Sprite::create("mini/army/plist/map_car/bg_2.png");
				bgEnemy2 = Sprite::create("mini/army/plist/map_car/bg_1.png");
				bgEnemy3 = Sprite::create("mini/army/plist/map_car/bg_1.png");
			}
			else if (ScreenManager::Instance()->CurrentMap() == MAP_8){
				// usa_b1_1
				bgEnemy1 = Sprite::create("mini/army/plist/map_car/usa_bg.png");
				bgEnemy2 = Sprite::create("mini/army/plist/map_car/usa_bg.png");
				bgEnemy3 = Sprite::create("mini/army/plist/map_car/usa_bg.png");
				bgEnemy4 = Sprite::create("mini/army/plist/map_car/usa_bg.png");
				bgEnemy5 = Sprite::create("mini/army/plist/map_car/usa_bg.png");
				bgEnemy6 = Sprite::create("mini/army/plist/map_car/usa_bg.png");
			}
			else if (ScreenManager::Instance()->CurrentMap() == MAP_11){
				scaleTargetShow *= 2.0;
				bgEnemy1 = Sprite::create("mini/army/plist/map_train/ja_bg.png");
				bgEnemy2 = Sprite::create("mini/army/plist/map_train/ja_bg.png");
				bgEnemy3 = Sprite::create("mini/army/plist/map_train/ja_bg.png");
			}
			else if (ScreenManager::Instance()->CurrentMap() == MAP_13){
				scaleTargetShow *= 2.0;
				bgEnemy1 = Sprite::create("mini/army/plist/map_train/ira_bg.png");
				bgEnemy2 = Sprite::create("mini/army/plist/map_train/ira_bg.png");
				bgEnemy3 = Sprite::create("mini/army/plist/map_train/ira_bg.png");
			}
			
			if (sizeEnemies == 3) // map 3 this->hideOptionBoard();
			{
				_isMapRandom3 = true;
				Enemy1 = Sprite::createWithSpriteFrameName(listEnemiesTexture[0]);

				float yTargetShow = _desciptContent->getPositionY()
					- _desciptContent->getContentSize().height * scaleY * 0.5
					- Enemy1->getContentSize().height * 1.5 * scaleTargetShow;

				Enemy1->setPosition(Point(_desciptContent->getPositionX(), yTargetShow));
				bgEnemy1->setPosition(Enemy1->getPosition());

				Enemy1->setScale(scaleTargetShow);
				bgEnemy1->setScale(scaleTargetShow);

				this->addChild(Enemy1, 8911);
				this->addChild(bgEnemy1, 8910);

				Enemy2 = Sprite::createWithSpriteFrameName(listEnemiesTexture[1]);
				Enemy2->setPosition(Point(_desciptContent->getPositionX() - Enemy1->getContentSize().width * scaleTargetShow * 0.5
					- Enemy2->getContentSize().width  * scaleTargetShow, yTargetShow));
				bgEnemy2->setPosition(Enemy2->getPosition());

				Enemy2->setScale(scaleTargetShow);
				bgEnemy2->setScale(scaleTargetShow);

				this->addChild(Enemy2, 8913);
				this->addChild(bgEnemy2, 8912);

				Enemy3 = Sprite::createWithSpriteFrameName(listEnemiesTexture[2]);
				Enemy3->setPosition(Point(_desciptContent->getPositionX() + Enemy1->getContentSize().width * scaleTargetShow * 0.5
					+ Enemy3->getContentSize().width  * scaleTargetShow, yTargetShow));
				bgEnemy3->setPosition(Enemy3->getPosition());

				Enemy3->setScale(scaleTargetShow);
				bgEnemy3->setScale(scaleTargetShow);

				this->addChild(Enemy3, 8915);
				this->addChild(bgEnemy3, 8914);

			}
			else if (sizeEnemies == 6) // map 6
			{
				_isMapRandom6 = true;

				Enemy1 = Sprite::createWithSpriteFrameName(listEnemiesTexture[0]);

				float yTargetShow = _desciptContent->getPositionY()
					- _desciptContent->getContentSize().height * scaleY * 0.5
					- Enemy1->getContentSize().height * 1.5 * Land::deltaScale;

				Enemy1->setPosition(Point(_desciptContent->getPositionX(), yTargetShow));
				bgEnemy1->setPosition(Enemy1->getPosition());

				Enemy1->setScale(scaleTargetShow);
				bgEnemy1->setScale(scaleTargetShow);

				this->addChild(Enemy1, 8911);
				this->addChild(bgEnemy1, 8910);

				Enemy2 = Sprite::createWithSpriteFrameName(listEnemiesTexture[1]);
				Enemy2->setPosition(Point(_desciptContent->getPositionX() - Enemy1->getContentSize().width * scaleTargetShow * 0.5
					- Enemy2->getContentSize().width  * scaleTargetShow, yTargetShow));
				bgEnemy2->setPosition(Enemy2->getPosition());

				Enemy2->setScale(scaleTargetShow);
				bgEnemy2->setScale(scaleTargetShow);

				this->addChild(Enemy2, 8913);
				this->addChild(bgEnemy2, 8912);

				Enemy3 = Sprite::createWithSpriteFrameName(listEnemiesTexture[2]);
				Enemy3->setPosition(Point(_desciptContent->getPositionX() + Enemy1->getContentSize().width * scaleTargetShow * 0.5
					+ Enemy3->getContentSize().width  * scaleTargetShow, yTargetShow));
				bgEnemy3->setPosition(Enemy3->getPosition());

				Enemy3->setScale(scaleTargetShow);
				bgEnemy3->setScale(scaleTargetShow);

				this->addChild(Enemy3, 8915);
				this->addChild(bgEnemy3, 8914);

				//////////////////////////////////////////////////////////////////////////

				Enemy4 = Sprite::createWithSpriteFrameName(listEnemiesTexture[3]);
				float yTargetShowUnder = yTargetShow - bgEnemy4->getContentSize().height * scaleTargetShow;
				Enemy4->setPosition(Point(_desciptContent->getPositionX(), yTargetShowUnder));
				bgEnemy4->setPosition(Enemy4->getPosition());

				Enemy4->setScale(scaleTargetShow);
				bgEnemy4->setScale(scaleTargetShow);

				this->addChild(Enemy4, 8917);
				this->addChild(bgEnemy4, 8916);

				Enemy5 = Sprite::createWithSpriteFrameName(listEnemiesTexture[4]);
				Enemy5->setPosition(Point(_desciptContent->getPositionX() - Enemy4->getContentSize().width * scaleTargetShow * 0.5
					- Enemy5->getContentSize().width  * scaleTargetShow, yTargetShowUnder));
				bgEnemy5->setPosition(Enemy5->getPosition());

				Enemy5->setScale(scaleTargetShow);
				bgEnemy5->setScale(scaleTargetShow);

				this->addChild(Enemy5, 8919);
				this->addChild(bgEnemy5, 8918);

				Enemy6 = Sprite::createWithSpriteFrameName(listEnemiesTexture[5]);
				Enemy6->setPosition(Point(_desciptContent->getPositionX() + Enemy4->getContentSize().width * scaleTargetShow * 0.5
					+ Enemy6->getContentSize().width  * scaleTargetShow, yTargetShowUnder));
				bgEnemy6->setPosition(Enemy6->getPosition());

				Enemy6->setScale(scaleTargetShow);
				bgEnemy6->setScale(scaleTargetShow);

				this->addChild(Enemy6, 8921);
				this->addChild(bgEnemy6, 8920);

			}
			auto sequenceStart = Sequence::create(actionFadeIn, delay, actionFadeOut, CallFunc::create(CC_CALLBACK_0(GameScene::startGame, this)), nullptr);
			_desciptContent->runAction(sequenceStart);
		}
		else
		{
			//Sequence::create(fadein, CallFunc::create(CC_CALLBACK_0(GameScene::runTutMap1, this)), nullptr);
			auto sequenceStart = Sequence::create(actionFadeIn, delay, actionFadeOut, CallFunc::create(CC_CALLBACK_0(GameScene::setupGuideUI, this)), nullptr);
			_desciptContent->runAction(sequenceStart);
		}
	}
	else
	{
		this->scheduleOnce(schedule_selector(GameScene::NoDesciptStart), 2.85f);
	}
}

void GameScene::NoDesciptStart(float dt)
{
    auto fadeOut = FadeOut::create(1.0f);
    auto sequenceStart = Sequence::create(fadeOut , CallFunc::create(CC_CALLBACK_0(GameScene::playMusic,this)),
                                                    CallFunc::create(CC_CALLBACK_0(GameScene::start,this)), nullptr);
    _blackBg->runAction(sequenceStart);
//	this->scheduleOnce(schedule_selector(GameScene::finishLoadingAndGoToStart), 1.0f);
}



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if(Land::isMoving)
		onPause();
}
#endif

void GameScene::playMusic()
{
	ScreenManager::Instance()->playMusicGameScene();
}

void GameScene::runTutMap1()
{
	//
	_iweaponTotal--;
	sprintf(_szWeaponTotalStr, " x %d ", _iweaponTotal);
	_weaponLabel->setString(_szWeaponTotalStr);

	this->scheduleOnce(schedule_selector(GameScene::runTutMap1StartGame), 1.0f);
}

void GameScene::finishBombMeetMap1()
{
	_focusLightBg = Sprite::create("mini/land/bg_nothing.jpg");
	_focusLightBg->setScale(visibleSize.width / 10);
	_focusLightBg->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	_focusLightBg->setOpacity(OPACITY_BACKGROUND_BLACK);
	this->addChild(_focusLightBg, 4197);

	_focusLight = Sprite::create("mini/scene/focus_light_white.png");
	_focusLight->setPosition(_targetLabel->getPosition());
	_focusLight->setScale(Land::deltaScale * 1.5);
	_focusLight->setOpacity(50);
	this->addChild(_focusLight, 4199);

	auto fadeInLight = FadeIn::create(0.5f);
	auto delay = DelayTime::create(0.75f);
	auto sq = Sequence::create(fadeInLight, CallFunc::create(CC_CALLBACK_0(GameScene::returnAfterBombMeetMap1, this)), nullptr);
	_focusLight->runAction(sq);
}


void GameScene::returnAfterBombMeetMap1()
{
	--_itargetTotal;
	sprintf(_szTargetTotalStr, " x %d ", _itargetTotal);
	_targetLabel->setString(_szTargetTotalStr);

	auto fadeOutLight = FadeOut::create(2.75f);
	auto fadeOutLightBg = FadeOut::create(2.75f);

	_focusLight->runAction(fadeOutLight);
	_focusLightBg->runAction(fadeOutLightBg);
}

void GameScene::runTutMap1StartGame(float dt)
{
	_isFinishBombMeet = true;
	_focusLight->setOpacity(0);
	_focusLightBg->setOpacity(0);
	this->playMusic();
	this->start();
	ScreenManager::Instance()->GetFighter()->Drop();
}

void GameScene::runTutMap4()
{
	_focusLightBg->setOpacity(0);
	_focusLight->setOpacity(0);
	_targetUnitTut4->setOpacity(0);
	_blackBg->setOpacity(0);
}

//void GameScene::runTutMap5()
//{
//
//}
//
//void GameScene::runTutMap14()
//{
//
//}

void GameScene::startGame()
{
	if (Land::isMoving)
		return;
	if (_isTut4)
	{
		_focusLightBg = Sprite::create("mini/land/bg_nothing.jpg");
		_focusLightBg->setScale(visibleSize.width / 10);
		_focusLightBg->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		_focusLightBg->setOpacity(50);
		this->addChild(_focusLightBg, 3150 + 85);

		_focusLight = Sprite::create("mini/scene/focus_light_white.png");
		_focusLight->setPosition(ScreenManager::Instance()->GetLand()->focusLightPos);
		_focusLight->setScale(Land::deltaScale);
		_focusLight->setOpacity(50);
		this->addChild(_focusLight, 3150 + 87);

		_targetUnitTut4 = Sprite::createWithSpriteFrameName("ene.png");
		_targetUnitTut4->setPosition(ScreenManager::Instance()->GetLand()->focusLightPos);
		_targetUnitTut4->setScale(Land::deltaScale);
		this->addChild(_targetUnitTut4, 3150 + 89);

		//auto delay = DelayTime::create(1.0f);
		auto fadeInLight = FadeIn::create(0.25f);
		auto fadeInLightBg = FadeTo::create(0.25f,180);

		auto delayLight = DelayTime::create(2.0f);
		auto delayLightBg = DelayTime::create(2.0f);

		auto fadeOutLight = FadeOut::create(0.2f);
		//auto fadeOutLightBg = FadeOut::create(0.5f);

		auto sqLightBg = Sequence::create(fadeInLightBg, delayLightBg,
			CallFunc::create(CC_CALLBACK_0(GameScene::playMusic, this)),
			CallFunc::create(CC_CALLBACK_0(GameScene::runTutMap4, this)),
			CallFunc::create(CC_CALLBACK_0(GameScene::start, this)),
			nullptr);
		_focusLightBg->runAction(sqLightBg);

		auto sqLight = Sequence::create(fadeInLight, delayLight, fadeOutLight, nullptr);
		_focusLight->runAction(sqLight);
		

		auto delayUnit = DelayTime::create(2.0f);
		auto fadeOut = FadeOut::create(0.2f);
		auto sqPoint = Sequence::create(delayUnit, fadeOut, nullptr);
		_targetUnitTut4->runAction(sqPoint);

		return;
	}
	_blackBg->setOpacity(0);
	this->playMusic();
	this->start();
}

void GameScene::hideOptionBoard()
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

