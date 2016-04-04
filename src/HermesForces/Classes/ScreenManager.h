//
//  ScreenManager.h
//  BombTerrorist
//
//  Created by Quan Rock on 1/26/16.
//
//

#ifndef ScreenManager_h
#define ScreenManager_h
#include "define.h"
#include "Engine.h"
#include "SplashScene.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "Missions/Land.h"
#include "Fighter/Fighter.h"

#define SIZE_TABLET 1680
#define SIZE_MINI_TABLET 1390

#define IS_TABLET 3
#define IS_MINI_TABLET 2
#define IS_PHONE 1

#define TIME_DELAY_MINI_TABLET 0.8f
#define TIME_DELAY_TABLET 0.7f

class ScreenManager
{
public:
    static ScreenManager* Instance()
    {
        if(_instance == NULL)
        {
            _instance = new ScreenManager();
        }
        return _instance;
    }
    
    void initInstance();
    void startApplication(const bool& isGoToSplash = false);
    void gotoSplash();
    void gotoMainMenu();
    void gotoGameScene(const int& map);
	void reloadGameScene();
    void gotoGameOver(const bool& isCompleted, const std::string& recentMap);
    void cleanGameScene();
    void continueGame();
    const int& CurrentMap();
	const float& getkScale();
	void scaleScreenFull(cocos2d::Sprite* bg);
	//void getRecentInfoGameOver(bool& isCompleted, std::string& recentMap);
	std::string& getRecentMapPath() { return _recentMap; }
	const bool& getStatusMapOver(){ return _isCompleted; }
	const bool& IsWelcome3s(){ return _isWelcome3s; }
	void writeResult();
	const int& getMaxMap();
	void writeSettingMusic(const bool& isOn);
	void writeSettingSound(const bool& isOn);
	void getMusicStatus();
	void getSoundStatus();
	void playMusicGameScene();
	void playMusicGameOverScene();

	const bool& isOnMusic();
	const bool& isOnSound();

	void turnOnOffMusic();
	void turnOnOffSound();
	void playSoundEffect(const char* path,bool loop = false);
	void playMusicMainMenu();

	const int& getTypeDevice();

	const float& getMinimunPixel();

	const float& getDelayTimeDevice();

	void setUpNewLand(cocos2d::Layer *layer);
	void setUpNewFighter(cocos2d::Layer *layer, const cocos2d::Point& leftAlignPos, const int& specialMap = 0);

	Land* GetLand();
	Fighter* GetFighter();

	void releaseGameScene();
private:
	float _delayTime;
		int _deviceType;
		bool _isOnMusic;
		bool _isOnSound;

		bool _isCompleted;
		bool _isWelcome3s;
		//bool _isAvaiableMemory;
		std::string _recentMap;
        static    ScreenManager*    _instance;
        ScreenManager();
        int _mapNumber;
        Scene* _scene;
		float _khBackground, _kwBackground;
		std::vector<std::string> _listThemeSongs;
		int _back/*_back2, _back , _random*/;
		float _minPixel;

		Land* CurrentLand;
		Fighter* CurrentFighter;
};
#endif /* ScreenManager_h */
