#include "MainMenuScene.h"
#include "ScreenManager.h"
#include "SimpleAudioEngine.h" 


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

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create( "mini/scene/main_scene.jpg" );
	
	float x = (Director::getInstance()->getVisibleSize().width/* + Director::getInstance()->getVisibleOrigin().x*/) / backgroundSprite->getContentSize().width;
	float y = (Director::getInstance()->getVisibleSize().height/* + Director::getInstance()->getVisibleOrigin().y*/) / backgroundSprite->getContentSize().height;

	backgroundSprite->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x,
		Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y));

	backgroundSprite->setScaleX(x);// (Director::getInstance()->getVisibleSize().width + Director::getInstance()->getVisibleOrigin().x) / 1024);
	backgroundSprite->setScaleY(y);// (Director::getInstance()->getVisibleSize().height + Director::getInstance()->getVisibleOrigin().y) / 768);

	//ScreenManager::Instance()->scaleScreenFull(backgroundSprite);
    this->addChild( backgroundSprite );
    
	//float heightEachRow = visibleSize.height * 0.2;
	// 0.18  
	// 

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

	//auto musicBtt = Sprite::create("mini/scene/musicbtt.png");
	//auto soundBtt = Sprite::create("mini/scene/soundbtt.png");
	musicBtt->setScale(x*1.5);
	soundBtt->setScale(x*1.5);

	float widthReal = visibleSize.width - musicBtt->getContentSize().width *  x;
	float widthEachCell = (widthReal)* 0.16;
	float heightEachCell = visibleSize.height * 0.26;
	float sizeCell = widthEachCell < heightEachCell ? widthEachCell : heightEachCell;
	_scaleMap = sizeCell/300; // 300 is height-width of image

	const float row_3 = 0.2 * visibleSize.height;
	const float row_2 = 0.5 * visibleSize.height;
	const float row_1 = 0.8 * visibleSize.height;

	const float col_1 = 0.14 * widthReal;// visibleSize.width;
	const float col_2 = 0.32 * widthReal;//visibleSize.width;
	const float col_3 = 0.5 * widthReal;//visibleSize.width;
	const float col_4 = 0.68 * widthReal;//visibleSize.width;
	const float col_5 = 0.86 * widthReal;//visibleSize.width;

	// 
//    auto titleSprite = Sprite::create( "game_scene/Menu_Button.png" );
//    titleSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height * 0.9 ) ); 
//	titleSprite->setScale(heightEachRow/titleSprite->getContentSize().height);
//    this->addChild( titleSprite );
	//

	// const std::string& const ccMenuCallback& callback
	// const float& col
    _mapMax = 8;//ScreenManager::Instance()->getMaxMap();

	this->addMapButton(MAP_1,"mini/scene/map_stage/iraq_map.png", "", CC_CALLBACK_2(MainMenuScene::GoToGameScene_1, this), col_1, row_1);
	this->addMapButton(MAP_2,"mini/scene/map_stage/syria_map.png", "mini/scene/map_stage/syria_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_2, this), col_2, row_1);

	this->addMapButton(MAP_3,"mini/scene/map_stage/morocco_map.png", "mini/scene/map_stage/morocco_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_3, this), col_3, row_1);
	this->addMapButton(MAP_4,"mini/scene/map_stage/india_map.png", "mini/scene/map_stage/india_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_4, this), col_4, row_1);

	this->addMapButton(MAP_5,"mini/scene/map_stage/china_map.png", "mini/scene/map_stage/china_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_5, this), col_5, row_1);


	this->addMapButton(MAP_6,"mini/scene/map_stage/london_map.png", "mini/scene/map_stage/london_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_6, this), col_1, row_2);

	this->addMapButton(MAP_7,"mini/scene/map_stage/berlin_map.png", "mini/scene/map_stage/berlin_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_7, this), col_2, row_2);
	this->addMapButton(MAP_8,"mini/scene/map_stage/paris_map.png", "mini/scene/map_stage/paris_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_8, this), col_3, row_2);

	this->addMapButton(MAP_9,"mini/scene/map_stage/jakarta_map.png", "mini/scene/map_stage/jakarta_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_9, this), col_4, row_2);
	this->addMapButton(MAP_10,"mini/scene/map_stage/isarel_map.png", "mini/scene/map_stage/isarel_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_10, this), col_5, row_2);

	this->addMapButton(MAP_11,"mini/scene/map_stage/egypt_map.png", "mini/scene/map_stage/egypt_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_11, this), col_1, row_3);
	this->addMapButton(MAP_12,"mini/scene/map_stage/usa_map.png", "mini/scene/map_stage/usa_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_12, this), col_2, row_3);

	this->addMapButton(MAP_13,"mini/scene/map_stage/iran_map.png", "mini/scene/map_stage/iran_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_13, this), col_3, row_3);
	this->addMapButton(MAP_14,"mini/scene/map_stage/russia_map.png", "mini/scene/map_stage/russia_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_14, this), col_4, row_3);
	this->addMapButton(MAP_15,"mini/scene/map_stage/pakistan_map.png", "mini/scene/map_stage/pakistan_map_no.png", CC_CALLBACK_2(MainMenuScene::GoToGameScene_15, this), col_5, row_3);

	auto map_15 = Sprite::create("mini/scene/map_stage/pakistan_map.png");
	const float col_6_start = col_5 + map_15->getContentSize().width *  0.5 * _scaleMap;
	float col_6 = (col_6_start + visibleSize.width) / 2;
	musicBtt->setPosition(Point(col_6, row_1 + map_15->getContentSize().height *  0.5 * _scaleMap -
		musicBtt->getContentSize().height * x * 0.5 *1.5));
	soundBtt->setPosition(Point(musicBtt->getPositionX(), musicBtt->getPositionY() - musicBtt->getContentSize().height * x * 1.25 * 1.5));

    
    
	this->addChild(musicBtt);
	this->addChild(soundBtt);

	auto cloudSprite = Sprite::create("mini/scene/cloud.png");
	cloudSprite->setPosition(Point(cloudSprite->getContentSize().width * 0.5 * y + origin.x * 0.5, visibleSize.height / 2 + origin.y * 0.5));
	cloudSprite->setScale(y);
	this->addChild(cloudSprite);
	
	auto moveToLeft = MoveTo::create(15, Point(cloudSprite->getContentSize().width * y - visibleSize.width, visibleSize.height * 0.5 + origin.y * 0.5));
	auto moveToRight = MoveTo::create(15, Point(cloudSprite->getPositionX(), visibleSize.height * 0.5 + origin.y * 0.5));
	auto seq = Sequence::create(moveToLeft, moveToRight, nullptr);
	cloudSprite->runAction(RepeatForever::create(seq));
	ScreenManager::Instance()->playMusicMainMenu();
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("heli_loop.mp3");
    return true;
}

void MainMenuScene::GoToGameScene_1(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_1);
	}
}
void MainMenuScene::GoToGameScene_2(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_2);
	}
}
void MainMenuScene::GoToGameScene_3(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_3);
	}
}
void MainMenuScene::GoToGameScene_4(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_4);
	}
}
void MainMenuScene::GoToGameScene_5(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_5);
	}
}
void MainMenuScene::GoToGameScene_6(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_6);
	}
}
void MainMenuScene::GoToGameScene_7(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_7);
	}
}
void MainMenuScene::GoToGameScene_8(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_8);
	}
}
void MainMenuScene::GoToGameScene_9(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_9);
	}
}
void MainMenuScene::GoToGameScene_10(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_10);
	}
}
void MainMenuScene::GoToGameScene_11(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_11);
	}
}
void MainMenuScene::GoToGameScene_12(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_12);
	}
}
void MainMenuScene::GoToGameScene_13(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_13);
	}
}
void MainMenuScene::GoToGameScene_14(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_14);
	}
}
void MainMenuScene::GoToGameScene_15(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		ScreenManager::Instance()->gotoGameScene(MAP_15);
	}
}

void MainMenuScene::addMapButton(const int& MapNumber, const std::string& path, const std::string& path_no, const cocos2d::ui::Widget::ccWidgetTouchCallback& callback, const float& col, const float& row)
{
	auto itemButton = cocos2d::ui::Button::create();
	//itemButton->setTouchEnabled(true);
	if (MapNumber <= _mapMax)
	{
		itemButton->loadTextures(path, "", "");
		itemButton->addTouchEventListener(callback);
	}
	else{
		itemButton->loadTextures(path_no, "", "");
	}
	// TODO:
	

	itemButton->setScale(_scaleMap);
	itemButton->setPosition(Point(col, row));
	
	this->addChild(itemButton);
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

		//UserCallback::GetDeviceType()	
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void MainMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	Director::getInstance()->end();
}
#endif



//void MainMenuScene::exitGame()
//{
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
//	return;
//#endif
//	Director::getInstance()->end(); 
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	exit(0);
//#endif
//}



