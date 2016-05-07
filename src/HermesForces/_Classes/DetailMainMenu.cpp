#include "DetailMainMenu.h"
#include "ScreenManager.h"
#include "SimpleAudioEngine.h" 
//
//
Scene* DetailMainMenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = DetailMainMenuScene::create();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	layer->setKeypadEnabled(true);
#endif

	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}


bool DetailMainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	_mapMax = ScreenManager::Instance()->getMaxMap();
	_kItem = 0;
	auto backgroundSprite = Sprite::create("mini/scene/main_scene_sky.jpg");

	_deltaScaleBgX = (Director::getInstance()->getVisibleSize().width + Director::getInstance()->getVisibleOrigin().x) / backgroundSprite->getContentSize().width;
	_deltaScaleX = (Director::getInstance()->getVisibleSize().height + Director::getInstance()->getVisibleOrigin().y) / backgroundSprite->getContentSize().height;
	backgroundSprite->setScaleX(_deltaScaleBgX);// (Director::getInstance()->getVisibleSize().width + Director::getInstance()->getVisibleOrigin().x) / 1024);
	backgroundSprite->setScaleY(_deltaScaleX);// (Director::getInstance()->getVisibleSize().height + Director::getInstance()->getVisibleOrigin().y) / 768);
	backgroundSprite->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x,
		Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y));
	this->addChild(backgroundSprite);

	//antitero
	auto antitero = Sprite::create("mini/scene/antitero.png");
	antitero->setScale(_deltaScaleBgX);
	antitero->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x,
		Director::getInstance()->getVisibleSize().height  * 0.9 + Director::getInstance()->getVisibleOrigin().y));
	this->addChild(antitero);

	auto cloudSprite = Sprite::create("mini/scene/cloud.png");
	cloudSprite->setPosition(Point((Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x / 2),
		(Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y / 2)));
	cloudSprite->setScale(_deltaScaleBgX, _deltaScaleX);
	this->addChild(cloudSprite, 1122);

	auto moveToLeft = MoveTo::create(10, Point(cloudSprite->getContentSize().width * _deltaScaleBgX - Director::getInstance()->getVisibleSize().width * 0.5,
		cloudSprite->getPositionY()));
	auto moveToRight = MoveTo::create(10, Point(cloudSprite->getPositionX()  * _deltaScaleBgX + Director::getInstance()->getVisibleSize().width * 0.5,
		cloudSprite->getPositionY()));
	auto seq = Sequence::create(moveToLeft, moveToRight, nullptr);
	cloudSprite->runAction(RepeatForever::create(seq));

	_isMoving = false;

	if (ScreenManager::Instance()->bigMap() == MAP_AREAX)
	{
		float width = Director::getInstance()->getVisibleSize().width + Director::getInstance()->getVisibleOrigin().x;
		float sizeOfItem = width;
		sizeOfItem *= 0.25;
		_deltaScaleX = sizeOfItem / 300; // 300 is size of button

		_row = Director::getInstance()->getVisibleSize().height + Director::getInstance()->getVisibleOrigin().y;
		_row *= 0.45;

		_col1 = width;
		_col1 *= 0.167;
		_col2 = width;
		_col2 *= 0.5;
		_col3 = width;
		_col3 *= 0.833;

		this->addMapButton(MAP_13, "mini/scene/map_stage/iran_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_13, this), _col1, _row);
		this->addMapButton(MAP_14, "mini/scene/map_stage/russia_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_14, this), _col2, _row);
		this->addMapButton(MAP_15, "mini/scene/map_stage/pakistan_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_15, this), _col3, _row);

	}
	else
	{
		float width = Director::getInstance()->getVisibleSize().width + Director::getInstance()->getVisibleOrigin().x;
		float sizeOfItem = width;
		sizeOfItem *= 0.2;

		_row = Director::getInstance()->getVisibleSize().height + Director::getInstance()->getVisibleOrigin().y;
		_row *= 0.5;

		_col1 = width;
		_col1 *= 0.125;
		_col2 = width;
		_col2 *= 0.375;
		_col3 = width;
		_col3 *= 0.625;
		_col4 = width;
		_col4 *= 0.875;
		_deltaScaleX = sizeOfItem / 300;
		if (ScreenManager::Instance()->bigMap() == MAP_DESERT)
		{
			this->addMapButton(MAP_1, "mini/scene/map_stage/iraq_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_1, this), _col1, _row);
			this->addMapButton(MAP_2, "mini/scene/map_stage/syria_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_2, this), _col2, _row);
			this->addMapButton(MAP_3, "mini/scene/map_stage/morocco_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_3, this), _col3, _row);
			this->addMapButton(MAP_4, "mini/scene/map_stage/egypt_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_4, this), _col4, _row);
		}
		else if (ScreenManager::Instance()->bigMap() == MAP_CITY)
		{
			this->addMapButton(MAP_5, "mini/scene/map_stage/china_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_5, this), _col1, _row);
			this->addMapButton(MAP_6, "mini/scene/map_stage/london_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_6, this), _col2, _row);
			this->addMapButton(MAP_7, "mini/scene/map_stage/berlin_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_7, this), _col3, _row);
			this->addMapButton(MAP_8, "mini/scene/map_stage/usa_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_8, this), _col4, _row);
		}
		else if (ScreenManager::Instance()->bigMap() == MAP_SUBURB)
		{
			this->addMapButton(MAP_9, "mini/scene/map_stage/india_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_9, this), _col1, _row);
			this->addMapButton(MAP_10, "mini/scene/map_stage/paris_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_10, this), _col2, _row);
			this->addMapButton(MAP_11, "mini/scene/map_stage/jakarta_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_11, this), _col3, _row);
			this->addMapButton(MAP_12, "mini/scene/map_stage/isarel_map.png", CC_CALLBACK_2(DetailMainMenuScene::GoToGameScene_12, this), _col4, _row);
		}
	}

	_maskClicked = Sprite::create("mini/scene/map_stage/map_click.png");
	_maskClicked->setScale(_deltaScaleX);
	_maskClicked->setOpacity(0);
	this->addChild(_maskClicked, 1133);


	this->scheduleOnce(schedule_selector(DetailMainMenuScene::finishLoadingButton1), 0.55f);
	this->scheduleOnce(schedule_selector(DetailMainMenuScene::finishLoadingButton2), 0.6f);
	this->scheduleOnce(schedule_selector(DetailMainMenuScene::finishLoadingButton3), 0.65f);
	if (_kItem > 3)
		this->scheduleOnce(schedule_selector(DetailMainMenuScene::finishLoadingButton4), 0.7f);

	this->scheduleOnce(schedule_selector(DetailMainMenuScene::onFinishButtonBackLoading), 0.75f);
	return true;
}

void DetailMainMenuScene::GoToMainMenuScene(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	ScreenManager::Instance()->gotoMainMenu();
}

void DetailMainMenuScene::addMapButton(const int& MapNumber, const std::string& path, const cocos2d::ui::Widget::ccWidgetTouchCallback& callback, const float& col, const float& row)
{
	_litemButton[_kItem] = cocos2d::ui::Button::create();
	//itemButton->setTouchEnabled(true);
	_litemButton[_kItem]->loadTextures(path, path, "");
	if (MapNumber <= _mapMax)
	{
		_litemButton[_kItem]->addTouchEventListener(callback);
	}
	else{
		auto maskLock = Sprite::create("mini/scene/map_stage/lock.png");
		maskLock->setScale(_deltaScaleX);
		maskLock->setPosition(Point(col, row));
		this->addChild(maskLock, 1111);
	}
	_litemButton[_kItem]->setScale(_deltaScaleX);
	_litemButton[_kItem]->setPosition(Point(col, row));
	_litemButton[_kItem]->setVisible(false);
	this->addChild(_litemButton[_kItem]);
	_kItem++;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void DetailMainMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	ScreenManager::Instance()->gotoMainMenu();
}
#endif

void DetailMainMenuScene::GoToGameScene_1(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col1, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_1);
	}
}
void DetailMainMenuScene::GoToGameScene_2(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col2, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_2);
	}
}
void DetailMainMenuScene::GoToGameScene_3(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col3, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;			
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_3);
	}
}
void DetailMainMenuScene::GoToGameScene_4(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col4, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_4);
	}
}
void DetailMainMenuScene::GoToGameScene_5(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col1, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_5);
	}
}
void DetailMainMenuScene::GoToGameScene_6(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col2, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_6);
	}
}
void DetailMainMenuScene::GoToGameScene_7(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col3, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_7);
	}
}
void DetailMainMenuScene::GoToGameScene_8(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col4, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_8);
	}
}
void DetailMainMenuScene::GoToGameScene_9(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col1, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_9);
	}
}
void DetailMainMenuScene::GoToGameScene_10(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col2, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_10);
	}
}
void DetailMainMenuScene::GoToGameScene_11(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col3, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_11);
	}
}
void DetailMainMenuScene::GoToGameScene_12(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col4, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_12);
	}
}
void DetailMainMenuScene::GoToGameScene_13(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col1, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_13);
	}
}
void DetailMainMenuScene::GoToGameScene_14(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col2, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_14);
	}
}
void DetailMainMenuScene::GoToGameScene_15(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_maskClicked->setOpacity(255);
		_maskClicked->setPosition(_col3, _row);
		_isMoving = false;
	}
	if (eEventType == ui::Widget::TouchEventType::MOVED)
	{
		if (!_isMoving)
		{
			_isMoving = true;
			auto fadeOut = FadeOut::create(0.15);
			_maskClicked->runAction(fadeOut);
		}
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_15);
	}
}

void DetailMainMenuScene::onFinishButtonBackLoading(float dt)
{
	auto backButton = cocos2d::ui::Button::create();
	backButton->loadTextures("mini/scene/btt_large.png", "mini/scene/btt_large.png", "");
	backButton->setScale(_deltaScaleX * 1.4);
	float distanceConer = 0.12 * Director::getInstance()->getVisibleSize().height;
	backButton->setPosition(Point(Director::getInstance()->getVisibleSize().width * 0.92 + Director::getInstance()->getVisibleOrigin().x,
		Director::getInstance()->getVisibleSize().height  * 0.9 + Director::getInstance()->getVisibleOrigin().y));
	//backButton->setPosition(Point(Director::getInstance()->getVisibleSize().width - distanceConer,
	//	Director::getInstance()->getVisibleSize().height - distanceConer));
	backButton->addTouchEventListener(CC_CALLBACK_2(DetailMainMenuScene::GoToMainMenuScene, this));
	this->addChild(backButton);
}



void DetailMainMenuScene::finishLoadingButton1(float dt)
{
	_litemButton[0]->setVisible(true);
}

void DetailMainMenuScene::finishLoadingButton2(float dt)
{
	_litemButton[1]->setVisible(true);
}

void DetailMainMenuScene::finishLoadingButton3(float dt)
{
	_litemButton[2]->setVisible(true);
}

void DetailMainMenuScene::finishLoadingButton4(float dt)
{
	_litemButton[3]->setVisible(true);
}
