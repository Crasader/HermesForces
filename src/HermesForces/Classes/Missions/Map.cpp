#include "Map.h"
// TO DO : because height of item is not changed -> use Land::height instead of using cocos2d::size
// remove default of switch
//namespace MAPGAME{


//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


//////////////////////////////////////////////////////////////////////////
////
////							DESERT
////
//////////////////////////////////////////////////////////////////////////
// map IRAQ
int targets_1[] = {0};
MapInfo* Map_1 = new MapInfo(targets_1, 0, 5, ITEM_BOMB_B52, 15, SPECIAL_HELPER_NO_SPEC, GAME_PLAY_TYPE_MAP_1_TUTORIAL, "mini/land/iraq",
	3.0, 3.5 , 3.5 ,
	75);

int targets_2[] = { 2, 1000, 2, 1550, 2, 2090, 2, 2450, 2, 2800, 2, 3340, 2, 3520, 2, 3810, 2, 4220, 2, 4750,
					2, 4980, 2, 5380, 2, 5630, 2, 6160, 2, 6560 };
MapInfo* Map_2 = new MapInfo(targets_2, 30 , 15, ITEM_BOMB_B52, 20, SPECIAL_HELPER_LIGHT, GAME_PLAY_TYPE_HIDDEN, "mini/land/syria",
	3.0, 3.5, 3.8,
	90);

// map_morocco
int targets_3[] = {443,900 , 5,940 , 4, 1220, 4,1380, 4,1790, 4,1890, 4,1990, 4,2160, 4,2290, 443, 2860 ,
					5, 2920 , 445,3200, 6,3300 , 4, 3390, 4 , 3470, 4, 3600 , 4, 3690 , 4,3800, 4,3900, 4,3990,
					4, 4400, 443,4490, 5, 4560, 4, 4600, 4 , 4690, 4 , 4780 , 4, 5100, 445, 5190 , 6, 5260 , 4, 5380};
MapInfo* Map_3 = new MapInfo(targets_3, 60, 25, ITEM_BOMB_B52, 30, SPECIAL_HELPER_NO_SPEC, GAME_PLAY_TYPE_MAP_FOCUS_TUTORIAL, "mini/land/morocco",
	3.0, 3.0, 3.8, 
	40); // 25 enes

// map_egypt.jpg 3 - 437
int targets_4[] = { 3, 1000, 3, 1440, 3, 1630, 3, 1800, 3, 2000,
3, 2190, 3, 2420, 3, 2610, 3, 2800, 3, 2990,
3, 3300, 3, 3490, 3, 3960, 3, 4380, 3, 4570 };
MapInfo* Map_4 = new MapInfo(targets_4, 30, 15, ITEM_BOMB_B52, 20, SPECIAL_HELPER_POINT_RADAR, GAME_PLAY_TYPE_MAP_FOCUS_TUTORIAL, "mini/land/egypt",
	2.5, 2.5, 3.5,
	120);

//////////////////////////////////////////////////////////////////////////
////
////							CITY
////
//////////////////////////////////////////////////////////////////////////
// map_china.jpg
int targets_5[] = { TARGET_NORMAL_CAR, TARGET_FAKE_CAR, 900, 1190, 1430, 1800, 2000, 2190, 2420, 2610, 2800, 2990, 3300, 3490, 3960, 4380, 4570
, 4860, 5100, 5290, 5500, 5700, 5900, 6220, 6510, 6700, 6900, 7240, 7490, 7680, 7890, 8100 };
MapInfo* Map_5 = new MapInfo(targets_5, 32, 3, ITEM_BOMB_CHINA, 5, SPECIAL_HELPER_NO_SPEC, GAME_PLAY_TYPE_RANDOM_3, "mini/land/china",
	3.0, 3.4, 3.8,
	120);

// map_london.jpg
int targets_6[] = { TARGET_IS_BODY_INVI, 800, 820, 1250, 1450, 1650, 1650, 1680, 1680, 2750, 2900,
3000, 3290, 3380, 3410, 3500, 3500, 3550, 3550, 4330, 4340,
4500, 4500, 4520, 4520, 4535, 4550, 4800, 4800, 4830, 4830 };
MapInfo* Map_6 = new MapInfo(targets_6, 15, 15, ITEM_BOMB_FIRE, 15, SPECIAL_HELPER_HEAT_RADAR, GAME_PLAY_RANDOM_ENEMIES_POSITION, "mini/land/london",
	3.0, 3.0, 3.8,
	100);

// map_berlin.jpg
int targets_7[] = { TARGET_IS_BOMB_WARNING, 800, 1200, 1250, 1450, 1650, 1650, 1760, 1780, 2750, 2900,
3000, 3290, 3380, 3410, 3500, 3500, 3530, 3550, 4330, 4340,
4400, 4500, 4590, 4590, 4735, 4740, 4900, 4900, 5000, 5000 }; // 5 . 20
MapInfo* Map_7 = new MapInfo(targets_7, 15, 15, ITEM_BOMB_SQUAD, 18, SPECIAL_HELPER_BOMB_RADAR, GAME_PLAY_RANDOM_ENEMIES_POSITION, "mini/land/berlin",
	3.0, 3.0, 3.8,
	80);

// map_usa.jpg
int targets_8[] = { TARGET_NORMAL_CAR, TARGET_FAKE_CAR, 900, 1190, 1430, 1800, 2000, 2190, 2420, 2610, 2800, 2990, 3300, 3490, 3960, 4380, 4570
, 4860, 5100, 5290, 5500, 5700, 5900, 6220, 6510, 6700, 6900, 7240, 7490, 7680, 7890, 8100 };
MapInfo* Map_8 = new MapInfo(targets_8, 32, 6, ITEM_BOMB_B52, 10, SPECIAL_HELPER_NO_SPEC, GAME_PLAY_TYPE_RANDOM_6, "mini/land/usa",
	3.0, 3.5, 3.8,
	80);


//////////////////////////////////////////////////////////////////////////
////
////							SUBURB
////
//////////////////////////////////////////////////////////////////////////


// map_india.jpg
int targets_9[] = { 7, 1200, 7, 1720, 7, 2250, 7, 2350, 7, 2770, 7, 2870, 7, 3550, 7, 3720, 7, 4220, 7, 4320, };
MapInfo* Map_9 = new MapInfo(targets_9, 20, 10, ITEM_INDIA_SPECIAL_FORCE, 10, SPECIAL_HELPER_POINT_RADAR, GAME_PLAY_TYPE_HIDDEN, "mini/land/india",
	3.0, 3.0, 3.8,
	107);

// map_paris.jpg
int targets_10[] = { TARGET_NORMAL_MANHOLE, TARGET_IS_MANHOLE, 950, 1300, 1500, 1700, 1920, 2160, 2400, 2720, 3000,
					3300, 3540, 3800, 4000, 4230, 4500, 4700, 4990, 5280, 5500, 5700 , 5970 , 6280 , 6500 , 6700 , 6980 };
MapInfo* Map_10 = new MapInfo(targets_10, 27, 5, ITEM_BOMB_FIRE, 7, SPECIAL_HELPER_POINT_RADAR, GAME_PLAY_RANDOM_5_TARGETS, "mini/land/paris",
	3.0, 3.0, 3.7, 
	250);

// map_indo.jpg
int targets_11[] = { TARGET_IS_JAKARTA_NOTHING_MAP_BOX, TARGET_IS_JAKARTA_TERRORIST_MAP_BOX, 
890, 1060, 1230, 1405,
1620,1790, 1960, 2135,
2345,2505, 2665, 
2800,2985, 3165, 3360, 
3525,3715, 3900, 
4070, 4240,4415, 4595,
4770, 4940,5110,
5300, 5420,5550,5670,
5800 }; // 5 . 20
MapInfo* Map_11 = new MapInfo(targets_11, 32, 3, ITEM_TRAIN_SPECIAL_FORCE, 4, SPECIAL_HELPER_NO_SPEC, GAME_PLAY_TYPE_RANDOM_3, "mini/land/jakarta",
	1.5, 1.5, 3.0,
	345);

// map_isarel.jpg
int targets_12[] = { TARGET_IS_BODY_INVI, 860, 1020, 1250, 1450, 1650, 1650, 1680, 1680, 2750, 2900,
3000, 3290, 3380, 3410, 3500, 3500, 3550, 3550, 4330, 4340,
4500, 4500, 4520, 4520, 4535, 4550, 4800, 4800, 4830, 4830 };
MapInfo* Map_12 = new MapInfo(targets_12, 15, 15, ITEM_BOMB_FIRE, 12, SPECIAL_HELPER_HEAT_RADAR, GAME_PLAY_RANDOM_ENEMIES_POSITION, "mini/land/isarel",
	3.0, 3.0, 3.8, 
	116);


//////////////////////////////////////////////////////////////////////////
////
////							AREA-X
////
//////////////////////////////////////////////////////////////////////////


// map_iran.jpg
int targets_13[] = { TARGET_IS_IRAN_NOTHING_MAP_BOX, TARGET_IS_IRAN_TERRORIST_MAP_BOX, 
1000, 
1090, 1250, 
1340, 1500, 
1590,1750, 

1840, 1985,
2075, 2235,
2325,2485,

2575, 2735,
2825, 2985,
3075,3235,

3325, 3485,
3575, 3735,
3815,3970,

4060, 4220,
4310, 4470,
4560
};
MapInfo* Map_13 = new MapInfo(targets_13, 32, 3, ITEM_TRAIN_SPECIAL_FORCE, 4, SPECIAL_HELPER_LIGHT/*SPECIAL_HELPER_LIGHT*/, GAME_PLAY_TYPE_RANDOM_3, "mini/land/iran",
	1.7, 1.7, 3.8, 
	492);

// map_russia.jpg
int targets_14[] = {TARGET_IS_SUBMARINE,750,1250,1550,2250,2500,3000 , 3220, 3240, 3590, 3590};
MapInfo* Map_14 = new MapInfo(targets_14, 5, 5, ITEM_MARINE_BOMB, 6, SPECIAL_HELPER_ANTI_ROCKET, GAME_PLAY_RANDOM_ENEMIES_POSITION, "mini/land/russia",
	2.5, 2.5, 3.4, 
	200);

// map_afghanistan.jpg
int targets_15[] = { 
	17, 900, 100,
	17, 990, 100,

	489, 1162, 100,
	19, 1210, 100,

	17, 1420, 360,
	17, 1572, 360,

	18, 1866, 190,
	17, 1938, 370,

	17, 2240, 370,
	17, 2278, 100,

	17, 2536, 100,
	18, 2660, 370,

	18, 3000, 370,
	17, 3001, 100,

	18, 3287, 370,
	489, 3440, 100,

	19, 3480, 100,
	18, 3572, 370, // 18



	18, 4000, 370,
	17, 4089, 100,
	489, 4140, 100,
	18, 4164, 360,
	489, 4180, 100,
	19, 4240, 100,
	17, 4256, 360,
	18, 4350, 370, //26

	18, 4630, 370,
	489, 4760, 100,
	19, 4800, 100,
	18, 4920, 370, // 30


	17, 5300, 100,
	18, 5350, 370,
	17, 5351, 100, // 33


	489, 5420, 360,
	18, 5480, 360,
	489, 5540, 360,
	17, 5610, 360,
	18, 6000, 370, //38

	17, 5421, 100,
	489, 5480, 100,
	17, 5540, 100,
	489, 5610, 100,
	19, 5680, 100 // 43

};
MapInfo* Map_15 = new MapInfo(targets_15, 129, 34, ITEM_SPECIAL_SHOOT, 10, SPECIAL_HELPER_LIGHT/*SPECIAL_HELPER_LIGHT*/, GAME_PLAY_ENEMIES_DIFF_HEIGHT, "mini/land/afghan",
	2.0, 2.0, 2.4,
	60);
//#endif


MapInfo* GameMap::ListMaps[]={Map_1,
							Map_2,
							Map_3,
							Map_4,
							Map_5,
							Map_6,
							Map_7,
							Map_8,
							Map_9,
							Map_10,
							Map_11,
							Map_12,
							Map_13,
							Map_14,
							Map_15
							};

//}