#include "Land.h"
#include "../Utility/Utility.h"
#include "../ScreenManager.h"

// TO DO :  change moving to delta time.

//float Land::distanceLand = 0;
bool Land::isMoving = false;
float Land::deltaScale = 1;
//float Land::movingLandTime = 0;
//float Land::enemiesMovingSpeed = 0;
//float Land::outOfScreenLength = 0;
//int Land::intoScreen = -1;
//int Land::outtoScreen = -1;
int Land::TypeWeapon = 0;
int Land::BombCount = 0;
float Land::PixelPerFPSBoomFall;
//int Land::ChosenMap;
cocos2d::Vec2 Land::origin;

float Land::pixelOfLandMoving;
float Land::pixelOfTargetMoving;

//int Land::OutOfLeftWidth = 0;
//int Land::OutOfRightWidth = 100;

Point Land::endPointFallingBomb;

bool Land::isCalculateEndPoint;

//bool Land::isClickSpecialBtt = false;

bool Land::isNight;

cocos2d::Size Land::visibleSize;

cocos2d::Size* Land::sizeBoom;
cocos2d::Vec2 Land::vec2Boom;

cocos2d::Layer* Land::parentLayer;
int Land::TimeDelayClickWeapon;
float Land::PosRocket = 0;

cocos2d::Point Land::FighterPos;

Land* Land::thisPointer = NULL;

//float physicsLand = 50;

#include "GameScene.h"
#include "MapProccessor.h"

//class Map;

Land::Land(cocos2d::Layer* layer , const int& stage)
{
	Land::isMoving = false;
	_mapStage = stage;
	k = 1;
	Land::isCalculateEndPoint = false;
	_SpecialButton = NULL;
	//Land::parentLayer = layer;
	_isTutorial = false;
	//Land::intoScreen = -1;
	//Land::outtoScreen = -1;
	//_objSpecial = 0;
	_targetCount = 0;
	//Size wsize = Director::getInstance()->getWinSize();
	Land::visibleSize = Director::getInstance( )->getVisibleSize( );
	Land::origin = Director::getInstance()->getVisibleOrigin();
	// init some info for bomb
	currentMap = new MapInfo();
	currentMap->copyFromSource(GameMap::ListMaps[stage]);
	
	// load map here !!
	startLandPath = currentMap->MapPath + "";	
	nextMap = currentMap->MapPath + "";

	startLandPath.append("_s.jpg");
	nextMap.append("_n.jpg");

	_land_start = Sprite::create(startLandPath);
	//_land_start->getContentSize().height
	Land::deltaScale = Director::getInstance()->getVisibleSize().height / _land_start->getContentSize().height;
	//Point centerPointMap = Point(_land_current->getContentSize().width * Land::deltaScale * 0.5, Director::getInstance()->getVisibleSize().height / 2);
	_land_start->setScale(Land::deltaScale);
	_land_start->setPosition(Point(Land::origin.x + _land_start->getContentSize().width * Land::deltaScale * 0.5, Land::origin.y + Director::getInstance()->getVisibleSize().height / 2));

	_land_next_1 = Sprite::create(nextMap);
	_land_next_2 = Sprite::create(nextMap);

	_land_next_1->setScale(Land::deltaScale);
	_land_next_2->setScale(Land::deltaScale);

	_land_next_current = _land_next_1;
	//Director::getInstance()->getVisibleSize().width + _land_next->getContentSize().width * Land::deltaScale * 0.5
	_xyNextMap = Point(Land::origin.x + Director::getInstance()->getVisibleSize().width + _land_next_current->getContentSize().width * Land::deltaScale * 0.5, 
						Land::origin.y + Director::getInstance()->getVisibleSize().height / 2);
	_land_next_1->setPosition(_xyNextMap);
	_land_next_2->setPosition(_xyNextMap);

	//int wc = Director::getInstance()->getVisibleSize().width;
	//int wl = _land_start->getContentSize().width;
	//int xl = _land_start->getPositionX();

	_distanceOfEndStartMapPieces = Land::origin.x + Director::getInstance()->getVisibleSize().width - 0.5 * _land_start->getContentSize().width * Land::deltaScale;
	_distanceOfEndNextMapPieces = Land::origin.x + Director::getInstance()->getVisibleSize().width - 0.5 * _land_next_current->getContentSize().width * Land::deltaScale;

	_pointXToDieStartMap = _land_start->getContentSize().width; _pointXToDieStartMap *= Land::deltaScale; _pointXToDieStartMap *= (-0.5); _pointXToDieStartMap += Land::origin.x;
	_pointXToDieNextMap = _land_next_current->getContentSize().width; _pointXToDieNextMap *= Land::deltaScale; _pointXToDieNextMap *= (-0.5); _pointXToDieNextMap += Land::origin.x;


	auto landBody = Sprite::create("mini/land/bg_nothing.jpg");
	landBody->setPosition(Point(Land::visibleSize.width / 2 + Land::origin.x, 0));
	landBody->setOpacity(0);
	auto boomBody = PhysicsBody::createBox(cocos2d::Size(10, 10));
	boomBody->setCollisionBitmask(POINT_LAND_BITMASK);
	boomBody->setContactTestBitmask(true);
	landBody->setPhysicsBody(boomBody);
	landBody->setScaleX(Director::getInstance()->getVisibleSize().width / 10);
	landBody->setScaleY(currentMap->physicsLandHeight * Land::deltaScale / 10);

	Land::LandPosY = currentMap->physicsLandHeight *  0.5  * Land::deltaScale  + origin.y;
	// add body land
	layer->addChild(landBody);
	//layer->addChild(bgMap);
	layer->addChild(_land_start);
	layer->addChild(_land_next_1);
	layer->addChild(_land_next_2);

	float deltaTimeByDevices = 1;// = Director::getInstance()->getVisibleSize().height / 480;

	Land::TypeWeapon = currentMap->WeaponType;
	Land::BombCount = currentMap->WeaponCount - 1; // index start from 0
	//Land::outOfScreenLength =  SIZE_OUT_OF_SCREEN * Land::deltaScale;
	Land::TimeDelayClickWeapon = 500; 

	// do something with fighter item
	MapProcessor::Instance()->doFighterItems(Land::TypeWeapon, Land::sizeBoom, Land::vec2Boom,Land::deltaScale, Land::TimeDelayClickWeapon);

	Land::pixelOfLandMoving = currentMap->PixelLand * ScreenManager::Instance()->getMinimunPixel();
	Land::pixelOfTargetMoving = currentMap->PixelTarget * ScreenManager::Instance()->getMinimunPixel();
	Land::PixelPerFPSBoomFall = currentMap->BombFallSpeed * ScreenManager::Instance()->getMinimunPixel();

	float w = Director::getInstance()->getWinSize().width;
	float h = Director::getInstance()->getWinSize().height;

	 // reset position
	parent = (GameScene*)layer;

	Land::parentLayer = layer;
	setUpSpecialAndAddTarget(layer);
	
	// show dialog target


	_delayTimeClickSpecial = 0;
	_lastTime = 0;

	_indexOutTarget = 0;
	//_indexInTarget = _targetCount;
	//_indexInTarget = 0;
	//Land::OutOfLeftWidth = 0;
	// TODO : remove outofRight
	//Land::OutOfRightWidth = Director::getInstance()->getVisibleSize().width + 200;

	_pixelTargetMoving = 0;
	_isNextLandAvaiable = false;
	_isEndOfStartLand = false;
	_isAllNextLandAvaiable = false;
	_isNext1 = true;
	Land::thisPointer = this;

	if (gettimeofday(&_oldTimer, nullptr) == 0)
	{
		_oldTimer.tv_sec = 0;
		_oldTimer.tv_usec = 0;
	}
	_isClickSpecialBtt = false;
}

//cocos2d::Sprite* Land::getLandSprite()
//{
//	return _land;
//}

void Land::stopMoveLand(const bool& isGood)
{
	//Land::isMoving = false;
	parent->returnScoreScreen(isGood);
}

void Land::addTargets(cocos2d::Layer* layer)
{
	float LandHeight = currentMap->physicsLandHeight * Land::deltaScale;
	int list6EnemiesItems[6];
	int layerId = INDEX_LAYER_TARGET;

	if (MapProcessor::Instance()->isTargetVisible())
		layerId = 3150;
	// prepair targets

	if (currentMap->targetPlayingType == GAME_PLAY_TYPE_RANDOM_3) // 3/30
	{
		// get random fake
		MapProcessor::Instance()->getRandomEnemies(list6EnemiesItems, currentMap->targetPlayingType);
		for (int i = 2; i < currentMap->CountItems; i++)
		{
			// TO DO : && => ||
			if (i != list6EnemiesItems[0] && i != list6EnemiesItems[1] && i != list6EnemiesItems[2])
			{
				_listTargets.push_back(new Target(Point(currentMap->Items[i] * Land::deltaScale, LandHeight), _targetCount, currentMap->Items[0]));
			}
			else
			{
				_listTargets.push_back(new Target(Point(currentMap->Items[i] * Land::deltaScale, LandHeight), _targetCount, currentMap->Items[1]));
			}
			//_listTargets[_targetCount] = new Target(Point(currentMap->Items[i] * Land::deltaScale,LandHeight),_targetCount,currentMap->Items[0]);
			//else
			//	_listTargets[_targetCount] = new Target(Point(currentMap->Items[i] * Land::deltaScale,LandHeight),_targetCount,currentMap->Items[1]);
			layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + i);
			//_targetCount++;
		}
	}
	else 	if (currentMap->targetPlayingType == GAME_PLAY_TYPE_RANDOM_6) // 3/30
	{
		// get random fake
		MapProcessor::Instance()->getRandomEnemies(list6EnemiesItems, currentMap->targetPlayingType);
		for (int i = 2; i < currentMap->CountItems; i++)
		{
			// TO DO : && => ||
			if (i != list6EnemiesItems[0] && i != list6EnemiesItems[1] && i != list6EnemiesItems[2] && i != list6EnemiesItems[3] && i != list6EnemiesItems[4] && i != list6EnemiesItems[5]){
				//_listTargets[_targetCount] = new Target(Point(currentMap->Items[i] * Land::deltaScale, LandHeight), _targetCount, currentMap->Items[0]);
				_listTargets.push_back(new Target(Point(currentMap->Items[i] * Land::deltaScale, LandHeight), _targetCount, currentMap->Items[0]));
			}
			else
			{
				_listTargets.push_back(new Target(Point(currentMap->Items[i] * Land::deltaScale, LandHeight), _targetCount, currentMap->Items[1]));
			}
			//_listTargets[_targetCount] = new Target(Point(currentMap->Items[i] * Land::deltaScale,LandHeight),_targetCount,currentMap->Items[1]);
			layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + i);
			//_targetCount++;
		}
	}
	else 	if (currentMap->targetPlayingType == GAME_PLAY_RANDOM_5_TARGETS) // 3/30
	{
		MapProcessor::Instance()->getRandomEnemies(list6EnemiesItems, currentMap->targetPlayingType);
		for (int i = 2; i < currentMap->CountItems; i++)
		{
			// TO DO : && => ||
			if (i != list6EnemiesItems[0] && i != list6EnemiesItems[1] && i != list6EnemiesItems[2] && i != list6EnemiesItems[3] && i != list6EnemiesItems[4]){
				//_listTargets[_targetCount] = new Target(Point(currentMap->Items[i] * Land::deltaScale, LandHeight), _targetCount, currentMap->Items[0]);
				_listTargets.push_back(new Target(Point(currentMap->Items[i] * Land::deltaScale, LandHeight), _targetCount, currentMap->Items[0]));
			}
			else{
				_listTargets.push_back(new Target(Point(currentMap->Items[i] * Land::deltaScale, LandHeight), _targetCount, currentMap->Items[1]));
				//_listTargets[_targetCount] = new Target(Point(currentMap->Items[i] * Land::deltaScale, LandHeight), _targetCount, currentMap->Items[1]);
			}
			layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + i);
			//_targetCount++;
		}
	}
	else 	if (currentMap->targetPlayingType == GAME_PLAY_RANDOM_ENEMIES_POSITION) // 3/30
	{
		for (int i = 1; i < (currentMap->CountItems * 2) + 1; i = i + 2)
		{
			int randPos = cocos2d::random(currentMap->Items[i], currentMap->Items[i + 1]);
			//_listTargets[_targetCount] = new Target(Point(randPos * Land::deltaScale,LandHeight),_targetCount,currentMap->Items[0]);
			_listTargets.push_back(new Target(Point(randPos * Land::deltaScale, LandHeight), _targetCount, currentMap->Items[0]));
			layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + i);
			//_targetCount++;
		}
	}
	else 	if (currentMap->targetPlayingType == GAME_PLAY_ENEMIES_DIFF_HEIGHT) // 3/30
	{
		for (int i = 0; i < currentMap->CountItems; i = i + 3)
		{
			//_listTargets[_targetCount] = new Target(Point(currentMap->Items[i+1] * Land::deltaScale,currentMap->Items[i+2] * Land::deltaScale),_targetCount,currentMap->Items[i]);
			_listTargets.push_back(new Target(Point(currentMap->Items[i + 1] * Land::deltaScale, currentMap->Items[i + 2] * Land::deltaScale), _targetCount, currentMap->Items[i]));
			layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + i);
			//_targetCount++;
		}
	}
	else if (currentMap->targetPlayingType == GAME_PLAY_TYPE_MAP_FOCUS_TUTORIAL) // 3/30
	{
		float w4on5 = visibleSize.width * 0.8;
		float delta = currentMap->Items[1] * Land::deltaScale - w4on5;
		focusLightPos = Point(w4on5, (LandHeight  * 0.5) + (10 * 0.5 * Land::deltaScale));
		
		_listTargets.push_back(new Target(Point(w4on5,LandHeight), _targetCount, currentMap->Items[0]));
		layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + 90);

		_listTargets.push_back(new Target(Point(currentMap->Items[3] * Land::deltaScale - delta, LandHeight), _targetCount, currentMap->Items[2]));
		layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + 91);

		for (int i = 4; i < currentMap->CountItems; i = i + 2)
		{
			_listTargets.push_back(new Target(Point(currentMap->Items[i + 1] * Land::deltaScale - delta, LandHeight), _targetCount, currentMap->Items[i]));
			layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + i);
		}
	}
	else if (currentMap->targetPlayingType == GAME_PLAY_TYPE_MAP_1_TUTORIAL) // 3/30
	{
		/// BEGIN for tut 1
		float posYFighter = visibleSize.height * 0.95 + origin.y - SIZE_AHALF_BTT_SPEC * Land::deltaScale;
		float posYBomb = posYFighter - 0.5 * Land::sizeBoom->height * Land::deltaScale - FIGHTER_POS_BOMB;
		float distanceBombToLand = posYBomb - LandHeight - 0.5 * Land::sizeBoom->height * Land::deltaScale;
		//+ 185_fighter->getContentSize().width * 0.5 * Land::deltaScale
		float xblank_top = 0.05 * visibleSize.height + origin.y;
		float posXMeet = xblank_top + SIZE_BTT_SPEC * Land::deltaScale + xblank_top + 185/*_fighter->getContentSize().width*/ * 0.5 * Land::deltaScale;
		
		float distanceMeetBombToTarget1st = posXMeet + distanceBombToLand + 45 * Land::deltaScale;
		if (!ScreenManager::Instance()->IsWelcome3s())
			distanceMeetBombToTarget1st += 450 * Land::deltaScale;

		//float timeFromBombToLand = distanceBombToLand / Land::PixelPerFPSBoomFall;
		//float distanceMeetBombToTarget1st = timeFromBombToLand * Land::pixelOfTargetMoving;
		/// END for tut 1

		_listTargets.push_back(new Target(Point(distanceMeetBombToTarget1st, LandHeight), _targetCount, TARGET_IS_IRAQ));
		layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + 1);

		_listTargets.push_back(new Target(Point(distanceMeetBombToTarget1st + 1050 * Land::deltaScale , LandHeight), _targetCount, TARGET_IS_IRAQ));
		layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + 2);

		_listTargets.push_back(new Target(Point(distanceMeetBombToTarget1st + 1960 * Land::deltaScale, LandHeight), _targetCount, TARGET_IS_IRAQ));
		layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + 3);

		_listTargets.push_back(new Target(Point(distanceMeetBombToTarget1st + 2750 * Land::deltaScale, LandHeight), _targetCount, TARGET_IS_IRAQ));
		layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + 4);

		_listTargets.push_back(new Target(Point(distanceMeetBombToTarget1st + 3599 * Land::deltaScale, LandHeight), _targetCount, TARGET_IS_IRAQ));
		layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + 5);
	}
	else
	{
		for (int i = 0; i < currentMap->CountItems; i = i + 2)
		{
			//_listTargets[_targetCount] = new Target(Point(currentMap->Items[i+1] * Land::deltaScale,LandHeight),_targetCount,currentMap->Items[i]);
			_listTargets.push_back(new Target(Point(currentMap->Items[i + 1] * Land::deltaScale, LandHeight), _targetCount, currentMap->Items[i]));
			layer->addChild(_listTargets[_targetCount++]->getSprite(), layerId + i);
			//_targetCount++;
		}
	}

	
}

const int& Land::destroyEnemies(const int& idTag)
{
	// recheck
	return _listTargets[idTag]->die();
}

void Land::detectInScreen()
{
	// show target here
	// show backgground here => 2 action ==> done ==> click later!!
	for (int i = _indexOutTarget; i< _targetCount; i++)
	{
		_listTargets[i]->detectTarget();
	}
}

void Land::preReleaseLand()
{
	for (int i = 0; i < _listTargets.size(); i++)
	{
		delete _listTargets[i];
	}
	delete currentMap;
	//Land::thisPointer = NULL;
}

void Land::fadeInOutSpecBtt()
{
	_isTutorial = true;
	if (_SpecialButton == NULL)
		return;
	
	//_SpecialButton->loadTextures("mini/land/special/btt_flare.png", "mini/land/special/btt_flare.png", "");
	auto fadein = FadeTo::create(0.1f, 0);
	auto fadeOut = FadeTo::create(0.5f, 255);
	auto seq = Sequence::create(fadein, fadeOut, nullptr);
	_SpecialButton->runAction(RepeatForever::create(seq));
	_SpecialButton->setTouchEnabled(true);
}

void Land::stopFadeInoutSpecBtt()
{
	_isTutorial = false;
	_SpecialButton->stopAllActions();
	_SpecialButton->setOpacity(255);
}

Land::~Land()
{
	this->preReleaseLand();
	//Land::thisPointer = NULL;
}

float Land::LandPosY = 0;

void Land::setUpSpecialAndAddTarget(cocos2d::Layer* layer)
{
	Land::isNight = false;
	if (currentMap->Special == SPECIAL_HELPER_NO_SPEC || currentMap->Special == SPECIAL_HELPER_ANTI_ROCKET){
		addTargets(layer);
		return;
	}

	_SpecialButton = cocos2d::ui::Button::create();
	_SpecialButton->setTouchEnabled(false);
	switch (currentMap->Special)
	{
	case SPECIAL_HELPER_LIGHT:
		addTargets(layer);
		_backgroundSpecial = Sprite::create( "mini/land/special/bomb_light_bg.png" ); // 480 * 320
		_backgroundSpecial->setScaleX(Director::getInstance()->getWinSize().width/480);
		_backgroundSpecial->setScaleY(Director::getInstance()->getWinSize().height/160);
		_backgroundSpecial->setPosition( Point( Land::visibleSize.width / 2 + Land::origin.x, Land::visibleSize.height + Land::origin.y) );
		_backgroundSpecial->setOpacity(255);
		layer->addChild( _backgroundSpecial,500 );
		_SpecialButton->loadTextures("mini/land/special/btt_flare.png", "mini/land/special/btt_flare.png", "");
		//_SpecialButton->setPosition(Point(50, Land::visibleSize.height - 50));
		_SpecialButton->addTouchEventListener(CC_CALLBACK_2(Land::turnOnLightSpecialEvent, this));
		_SpecialButton->setScale(Land::deltaScale);
		//// init flare rocket 
		//_objSpecial = Sprite::create( "mini/land/special/flare_fall.png" );
		//_objSpecial->setPosition(Point(Land::visibleSize.width/2,Land::visibleSize.height - 50));
		//_objSpecial->setOpacity(0);
		Land::isNight = true;
		break;
	case SPECIAL_HELPER_POINT_RADAR:
		_backgroundSpecial = Sprite::create( "mini/land/special/coordinate.png" );//600 375
		_backgroundSpecial->setScaleX(Director::getInstance()->getWinSize().width/600);
		_backgroundSpecial->setScaleY(Director::getInstance()->getWinSize().height/375);
		_backgroundSpecial->setPosition( Point( Land::visibleSize.width / 2 + Land::origin.x, Land::visibleSize.height / 2 + Land::origin.y) );
		_backgroundSpecial->setOpacity(0);
		layer->addChild( _backgroundSpecial , 2865 );

		
		_SpecialButton->loadTextures("mini/land/special/btt_radar.png", "mini/land/special/btt_radar.png", "");
		//_SpecialButton->setPosition(Point(50, Land::visibleSize.height - 50));
		_SpecialButton->addTouchEventListener(CC_CALLBACK_2(Land::turnOnRadarPointSpecialEvent, this));
		_SpecialButton->setScale(Land::deltaScale);
		addTargets(layer);
		break;
	case SPECIAL_HELPER_HEAT_RADAR:
		_backgroundSpecial = Sprite::create( "mini/land/special/heat_radar_bg.png" );
		_backgroundSpecial->setScaleX(Director::getInstance()->getWinSize().width/100);
		_backgroundSpecial->setScaleY(Director::getInstance()->getWinSize().height/100);
		_backgroundSpecial->setPosition( Point( Land::visibleSize.width / 2 + Land::origin.x, Land::visibleSize.height / 2 + Land::origin.y) );
		_backgroundSpecial->setOpacity(0);
		layer->addChild(_backgroundSpecial, 2865);
		
		_SpecialButton->loadTextures("mini/land/special/heat_radar.png", "mini/land/special/heat_radar.png", "");
		//_SpecialButton->setPosition(Point(50, Land::visibleSize.height - 50));
		_SpecialButton->addTouchEventListener(CC_CALLBACK_2(Land::turnOnRadarHeatSpecialEvent, this));
		_SpecialButton->setScale(Land::deltaScale);

		addTargets(layer);
		break;
	case SPECIAL_HELPER_BOMB_RADAR:
		_backgroundSpecial = Sprite::create( "mini/land/special/coordinate.png" );//600 375
		_backgroundSpecial->setScaleX(Director::getInstance()->getWinSize().width/600);
		_backgroundSpecial->setScaleY(Director::getInstance()->getWinSize().height/375);
		_backgroundSpecial->setPosition( Point( Land::visibleSize.width / 2 + Land::origin.x, Land::visibleSize.height / 2 + origin.y) );
		_backgroundSpecial->setOpacity(0);
		layer->addChild(_backgroundSpecial, 2865);


		_SpecialButton->loadTextures("mini/land/special/radar_bomb.png", "mini/land/special/radar_bomb.png", "");
		//_SpecialButton->setPosition(Point(50, Land::visibleSize.height - 50));
		_SpecialButton->addTouchEventListener(CC_CALLBACK_2(Land::turnOnRadarBombSpecialEvent, this));
		_SpecialButton->setScale(Land::deltaScale);
		addTargets(layer);
		break;
	default:
		break;
	}
	_maskButtonSpec = Sprite::create("mini/land/special/mask_spec.png"); 
	_SpecialButton->setScale(Land::deltaScale);
	_maskButtonSpec->setScale(Land::deltaScale);
	_maskButtonSpec->setOpacity(0);

	layer->addChild(_SpecialButton, 2895);
	layer->addChild(_maskButtonSpec, 3000);
	//if(_objSpecial != 0)
	//	layer->addChild(_objSpecial);
}

void Land::turnOnLightSpecialEvent(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType != ui::Widget::TouchEventType::ENDED)
	{
		//int currT = Utility::getCurrentTime();
		//if( currT  - _delayTimeClickSpecial >= DELAY_SPECIAL_CLICK_1)
		{
			//_delayTimeClickSpecial = currT;
			if (_isTutorial){
				_isTutorial = false;
				_SpecialButton->setTouchEnabled(false);
				_SpecialButton->stopAllActions();
				parent->startGame();
			}

			turnOnLight();
		}
	}
}

void Land::turnOnRadarPointSpecialEvent(Ref* pSender, ui::Widget::TouchEventType eEventType)
{

	if (eEventType != ui::Widget::TouchEventType::ENDED)
	{
		if (_isTutorial){
			_isTutorial = false;
			_SpecialButton->setTouchEnabled(false);
			_SpecialButton->stopAllActions();
			auto fadeIn = FadeIn::create(0.25f);
			auto delay = DelayTime::create(1.5f);
			auto fadeOut = FadeOut::create(0.25f);
			auto seq = Sequence::create(fadeIn, delay, fadeOut, nullptr);
			_backgroundSpecial->runAction(seq);

			parent->startGame();
			return;
		}
		//int currT = Utility::getCurrentTime();
		//if( currT  - _delayTimeClickSpecial >= DELAY_SPECIAL_CLICK_2)
		{
			//_delayTimeClickSpecial = currT;
			turnOnPointRadar();
		}
	}
}

void Land::turnOnRadarHeatSpecialEvent(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType != ui::Widget::TouchEventType::ENDED)
	{
		if (_isTutorial){
			_isTutorial = false;
			_SpecialButton->setTouchEnabled(false);
			_SpecialButton->stopAllActions();
			parent->startGame();
		}
		//int currT = Utility::getCurrentTime();
		//if( currT  - _delayTimeClickSpecial >= DELAY_SPECIAL_CLICK_2)
		{
			//_delayTimeClickSpecial = currT;
			turnOnHeatRadar();
		}
	}
}

void Land::turnOnRadarBombSpecialEvent(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType != ui::Widget::TouchEventType::ENDED)
	{

		//int currT = Utility::getCurrentTime();
		//if( currT  - _delayTimeClickSpecial >= DELAY_SPECIAL_CLICK_2)
		{
			//_delayTimeClickSpecial = currT;
			turnOnBombRadar();
		}
	}
}
// action of special
void Land::turnOnLight()
{
	if (!_isClickSpecialBtt)
	{
		_isClickSpecialBtt = true;
		_maskButtonSpec->setOpacity(255);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		ScreenManager::Instance()->playSoundEffect("Sounds/antirocket.ogg");
#else
		ScreenManager::Instance()->playSoundEffect("Sounds/antirocket.mp3");
#endif
		_backgroundSpecial->stopAllActions();
		
		auto movingFall = MoveTo::create(ScreenManager::Instance()->getDelayTimeDevice(), Point(_backgroundSpecial->getPositionX(), Land::origin.y));
		DelayTime* delayTimeClickSpecBtt;
		if (ScreenManager::Instance()->CurrentMap() == MAP_15)
			delayTimeClickSpecBtt = DelayTime::create(5.0f / ScreenManager::Instance()->getDelayTimeDevice());
		else
			delayTimeClickSpecBtt = DelayTime::create(3.0f / ScreenManager::Instance()->getDelayTimeDevice());

		auto movingUp = MoveTo::create(ScreenManager::Instance()->getDelayTimeDevice(), Point(_backgroundSpecial->getPositionX(), _backgroundSpecial->getPositionY()));

		auto sequenceMoving = Sequence::create(movingFall, delayTimeClickSpecBtt, movingUp ,CallFunc::create(CC_CALLBACK_0(Land::enableSpecialButton, this)), nullptr);
		_backgroundSpecial->runAction(sequenceMoving);
	}
}

//void Land::turnOffLight()
//{
//	//_backgroundSpecial->setPositionY(Land::visibleSize.height + Land::origin.y);
//	//CallFunc::create(CC_CALLBACK_0(IUnit::comeToScreen,this))
//	//_objSpecial->setOpacity(0);
//}

void Land::turnOnHeatRadar()
{
	if (!_isClickSpecialBtt)
	{
		
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		ScreenManager::Instance()->playSoundEffect("Sounds/scanner.ogg");
#else
		ScreenManager::Instance()->playSoundEffect("Sounds/scanner.mp3");
#endif

		_isClickSpecialBtt = true;
		_maskButtonSpec->setOpacity(255);

		detectInScreen();
		auto actionFadeIn = FadeTo::create(0.2, 255);
		auto delay = DelayTime::create(0.3 * ScreenManager::Instance()->getDelayTimeDevice());
		//auto delayEnd = DelayTime::create(0.2 / ScreenManager::Instance()->getDelayTimeDevice());

		auto sequenceShowing = Sequence::create(actionFadeIn, delay, CallFunc::create(CC_CALLBACK_0(Land::turnOffHeatRadar, this)) , 
			CallFunc::create(CC_CALLBACK_0(Land::enableSpecialButton, this)) , nullptr);
		_backgroundSpecial->runAction(sequenceShowing);
	}
}

void Land::turnOffHeatRadar()
{
	_backgroundSpecial->setOpacity(0);
}

void Land::turnOnPointRadar()
{
	if (!_isClickSpecialBtt)
	{
		//ScreenManager::Instance()->playSoundEffect("Sounds/scanner.mp3");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		ScreenManager::Instance()->playSoundEffect("Sounds/scanner.ogg");
#else
		ScreenManager::Instance()->playSoundEffect("Sounds/scanner.mp3");
#endif
		_isClickSpecialBtt = true;
		_maskButtonSpec->setOpacity(255);
		detectInScreen();

		auto actionFadeIn = FadeTo::create(0.2, 255);
		auto delay = DelayTime::create(0.3 * ScreenManager::Instance()->getDelayTimeDevice());
		//auto delayEnd = DelayTime::create(0.5f / ScreenManager::Instance()->getDelayTimeDevice());

		auto sequenceShowing = Sequence::create(actionFadeIn, delay, CallFunc::create(CC_CALLBACK_0(Land::turnOffPointRadar, this)) ,
			CallFunc::create(CC_CALLBACK_0(Land::enableSpecialButton, this))  , nullptr);
		_backgroundSpecial->runAction(sequenceShowing);
	}
}

void Land::turnOffPointRadar()
{
	_backgroundSpecial->setOpacity(0);
}

void Land::turnOnBombRadar()
{
	if (!_isClickSpecialBtt)
	{
		//ScreenManager::Instance()->playSoundEffect("Sounds/scanner.mp3");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		ScreenManager::Instance()->playSoundEffect("Sounds/scanner.ogg");
#else
		ScreenManager::Instance()->playSoundEffect("Sounds/scanner.mp3");
#endif
		_isClickSpecialBtt = true;
		_maskButtonSpec->setOpacity(255);
		detectInScreen();
		auto actionFadeIn = FadeTo::create(0.2, 255);
		auto delay = DelayTime::create(0.3 * ScreenManager::Instance()->getDelayTimeDevice());
		//auto delayEnd = DelayTime::create(0.5f / ScreenManager::Instance()->getDelayTimeDevice());

		auto sequenceShowing = Sequence::create(actionFadeIn, delay, CallFunc::create(CC_CALLBACK_0(Land::turnOffBombRadar, this)),
			CallFunc::create(CC_CALLBACK_0(Land::enableSpecialButton, this)), nullptr);
		_backgroundSpecial->runAction(sequenceShowing);
	}

}

void Land::turnOffBombRadar()
{
	_backgroundSpecial->setOpacity(0);
}



void Land::updateLandPositionToTheLeft()
{
	moveToLeft(/*_deltaMovingLand*/);

	//if (!Land::isMoving)
	//	return;

	//_pixelTargetMoving += _deltaMovingTargets;
	for (int i = _indexOutTarget ; i < _targetCount/* - 1*/; i++)
	{
		if (!_listTargets[i]->updatePositionToTheLeft(/*_deltaMovingTargets*/))
			_indexOutTarget = i;
	}

	if (_indexOutTarget + 2 > _targetCount)
		this->stopMoveLand(false);
}

const bool& Land::hitWeaponEnemies(const int& idWeapons)
{
	_listTargets[idWeapons]->hitMainCharacter();
	return true;
}

void Land::moveToLeft()
{
	if (!_isEndOfStartLand)
	{
		_posStartLand = _land_start->getPositionX();
		// load next !!
		if (!_isNextLandAvaiable)
		{
			if (_posStartLand <= _distanceOfEndStartMapPieces) // end of start land -> come to next land
			{
					_isNextLandAvaiable = true;
					_land_next_current->setPositionX(_land_next_current->getPositionX() - (_distanceOfEndStartMapPieces - _land_start->getPositionX()) - Land::pixelOfLandMoving /*+ 10*/);
			}
		}

		// check start land is end ?
		if (_land_start->getPositionX() < _pointXToDieStartMap){
			_isEndOfStartLand = true;
			_land_start->removeFromParentAndCleanup(true);
		}
		else
		{
			_land_start->setPositionX(_land_start->getPositionX() - Land::pixelOfLandMoving);
		}
	}

	if (_isNextLandAvaiable){
		_posNextLand = _land_next_current->getPositionX();
		if (_land_next_current->getPositionX() <= _distanceOfEndNextMapPieces) // come to next next land
		{
			_deltaDisNext = _distanceOfEndNextMapPieces - _land_next_current->getPositionX();
			if (_land_next_current == _land_next_1)
			{
				_land_next_current_rest = _land_next_1;
				_land_next_current = _land_next_2;
				//_isNext1 = false;
			}
			else
			{
				_land_next_current = _land_next_1;
				_land_next_current_rest = _land_next_2;
				//_isNext1 = true;
			}
			//_xyNextMap
			//_pixelLandMoving = _xyNextMap.x; _pixelLandMoving -= _deltaDisNext; _pixelLandMoving -= pixel;
			_land_next_current->setPositionX(_land_next_current->getPositionX() - _deltaDisNext - Land::pixelOfLandMoving /*+ 10*/);//_xyNextMap.x - _deltaDisNext - pixel
			if (!_isAllNextLandAvaiable)
				_isAllNextLandAvaiable = true;
		}

		//_pointXToDieNextMap
		_land_next_current->setPositionX(_land_next_current->getPositionX() - Land::pixelOfLandMoving);
		if (_isAllNextLandAvaiable){	
			//_land_next_current_rest->setPositionX(_land_next_current_rest->getPositionX() - pixel);
			if (_land_next_current_rest->getPositionX() >= _pointXToDieNextMap) // return land position
			{
				_land_next_current_rest->setPositionX(_land_next_current_rest->getPositionX() - Land::pixelOfLandMoving);
			}
			else{
				_land_next_current_rest->setPositionX(_xyNextMap.x);
				_isAllNextLandAvaiable = false;
			}			
		}
			
	}
}

void Land::startMoving()
{
	if (_SpecialButton)
		_SpecialButton->setTouchEnabled(true);

	for (int i = 0; i < _targetCount; i++)
	{
		_listTargets[i]->startMoving();
	}
}

void Land::setPositionSpecialBtt(const cocos2d::Point& p)
{
	if (currentMap->Special != SPECIAL_HELPER_NO_SPEC){
			_SpecialButton->setPosition(p);
			_maskButtonSpec->setPosition(p);
	}
		
}

const bool& Land::isSpecialButtonExist()
{
	if (currentMap->Special != SPECIAL_HELPER_NO_SPEC)
		return true;
	return false;
}

void Land::getWeaponsAndTarget(int& weaponNum, int& targetNum)
{
	weaponNum = currentMap->WeaponCount;
	targetNum = currentMap->enemiesCount;
}

void Land::enableSpecialButton()
{
	_isClickSpecialBtt = false;
	_maskButtonSpec->setOpacity(0);
}



////////////////////////////////////////////////////////////////////////////
//const bool& GameScene::checkDeltaTime()
//{
//	//struct timeval now;
//	if (gettimeofday(&_currTimer, nullptr) != 0)
//	{
//		CCLOG("error in gettimeofday");
//		return true; // bomb anyway
//	}
//
//	if (_currTimer.tv_sec == _oldTimer.tv_sec) // same second
//	{
//		if (_currTimer.tv_usec >= _oldTimer.tv_usec + DELTA_TIME)
//			return true;
//		else
//			return false;
//	} // 
//	else if (_currTimer.tv_sec == _oldTimer.tv_sec + 1)
//	{
//		if (_currTimer.tv_usec >= _oldTimer.tv_usec - DELTA_TIME)
//		{
//			return true;
//		}
//		else
//			return false;
//	}
//	else
//		return true;
//	//_currTimer = (now.tv_sec) * 100 + (now.tv_usec) / 10000;
//	//sprintf(_szTest, "s:%d|ms:%d|rs:%d|,", now.tv_sec, now.tv_usec, _currTimer);
//	//_testLabel->setString(_szTest);
//}





