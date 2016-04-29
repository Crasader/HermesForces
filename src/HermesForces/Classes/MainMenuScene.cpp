#include "MainMenuScene.h"
#include "ScreenManager.h"
#include "SimpleAudioEngine.h" 
//
//
Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	layer->setKeypadEnabled(true);
#endif
    
	// add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool MainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
	    return false;
	}
    this->scheduleOnce(schedule_selector(MainMenuScene::finishLoadingToRunMusic), 1.0f);
    
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create( "mini/scene/main_scene.jpg" );
		
	x = (Director::getInstance()->getVisibleSize().width + Director::getInstance()->getVisibleOrigin().x) / backgroundSprite->getContentSize().width;
	y = (Director::getInstance()->getVisibleSize().height + Director::getInstance()->getVisibleOrigin().y) / backgroundSprite->getContentSize().height;
	backgroundSprite->setScaleX(x);// (Director::getInstance()->getVisibleSize().width + Director::getInstance()->getVisibleOrigin().x) / 1024);
	backgroundSprite->setScaleY(y);// (Director::getInstance()->getVisibleSize().height + Director::getInstance()->getVisibleOrigin().y) / 768);
		backgroundSprite->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x,
			Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y));
	this->addChild(backgroundSprite);

	//antitero
	antitero = Sprite::create("mini/scene/antitero.png");
	antitero->setScale(x);
	antitero->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x,
		Director::getInstance()->getVisibleSize().height  * 0.9 + Director::getInstance()->getVisibleOrigin().y));

	this->addChild(antitero);

	this->loadAllButton();
	

	_cloudSprite = Sprite::create("mini/scene/cloud.png");
	_cloudSprite->setPosition(Point(_cloudSprite->getContentSize().width * 0.5 * y + origin.x * 0.5, visibleSize.height / 2 + origin.y * 0.5));
	_cloudSprite->setScale(y);
	this->addChild(_cloudSprite);

	_minDistanceToMove = visibleSize.width / 200;

	_touchListener = EventListenerTouchOneByOne::create();
	_touchListener->setSwallowTouches(true);
	_touchListener->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan, this);
	_touchListener->onTouchMoved = CC_CALLBACK_2(MainMenuScene::onTouchMoved, this);
	_touchListener->onTouchEnded = CC_CALLBACK_2(MainMenuScene::onTouchEnded, this);
	_touchListener->onTouchCancelled = CC_CALLBACK_2(MainMenuScene::onTouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);

	
	return true;
}

bool MainMenuScene::onTouchBegan(Touch *touch, Event *event)
{
	// FOR TEST
	//ScreenManager::Instance()->gotoCreditScene();
	//return false;


	if (isTouchDown)
		return false;

	initialTouchPosX = touch->getLocation().x;
	//currentTouchPosX = touch->getLocation().x;

	isTouchDown = true;
	checkInsideMap(initialTouchPosX, touch->getLocation().y);
	// show here !!


	return true;
}

void MainMenuScene::onTouchMoved(Touch *touch, Event *event)
{

	//currentTouchPosX = touch->getLocation().x;
	// code here !!
	_deltaTouchX = touch->getLocation().x - initialTouchPosX;

	if (_isInside){
		if (abs(_deltaTouchX) > _minDistanceToMove)
		{
			_isInside = false;
			auto fadeOut = FadeOut::create(0.1f);
			_maskClicked->runAction(fadeOut);
		}
	}
	
	_bttDesert->setPositionX(_pointDesert + _deltaTouchX * 0.8);
	_bttCity->setPositionX(_pointCity + _deltaTouchX * 0.8);
	_bttSuburb->setPositionX(_pointSuburb + _deltaTouchX * 0.8);
	_bttAreaX->setPositionX(_pointAreaX + _deltaTouchX * 0.8);

	if (_currentBigMap == MAP_DESERT)
		_maskClicked->setPositionX(_bttDesert->getPositionX());
	else if (_currentBigMap == MAP_CITY)
	{
		_maskClicked->setPositionX(_bttCity->getPositionX());
	}
	else if (_currentBigMap == MAP_SUBURB)
	{
		_maskClicked->setPositionX(_bttSuburb->getPositionX());
	}
	else
		_maskClicked->setPositionX(_bttAreaX->getPositionX());
}

void MainMenuScene::onTouchEnded(Touch *touch, Event *event)
{

	if (_isInside == true/* && abs(_bttDesert->getPositionX() == _pointDesert) < 3*/)
	{
		_maskClicked->setOpacity(0);
		// go to detail menu scene here
		isTouchDown = false;
		_isInside = false;
		ScreenManager::Instance()->setCurrentBigMap(_currentBigMap);
		ScreenManager::Instance()->gotoDetailMap();
		return;
	}
	// return or not
	if (_bttDesert->getPositionX() < _minSlide)
	{
		_pointDesert = -0.425 * Director::getInstance()->getVisibleSize().width;
		_pointCity = -0.025 * Director::getInstance()->getVisibleSize().width;
		_pointSuburb = 0.375 * Director::getInstance()->getVisibleSize().width;
		_pointAreaX = 0.775 * Director::getInstance()->getVisibleSize().width;
	}
	else if (_bttDesert->getPositionX() > _maxSlide)
	{
		_pointDesert = 0.225 * Director::getInstance()->getVisibleSize().width;
		_pointCity = 0.625 * Director::getInstance()->getVisibleSize().width;
		_pointSuburb = 1.025 * Director::getInstance()->getVisibleSize().width;
		_pointAreaX = 1.425 * Director::getInstance()->getVisibleSize().width;
	}
	else
	{
		_pointDesert = -0.1 * Director::getInstance()->getVisibleSize().width;
		_pointCity = 0.3 * Director::getInstance()->getVisibleSize().width;
		_pointSuburb = 0.7 * Director::getInstance()->getVisibleSize().width;
		_pointAreaX = 1.1 * Director::getInstance()->getVisibleSize().width;
	}
	auto actionMoveDesert = MoveTo::create(0.2, Point(_pointDesert, _bttDesert->getPositionY()));
	_bttDesert->runAction(actionMoveDesert);

	auto actionMoveCity = MoveTo::create(0.2, Point(_pointCity, _bttCity->getPositionY()));
	_bttCity->runAction(actionMoveCity);

	auto actionMoveSub = MoveTo::create(0.2, Point(_pointSuburb, _bttSuburb->getPositionY()));
	_bttSuburb->runAction(actionMoveSub);

	auto actionMoveAre = MoveTo::create(0.2, Point(_pointAreaX, _bttAreaX->getPositionY()));
	auto sequenceMoving = Sequence::create(actionMoveAre, CallFunc::create(CC_CALLBACK_0(MainMenuScene::EndMoving, this)), nullptr);

	_bttAreaX->runAction(sequenceMoving);
}

void MainMenuScene::onTouchCancelled(Touch *touch, Event *event)
{
	onTouchEnded(touch, event);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void MainMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	Director::getInstance()->end();
}
#endif

void MainMenuScene::gotoCreditScene(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	ScreenManager::Instance()->gotoCreditScene();
}

void MainMenuScene::turnOnOffMusicButton(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->turnOnOffMusic();
		if (ScreenManager::Instance()->isOnMusic()){
			ScreenManager::Instance()->playMusicMainMenu();
			musicBtt->loadTextures("mini/scene/musicbtt.png", "mini/scene/musicbtt.png", "");
		}
		else
			musicBtt->loadTextures("mini/scene/musicbtt_no.png", "mini/scene/musicbtt_no.png", "");
	}
}

void MainMenuScene::turnOnOffSoundButton(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->turnOnOffSound();
		if (ScreenManager::Instance()->isOnSound())
			soundBtt->loadTextures("mini/scene/soundbtt.png", "mini/scene/soundbtt.png", "");
		else
			soundBtt->loadTextures("mini/scene/soundbtt_no.png", "mini/scene/soundbtt_no.png", "");
	}
}

void MainMenuScene::EndMoving()
{
	_bttDesert->stopAllActions();
	_bttDesert->setPositionX(_pointDesert);
	_bttCity->stopAllActions();
	_bttCity->setPositionX(_pointCity);
	_bttSuburb->stopAllActions();
	_bttSuburb->setPositionX(_pointSuburb);
	updateXY();
	isTouchDown = false;
}

void MainMenuScene::checkInsideMap(const float& x, const  float& y)
{
	if (x > xD2 && x < xD1 && y < yD1 && y > yD2){
		//Point xy = _bttDesert->getPosition();
		_maskClicked->setPosition(_bttDesert->getPosition());
		_maskClicked->setOpacity(255);
		_currentBigMap = MAP_DESERT;
		_isInside = true;
	}	
	else if (x > xC2 && x < xC1 && y < yC1 && y > yC2){
		_maskClicked->setPosition(_bttCity->getPosition());
		_maskClicked->setOpacity(255);
		_currentBigMap = MAP_CITY;
		_isInside = true;
	}
	else if (x > xS2 && x < xS1 && y < yS1 && y > yS2){
		_maskClicked->setPosition(_bttSuburb->getPosition());
		_maskClicked->setOpacity(255);
		_currentBigMap = MAP_SUBURB;
		_isInside = true;
	}	
	else if (x > xA2 && x < xA1 && y < yA1 && y > yA2){
		_maskClicked->setPosition(_bttAreaX->getPosition());
		_maskClicked->setOpacity(255);
		_currentBigMap = MAP_AREAX;
		_isInside = true;
	}
	else	
		_isInside = false;
}

void MainMenuScene::updateXY()
{
	xD1 = _bttDesert->getPositionX() + _bttDesert->getContentSize().width * 0.5 * x;
	xD2 = _bttDesert->getPositionX() - _bttDesert->getContentSize().width * 0.5 * x;
	yD1 = _bttDesert->getPositionY() + _bttDesert->getContentSize().height * 0.5 * x;
	yD2 = _bttDesert->getPositionY() - _bttDesert->getContentSize().height * 0.5 * x;
	xC1 = _bttCity->getPositionX() + _bttCity->getContentSize().width * 0.5 * x;
	xC2 = _bttCity->getPositionX() - _bttCity->getContentSize().width * 0.5 * x;
	yC1 = _bttCity->getPositionY() + _bttCity->getContentSize().height * 0.5 * x;
	yC2 = _bttCity->getPositionY() - _bttCity->getContentSize().height * 0.5 * x;
	xS1 = _bttSuburb->getPositionX() + _bttSuburb->getContentSize().width * 0.5 * x;
	xS2 = _bttSuburb->getPositionX() - _bttSuburb->getContentSize().width * 0.5 * x;
	yS1 = _bttSuburb->getPositionY() + _bttSuburb->getContentSize().height * 0.5 * x;
	yS2 = _bttSuburb->getPositionY() - _bttSuburb->getContentSize().height * 0.5 * x;
	xA1 = _bttAreaX->getPositionX() + _bttAreaX->getContentSize().width * 0.5 * x;
	xA2 = _bttAreaX->getPositionX() - _bttAreaX->getContentSize().width * 0.5 * x;
	yA1 = _bttAreaX->getPositionY() + _bttAreaX->getContentSize().height * 0.5 * x;
	yA2 = _bttAreaX->getPositionY() - _bttAreaX->getContentSize().height * 0.5 * x;
}

void MainMenuScene::finishLoadingButtonDesert(float dt)
{
	_bttDesert->setVisible(true);
}

void MainMenuScene::finishLoadingButtonCity(float dt)
{
	_bttCity->setVisible(true);
}

void MainMenuScene::finishLoadingButtonSuburb(float dt)
{
	_bttSuburb->setVisible(true);
}

void MainMenuScene::finishLoadingButtonAreaX(float dt)
{
	_bttAreaX->setVisible(true);
}

void MainMenuScene::finishLoadingOthers(float dt)
{
	musicBtt->setVisible(true);
	soundBtt->setVisible(true);
	copyrightBtt->setVisible(true);
}

void MainMenuScene::loadAllButton()
{
	//////////////////////////////////////////////////////////////////////////
	///						MUSIC - SOUND - COPYRIGHT					   ///
	//////////////////////////////////////////////////////////////////////////

	musicBtt = cocos2d::ui::Button::create();
	if (ScreenManager::Instance()->isOnMusic())
		musicBtt->loadTextures("mini/scene/musicbtt.png", "mini/scene/musicbtt.png", "");
	else
		musicBtt->loadTextures("mini/scene/musicbtt_no.png", "mini/scene/musicbtt_no.png", "");
	musicBtt->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::turnOnOffMusicButton, this));
	musicBtt->setVisible(false);

	soundBtt = cocos2d::ui::Button::create();
	if (ScreenManager::Instance()->isOnSound())
		soundBtt->loadTextures("mini/scene/soundbtt.png", "mini/scene/soundbtt.png", "");
	else
		soundBtt->loadTextures("mini/scene/soundbtt_no.png", "mini/scene/soundbtt_no.png", "");

	soundBtt->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::turnOnOffSoundButton, this));
	soundBtt->setVisible(false);

	copyrightBtt = cocos2d::ui::Button::create();
	copyrightBtt->loadTextures("mini/scene/copyrightbtt.png", "mini/scene/copyrightbtt.png", "");
	copyrightBtt->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::gotoCreditScene, this));
	copyrightBtt->setVisible(false);

	musicBtt->setScale(x*1.5);
	soundBtt->setScale(x*1.5);
	copyrightBtt->setScale(x*1.5);

	musicBtt->setPosition(Point(Director::getInstance()->getVisibleSize().width * 0.1, Director::getInstance()->getVisibleSize().height  * 0.1 + Director::getInstance()->getVisibleOrigin().y));
	soundBtt->setPosition(Point(musicBtt->getPositionX() + soundBtt->getContentSize().width * x * 1.75, musicBtt->getPositionY()));
	copyrightBtt->setPosition(Point(Director::getInstance()->getVisibleSize().width * 0.9, musicBtt->getPositionY()));

	this->addChild(musicBtt);
	this->addChild(soundBtt);
	this->addChild(copyrightBtt);

	// middle
	float deltaSizeH = Director::getInstance()->getVisibleSize().height * 0.8 + Director::getInstance()->getVisibleOrigin().x
		- antitero->getContentSize().height * x
		- soundBtt->getContentSize().height * x;
	deltaSizeH *= 0.8;
	float deltaSize = 0.35 * Director::getInstance()->getVisibleSize().width;
	if (deltaSizeH < deltaSize)
		deltaSize = deltaSizeH;

	float middleY = Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y;

	_bttDesert = Sprite::create("mini/scene/bigmenu/desert.png");
	float deltaScaleButtonMenu = deltaSize / _bttDesert->getContentSize().width;
	_bttDesert->setPosition(Point(Director::getInstance()->getVisibleSize().width * 0.225 + Director::getInstance()->getVisibleOrigin().x, middleY));
	_bttDesert->setScale(deltaScaleButtonMenu);
	_bttDesert->setVisible(false);
	this->addChild(_bttDesert);

	_mapMax = ScreenManager::Instance()->getMaxMap();

	if (_mapMax < MAP_5)
		_bttCity = Sprite::create("mini/scene/bigmenu/city_lock.png");
	else
		_bttCity = Sprite::create("mini/scene/bigmenu/city.png");
	_bttCity->setPosition(Point(Director::getInstance()->getVisibleSize().width * 0.625 + Director::getInstance()->getVisibleOrigin().x, middleY));
	_bttCity->setScale(deltaScaleButtonMenu);
	_bttCity->setVisible(false);
	this->addChild(_bttCity);

	if (_mapMax < MAP_9)
		_bttSuburb = Sprite::create("mini/scene/bigmenu/suburb_lock.png");
	else
		_bttSuburb = Sprite::create("mini/scene/bigmenu/suburb.png");
	_bttSuburb->setPosition(Point(Director::getInstance()->getVisibleSize().width * 1.025 + Director::getInstance()->getVisibleOrigin().x, middleY));
	_bttSuburb->setScale(deltaScaleButtonMenu);
	_bttSuburb->setVisible(false);
	this->addChild(_bttSuburb);

	if (_mapMax < MAP_13)
		_bttAreaX = Sprite::create("mini/scene/bigmenu/areax_lock.png");
	else
		_bttAreaX = Sprite::create("mini/scene/bigmenu/areax.png");
	_bttAreaX->setPosition(Point(Director::getInstance()->getVisibleSize().width * 1.425 + Director::getInstance()->getVisibleOrigin().x, middleY));
	_bttAreaX->setScale(deltaScaleButtonMenu);
	_bttAreaX->setVisible(false);
	this->addChild(_bttAreaX);

	_maskClicked = Sprite::create("mini/scene/bigmenu/sun.png");
	_maskClicked->setScale(deltaScaleButtonMenu);
	_maskClicked->setOpacity(0);
	this->addChild(_maskClicked);

	_pointDesert = _bttDesert->getPositionX();
	_pointCity = _bttCity->getPositionX();
	_pointSuburb = _bttSuburb->getPositionX();
	_pointAreaX = _bttAreaX->getPositionX();

	//////////////////////////////////////////////////////////////////////////
	///									OTHERS							   ///
	//////////////////////////////////////////////////////////////////////////

	isTouchDown = false;
	initialTouchPosX = 0;
	_isInside = true;
	_currentBigMap = MAP_DESERT;
	updateXY();
	_minSlide = -0.275 * Director::getInstance()->getVisibleSize().width;
	_maxSlide = 0.05 * Director::getInstance()->getVisibleSize().width;

	this->scheduleOnce(schedule_selector(MainMenuScene::finishLoadingButtonDesert), 0.6f);
	this->scheduleOnce(schedule_selector(MainMenuScene::finishLoadingButtonCity), 0.65f);
	this->scheduleOnce(schedule_selector(MainMenuScene::finishLoadingButtonSuburb), 0.7f);
	this->scheduleOnce(schedule_selector(MainMenuScene::finishLoadingButtonAreaX), 0.75f);
	this->scheduleOnce(schedule_selector(MainMenuScene::finishLoadingOthers), 0.8f);

}

void MainMenuScene::finishLoadingToRunMusic(float dt)
{
	ScreenManager::Instance()->playMusicMainMenu();
    auto moveToLeft = MoveTo::create(15, Point(_cloudSprite->getContentSize().width * y - visibleSize.width, visibleSize.height * 0.5 + origin.y * 0.5));
    auto moveToRight = MoveTo::create(15, Point(_cloudSprite->getPositionX(), visibleSize.height * 0.5 + origin.y * 0.5));
    auto seq = Sequence::create(moveToLeft, moveToRight, nullptr);
    _cloudSprite->runAction(RepeatForever::create(seq));
}
