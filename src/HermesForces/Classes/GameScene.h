#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "define.h"
#include "Fighter/Fighter.h"
#include "SimpleAudioEngine.h"
#include "Missions/Land.h"
using namespace CocosDenshion;
#define OPACITY_BACKGROUND_BLACK 210
#define DELTA_TIME 200000
typedef unsigned long long timestamp_t;

//struct time_measure {
//	timestamp_t     start;
//	timestamp_t     stop;
//	double      result;
//};
//
//timestamp_t get_timestamp()
//{
//	struct timeval now;
//	gettimeofday(&now, NULL);
//	return now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
//}
//void update_time(struct time_measure *t) {
//	t->result = (t->stop - t->start) / 1000000.0L;
//	CCLOG("%f", t->result);
//}

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
#endif
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    void returnScoreScreen(const bool& _isCompleted);
	void touchPauseEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void touchResumeEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void touchReloadEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void touchHomeEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void touchOnOffMusicEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void touchOnOffSoundEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void stopGame();

	void setupDialogUI();
	const bool& checkDeltaTime();
	void onPause();

	void NoDesciptStart(float dt);
private:
	char _szTest[150];

    void SetPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };
    
    bool onContactBegin( cocos2d::PhysicsContact &contact );
    
    bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event );
    
    void StopFlying( float dt );
    void update( float dt );
    
    int getAngle2Sprite();

	void setupUI();

	void runTutorial();
	cocos2d::EventListenerPhysicsContact* _contactListener;
	cocos2d::EventListenerTouchOneByOne* _touchListener;

    cocos2d::PhysicsWorld *sceneWorld;
	int _itargetTotal, _iweaponTotal ;
	//cocos2d::__String *_weaponTotal, *_targetTotal;
	char _szWeaponTotalStr[5], _szTargetTotalStr[5];
    cocos2d::Label *_targetLabel ,*_weaponLabel/* ,*_testLabel*/;

	Sprite *_blackBg, *_boardNoti , *_desciptContent;
	cocos2d::ui::Button *_pauseButton,*_resumeBtt, *_reloadBtt, *_homeBtt, *_musicBtt, *_soundBtt;

	Sprite *Enemy1, *Enemy2, *Enemy3, *Enemy4, *Enemy5, *Enemy6;
	bool _isGameOver;
	bool _isEmptyWeapons;
	bool _isMapRandom3, _isMapRandom6;
	int _rs;

    //Land* _land;
    //Fighter *_fighter;
    
    void start();
    int _typeWeapon;
    int _testCallerUpdater;
    //cocos2d::__String* _currScore;

    bool _isSpecialMap;
	bool _isMap14, _isMap15;
    //bool _isUnlimitedGun;

	long long _lastTimeClicked, _currentTime;

	cocos2d::Size visibleSize;
	Vec2 origin;

	bool _clickPause;

	timeval _oldTimer, _currTimer;
	//time_measure _tm;

	int _disTime;
};

#endif // __GAME_SCENE_H__
