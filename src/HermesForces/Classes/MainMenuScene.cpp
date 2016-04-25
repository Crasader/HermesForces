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
	auto antitero = Sprite::create("mini/scene/antitero.png");
	antitero->setScale(x);
	antitero->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x,
		Director::getInstance()->getVisibleSize().height  * 0.9 + Director::getInstance()->getVisibleOrigin().y));

	this->addChild(antitero);

	musicBtt = cocos2d::ui::Button::create();
	if (ScreenManager::Instance()->isOnMusic())
		musicBtt->loadTextures("mini/scene/musicbtt.png", "mini/scene/musicbtt.png", "");
	else
		musicBtt->loadTextures("mini/scene/musicbtt_no.png", "mini/scene/musicbtt_no.png", "");
	musicBtt->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::turnOnOffMusicButton, this));
	
	soundBtt = cocos2d::ui::Button::create();
	if (ScreenManager::Instance()->isOnSound())
		soundBtt->loadTextures("mini/scene/soundbtt.png", "mini/scene/soundbtt.png", "");
	else
		soundBtt->loadTextures("mini/scene/soundbtt_no.png", "mini/scene/soundbtt_no.png", "");
	
	soundBtt->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::turnOnOffSoundButton, this));
	
	copyrightBtt = cocos2d::ui::Button::create();
	copyrightBtt->loadTextures("mini/scene/copyrightbtt.png", "mini/scene/copyrightbtt.png", "");
	copyrightBtt->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::gotoCreditScene, this));
	
	musicBtt->setScale(x*1.5);
	soundBtt->setScale(x*1.5);
	copyrightBtt->setScale(x*1.5);


	/// middle
	float deltaSizeH = Director::getInstance()->getVisibleSize().height * 0.8 + Director::getInstance()->getVisibleOrigin().x
		- antitero->getContentSize().height * x
		- soundBtt->getContentSize().height * x;
	deltaSizeH *= 0.8;
	float deltaSize = 0.35 * Director::getInstance()->getVisibleSize().width;
	if (deltaSizeH < deltaSize)
		deltaSize = deltaSizeH;

	float middleY = Director::getInstance()->getVisibleSize().height/2 + Director::getInstance()->getVisibleOrigin().y;
	//_bttDesert = cocos2d::ui::Button::create(); 
	//_bttDesert->loadTextures("mini/scene/bigmenu/desert.png","","");
	_bttDesert = Sprite::create("mini/scene/bigmenu/desert.png");
	float deltaScaleButtonMenu = deltaSize / _bttDesert->getContentSize().width;
	_bttDesert->setPosition(Point(Director::getInstance()->getVisibleSize().width * 0.225 + Director::getInstance()->getVisibleOrigin().x, middleY));
	_bttDesert->setScale(deltaScaleButtonMenu);
	this->addChild(_bttDesert);

	_mapMax = ScreenManager::Instance()->getMaxMap();

	//_bttCity = cocos2d::ui::Button::create();
	//_bttCity->loadTextures("mini/scene/bigmenu/city.png", "", "");
	if (_mapMax < MAP_5)
		_bttCity = Sprite::create("mini/scene/bigmenu/city_lock.png");
	else
		_bttCity = Sprite::create("mini/scene/bigmenu/city.png");
	_bttCity->setPosition(Point(Director::getInstance()->getVisibleSize().width * 0.625 + Director::getInstance()->getVisibleOrigin().x, middleY));
	_bttCity->setScale(deltaScaleButtonMenu);
	this->addChild(_bttCity);


	//_bttSuburb = cocos2d::ui::Button::create();
	//_bttSuburb->loadTextures("mini/scene/bigmenu/suburb.png", "", "");
	if (_mapMax < MAP_9)
		_bttSuburb = Sprite::create("mini/scene/bigmenu/suburb_lock.png");
	else
		_bttSuburb = Sprite::create("mini/scene/bigmenu/suburb.png");
	_bttSuburb->setPosition(Point(Director::getInstance()->getVisibleSize().width * 1.025 + Director::getInstance()->getVisibleOrigin().x, middleY));
	_bttSuburb->setScale(deltaScaleButtonMenu);
	this->addChild(_bttSuburb);


	//_bttAreaX = cocos2d::ui::Button::create();
	//_bttAreaX->loadTextures("mini/scene/bigmenu/areax.png", "", "");
	if (_mapMax < MAP_13)
		_bttAreaX = Sprite::create("mini/scene/bigmenu/areax_lock.png");
	else
		_bttAreaX = Sprite::create("mini/scene/bigmenu/areax.png");
	_bttAreaX->setPosition(Point(Director::getInstance()->getVisibleSize().width * 1.425 + Director::getInstance()->getVisibleOrigin().x, middleY));
	_bttAreaX->setScale(deltaScaleButtonMenu);
	this->addChild(_bttAreaX);

	_maskClicked = Sprite::create("mini/scene/bigmenu/sun.png");
	_maskClicked->setScale(deltaScaleButtonMenu);
	_maskClicked->setOpacity(0);
	this->addChild(_maskClicked);


	/// add lock mask
	//if (_mapMax < MAP_13)
	//{
	//	auto maskLock = Sprite::create("mini/scene/bigmenu/lock_big.png");
	//	maskLock->setPosition(_bttAreaX->getPosition());
	//	maskLock->setScale(deltaScaleButtonMenu);
	//	this->addChild(maskLock);
	//}
	//if (_mapMax < MAP_9)
	//{
	//	auto maskLock = Sprite::create("mini/scene/bigmenu/lock_big.png");
	//	maskLock->setPosition(_bttSuburb->getPosition());
	//	maskLock->setScale(deltaScaleButtonMenu);
	//	this->addChild(maskLock);
	//}
	//else if (_mapMax < MAP_5)
	//{
	//	auto maskLock = Sprite::create("mini/scene/bigmenu/lock_big.png");
	//	maskLock->setPosition(_bttCity->getPosition());
	//	maskLock->setScale(deltaScaleButtonMenu);
	//	this->addChild(maskLock);
	//}


	_minSlide = -0.275 * Director::getInstance()->getVisibleSize().width;
	_maxSlide = 0.05 * Director::getInstance()->getVisibleSize().width;


	musicBtt->setPosition(Point(Director::getInstance()->getVisibleSize().width * 0.1, Director::getInstance()->getVisibleSize().height  * 0.1 + Director::getInstance()->getVisibleOrigin().y));
	soundBtt->setPosition(Point(musicBtt->getPositionX() + soundBtt->getContentSize().width * x * 1.75, musicBtt->getPositionY()));
	copyrightBtt->setPosition(Point(Director::getInstance()->getVisibleSize().width * 0.9, musicBtt->getPositionY()));

	this->addChild(musicBtt);
	this->addChild(soundBtt);
	this->addChild(copyrightBtt);

	auto cloudSprite = Sprite::create("mini/scene/cloud.png");
	cloudSprite->setPosition(Point(cloudSprite->getContentSize().width * 0.5 * y + origin.x * 0.5, visibleSize.height / 2 + origin.y * 0.5));
	cloudSprite->setScale(y);
	this->addChild(cloudSprite);

	auto moveToLeft = MoveTo::create(15, Point(cloudSprite->getContentSize().width * y - visibleSize.width, visibleSize.height * 0.5 + origin.y * 0.5));
	auto moveToRight = MoveTo::create(15, Point(cloudSprite->getPositionX(), visibleSize.height * 0.5 + origin.y * 0.5));
	auto seq = Sequence::create(moveToLeft, moveToRight, nullptr);
	cloudSprite->runAction(RepeatForever::create(seq));
	ScreenManager::Instance()->playMusicMainMenu();



	_pointDesert = _bttDesert->getPositionX();
	_pointCity = _bttCity->getPositionX();
	_pointSuburb = _bttSuburb->getPositionX();
	_pointAreaX = _bttAreaX->getPositionX();


	_touchListener = EventListenerTouchOneByOne::create();
	_touchListener->setSwallowTouches(true);
	_touchListener->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan, this);
	_touchListener->onTouchMoved = CC_CALLBACK_2(MainMenuScene::onTouchMoved, this);
	_touchListener->onTouchEnded = CC_CALLBACK_2(MainMenuScene::onTouchEnded, this);
	_touchListener->onTouchCancelled = CC_CALLBACK_2(MainMenuScene::onTouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
	isTouchDown = false;
	initialTouchPosX = 0;
	_isInside = true;
	_currentBigMap = MAP_DESERT;
	//this->scheduleUpdate();
	updateXY();
	return true;
}

bool MainMenuScene::onTouchBegan(Touch *touch, Event *event)
{
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
	if (_isInside){
		_isInside = false;
		_maskClicked->setOpacity(0);
	}
	_deltaTouchX = touch->getLocation().x - initialTouchPosX;
	_bttDesert->setPositionX(_pointDesert + _deltaTouchX * 0.8);
	_bttCity->setPositionX(_pointCity + _deltaTouchX * 0.8);
	_bttSuburb->setPositionX(_pointSuburb + _deltaTouchX * 0.8);
	_bttAreaX->setPositionX(_pointAreaX + _deltaTouchX * 0.8);

}

void MainMenuScene::onTouchEnded(Touch *touch, Event *event)
{
	if (_bttDesert->getPositionX() == _pointDesert)
	{
		_maskClicked->setOpacity(0);
		// go to detail menu scene here
		isTouchDown = false;
		_isInside = false;
		ScreenManager::Instance()->gotoDetailMap(_currentBigMap);
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

	//_bttDesert->setPositionX(_pointDesert);
	//_bttCity->setPositionX(_pointCity);
	//_bttSuburb->setPositionX(_pointSuburb);
	//_bttAreaX->setPositionX(_pointAreaX);

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

//
//void MainMenuScene::update(float dt)
//{
//	//if (true == isTouchDown)
//	//{
//
//	//}
//}

//
//// on "init" you need to initialize your instance
//bool MainMenuScene::init()
//{
//    //////////////////////////////
//    // 1. super init first
//    if ( !Layer::init() )
//    {
//        return false;
//    }
//    
//
//    visibleSize = Director::getInstance()->getVisibleSize();
//    origin = Director::getInstance()->getVisibleOrigin();
//
//    auto backgroundSprite = Sprite::create( "mini/scene/main_scene.jpg" );
//	
//	x = (Director::getInstance()->getVisibleSize().width/* + Director::getInstance()->getVisibleOrigin().x*/) / backgroundSprite->getContentSize().width;
//	y = (Director::getInstance()->getVisibleSize().height/* + Director::getInstance()->getVisibleOrigin().y*/) / backgroundSprite->getContentSize().height;
//
//	backgroundSprite->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x,
//		Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y));
//
//	backgroundSprite->setScaleX(x);// (Director::getInstance()->getVisibleSize().width + Director::getInstance()->getVisibleOrigin().x) / 1024);
//	backgroundSprite->setScaleY(y);// (Director::getInstance()->getVisibleSize().height + Director::getInstance()->getVisibleOrigin().y) / 768);
//
//	//ScreenManager::Instance()->scaleScreenFull(backgroundSprite);
//    this->addChild( backgroundSprite );
//    
//	//float heightEachRow = visibleSize.height * 0.2;
//	// 0.18  
//	//  
//
//	this->scheduleOnce(schedule_selector(MainMenuScene::onFinishLoading), 0.05f);
//
//	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("heli_loop.mp3");
//    return true;
//}
//
//void MainMenuScene::GoToGameScene_1(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_1);
//	}
//}
//void MainMenuScene::GoToGameScene_2(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_2);
//	}
//}
//void MainMenuScene::GoToGameScene_3(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_3);
//	}
//}
//void MainMenuScene::GoToGameScene_4(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_4);
//	}
//}
//void MainMenuScene::GoToGameScene_5(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_5);
//	}
//}
//void MainMenuScene::GoToGameScene_6(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_6);
//	}
//}
//void MainMenuScene::GoToGameScene_7(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_7);
//	}
//}
//void MainMenuScene::GoToGameScene_8(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_8);
//	}
//}
//void MainMenuScene::GoToGameScene_9(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_9);
//	}
//}
//void MainMenuScene::GoToGameScene_10(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_10);
//	}
//}
//void MainMenuScene::GoToGameScene_11(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_11);
//	}
//}
//void MainMenuScene::GoToGameScene_12(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_12);
//	}
//}
//void MainMenuScene::GoToGameScene_13(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_13);
//	}
//}
//void MainMenuScene::GoToGameScene_14(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_14);
//	}
//}
//void MainMenuScene::GoToGameScene_15(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->gotoGameScene(MAP_15);
//	}
//}
//
//void MainMenuScene::addMapButton(const int& MapNumber, const std::string& path, const std::string& path_no, const cocos2d::ui::Widget::ccWidgetTouchCallback& callback, const float& col, const float& row)
//{
//	auto itemButton = cocos2d::ui::Button::create();
//	//itemButton->setTouchEnabled(true);
//	if (MapNumber <= _mapMax)
//	{
//		itemButton->loadTextures(path, "", "");
//		itemButton->addTouchEventListener(callback);
//	}
//	else{
//		itemButton->loadTextures(path_no, "", "");
//	}
//	// TODO:
//	
//
//	itemButton->setScale(_scaleMap);
//	itemButton->setPosition(Point(col, row));
//	
//	this->addChild(itemButton);
//}
//
//void MainMenuScene::turnOnOffMusicButton(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->turnOnOffMusic();
//		if (ScreenManager::Instance()->isOnMusic()){
//			ScreenManager::Instance()->playMusicMainMenu();
//			musicBtt->loadTextures("mini/scene/musicbtt.png", "mini/scene/musicbtt.png", "");
//		}
//		else
//			musicBtt->loadTextures("mini/scene/musicbtt_no.png", "mini/scene/musicbtt_no.png", "");
//
//		//UserCallback::GetDeviceType()	
//	}
//}
//
//void MainMenuScene::turnOnOffSoundButton(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	if (eEventType == ui::Widget::TouchEventType::ENDED)
//	{
//		ScreenManager::Instance()->turnOnOffSound();
//		if (ScreenManager::Instance()->isOnSound())
//			soundBtt->loadTextures("mini/scene/soundbtt.png", "mini/scene/soundbtt.png", "");
//		else
//			soundBtt->loadTextures("mini/scene/soundbtt_no.png", "mini/scene/soundbtt_no.png", "");
//	}
//}
//
//void MainMenuScene::onFinishLoading(float dt)
//{
//	musicBtt = cocos2d::ui::Button::create();
//	if (ScreenManager::Instance()->isOnMusic())
//		musicBtt->loadTextures("mini/scene/musicbtt.png", "mini/scene/musicbtt.png", "");
//	else
//		musicBtt->loadTextures("mini/scene/musicbtt_no.png", "mini/scene/musicbtt_no.png", "");
//	musicBtt->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::turnOnOffMusicButton, this));
//
//	soundBtt = cocos2d::ui::Button::create();
//	if (ScreenManager::Instance()->isOnSound())
//		soundBtt->loadTextures("mini/scene/soundbtt.png", "mini/scene/soundbtt.png", "");
//	else
//		soundBtt->loadTextures("mini/scene/soundbtt_no.png", "mini/scene/soundbtt_no.png", "");
//
//	soundBtt->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::turnOnOffSoundButton, this));
//
//	copyrightBtt = cocos2d::ui::Button::create();
//	copyrightBtt->loadTextures("mini/scene/copyrightbtt.png", "mini/scene/copyrightbtt.png", "");
//	copyrightBtt->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::gotoCreditScene, this));
//
//	//auto musicBtt = Sprite::create("mini/scene/musicbtt.png");
//	//auto soundBtt = Sprite::create("mini/scene/soundbtt.png");
//	musicBtt->setScale(x*1.5);
//	soundBtt->setScale(x*1.5);
//	copyrightBtt->setScale(x*1.5);
//
//	float widthReal = visibleSize.width - musicBtt->getContentSize().width *  x;
//	float widthEachCell = (widthReal)* 0.16;
//	float heightEachCell = visibleSize.height * 0.26;
//	float sizeCell = widthEachCell < heightEachCell ? widthEachCell : heightEachCell;
//	_scaleMap = sizeCell / 300; // 300 is height-width of image
//
//	const float row_3 = 0.2 * visibleSize.height;
//	const float row_2 = 0.5 * visibleSize.height;
//	const float row_1 = 0.8 * visibleSize.height;
//
//	const float col_1 = 0.14 * widthReal;// visibleSize.width;
//	const float col_2 = 0.32 * widthReal;//visibleSize.width;
//	const float col_3 = 0.5 * widthReal;//visibleSize.width;
//	const float col_4 = 0.68 * widthReal;//visibleSize.width;
//	const float col_5 = 0.86 * widthReal;//visibleSize.width;
//
//	// 
//	//    auto titleSprite = Sprite::create( "game_scene/Menu_Button.png" );
//	//    titleSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height * 0.9 ) ); 
//	//	titleSprite->setScale(heightEachRow/titleSprite->getContentSize().height);
//	//    this->addChild( titleSprite );
//	//
//
//	// const std::string& const ccMenuCallback& callback
//	// const float& col
//
//
//	auto map_15 = Sprite::create("mini/scene/map_stage/pakistan_map.png");
//	const float col_6_start = col_5 + map_15->getContentSize().width *  0.5 * _scaleMap;
//	float col_6 = (col_6_start + visibleSize.width) / 2;
//	musicBtt->setPosition(Point(col_6, row_1 + map_15->getContentSize().height *  0.5 * _scaleMap -
//		musicBtt->getContentSize().height * x * 0.5 *1.5));
//	soundBtt->setPosition(Point(musicBtt->getPositionX(), musicBtt->getPositionY() - musicBtt->getContentSize().height * x * 1.25 * 1.5));
//	copyrightBtt->setPosition(Point(soundBtt->getPositionX(), soundBtt->getPositionY() - soundBtt->getContentSize().height * x * 1.25 * 1.5));
//	
//	this->addChild(musicBtt);
//	this->addChild(soundBtt);
//	this->addChild(copyrightBtt);
//
//	auto cloudSprite = Sprite::create("mini/scene/cloud.png");
//	cloudSprite->setPosition(Point(cloudSprite->getContentSize().width * 0.5 * y + origin.x * 0.5, visibleSize.height / 2 + origin.y * 0.5));
//	cloudSprite->setScale(y);
//	this->addChild(cloudSprite);
//
//	auto moveToLeft = MoveTo::create(15, Point(cloudSprite->getContentSize().width * y - visibleSize.width, visibleSize.height * 0.5 + origin.y * 0.5));
//	auto moveToRight = MoveTo::create(15, Point(cloudSprite->getPositionX(), visibleSize.height * 0.5 + origin.y * 0.5));
//	auto seq = Sequence::create(moveToLeft, moveToRight, nullptr);
//	cloudSprite->runAction(RepeatForever::create(seq));
//	ScreenManager::Instance()->playMusicMainMenu();
//
//	_mapMax =  ScreenManager::Instance()->getMaxMap();
//
//	this->addMapButton(MAP_1, "mini/scene/map_stage/iraq_map.png", "", CC_CALLBACK_2(MainMenuScene::GoToGameScene_1, this), col_1, row_1);
//	this->addMapButton(MAP_2, "mini/scene/map_stage/syria_map.png", "mini/scene/map_stage/syria_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_2, this), col_2, row_1);
//
//	this->addMapButton(MAP_3, "mini/scene/map_stage/morocco_map.png", "mini/scene/map_stage/morocco_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_3, this), col_3, row_1);
//	this->addMapButton(MAP_4, "mini/scene/map_stage/india_map.png", "mini/scene/map_stage/india_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_4, this), col_4, row_1);
//
//	this->addMapButton(MAP_5, "mini/scene/map_stage/china_map.png", "mini/scene/map_stage/china_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_5, this), col_5, row_1);
//
//
//	this->addMapButton(MAP_6, "mini/scene/map_stage/london_map.png", "mini/scene/map_stage/london_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_6, this), col_1, row_2);
//
//	this->addMapButton(MAP_7, "mini/scene/map_stage/berlin_map.png", "mini/scene/map_stage/berlin_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_7, this), col_2, row_2);
//	this->addMapButton(MAP_8, "mini/scene/map_stage/paris_map.png", "mini/scene/map_stage/paris_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_8, this), col_3, row_2);
//
//	this->addMapButton(MAP_9, "mini/scene/map_stage/jakarta_map.png", "mini/scene/map_stage/jakarta_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_9, this), col_4, row_2);
//	this->addMapButton(MAP_10, "mini/scene/map_stage/isarel_map.png", "mini/scene/map_stage/isarel_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_10, this), col_5, row_2);
//
//	this->addMapButton(MAP_11, "mini/scene/map_stage/egypt_map.png", "mini/scene/map_stage/egypt_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_11, this), col_1, row_3);
//	this->addMapButton(MAP_12, "mini/scene/map_stage/usa_map.png", "mini/scene/map_stage/usa_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_12, this), col_2, row_3);
//
//	this->addMapButton(MAP_13, "mini/scene/map_stage/iran_map.png", "mini/scene/map_stage/iran_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_13, this), col_3, row_3);
//	this->addMapButton(MAP_14, "mini/scene/map_stage/russia_map.png", "mini/scene/map_stage/russia_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_14, this), col_4, row_3);
//	this->addMapButton(MAP_15,"mini/scene/map_stage/pakistan_map.png", "mini/scene/map_stage/pakistan_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_15, this), col_5, row_3);
//}
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//void MainMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
//{
//	Director::getInstance()->end();
//}
//#endif
//
//void MainMenuScene::gotoCreditScene(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//	ScreenManager::Instance()->gotoCreditScene();
//}
//
//
//
//
////void MainMenuScene::exitGame()
////{
////
////#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
////	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
////	return;
////#endif
////	Director::getInstance()->end(); 
////
////#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
////	exit(0);
////#endif
////}
//
//
//
