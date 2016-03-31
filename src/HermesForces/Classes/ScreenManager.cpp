//
//  ScreenManager.cpp
//  BombTerrorist
//
//  Created by Quan Rock on 1/26/16.
//
//

#include "ScreenManager.h"
#include "Missions/MapProccessor.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "SonarFrameworks.h"
#endif
// bg for all : 500 * 1680
Scene* _currentScene;
ScreenManager*    ScreenManager::_instance = NULL;

#define MIN_PIXEL_EACH_INCH 640

inline int ToInt(const char* number)
{
	char *end;
	int value = strtol(number, &end, 10);
	if (end == number || *end != '\0' || errno == ERANGE)
		return 0;
	else
		return value;
}

ScreenManager::ScreenManager()
{

}

void ScreenManager::initInstance()
{
    _mapNumber = -1;
    _isOnMusic = true;
    _isOnSound = true;
    _deviceType = IS_PHONE;
    //_isWelcome3s = true;
    //float a = Engine::Instance()->getVisibleSize().height;
    //_khBackground = 500 / a;
    _listThemeSongs.push_back("Sounds/Fortunate_Son.mp3");
    _listThemeSongs.push_back("Sounds/AllDayAndAllOfTheNight.mp3");
    _listThemeSongs.push_back("Sounds/PsychoticReaction.mp3");
    _listThemeSongs.push_back("Sounds/UpAroundTheBend.mp3");
    _back = -1;
    _back2 = -1;
    this->getMusicStatus();
    this->getSoundStatus();
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sounds/heli_loop.mp3");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    _deviceType = SonarCocosHelper::UserCallback::GetDeviceSize();
#endif
    _minPixel = Director::getInstance()->getVisibleSize().width / MIN_PIXEL_EACH_INCH;
    _delayTime = 1;
    if (_deviceType == IS_MINI_TABLET)
        _delayTime = TIME_DELAY_MINI_TABLET;
    else if (_deviceType == IS_TABLET)
    {
        _delayTime = TIME_DELAY_TABLET;
    }
    _minPixel *= _delayTime;
}

void ScreenManager::startApplication(const bool& isGoToSplash)
{
    if(isGoToSplash){
        this->gotoSplash();
    }
    else{
        this->initInstance();
        this->gotoMainMenu();
    }
}


const int& ScreenManager::CurrentMap()
{
	return _mapNumber;
}


const float& ScreenManager::getkScale()
{
	return _khBackground;
}


void ScreenManager::scaleScreenFull(cocos2d::Sprite* bg)
{
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//int w = Director::getInstance()->getWinSize().width;
	//int h = Director::getInstance()->getWinSize().height;

	float x = (Director::getInstance()->getVisibleSize().width/* + Director::getInstance()->getVisibleOrigin().x*/) / bg->getContentSize().width;
	float y = (Director::getInstance()->getVisibleSize().height/* + Director::getInstance()->getVisibleOrigin().y*/) / bg->getContentSize().height;

	bg->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x,
		Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y));

	bg->setScaleX(x);// (Director::getInstance()->getVisibleSize().width + Director::getInstance()->getVisibleOrigin().x) / 1024);
	bg->setScaleY(y);// (Director::getInstance()->getVisibleSize().height + Director::getInstance()->getVisibleOrigin().y) / 768);
}

void ScreenManager::writeResult()
{
	char szMapStr[10] = { 0 };
	sprintf(szMapStr, "%d", _mapNumber+1);
	std::string path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "631164782_map.db";
	FILE *fp1 = fopen(path.c_str(), "w");
	if (fp1)
	{
		fputs(szMapStr, fp1);
	}
	else
	{
		fclose(fp1);
		return;
	}
	fclose(fp1);
}

const int& ScreenManager::getMaxMap()
{
	std::string path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "631164782_map.db";
	FILE* f = fopen(path.c_str(), "r");
	if (cocos2d::FileUtils::sharedFileUtils()->isFileExist(path) == true)
	{
		char buf1[12] = { 0 };
		if (f)
		{
			fgets(buf1, 12, f);
		}
		else
		{
			fclose(f);
			return 0;
		}
		fclose(f);
		return ToInt(buf1);
	}
	return 0;
}

void ScreenManager::writeSettingMusic(const bool& isOn)
{
	std::string path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "631164782_music.db";
	FILE *fp1 = fopen(path.c_str(), "w");
	//if (!fp1)
	//{
	//	//CCLOG("can not open file %s", path.c_str());
	//}
	if (fp1)
	{
		if (isOn)
			fputs("1", fp1);
		else
			fputs("0", fp1);
	}
	else
	{
		fclose(fp1);
		return;
	}
	fclose(fp1);
	_isOnMusic = isOn;
}


void ScreenManager::writeSettingSound(const bool& isOn)
{
	std::string path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "631164782_sound.db";
	FILE *fp1 = fopen(path.c_str(), "w");
	if (fp1)
	{
		if (isOn)
			fputs("1", fp1);
		else
			fputs("0", fp1);
	}
	else
	{
		fclose(fp1);
		return;
	}
	fclose(fp1);
	_isOnSound = isOn;
}

void ScreenManager::getMusicStatus()
{
	std::string path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "631164782_music.db";
	if (cocos2d::FileUtils::sharedFileUtils()->isFileExist(path) == true)
	{
		FILE* f = fopen(path.c_str(), "r");
		char buf1[12] = { 0 };

		if (f)
		{
			fgets(buf1, 12, f);
		}
		else
		{
			fclose(f);
			return;
		}
		fclose(f);
		if (strlen(buf1) == 0)
			return;

		if (strcmp(buf1, "0") == 0)
			_isOnMusic = false;
	}
	//return ToInt(buf1);
}

void ScreenManager::getSoundStatus()
{
	std::string path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "631164782_sound.db";
	if (cocos2d::FileUtils::sharedFileUtils()->isFileExist(path) == true)
	{
		FILE* f = fopen(path.c_str(), "r");
		char buf1[12] = { 0 };

		if (f)
		{
			fgets(buf1, 12, f);
		}
		else
		{
			fclose(f);
			return;
		}
		fclose(f);

		if (strlen(buf1) == 0)
			return;

		if (strcmp(buf1, "0") == 0)
			_isOnSound = false;
	}
}

void ScreenManager::playMusicGameScene()
{
	if (_mapNumber == MAP_5)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sounds/zeppelin.mp3", true);
	else
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sounds/heli_loop.mp3", true);

	if (!_isOnMusic)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	else
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void ScreenManager::playMusicGameOverScene()
{
	if (_isOnSound)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

	if (_isOnMusic){
		if (_mapNumber == MAP_5)
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sounds/zeppelin.mp3", true);
		else
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sounds/over_loop.mp3", true);
	}

}

const bool& ScreenManager::isOnMusic()
{
	return _isOnMusic;
}

const bool& ScreenManager::isOnSound()
{
	return _isOnSound;
}

void ScreenManager::turnOnOffMusic()
{
	if (_isOnMusic)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	else
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	
	this->writeSettingMusic(!_isOnMusic);
}

void ScreenManager::turnOnOffSound()
{
	if (_isOnSound)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

	this->writeSettingSound(!_isOnSound);
}

void ScreenManager::playSoundEffect(const char* path, bool loop)
{
	if (_isOnSound)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(path, loop);
}

void ScreenManager::playMusicMainMenu()
{
	if (_isOnSound)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	do
	{
		_random = cocos2d::random(0, 3);
	} while (_random == _back || _random == _back2);
	_back2 = _back;
	_back = _random;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		_listThemeSongs.at(_random).c_str(), true);
	if (!_isOnMusic)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	else
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

const int& ScreenManager::getTypeDevice()
{
	return _deviceType;
}

const float& ScreenManager::getMinimunPixel()
{
	return _minPixel;
}

const float& ScreenManager::getDelayTimeDevice()
{
	return _delayTime;
}

void ScreenManager::gotoSplash()
{
    _scene = SplashScene::createScene();
    Engine::Instance()->gotoScene(_scene);
}

void ScreenManager::gotoMainMenu()
{
	_scene = MainMenuScene::createScene();
	Engine::Instance()->replaceScene(_scene, 1);
}

void ScreenManager::gotoGameScene(const int& map)
{
	//int map2 = 0;


	_isWelcome3s = true;
	if (map != _mapNumber){
		SpriteFrameCache::getInstance()->removeSpriteFrames();
		MapProcessor::Instance()->InitMapProcessor(map);
	}
	else
		MapProcessor::Instance()->InitMapProcessor(map, true);
	_mapNumber = map;
	_scene = GameScene::createScene();
	Engine::Instance()->replaceScene(_scene, 1);
}

void ScreenManager::reloadGameScene()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	if (_mapNumber == MAP_5 || _mapNumber == MAP_9 || _mapNumber == MAP_11 || _mapNumber == MAP_12 || _mapNumber == MAP_13)
		_isWelcome3s = true;
	else
		_isWelcome3s = false;
	MapProcessor::Instance()->InitMapProcessor(_mapNumber, true);
	_scene = GameScene::createScene();
	Engine::Instance()->replaceScene(_scene, 1);

	//_scene = TransitGameScene::createScene();
	//Engine::Instance()->replaceScene(_scene, 0.1f);
}

void ScreenManager::gotoGameOver(const bool& isCompleted, const std::string& recentMap)
{
	_isCompleted = isCompleted;
	_recentMap = recentMap + "";
	_scene = GameOverScene::createScene();
	Engine::Instance()->replaceScene(_scene, 1);
}

void ScreenManager::cleanGameScene()
{

}

void ScreenManager::continueGame()
{
	_scene = GameScene::createScene();
	Engine::Instance()->replaceScene(_scene);
}