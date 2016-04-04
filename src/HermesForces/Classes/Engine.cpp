//
//  Engine.cpp
//  BombTerrorist
//
//  Created by Quan Rock on 1/26/16.
//
//

#include "Engine.h"
Engine*    Engine::_instance = NULL;
#define IS_LANDSCAPE true
#define MAX(x,y) x > y ? x : y;
Engine::Engine()
{
    
}

// init infor
void Engine::init()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);

}

// get type of scene
int Engine::getSizeTypeDevice()
{
    return _typeSizeDevice;
}

void Engine::setDirector()
{
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
		glview = GLViewImpl::create("Flappy Bird Clone. By Sonar Systems");
#else
		glview = GLViewImpl::create("My Game");
#endif
		director->setOpenGLView(glview);
	}

	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	//auto fileUtils = FileUtils::getInstance();
	auto screenSize = glview->getFrameSize();
	//std::vector<std::string> resDirOrders;

	int maxSize = MAX(screenSize.width, screenSize.height);
	int minSize = screenSize.height + screenSize.width - maxSize;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//// check which assets the devices requires
	//if (2048 =< screenSize.width || 2048 =< screenSize.height) // retina iPad
	//{
	//	//resDirOrders.push_back("ipadhd");
	//	//resDirOrders.push_back("ipad");
	//	//resDirOrders.push_back("iphonehd5");
	//	//resDirOrders.push_back("iphonehd");
	//	//resDirOrders.push_back("iphone");

	//	if (true == IS_LANDSCAPE)
	//	{
	//		glview->setDesignResolutionSize(2048, 1536, ResolutionPolicy::NO_BORDER);
	//	}
	//	else
	//	{
	//		glview->setDesignResolutionSize(1536, 2048, ResolutionPolicy::NO_BORDER);
	//	}
	//}
	//else if (1136 >= screenSize.width || 1136 >= screenSize.height) // retina iPhone (5 and 5S)
	//{
	//	//resDirOrders.push_back("iphonehd5");
	//	//resDirOrders.push_back("iphonehd");
	//	//resDirOrders.push_back("iphone");

	//	if (true == IS_LANDSCAPE)
	//	{
	//		glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::NO_BORDER);
	//	}
	//	else
	//	{
	//		glview->setDesignResolutionSize(640, 1136, ResolutionPolicy::NO_BORDER);
	//	}
	//}
	//else if (1024 >= screenSize.width || 1024 >= screenSize.height) // non retina iPad
	//{
	//	//resDirOrders.push_back("ipad");
	//	//resDirOrders.push_back("iphonehd5");
	//	//resDirOrders.push_back("iphonehd");
	//	//resDirOrders.push_back("iphone");

	//	if (true == IS_LANDSCAPE)
	//	{
	//		glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::NO_BORDER);
	//	}
	//	else
	//	{
	//		glview->setDesignResolutionSize(768, 1024, ResolutionPolicy::NO_BORDER);
	//	}
	//}
	//else if (960 == screenSize.width || 960 == screenSize.height) // retina iPhone (4 and 4S)
	//{
	//	//resDirOrders.push_back("iphonehd");
	//	//resDirOrders.push_back("iphone");

	//	if (true == IS_LANDSCAPE)
	//	{
	//		glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
	//	}
	//	else
	//	{
	//		glview->setDesignResolutionSize(640, 960, ResolutionPolicy::NO_BORDER);
	//	}
	//}
	//else // non retina iPhone and Android devices
	//{
	//	if (1080 < screenSize.width && 1080 < screenSize.height) // android devices that have a high resolution
	//	{
	//		//resDirOrders.push_back("iphonehd");
	//		//resDirOrders.push_back("iphone");

	//		if (true == IS_LANDSCAPE)
	//		{
	//			glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
	//		}
	//		else
	//		{
	//			glview->setDesignResolutionSize(640, 960, ResolutionPolicy::NO_BORDER);
	//		}
	//	}
	//	else // non retina iPhone and Android devices with lower resolutions
	//	{
	//		//resDirOrders.push_back("iphone");

	//		if (true == IS_LANDSCAPE)
	//		{
	//			glview->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);
	//		}
	//		else
	//		{
	//			glview->setDesignResolutionSize(320, 480, ResolutionPolicy::NO_BORDER);
	//		}
	//	}
	//}
	//glview->setFrameSize(maxSize, minSize);
	//glview->setDesignResolutionSize(maxSize, minSize, ResolutionPolicy::NO_BORDER);
	glview->setFrameSize(maxSize, minSize);
	glview->setDesignResolutionSize(maxSize, minSize, ResolutionPolicy::NO_BORDER);
	

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	//resDirOrders.push_back("ipad");
	//resDirOrders.push_back("iphonehd5");
	//resDirOrders.push_back("iphonehd");
	//resDirOrders.push_back("iphone");

	if (true == IS_LANDSCAPE)
	{
		glview->setFrameSize(1024, 768);
		glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::NO_BORDER);
	}
	else
	{
		glview->setFrameSize(768, 1024);
		glview->setDesignResolutionSize(768, 1024, ResolutionPolicy::NO_BORDER);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//resDirOrders.push_back("ipad");
	//resDirOrders.push_back("iphonehd5");
	//resDirOrders.push_back("iphonehd");
	//resDirOrders.push_back("iphone");
//float kWH = maxSize / minSize;

glview->setFrameSize(1337, 750);
glview->setDesignResolutionSize(1337, 750, ResolutionPolicy::EXACT_FIT);
//
//glview->setFrameSize(920, 680);
//glview->setDesignResolutionSize(920, 680, ResolutionPolicy::EXACT_FIT);

//glview->setFrameSize(1330, 750);
//glview->setDesignResolutionSize(1330, 750, ResolutionPolicy::EXACT_FIT);

	//if (true == IS_LANDSCAPE)
	//{
	//	glview->setFrameSize(1024, 768);
	//	glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::EXACT_FIT);
	//}
	//else
	//{
	//	glview->setFrameSize(768, 1024);
	//	glview->setDesignResolutionSize(768, 1024, ResolutionPolicy::EXACT_FIT);
	//}

#endif

	//fileUtils->setSearchPaths(resDirOrders);




	// OLD CODE
//	cocos2d::Size PCSizeTest = cocos2d::Size(1024, 768);
//
//    cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
//    cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
//    cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
//    cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);
//    
//    auto director = Director::getInstance();
//    auto glview = director->getOpenGLView();
//    if(!glview) {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
//		glview = GLViewImpl::createWithRect("BombTerrorist", Rect(0, 0, PCSizeTest.width, PCSizeTest.height));
//#else
//        glview = GLViewImpl::create("BombTerrorist");
//#endif
//        director->setOpenGLView(glview);
//    }
//    
//    // turn on display FPS
//    director->setDisplayStats(true);
//    
//    // set FPS. the default value is 1.0/60 if you don't call this
//    director->setAnimationInterval(1.0 / 60);
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
//	glview->setDesignResolutionSize(PCSizeTest.width, PCSizeTest.height, ResolutionPolicy::NO_BORDER);
//#else
//    // Set the design resolution
//    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
//#endif
//
//    Size frameSize = glview->getFrameSize();
//    // if the frame's height is larger than the height of medium size.
//    if (frameSize.height > mediumResolutionSize.height)
//    {
//        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
//		//glview->setDesignResolutionSize(largeResolutionSize.width, largeResolutionSize.height, ResolutionPolicy::NO_BORDER);
//    }
//    // if the frame's height is larger than the height of small size.
//    else if (frameSize.height > smallResolutionSize.height)
//    {
//        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
//		//glview->setDesignResolutionSize(mediumResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
//    }
//    // if the frame's height is smaller than the height of medium size.
//    else
//    {
//        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
//		//glview->setDesignResolutionSize(smallResolutionSize.width, smallResolutionSize.height, ResolutionPolicy::NO_BORDER);
//    }
//	_visibleSize = Director::getInstance()->getVisibleSize();
}

void Engine::startAnimationGame()
{
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void Engine::stopAnimationGame()
{
    Director::getInstance()->stopAnimation();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

cocos2d::Size Engine::getVisibleSize() const 
{
    return _visibleSize;
}

void Engine::gotoScene(Scene* scene)
{
    Director::getInstance()->runWithScene(scene );
}

void Engine::replaceScene(Scene* scene,  const int& delaytime)
{
    Director::getInstance()->replaceScene(TransitionFade::create( delaytime, scene ) );
}



