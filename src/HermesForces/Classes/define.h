//
//  define.h
//  BombTerrorist
//
//  Created by Quan Rock on 1/26/16.
//
//

#ifndef define_h
#define define_h

// TO DO : because switch case create map value -> use value increase is better !!
// add value better than statement = inline function adder
// using inline whenever
// set calculation inside loop outside
// using template if possible
// all params is const ref
// optimize condition
// do not put object to constructor
// Assign by put data to Class in declare -> class A : Age(age) , Name(name)
// if need -> overload =
// put data to function and set value to them, don't create new object and return inside method
// avoid temporary object
// function with const  =>  int getNumber() const;

#define IS_SMALL_SCENE 1
#define IS_MEDIUM_SCENE 2
#define IS_LARGE_SCENE 3

#include "cocos2d.h"
USING_NS_CC;
#include "ui/CocosGUI.h"
#include "ui/GUIDefine.h"
#include "SimpleAudioEngine.h"

#define SCORE_FONT_SIZE 15
#define TRANSITION_TIME_GAMESCENE 0.1
#define DISPLAY_TIME_SPLASH_SCENE 0.1
#define DEFAULT_TRANSITION_TIME 0.1
#define TRANSITION_TIME_GAMEOVER 2

#define DISPLAY_TIME_FAIL_GAME_SCENE 1
#define TRANSITION_TIME 1

#define BIRD_COLLISION_BITMASK 0x000001
#define OBSTACLE_COLLISION_BITMASK 0x000002
#define POINT_COLLISION_BITMASK 0x000003
#define POINT_LAND_BITMASK 0x000004
#define POINT_FIGHTER_ITEMS_BITMASK 0x000005

#define POINT_TARGET_BITMASK 0x000006
#define POINT_TARGET_ROCKET_BITMASK 0x000007
#define POINT_ANTI_ROCKET_FIGHTER 0x000008
#define POINT_ENEMIES_WEAPON_ITEMS_BITMASK 0x000009
#define POINT_VIEWER_ITEMS_BITMASK 0x0000010
#define POINT_FIGHTER_BITMASK 0x0000011

#define DELAY_SPECIAL_CLICK_1 1000
#define DELAY_SPECIAL_CLICK_2 2000
#define DELAY_SPECIAL_CLICK_3 3000
#define DELAY_SPECIAL_CLICK_4 4000

#define GAME_PLAY_TYPE_NO_SPECIAL 0
#define GAME_PLAY_TYPE_HIDDEN 1
#define GAME_PLAY_TYPE_RANDOM_3 2
#define GAME_PLAY_TYPE_RANDOM_6 3
#define GAME_PLAY_RANDOM_ENEMIES_POSITION 4
#define GAME_PLAY_RANDOM_5_TARGETS 5
#define GAME_PLAY_ENEMIES_DIFF_HEIGHT 7

//#define GAME_PLAY_TYPE_NO_SPECIAL 0

// lower than 50
#define TARGET_IS_IRAQ 1
#define TARGET_IS_SYRIA 2
#define TARGET_IS_EGYPT 3

#define TARGET_IS_MOROCCO 4
#define TARGET_IS_KNIFE 5
#define TARGET_IS_FIRE 6

#define TARGET_IS_INDIAN 7
#define TARGET_FAKE_CAR 8

#define TARGET_IS_BODY_INVI 9

#define TARGET_IS_BOMB_WARNING 10

#define  TARGET_IS_TERRORIST_MAP_BOX_BANGLADESH 11

//#define TARGET_IS_BODY_INVI 12

#define TARGET_IS_MANHOLE 14

#define TARGET_IS_JAKARTA_TERRORIST_MAP_BOX 151
#define TARGET_IS_IRAN_TERRORIST_MAP_BOX 152

#define TARGET_IS_SUBMARINE 16
#define TARGET_IS_ALQUEDA 17
#define TARGET_IS_ALQUEDA_ROCKET 18
#define TARGET_IS_ALQUEDA_FIRE 19

// lower than 500
#define TARGET_IRAQ_CIVILIANS 333
#define TARGET_SYRIA_CIVILIANS 433
#define TARGET_EGYPT_CIVILIANS 437

#define TARGET_MOROCCO_CIVILIANS 441
#define TARGET_MOROCCO_VICTIM 443
#define TARGET_MOROCCO_VICTIM_CAGE 445

#define TARGET_INDIAN 451
#define TARGET_NORMAL_CAR 453

#define TARGET_IS_NORMAL_WARNING 457

#define TARGET_IS_JAKARTA_NOTHING_MAP_BOX 4611
#define TARGET_IS_IRAN_NOTHING_MAP_BOX 4612

#define TARGET_NORMAL_MANHOLE 463
#define TARGET_ALQUEDA_VICTIM 489

// lower than 1000
#define TARGET_IS_CIVILIAN_CAR 555
#define TARGET_IS_SAFE_AREA 557
#define TARGET_IS_GUNPOWDER 559

// special : lower than 2000
#define TARGET_IS_MANHOLE_COVER 1315

#define IS_VICTIM(x)  x > 300 && x < 2000 ? true : false

#define DESTROY_ENEMY_DONOTHING 0
#define DESTROY_ENEMY_GOODKILL 11
#define DESTROY_ENEMY_BADKILL 13

//#define TARGET_IS_SOLDIER 0
//#define TARGET_IS_MACHINE 1
//#define TARGET_IS_BUNKER 2
//#define TARGET_IS_VICTIM -1

#define ITEM_BOMB_B52 22
#define ITEM_BOMB_CHINA 23

#define ITEM_BULLET 27
#define ITEM_BOMB_FIRE 31
#define ITEM_BOMB_FIRE_PARIS 33
#define ITEM_BOMB_SQUAD 35
#define ITEM_TRAIN_SPECIAL_FORCE 37
//#define ITEM_TRAIN_SPECIAL_FORCE_NIGHT 39

#define ITEM_INDIA_SPECIAL_FORCE 41
#define ITEM_MARINE_BOMB 43
#define ITEM_SPECIAL_SHOOT 47

#define MAP_1 0
#define MAP_2 1
#define MAP_3 2
#define MAP_4 3

#define MAP_5 4
#define MAP_6 5
#define MAP_7 6
#define MAP_8 7

#define MAP_9 8
#define MAP_10 9
#define MAP_11 10
#define MAP_12 11

#define MAP_13 12
#define MAP_14 13
#define MAP_15 14
#define MAP_16 15

#define SPECIAL_HELPER_LIGHT 183
#define SPECIAL_HELPER_POINT_RADAR 189
#define SPECIAL_HELPER_NO_SPEC 111
#define SPECIAL_HELPER_HEAT_RADAR 171
#define SPECIAL_HELPER_BOMB_RADAR 173
#define SPECIAL_HELPER_ANTI_ROCKET 191

#define MANHOLE_HEIGHT_OR_WIDTH 20 // (0.5) * 22


#define OUT_OFF_LEFT_SCREEN_PIXEL -200
#define OUT_OFF_RIGHT_SCREEN_PIXEL 200

#define END_LEFT_TARGET 1011
#define END_RIGHT_TARGET 1013
#define ON_SCENE_TARGET 1015
#define IS_DISABLED 1017

#define NO_IMPLEMENT -1
#define BE_DETECTED 100
#define BE_DEAD_NO_DETECT 200

#define MAP_DESERT 17
#define MAP_CITY 19
#define MAP_SUBURB 23
#define MAP_AREAX 29
#define NO_MAP_AREA -31


#endif /* define_h */
