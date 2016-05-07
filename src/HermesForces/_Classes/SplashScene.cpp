#include "SplashScene.h"
#include "ScreenManager.h"
Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{ 
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
   
//    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("mini/scene/splash_scene.jpg");
    ScreenManager::Instance()->scaleScreenFull(sprite);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), 0.0f);
    return true;
}
void SplashScene::GoToMainMenuScene(float dt)
{
    ScreenManager::Instance()->initInstance();
	ScreenManager::Instance()->gotoMainMenu();
}



