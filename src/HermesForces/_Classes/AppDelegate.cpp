#include "AppDelegate.h"
//#include "HelloWorldScene.h"

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    Engine::Instance()->init();
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Engine::Instance()->setDirector();
    register_all_packages();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ScreenManager::Instance()->startApplication(false);
#else
    ScreenManager::Instance()->startApplication(true);
#endif
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Engine::Instance()->stopAnimationGame();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Engine::Instance()->startAnimationGame();
}
