#include "GameOverScene.h"
#include "ScreenManager.h"
#include "Missions/Land.h"
#include "Fighter/Fighter.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "SonarFrameworks.h"
#endif
Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	layer->setKeypadEnabled(true);
#endif
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //mx[0] = 0;
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	std::string path_today = ScreenManager::Instance()->getRecentMapPath();

	auto backgroundSprite = Sprite::create(path_today);

	float x = (Director::getInstance()->getVisibleSize().width/* + Director::getInstance()->getVisibleOrigin().x*/) / backgroundSprite->getContentSize().width;
	float y = (Director::getInstance()->getVisibleSize().height/* + Director::getInstance()->getVisibleOrigin().y*/) / backgroundSprite->getContentSize().height;

	backgroundSprite->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x,
		Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y));

	backgroundSprite->setScaleX(x);// (Director::getInstance()->getVisibleSize().width + Director::getInstance()->getVisibleOrigin().x) / 1024);
	backgroundSprite->setScaleY(y);// (Director::getInstance()->getVisibleSize().height + Director::getInstance()->getVisibleOrigin().y) / 768);

	//ScreenManager::Instance()->scaleScreenFull(backgroundSprite);
	this->addChild(backgroundSprite);
    
	Sprite* _statusImage;
	if (ScreenManager::Instance()->getStatusMapOver()){
		_statusImage = Sprite::create("mini/scene/mission_finish.png");
		ScreenManager::Instance()->writeResult();
	}	
	else
		_statusImage = Sprite::create("mini/scene/mission_failed.png");
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	ScreenManager::Instance()->playMusicGameOverScene();

	//radioloop
	_statusImage->setPosition(Point(visibleSize.width / 2, visibleSize.height * 0.8));
	_statusImage->setScale(Land::deltaScale);
	this->addChild(_statusImage);


//    auto retryItem = MenuItemImage::create( "mini/scene/button_retry.jpg", "mini/scene/button_retry.jpg", CC_CALLBACK_1( GameOverScene::GoToGameScene, this ) );
//    retryItem->setPosition( Point( visibleSize.width * 0.25 , visibleSize.height * 0.5 ) );
//	retryItem->setScale(Land::deltaScale);
//    auto mainMenuItem = MenuItemImage::create( "mini/scene/button_menu.jpg", "mini/scene/button_menu.jpg", CC_CALLBACK_1( GameOverScene::GoToMainMenuScene, this ) );
//	mainMenuItem->setPosition(Point(visibleSize.width * 0.75, visibleSize.height * 0.5));
//	mainMenuItem->setScale(Land::deltaScale);
//    auto menu = Menu::create( retryItem, mainMenuItem, NULL );
//    menu->setPosition( Point::ZERO );
//    
//    this->addChild( menu );
    
//    auto retryItem = cocos2d::ui::Button::cMenuItemImage::create( "mini/scene/button_retry.jpg", "mini/scene/button_retry.jpg", CC_CALLBACK_1( GameOverScene::GoToGameScene, this ) );
//    retryItem->setPosition( Point( visibleSize.width * 0.25 , visibleSize.height * 0.5 ) );
//    retryItem->setScale(Land::deltaScale);
//    auto mainMenuItem = MenuItemImage::create( "mini/scene/button_menu.jpg", "mini/scene/button_menu.jpg", CC_CALLBACK_1( GameOverScene::GoToMainMenuScene, this ) );
//    mainMenuItem->setPosition(Point(visibleSize.width * 0.75, visibleSize.height * 0.5));
//    mainMenuItem->setScale(Land::deltaScale);
    
    
	auto cloudSprite = Sprite::create("mini/scene/cloud.png");
	cloudSprite->setPosition(Point(cloudSprite->getContentSize().width * 0.5 * y + origin.x * 0.5, visibleSize.height / 2 + origin.y * 0.5));
	cloudSprite->setScale(y);
	this->addChild(cloudSprite);

	auto moveToLeft = MoveTo::create(15, Point(cloudSprite->getContentSize().width * y - visibleSize.width, visibleSize.height * 0.5 + origin.y * 0.5));
	auto moveToRight = MoveTo::create(15, Point(cloudSprite->getPositionX(), visibleSize.height * 0.5 + origin.y * 0.5));
	auto seq = Sequence::create(moveToLeft, moveToRight, nullptr);
	cloudSprite->runAction(RepeatForever::create(seq));

	
	//float wi = cloudSprite->getContentSize().width * 0.5 * x + origin.x * 0.5;
	//float wl = cloudSprite->getContentSize().width * x - visibleSize.width;
	//float wx = cloudSprite->getPositionX();


	// ios > 3
	if(ScreenManager::Instance()->CurrentMap() >= 3)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		SonarCocosHelper::IOS::Setup();
		SonarCocosHelper::AdMob::showBannerAd(SonarCocosHelper::AdBannerPosition::eTop);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SonarCocosHelper::AdMob::showBannerAd(SonarCocosHelper::AdBannerPosition::eBottom);
#endif
	}


	this->scheduleOnce(schedule_selector(GameOverScene::onFinishLoading), 0.75f);
    return true;
}

//void GameOverScene::GoToMainMenuScene( cocos2d::Ref *sender )
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    SonarCocosHelper::AdMob::hideBannerAd(SonarCocosHelper::AdBannerPosition::eBottom);
//#endif
//    ScreenManager::Instance()->gotoMainMenu();
//}
//
//void GameOverScene::GoToGameScene( cocos2d::Ref *sender )
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    SonarCocosHelper::AdMob::hideBannerAd(SonarCocosHelper::AdBannerPosition::eBottom);
//#endif
//    ScreenManager::Instance()->reloadGameScene();
//}

void GameOverScene::GoToMainMenuScene( Ref* pSender, ui::Widget::TouchEventType eEventType )
{
	//if (Land::thisPointer)
	//	delete Land::thisPointer;
	//if (Fighter::ThisPointer)
	//	delete Fighter::ThisPointer;
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		if(ScreenManager::Instance()->CurrentMap() >= 3)
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			SonarCocosHelper::AdMob::hideBannerAd(SonarCocosHelper::AdBannerPosition::eBottom);
#endif
		}
        ScreenManager::Instance()->gotoMainMenu();
    }
}

void GameOverScene::GoToGameScene( Ref* pSender, ui::Widget::TouchEventType eEventType )
{
	//if (Land::thisPointer)
	//	Land::thisPointer->preReleaseLand();
	//if (Fighter::ThisPointer)
	//	delete Fighter::ThisPointer;

	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		if(ScreenManager::Instance()->CurrentMap() >= 3)
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			SonarCocosHelper::AdMob::hideBannerAd(SonarCocosHelper::AdBannerPosition::eBottom);
#endif
		}
        ScreenManager::Instance()->reloadGameScene();
    }
}

GameOverScene::~GameOverScene()
{

}


void GameOverScene::onFinishLoading(float dt)
{
	//ScreenManager::Instance()->releaseGameScene();

	itemRetryButton = cocos2d::ui::Button::create();
	itemRetryButton->loadTextures("mini/scene/button_retry.jpg", "", "");
	itemRetryButton->addTouchEventListener(CC_CALLBACK_2(GameOverScene::GoToGameScene, this));
	itemRetryButton->setPosition(Point(Director::getInstance()->getVisibleSize().width * 0.25, Director::getInstance()->getVisibleSize().height * 0.5));
	itemRetryButton->setScale(Land::deltaScale);
	this->addChild(itemRetryButton);


	itemMenuButton = cocos2d::ui::Button::create();
	itemMenuButton->loadTextures("mini/scene/button_menu.jpg", "", "");
	itemMenuButton->addTouchEventListener(CC_CALLBACK_2(GameOverScene::GoToMainMenuScene, this));
	itemMenuButton->setPosition(Point(Director::getInstance()->getVisibleSize().width * 0.75, Director::getInstance()->getVisibleSize().height * 0.5));
	itemMenuButton->setScale(Land::deltaScale);
	this->addChild(itemMenuButton);

}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void GameOverScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if(ScreenManager::Instance()->CurrentMap() >= 3)
	{
	SonarCocosHelper::AdMob::hideBannerAd(SonarCocosHelper::AdBannerPosition::eBottom);
	}
	ScreenManager::Instance()->gotoMainMenu();
}
#endif

