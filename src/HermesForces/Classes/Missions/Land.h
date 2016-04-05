#ifndef __LAND_MAP_H__
#define __LAND_MAP_H__

#include "define.h"
#include "../Targets/Target.h"
#include "Map.h"

//#define SPEED_MOVE_LAND 50
#define  SIZE_OUT_OF_SCREEN -200
#define SIZE_BTT_SPEC 80 //80 px
#define SIZE_AHALF_BTT_SPEC 40
class GameScene;
class Target;

struct MapNext
{
	cocos2d::Sprite *info;
	MapNext *next;
};

class Land
{
public:
    Land(cocos2d::Layer* layer ,const int& stage);
	~Land();
	static float LandPosY;
	static bool isMoving;
	static float deltaScale;
	static int TypeWeapon;
	static int BombCount;
	static float PixelPerFPSBoomFall;
	static cocos2d::Size* sizeBoom;
	static cocos2d::Vec2 vec2Boom;

	static int TimeDelayClickWeapon;
	static float PosRocket;
	static cocos2d::Layer* parentLayer;
	static cocos2d::Size visibleSize;
	static cocos2d::Vec2 origin;
	static float pixelOfLandMoving;
	static float pixelOfTargetMoving;
	static int OutOfLeftWidth;
	//static int OutOfRightWidth;
	static cocos2d::Point endPointFallingBomb;
	static bool isCalculateEndPoint;
	//static bool isClickSpecialBtt;
	static bool isNight;
	static cocos2d::Point FighterPos;
	static Land* thisPointer;

	void stopMoveLand();
	void addTargets(cocos2d::Layer* layer);
	void detectInScreen();
	void turnOnLight();
	//void turnOffLight();
	void turnOnHeatRadar();
	void turnOffHeatRadar();
	void turnOnPointRadar();
	void turnOffPointRadar();
	void turnOnBombRadar();
	void turnOffBombRadar();
	void setUpSpecialAndAddTarget(cocos2d::Layer* layer);

	void turnOnLightSpecialEvent(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void turnOnRadarPointSpecialEvent(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void turnOnRadarHeatSpecialEvent(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void turnOnRadarBombSpecialEvent(Ref* pSender, ui::Widget::TouchEventType eEventType);
	//void turnOnLight();

	void updateLandPositionToTheLeft();
	const bool& hitWeaponEnemies(const int& idWeapons);
	const int& destroyEnemies(const int& idTag);
	void moveToLeft();
	void startMoving();
	void setPositionSpecialBtt(const cocos2d::Point& p);
	const bool& isSpecialButtonExist();
	void getWeaponsAndTarget(int& weaponNum, int& targetNum);
	std::string& getPathMap(){ return startLandPath; }

	void enableSpecialButton();

	void preReleaseLand();

	void fadeInOutSpecBtt();
	void stopFadeInoutSpecBtt();
private:
	//const bool& checkDeltaTime();

	std::string nextMap, startLandPath;
	//cocos2d::Sprite* _land;
	cocos2d::Sprite* _backgroundSpecial;
	cocos2d::Sprite* _maskButtonSpec;
	//cocos2d::Sprite* _objSpecial;
	//cocos2d::Sprite* _bttSpecial;
	cocos2d::ui::Button* _SpecialButton;
	float _posHeight;

	int _targetCount;
	cocos2d::Sprite *_land_start, *_land_next_1, *_land_next_2;
	cocos2d::Sprite *_land_next_current, *_land_next_current_rest;

	//MapNext* _mapNext;
	//Target* _listTargets[50];
	std::vector<Target*> _listTargets;
	GameScene* parent;

	int _typeBomb;
	MapInfo* currentMap;
	int _delayTimeClickSpecial;
	int _mapStage;

	cocos2d::Layer* _landAndEnemiesLayer;

	float _deltaMovingLand,_deltaMovingTargets,k;
	int leftBit;
	float _distanceOfEndStartMapPieces, _distanceOfEndNextMapPieces;
	int _pointXToDieStartMap, _pointXToDieNextMap;

	int _lastTime;
	int _isGoodTarget , /*_indexInTarget, */_indexOutTarget;
	float _pixelTargetMoving , _pixelLandMoving;

	bool _isNextLandAvaiable , _isAllNextLandAvaiable , _isEndOfStartLand;
	int _posStartLand,_posNextLand;
	cocos2d::Point _xyNextMap;

	int _deltaDisStart,_deltaDisNext;
	bool _isNext1;

	timeval _oldTimer, _currTimer;

	bool _isClickSpecialBtt;

	// 1 ms -> 0.5px => 1s ->50px 
};

#endif // land
