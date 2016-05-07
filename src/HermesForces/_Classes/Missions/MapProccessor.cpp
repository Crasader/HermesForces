#include "MapProccessor.h"
#include "../ScreenManager.h"
#define FIRE_BOMB_LONDON_SIZE_WIDTH 20
#define FIRE_BOMB_LONDON_SIZE_HEIGHT 20

#define BOMB_SIZE_WIDTH 20
#define BOMB_SIZE_HEIGHT 20

#define BULLET_SIZE_HEIGHT 5
#define BULLET_SIZE_WIDTH 5

#define BOMB_SQUAD_WIDTH 20
#define BOMB_SQUAD_HEIGHT 20

#define SPECIAL_FORCE_WIDTH 20
#define SPECIAL_FORCE_HEIGHT 40

#define MARINE_BOMB_WIDTH 30
#define MARINE_BOMB_HEIGHT 40

int rand_3_15_1[] = {2,5,14}; // >= 2 <= 17
int rand_3_15_2[] = {4,11,16}; 
int rand_3_15_3[] = {7,11,12}; 
int rand_3_15_4[] = {3,9,10}; 
int rand_3_15_5[] = {6,13,15}; 

int rand_3_30_1[] = {2,20,27}; // >= 2 <= 32
int rand_3_30_2[] = {4,11,23}; 
int rand_3_30_3[] = {11,19,28}; 
int rand_3_30_4[] = {3,16,25}; 
int rand_3_30_5[] = {6,17,29};
int rand_3_30_6[]  = {19,8,23}; // >= 2 <= 32
int rand_3_30_7[]  = {28,13,18}; 
int rand_3_30_8[]  = {5,10,24}; 
int rand_3_30_9[]  = {15,30,21}; 
int rand_3_30_10[] = {22,14,26}; 

int rand_6_30_1[] = {2,20,27,22,14,26}; // >= 2 <= 32
int rand_6_30_2[] = {15,30,21,4,11,23}; 
int rand_6_30_3[] = {11,19,28,5,10,24}; 
int rand_6_30_4[] = {28,13,18,3,16,25}; 
int rand_6_30_5[] = {6,17,29,19,8,23};
int rand_6_30_6[]  = {19,8,23,2,20,27}; // >= 2 <= 32
int rand_6_30_7[]  = {4,11,23,28,13,18}; 
int rand_6_30_8[]  = {5,10,24,6,17,29}; 
int rand_6_30_9[]  = {3,16,25,15,30,21}; 
int rand_6_30_10[] = {22,14,26,6,17,29}; 


//comment
int map_15_1[] = {8,1,9,2,7,10,4,11,13,15,3,6,14,12,5};
int map_15_2[] = {4,6,3,13,14,5,8,2,12,15,1,7,11,9,10};
int map_15_3[] = {2,8,7,9,1,11,10,6,13,12,3,15,14,4,5};
int map_15_4[] = {6,7,1,8,4,11,3,10,9,5,15,13,2,12,14};
int map_15_5[] = {10,6,11,5,7,4,9,3,8,15,13,1,14,12,2};

int map_30_1[] = {8,1,9,2,7,10,4,11,13,15,3,6,14,12,5,16,20,21,26,25,18,19,27,17,28,30,22,24,29,23};
int map_30_2[] = {4,6,3,13,14,5,8,2,12,15,1,7,11,9,10,25,30,28,26,16,24,19,27,20,17,22,29,18,23,21};
int map_30_3[] = {2,8,7,9,1,11,10,6,13,12,3,15,14,4,5,21,18,22,23,17,25,20,19,28,29,16,24,27,30,26};
int map_30_4[] = {6,7,1,8,4,11,3,10,9,5,15,13,2,12,14,21,24,22,25,26,23,20,30,28,27,29,17,18,19,16};
int map_30_5[] = {10,6,11,5,7,4,9,3,8,15,13,1,14,12,2,20,22,21,19,23,18,30,26,25,17,29,16,24,28,27};
int map_30_6[]  = {16,20,21,26,25,18,19,27,17,28,30,22,24,29,23,8,1,9,2,7,11,4,10,13,15,3,6,14,12,5};
int map_30_7[]  = {28,26,16,24,19,27,20,17,22,29,18,23,21,4,6,3,13,14,5,8,2,12,15,1,7,11,9,10,25,30};
int map_30_8[]  = {22,23,17,25,20,19,28,29,16,24,27,30,26,2,8,7,9,1,11,10,6,13,12,3,15,14,4,5,21,18};
int map_30_9[]  = {24,22,25,26,23,20,30,28,27,29,17,18,19,16,6,7,1,8,4,11,3,10,9,5,15,13,2,12,14,21};
int map_30_10[] = {22,21,19,23,18,30,26,25,17,29,16,24,28,27,10,6,11,5,7,4,9,3,8,15,13,1,14,12,2,20};

int* rand_3_15[] = {rand_3_15_1,rand_3_15_2,rand_3_15_3,rand_3_15_4,rand_3_15_5};
int* rand_3_30[] = {rand_3_30_1,rand_3_30_2,rand_3_30_3,rand_3_30_4,rand_3_30_5,rand_3_30_6,rand_3_30_7,rand_3_30_8,rand_3_30_9,rand_3_30_10};
int* rand_6_30[] = {rand_6_30_1,rand_6_30_2,rand_6_30_3,rand_6_30_4,rand_6_30_5,rand_6_30_6,rand_6_30_7,rand_6_30_8,rand_6_30_9,rand_6_30_10};

int* map_15[] = {map_15_1,map_15_2,map_15_3,map_15_4,map_15_5};
int* map_30[] = {map_30_1,map_30_2,map_30_3,map_30_4,map_30_5,map_30_6,map_30_7,map_30_8,map_30_9,map_30_10};

int rand_bomb_5_7_1[] = { 4,8,12,16,20}; // total 5/20
int rand_bomb_5_7_2[] = { 3,7,12,16,19};
int rand_bomb_5_7_3[] = { 2,6,10,14,18};
int rand_bomb_5_7_4[] = { 5,8,13,17,20};

int* map_5_in_20[] = {rand_bomb_5_7_1,rand_bomb_5_7_2,rand_bomb_5_7_3,rand_bomb_5_7_4};
void MapProcessor::InitMapProcessor(const int& MapNumber)
{
	_isTrainMap = false;
	//_isCached = isCached;
	_lEnemiesTexture.clear();
	//if (isCached)
	//	return;
	
	//SpriteFrameCache::getInstance()->removeSpriteFrames();

	_mapNumber = MapNumber;
	_animTargetFrames.clear();
	_animFighterFrames.clear();
	_currentEnemiesPath[0] = 0;
	_weaponFrameName = "";

	SpriteFrameCache::getInstance()->removeSpriteFrames();
	SpriteFrameCache::getInstance()->destroyInstance();
	SpriteFrameCache::getInstance()->init();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/Weapons/fighter/sprites.plist"
		, "mini/army/Weapons/fighter/sprites.png");
	_hitLand = "";
	_targetDie = "";
	_bombFall = "";
	_isVisibleMap = false;
	if (MapNumber == MAP_1){
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/map_iraq/sprites.plist"
				, "mini/army/plist/map_iraq/sprites.png");
		

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			_hitLand = "Sounds/bombexp.ogg";
			_targetDie = "Sounds/ahcut.ogg";
			_bombFall = "Sounds/ziuziu.ogg";
#else
			_hitLand = "Sounds/bombexp.mp3";
			_targetDie = "Sounds/ahcut.mp3";
			_bombFall = "Sounds/ziuziu.mp3";
#endif

			//CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.8);
			//// 0
			Vector<SpriteFrame*> frames_1;
			//frames_1.reserve(3);
			frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_1.png"));
			frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_2.png"));
			frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_3.png"));
			frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_4.png"));
			frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_5.png"));
			_animTargetFrames.push_back(frames_1);

			//// 1
			Vector<SpriteFrame*> frames_2;
			//frames_2.reserve(3);
			frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_gun_1.png"));
			frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_gun_2.png"));
			frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_gun_3.png"));
			frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_gun_4.png"));
			frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_gun_5.png"));
			_animTargetFrames.push_back(frames_2);

			//// 3 => die
			Vector<SpriteFrame*> frames_3;
			frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_bomb_0.png"));
			frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_bomb_1.png"));
			frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_bomb_2.png"));
			frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_bomb_3.png"));
			frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_iraq_bomb_4.png"));
			_animTargetFrames.push_back(frames_3);
		//this->addEnemies("is_iraq_1.png");
		//this->addEnemies("is_iraq_gun_1.png");
	}
	else if (MapNumber == MAP_2){
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/map_syria/sprites.plist"
			, "mini/army/plist/map_syria/sprites.png");



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_hitLand = "Sounds/bombexp.ogg";
		_targetDie = "Sounds/ahcut.ogg";
		_bombFall = "Sounds/ziuziu.ogg";
#else
		_hitLand = "Sounds/bombexp.mp3";
		_targetDie = "Sounds/ahcut.mp3";
		_bombFall = "Sounds/ziuziu.mp3";
#endif

		//// 0
		Vector<SpriteFrame*> frames_1;
		//frames_1.reserve(3);
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("oil_carrier_0.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("oil_carrier_1.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("oil_carrier_2.png"));
		_animTargetFrames.push_back(frames_1);

		//// 3 => die
		Vector<SpriteFrame*> frames_2;
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("oil_carrier_bomb_1.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("oil_carrier_bomb_2.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("oil_carrier_bomb_3.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("oil_carrier_bomb_4.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("oil_carrier_bomb_5.png"));
		_animTargetFrames.push_back(frames_2);
		//this->addEnemies("oil_carrier_0.png");
	}
	else if (MapNumber == MAP_3){
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/is_soldier/sprites.plist"
			, "mini/army/plist/is_soldier/sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/burn_body/sprites.plist"
			, "mini/army/plist/burn_body/sprites.png");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_hitLand = "Sounds/bombexp.ogg";
		_targetDie = "Sounds/ahcut.ogg";
		_bombFall = "Sounds/ziuziu.ogg";
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/machinegun.ogg");
#else
		_hitLand = "Sounds/bombexp.mp3";
		_targetDie = "Sounds/ahcut.mp3";
		_bombFall = "Sounds/ziuziu.mp3";
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/machinegun.mp3");
#endif

		
		
		

		//// 0
		Vector<SpriteFrame*> frames_1;
		frames_1.reserve(4);
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_fire_1.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_fire_2.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_fire_3.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_fire_4.png"));
		_animTargetFrames.push_back(frames_1);

		//// 1
		Vector<SpriteFrame*> frames_2;
		frames_2.reserve(4);
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_knife_0.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_knife_1.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_knife_2.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_knife_3.png"));
		_animTargetFrames.push_back(frames_2);

		//// 2 
		Vector<SpriteFrame*> frames_3;
		frames_3.reserve(5);
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_gun_1.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_gun_2.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_gun_3.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_gun_4.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_gun_5.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_gun_1.png"));
		_animTargetFrames.push_back(frames_3);

		//// 3 => die
		Vector<SpriteFrame*> frames_4;
		frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_body_1.png"));
		frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_body_2.png"));
		frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_body_3.png"));
		frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_body_4.png"));
		frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_body_5.png"));
		_animTargetFrames.push_back(frames_4);

		//this->addEnemies("is_fire_1.png");
		//this->addEnemies("is_knife_0.png");
		//this->addEnemies("is_shoot_gun_1.png");
	}
	else if (MapNumber == MAP_4){
		// egypt !

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_hitLand = "Sounds/bombexp.ogg";
		_targetDie = "Sounds/ahcut.ogg";
		_bombFall = "Sounds/ziuziu.ogg";
#else
		_hitLand = "Sounds/bombexp.mp3";
		_targetDie = "Sounds/ahcut.mp3";
		_bombFall = "Sounds/ziuziu.mp3";
#endif
		//map_point_radar
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/map_point_radar/sprites.plist"
			, "mini/army/plist/map_point_radar/sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/car_burn/sprites.plist"
			, "mini/army/plist/car_burn/sprites.png");
		Vector<SpriteFrame*> frames_1;
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_burn_0.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_burn_1.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_burn_2.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_burn_3.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_burn_4.png"));
		_animTargetFrames.push_back(frames_1);

		_isVisibleMap = true;


	}
	else if (MapNumber == MAP_5){
		// china
		sprintf(_currentEnemiesPath, "car_");
		_randEnemies = cocos2d::random(0, 9);
		_randMap = cocos2d::random(0, 9);
		_targetRandomList = map_30[_randMap];
		_enemiesRandList = rand_3_30[_randEnemies];
		this->addCarAnimation();



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_hitLand = "Sounds/bombexp.ogg";
		_targetDie = "Sounds/ahcut.ogg";
		_bombFall = "Sounds/ziuziu.ogg";
#else
		_hitLand = "Sounds/bombexp.mp3";
		_targetDie = "Sounds/ahcut.mp3";
		_bombFall = "Sounds/ziuziu.mp3";
#endif

	}
	else if (MapNumber == MAP_6 || MapNumber == MAP_12){
		// london - isarel
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/burn_body/sprites.plist"
			, "mini/army/plist/burn_body/sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/heat_body/sprites.plist"
			, "mini/army/plist/heat_body/sprites.png");
		Vector<SpriteFrame*> frames_1;
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_body_1.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_body_2.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_body_3.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_body_4.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_body_5.png"));
		_animTargetFrames.push_back(frames_1);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_hitLand = "Sounds/fire.ogg";
		_targetDie = "Sounds/ahcut.ogg";
		_bombFall = "Sounds/fire.ogg";
#else
		_hitLand = "Sounds/fire.mp3";
		_targetDie = "Sounds/ahcut.mp3";
		_bombFall = "Sounds/fire.mp3";
#endif
		_isVisibleMap = true;
	}
	else if (MapNumber == MAP_7){
		//berlin
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_hitLand = "Sounds/hitland.ogg";
		_targetDie = "Sounds/targetdestroy.ogg";//siryessir.mp3
		_bombFall = "Sounds/siryessir.ogg";
#else
		_hitLand = "Sounds/hitland.mp3";
		_targetDie = "Sounds/targetdestroy.mp3";//siryessir.mp3
		_bombFall = "Sounds/siryessir.mp3";
#endif


		_isVisibleMap = true;
	}
	else if (MapNumber == MAP_8){
		// usa

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_hitLand = "Sounds/bombexp.ogg";
		_targetDie = "Sounds/ahcut.ogg";
		_bombFall = "Sounds/ziuziu.ogg";
#else
		_hitLand = "Sounds/bombexp.mp3";
		_targetDie = "Sounds/ahcut.mp3";
		_bombFall = "Sounds/ziuziu.mp3";
#endif

		sprintf(_currentEnemiesPath, "car_");
		_randEnemies = cocos2d::random(0, 9);
		_randMap = cocos2d::random(0, 9);
		_targetRandomList = map_30[_randMap];
		_enemiesRandList = rand_6_30[_randEnemies];
		this->addCarAnimation();

	}
	else if (MapNumber == MAP_9)
	{

		// india
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/map_point_radar/sprites.plist"
			, "mini/army/plist/map_point_radar/sprites.png");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_hitLand = "Sounds/hitland.ogg";
		_targetDie = "Sounds/targetdestroy.ogg";//siryessir.mp3
		_bombFall = "Sounds/siryessir.ogg";
#else
		_hitLand = "Sounds/hitland.mp3";
		_targetDie = "Sounds/targetdestroy.mp3";//siryessir.mp3
		_bombFall = "Sounds/siryessir.mp3";
#endif

		_isVisibleMap = true;
	}
	else if (MapNumber == MAP_10)
	{
		// paris

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_hitLand = "Sounds/fire.ogg";
		_targetDie = "Sounds/ahcut.ogg";//siryessir.mp3
		_bombFall = "Sounds/fire.ogg";
#else
		_hitLand = "Sounds/fire.mp3";
		_targetDie = "Sounds/ahcut.mp3";//siryessir.mp3
		_bombFall = "Sounds/fire.mp3";
#endif

		_randEnemies = cocos2d::random(0, 3);
		_enemiesRandList = map_5_in_20[_randEnemies];

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/map_paris/sprites.plist"
			, "mini/army/plist/map_paris/sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/map_point_radar/sprites.plist"
			, "mini/army/plist/map_point_radar/sprites.png");
		Vector<SpriteFrame*> frames_1;
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("paris_fire_hit_1.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("paris_fire_hit_2.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("paris_fire_hit_3.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("paris_fire_hit_4.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("paris_fire_hit_5.png"));
		_animTargetFrames.push_back(frames_1);

		Vector<SpriteFrame*> frames_2;
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("paris_fire_no_hit_1.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("paris_fire_no_hit_2.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("paris_fire_no_hit_3.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("paris_fire_no_hit_4.png"));
		_animTargetFrames.push_back(frames_2);

		//this->addEnemies("drain_cover.png");
	}
	else if (MapNumber == MAP_11 || MapNumber == MAP_13){
		// jakarta - iran

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_hitLand = "Sounds/hitland.ogg";
		_targetDie = "Sounds/targetdestroy.ogg";//siryessir.mp3
		_bombFall = "Sounds/siryessir.ogg";
#else
		_hitLand = "Sounds/hitland.mp3";
		_targetDie = "Sounds/targetdestroy.mp3";//siryessir.mp3
		_bombFall = "Sounds/siryessir.mp3";
#endif

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/map_train/sprites.plist"
			, "mini/army/plist/map_train/sprites.png");

		sprintf(_currentEnemiesPath, "number_box_");
		_randEnemies = cocos2d::random(0, 9);
		_randMap = cocos2d::random(0, 9);
		_targetRandomList = map_30[_randMap];
		_enemiesRandList = rand_3_30[_randEnemies];
		_isTrainMap = true;
	}
	else if (MapNumber == MAP_14){
		// russia 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_hitLand = "Sounds/waterbomb.ogg";
		_targetDie = "Sounds/targetdestroy.ogg";
		_bombFall = "Sounds/ziuziu.ogg";
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/antirocket.ogg");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/fighter_exp.ogg");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/rocket_launch.ogg");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/waterbomb.ogg");
#else
		_hitLand = "Sounds/waterbomb.mp3";
		_targetDie = "Sounds/targetdestroy.mp3";
		_bombFall = "Sounds/ziuziu.mp3";
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/antirocket.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/fighter_exp.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/rocket_launch.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/waterbomb.mp3");
#endif


		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/map_russia/sprites.plist"
			, "mini/army/plist/map_russia/sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/rocket/sprites.plist"
			, "mini/army/plist/rocket/sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/Weapons/fighter/apache_hit/sprites.plist"
			, "mini/army/Weapons/fighter/apache_hit/sprites.png");
		Vector<SpriteFrame*> frames_1;
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("water_4.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("water_3.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("water_2.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("water_1.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("water_2.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("water_3.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("water_4.png"));
		_animTargetFrames.push_back(frames_1);

		Vector<SpriteFrame*> frames_2;
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("sub_mar_hit_0.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("sub_mar_hit_1.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("sub_mar_hit_2.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("sub_mar_hit_3.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("sub_mar_hit_4.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("sub_mar_hit_5.png"));
		_animTargetFrames.push_back(frames_2);

		//// 2 => rocket hit
		Vector<SpriteFrame*> frames_3;
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("rocket_hit_1.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("rocket_hit_2.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("rocket_hit_3.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("rocket_hit_4.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("rocket_hit_5.png"));
		_animTargetFrames.push_back(frames_3);

	}
	else if (MapNumber == MAP_15){
		// afghanistan
		
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_targetDie = "Sounds/ahcut.ogg";
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/rocketexp.ogg");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/gun.ogg");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/machinegun.ogg");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/fighter_exp.ogg");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/rocket_launch.ogg");
#else
		_targetDie = "Sounds/ahcut.mp3";
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/rocketexp.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/gun.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/machinegun.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/fighter_exp.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/rocket_launch.mp3");
#endif

		//rocket_launch


		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/is_soldier/sprites.plist"
			, "mini/army/plist/is_soldier/sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/hit_body/sprites.plist"
			, "mini/army/plist/hit_body/sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/rocket/sprites.plist"
			, "mini/army/plist/rocket/sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/Weapons/fighter/apache_hit/sprites.plist"
			, "mini/army/Weapons/fighter/apache_hit/sprites.png");
		//// 0
		Vector<SpriteFrame*> frames_1;
		frames_1.reserve(4);
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_fire_1.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_fire_2.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_fire_3.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_fire_4.png"));
		_animTargetFrames.push_back(frames_1);

		//// 1 
		Vector<SpriteFrame*> frames_2;
		frames_2.reserve(5);
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_gun_1.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_gun_2.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_gun_3.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_gun_4.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_gun_5.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_gun_1.png"));
		_animTargetFrames.push_back(frames_2);

		//// 2 
		Vector<SpriteFrame*> frames_3;
		frames_2.reserve(5);
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_air_3.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_air_2.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_air_4.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_air_5.png"));
		frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("is_shoot_air_1.png"));
		_animTargetFrames.push_back(frames_3);

		//// 3 => die
		Vector<SpriteFrame*> frames_4;
		frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("blood_1.png"));
		frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("blood_2.png"));
		frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("blood_3.png"));
		frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("blood_4.png"));
		frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("blood_5.png"));
		_animTargetFrames.push_back(frames_4);

		//// 4 => rocket hit
		Vector<SpriteFrame*> frames_5;
		frames_5.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("rocket_hit_1.png"));
		frames_5.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("rocket_hit_2.png"));
		frames_5.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("rocket_hit_3.png"));
		frames_5.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("rocket_hit_4.png"));
		frames_5.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("rocket_hit_5.png"));
		_animTargetFrames.push_back(frames_5);
	}
	

	if (!_hitLand.empty())
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(_hitLand.c_str());
	if (!_targetDie.empty())
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(_targetDie.c_str());
	if (!_bombFall.empty())
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(_bombFall.c_str());

	_currPosTargets = 0;	
	// get enemies to show
}

std::vector<std::string> MapProcessor::getListEnemies()
{
	return _lEnemiesTexture;
}

//MapProcessor::MapProcessor()
//{
//
//}

//void MapProcessor::addEnemies(std::string path)
//{
//	_lEnemiesTexture.push_back(path);
//}

int MapProcessor::getSpecialNumberFile()
{
	return 0;
}

Vector<SpriteFrame*> MapProcessor::getTargetAnimeFramesByIndex(const int& index)
{
	//Animation* animation = (Animation*)(_targetAnimes.at(index))->getAnimation();
	//Animate* animate = Animate::create(animation);
	//target->runAction(RepeatForever::create(animate));
	//_animFrames.at(index)
	return _animTargetFrames.at(index);
}

Vector<SpriteFrame*> MapProcessor::getFighterItemAnimeFrames(const int& index)
{
	return _animFighterFrames.at(index);
}

void MapProcessor::doFighterItems(const int& typeWeapon, cocos2d::Size* &sizeBoom, cocos2d::Vec2 &vec2Boom, const float& deltaScale,
	int& TimeDelayClickWeapon/*, int& endPointBomb, const int& heightLandY*/)
{
	//if (_currentWeapon == typeWeapon)
	//	return;
	//_currentWeapon = typeWeapon;
	
	//if (_isCached)
	//	return;

	Vector<SpriteFrame*> frames_1; // unusual sometime
	Vector<SpriteFrame*> frames_2;
	Sprite* sizeItems;
	switch (typeWeapon)
	{
	case ITEM_BOMB_B52:
		_weaponFrameName = "mini/scene/weapons/b52.png";
	case ITEM_BOMB_CHINA:
		// add bomb_b52.png army\Weapons\b52
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/Weapons/bomb/sprites.plist"
			, "mini/army/Weapons/bomb/sprites.png");
		
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("b52_ex_1.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("b52_ex_2.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("b52_ex_3.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("b52_ex_4.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("b52_ex_5.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("b52_ex_6.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("b52_ex_7.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("b52_ex_8.png"));
		_animFighterFrames.push_back(frames_1);

		sizeItems = Sprite::createWithSpriteFrameName("bom_china.png");
		sizeBoom = new Size(sizeItems->getContentSize().width /* * deltaScale*/, sizeItems->getContentSize().height * 0.95/* * deltaScale*/);
		vec2Boom = Vec2(0, (-0.42) * sizeBoom->height);
		if (_weaponFrameName.empty())
			_weaponFrameName = "mini/scene/weapons/china.png";

		break;
	//case ITEM_BULLET:
	//	sizeBoom = new Size(BULLET_SIZE_WIDTH * deltaScale, BULLET_SIZE_HEIGHT* deltaScale);
	//	PixelPerFPSBoomFall = 11;
	//	TimeDelayClickWeapon = 100;
	//	break;
	case ITEM_BOMB_FIRE:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/Weapons/fire_bomb/sprites.plist"
			, "mini/army/Weapons/fire_bomb/sprites.png");

		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("hitfire_1.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("hitfire_2.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("hitfire_3.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("hitfire_4.png"));
		_animFighterFrames.push_back(frames_1);
		sizeItems = Sprite::createWithSpriteFrameName("fire_bomb_ori.png");
		sizeBoom = new Size(sizeItems->getContentSize().width, sizeItems->getContentSize().height * 0.95);
		vec2Boom = Vec2(0, (-0.45) * sizeBoom->height);

		_weaponFrameName = "mini/scene/weapons/fire.png";
		break;
	case ITEM_BOMB_SQUAD:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/Weapons/bomb_squad/sprites.plist"
			, "mini/army/Weapons/bomb_squad/sprites.png");

		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb_squad_hit.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb_squad_hit_2.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb_squad_hit_bomb.png"));
		_animFighterFrames.push_back(frames_1);

		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb_squad_hit.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb_squad_hit_2.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb_squad_hit_nothing.png"));
		_animFighterFrames.push_back(frames_2);

		sizeItems = Sprite::createWithSpriteFrameName("bomb_squad_jump.png");
		sizeBoom = new Size(sizeItems->getContentSize().width, sizeItems->getContentSize().height);
		vec2Boom = Vec2(0, (-0.45) * sizeBoom->height);

		_weaponFrameName = "mini/scene/weapons/squad.png";
		break;
	case ITEM_TRAIN_SPECIAL_FORCE:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/Weapons/train_special_force/sprites.plist"
			, "mini/army/Weapons/train_special_force/sprites.png");

		//frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("swat_indo_hit_pre.png"));
		//_animFighterFrames.push_back(frames_1);

		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("swat_indo_hit_pre.png"));
		frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("swat_indo_hit_pre_nohit.png"));
		_animFighterFrames.push_back(frames_1);

		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("swat_indo_hit_shoot_1.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("swat_indo_hit_shoot_2.png"));
		frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("swat_indo_hit_shoot_1.png"));
		_animFighterFrames.push_back(frames_2);

		sizeItems = Sprite::createWithSpriteFrameName("swat_indo_jump.png");
		sizeBoom = new Size(sizeItems->getContentSize().width, sizeItems->getContentSize().height);
		vec2Boom = Vec2(0, (-0.45) * sizeBoom->height);

		_weaponFrameName = "mini/scene/weapons/indo.png";
		break;
	case ITEM_MARINE_BOMB:
		sizeBoom = new Size(MARINE_BOMB_WIDTH * deltaScale, MARINE_BOMB_HEIGHT * deltaScale);
		vec2Boom = Vec2(0, (-0.45) * sizeBoom->height);

		_weaponFrameName = "mini/scene/weapons/mar.png";
		break;	
	case ITEM_INDIA_SPECIAL_FORCE:
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/Weapons/india_swat/sprites.plist"
				, "mini/army/Weapons/india_swat/sprites.png");
			Vector<SpriteFrame*> frames_1;
			frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("india_police_hit_1.png"));
			frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("india_police_hit_2.png"));
			frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("india_police_hit_3.png"));
			frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("india_police_hit_2.png"));
			frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("india_police_hit_4.png"));
			_animFighterFrames.push_back(frames_1);

			Vector<SpriteFrame*> frames_2;
			frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("india_police_no_hit_1.png"));
			frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("india_police_no_hit_2.png"));
			_animFighterFrames.push_back(frames_2);
			//_animFighterFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("india_police_no_hit_2.png"));

			sizeItems = Sprite::createWithSpriteFrameName("poli_jum.png");
			sizeBoom = new Size(sizeItems->getContentSize().width, sizeItems->getContentSize().height);
			vec2Boom = Vec2(0, (-0.45) * sizeBoom->height);
			_weaponFrameName = "mini/scene/weapons/india.png";
			break;
	}
}

void MapProcessor::addCarAnimation()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/map_car/sprites.plist"
		, "mini/army/plist/map_car/sprites.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mini/army/plist/car_burn/sprites.plist"
		, "mini/army/plist/car_burn/sprites.png");

	Vector<SpriteFrame*> frames_1;
	frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_1.png"));
	frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_1_2.png"));
	frames_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_1_3.png"));

	Vector<SpriteFrame*> frames_2;
	frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_2.png"));
	frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_2_2.png"));
	frames_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_2_3.png"));

	Vector<SpriteFrame*> frames_3;
	frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_3.png"));
	frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_3_2.png"));
	frames_3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_3_3.png"));

	Vector<SpriteFrame*> frames_4;
	frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_4.png"));
	frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_4_2.png"));
	frames_4.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_4_3.png"));

	Vector<SpriteFrame*> frames_5;
	frames_5.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_5.png"));
	frames_5.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_5_2.png"));
	frames_5.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_5_3.png"));

	Vector<SpriteFrame*> frames_6;
	frames_6.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_6.png"));
	frames_6.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_6_2.png"));
	frames_6.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_6_3.png"));

	Vector<SpriteFrame*> frames_7;
	frames_7.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_7.png"));
	frames_7.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_7_2.png"));
	frames_7.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_7_3.png"));

	Vector<SpriteFrame*> frames_8;
	frames_8.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_8.png"));
	frames_8.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_8_2.png"));
	frames_8.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_8_3.png"));

	Vector<SpriteFrame*> frames_9;
	frames_9.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_9.png"));
	frames_9.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_9_2.png"));
	frames_9.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_9_3.png"));

	Vector<SpriteFrame*> frames_10;
	frames_10.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_10.png"));
	frames_10.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_10_2.png"));
	frames_10.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_10_3.png"));

	Vector<SpriteFrame*> frames_11;
	frames_11.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_11.png"));
	frames_11.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_11_2.png"));
	frames_11.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_11_3.png"));

	Vector<SpriteFrame*> frames_12;
	frames_12.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_12.png"));
	frames_12.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_12_2.png"));
	frames_12.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_12_3.png"));

	Vector<SpriteFrame*> frames_13;
	frames_13.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_13.png"));
	frames_13.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_13_2.png"));
	frames_13.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_13_3.png"));

	Vector<SpriteFrame*> frames_14;
	frames_14.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_14.png"));
	frames_14.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_14_2.png"));
	frames_14.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_14_3.png"));

	Vector<SpriteFrame*> frames_15;
	frames_15.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_15.png"));
	frames_15.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_15_2.png"));
	frames_15.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_15_3.png"));

	Vector<SpriteFrame*> frames_16;
	frames_16.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_16.png"));
	frames_16.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_16_2.png"));
	frames_16.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_16_3.png"));

	Vector<SpriteFrame*> frames_17;
	frames_17.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_17.png"));
	frames_17.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_17_2.png"));
	frames_17.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_17_3.png"));

	Vector<SpriteFrame*> frames_18;
	frames_18.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_18.png"));
	frames_18.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_18_2.png"));
	frames_18.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_18_3.png"));

	Vector<SpriteFrame*> frames_19;
	frames_19.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_19.png"));
	frames_19.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_19_2.png"));
	frames_19.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_19_3.png"));

	Vector<SpriteFrame*> frames_20;
	frames_20.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_20.png"));
	frames_20.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_20_2.png"));
	frames_20.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_20_3.png"));

	Vector<SpriteFrame*> frames_21;
	frames_21.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_21.png"));
	frames_21.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_21_2.png"));
	frames_21.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_21_3.png"));

	Vector<SpriteFrame*> frames_22;
	frames_22.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_22.png"));
	frames_22.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_22_2.png"));
	frames_22.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_22_3.png"));

	Vector<SpriteFrame*> frames_23;
	frames_23.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_23.png"));
	frames_23.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_23_2.png"));
	frames_23.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_23_3.png"));

	Vector<SpriteFrame*> frames_24;
	frames_24.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_24.png"));
	frames_24.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_24_2.png"));
	frames_24.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_24_3.png"));

	Vector<SpriteFrame*> frames_25;
	frames_25.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_25.png"));
	frames_25.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_25_2.png"));
	frames_25.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_25_3.png"));

	Vector<SpriteFrame*> frames_26;
	frames_26.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_26.png"));
	frames_26.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_26_2.png"));
	frames_26.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_26_3.png"));

	Vector<SpriteFrame*> frames_27;
	frames_27.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_27.png"));
	frames_27.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_27_2.png"));
	frames_27.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_27_3.png"));

	Vector<SpriteFrame*> frames_28;
	frames_28.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_28.png"));
	frames_28.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_28_2.png"));
	frames_28.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_28_3.png"));

	Vector<SpriteFrame*> frames_29;
	frames_29.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_29.png"));
	frames_29.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_29_2.png"));
	frames_29.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_29_3.png"));

	Vector<SpriteFrame*> frames_30;
	frames_30.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_30.png"));
	frames_30.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_30_2.png"));
	frames_30.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_30_3.png"));

	// index : 0 -> burn
	Vector<SpriteFrame*> frames_100;
	frames_100.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_burn_0.png"));
	frames_100.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_burn_1.png"));
	frames_100.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_burn_2.png"));
	frames_100.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_burn_3.png"));
	frames_100.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("car_burn_4.png"));
	_animTargetFrames.push_back(frames_100);

	// add frame !!
	// index 1->30
	_animTargetFrames.push_back(frames_1);
	_animTargetFrames.push_back(frames_2);
	_animTargetFrames.push_back(frames_3);
	_animTargetFrames.push_back(frames_4);
	_animTargetFrames.push_back(frames_5);
	_animTargetFrames.push_back(frames_6);
	_animTargetFrames.push_back(frames_7);
	_animTargetFrames.push_back(frames_8);
	_animTargetFrames.push_back(frames_9);
	_animTargetFrames.push_back(frames_10);
	_animTargetFrames.push_back(frames_11);
	_animTargetFrames.push_back(frames_12);
	_animTargetFrames.push_back(frames_13);
	_animTargetFrames.push_back(frames_14);
	_animTargetFrames.push_back(frames_15);
	_animTargetFrames.push_back(frames_16);
	_animTargetFrames.push_back(frames_17);
	_animTargetFrames.push_back(frames_18);
	_animTargetFrames.push_back(frames_19);
	_animTargetFrames.push_back(frames_20);
	_animTargetFrames.push_back(frames_21);
	_animTargetFrames.push_back(frames_22);
	_animTargetFrames.push_back(frames_23);
	_animTargetFrames.push_back(frames_24);
	_animTargetFrames.push_back(frames_25);
	_animTargetFrames.push_back(frames_26);
	_animTargetFrames.push_back(frames_27);
	_animTargetFrames.push_back(frames_28);
	_animTargetFrames.push_back(frames_29);
	_animTargetFrames.push_back(frames_30);

}

const std::string& MapProcessor::getWeaponsSpriteFrameName()
{
	return _weaponFrameName;
}

void MapProcessor::playSoundEffectHitLand()
{
	//if (!_hitLand.empty())
		ScreenManager::Instance()->playSoundEffect(_hitLand.c_str());
}

//const bool& MapProcessor::getSoundEffectHitTarget()
//{
//
//}

void MapProcessor::playSoundEffectTargetDie(/*const bool& loop*/)
{
	if (!_targetDie.empty())
		ScreenManager::Instance()->playSoundEffect(_targetDie.c_str());
}

void MapProcessor::playSoundEffectBombFall()
{
	if (!_bombFall.empty())
		ScreenManager::Instance()->playSoundEffect(_bombFall.c_str());
}

const bool& MapProcessor::isTargetVisible()
{
	return _isVisibleMap;
}

void MapProcessor::getRandomEnemies(int* listEnemies, const int& enemiesType)
{
	switch (enemiesType)
	{
	case GAME_PLAY_TYPE_RANDOM_3:
		listEnemies[0] = _enemiesRandList[0];
		listEnemies[1] = _enemiesRandList[1];
		listEnemies[2] = _enemiesRandList[2];
		break;
	case GAME_PLAY_TYPE_RANDOM_6:
		listEnemies[0] = _enemiesRandList[0];
		listEnemies[1] = _enemiesRandList[1];
		listEnemies[2] = _enemiesRandList[2];
		listEnemies[3] = _enemiesRandList[3];
		listEnemies[4] = _enemiesRandList[4];
		listEnemies[5] = _enemiesRandList[5];
		break;
	case GAME_PLAY_RANDOM_5_TARGETS:
		listEnemies[0] = _enemiesRandList[0];
		listEnemies[1] = _enemiesRandList[1];
		listEnemies[2] = _enemiesRandList[2];
		listEnemies[3] = _enemiesRandList[3];
		listEnemies[4] = _enemiesRandList[4];
		break;
	}

}

std::string MapProcessor::getPathRandomItemNotLoop(const bool& isEnemy)
{
	char randomTarget[255] = {0};
	//if (_isTrainMap)
		sprintf(randomTarget, "%s%d.png", _currentEnemiesPath, _targetRandomList[_currPosTargets]);
	//else
	//	sprintf(randomTarget, "%s%d", _currentEnemiesPath, _targetRandomList[_currPosTargets]);
	
	_currPosTargets++;

	if(isEnemy)
		_lEnemiesTexture.push_back(std::string(randomTarget));
	return std::string(randomTarget);
}



std::string MapProcessor::getPathRandomItemNotLoopWithIndex(const bool& isEnemy, int& getIndex)
{
	char randomTarget[255] = { 0 };
	sprintf(randomTarget, "%s%d.png", _currentEnemiesPath, _targetRandomList[_currPosTargets]);
	getIndex = _targetRandomList[_currPosTargets];
	_currPosTargets++;
	if (isEnemy)
		_lEnemiesTexture.push_back(std::string(randomTarget));
	return std::string(randomTarget);
}

//int MapProcessor::getMapNumber()
//{
//	return _mapNumber;
//}

MapProcessor* MapProcessor::_instance = 0;

