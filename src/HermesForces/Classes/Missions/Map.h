#ifndef MAP_H
#define MAP_H
#include "define.h"
//#include <stdio.h>
#include <string>
//namespace MAPGAME{
//#define ARAB_CIVI 
class MapInfo;

class GameMap
{
public:
	//static MapInfo* Map_1;
	//static MapInfo* Map_2;
	//static MapInfo* Map_3;
	//static MapInfo* Map_4;
	//static MapInfo* Map_5;
	//static MapInfo* Map_6;
	//static MapInfo* Map_7;
	//static MapInfo* Map_8;
	//static MapInfo* Map_9;
	//static MapInfo* Map_10;
	//static MapInfo* Map_11;
	//static MapInfo* Map_12;
	//static MapInfo* Map_13;
	//static MapInfo* Map_14;
	//static MapInfo* Map_15;

	static MapInfo* ListMaps[];
};

class MapInfo
{
public:
	int* Items;// type, distance to previous
	int WeaponType;
	int WeaponCount;
	int Special;
	std::string MapPath; // name of landscape
	//std::string BackGroundPath;
	float physicsLandHeight;
	int CountItems;
	
	//int pixelPerDeltaTimeOfLand_Tiny, pixelPerDeltaTimeOfLand_Med, pixelPerDeltaTimeOfLand_Big;
	//int pixelPerDeltaTimeOfTargets_Tiny, pixelPerDeltaTimeOfTargets_Med, pixelPerDeltaTimeOfTargets_Big;
	
	float PixelLand;
	float PixelTarget;
	float BombFallSpeed;

	int targetPlayingType;
	// TODO : remove widthMap, heightMap
	//int widthMap;
	//int heightMap;
	int enemiesCount;
	
	MapInfo() {}
	//MapInfo& MapInfo::operator=(const MapInfo* rhs) {
	//	//test
	//	this->Items = rhs->Items;
	//	this->WeaponType = rhs->WeaponType;
	//	this->WeaponCount = rhs->WeaponCount;
	//	this->Special = rhs->Special;
	//	this->physicsLandHeight = rhs->physicsLandHeight;
	//	this->CountItems = rhs->CountItems;
	//	this->pixelPerDeltaTimeOfLand = rhs->pixelPerDeltaTimeOfLand;
	//	this->pixelPerDeltaTimeOfTargets = rhs->pixelPerDeltaTimeOfTargets;
	//	this->targetPlayingType = rhs->targetPlayingType;
	//	this->MapPath.append(rhs->MapPath);
	//}
	void copyFromSource(const MapInfo* rhs)
	{
		this->Items = rhs->Items;
		this->WeaponType = rhs->WeaponType;
		this->WeaponCount = rhs->WeaponCount;
		this->Special = rhs->Special;
		this->physicsLandHeight = rhs->physicsLandHeight;
		this->CountItems = rhs->CountItems;

		//this->pixelPerDeltaTimeOfLand_Tiny = rhs->pixelPerDeltaTimeOfLand_Tiny;
		//this->pixelPerDeltaTimeOfLand_Med = rhs->pixelPerDeltaTimeOfLand_Med;
		//this->pixelPerDeltaTimeOfLand_Big = rhs->pixelPerDeltaTimeOfLand_Big;
		//
		//this->pixelPerDeltaTimeOfTargets_Tiny = rhs->pixelPerDeltaTimeOfTargets_Tiny;
		//this->pixelPerDeltaTimeOfTargets_Med = rhs->pixelPerDeltaTimeOfTargets_Med;
		//this->pixelPerDeltaTimeOfTargets_Big = rhs->pixelPerDeltaTimeOfTargets_Big;
		this->BombFallSpeed = rhs->BombFallSpeed;
		this->PixelLand = rhs->PixelLand;
		this->PixelTarget = rhs->PixelTarget;

		this->targetPlayingType = rhs->targetPlayingType;
		//this->widthMap = rhs->widthMap;
		//this->heightMap = rhs->heightMap;
		this->enemiesCount = rhs->enemiesCount;
		this->MapPath.append(rhs->MapPath);
	}
	MapInfo(int *items, int countitems, int enemiescount, int weapontype, int weaponcount, int special, int targetptype, std::string mappath,
		float _perpixelLand, float _perpixelTarget, float bombFallSpeed,
		/*		int __pixelPerDeltaTimeOfLand_tiny, int __pixelPerDeltaTimeOfLand_med, int __pixelPerDeltaTimeOfLand_big,
				int __pixelPerDeltaTimeOfTargets_tiny, int __pixelPerDeltaTimeOfTargets_med, int __pixelPerDeltaTimeOfTargets_big*/
		float physicslandheight
		/*,int _widthmap, int heightmap*/)
	{
		this->Items = items;
		this->CountItems = countitems;
		this->WeaponType = weapontype;
		this->WeaponCount = weaponcount;
		this->Special = special;

		this->MapPath = mappath;
		this->physicsLandHeight = physicslandheight;


		this->PixelLand = _perpixelLand;
		this->PixelTarget = _perpixelTarget;

		this->BombFallSpeed = bombFallSpeed;
		//this->pixelPerDeltaTimeOfLand_Tiny = __pixelPerDeltaTimeOfLand_tiny;
		//this->pixelPerDeltaTimeOfLand_Med = __pixelPerDeltaTimeOfLand_med;
		//this->pixelPerDeltaTimeOfLand_Big = __pixelPerDeltaTimeOfLand_big;

		//this->pixelPerDeltaTimeOfTargets_Tiny = __pixelPerDeltaTimeOfTargets_tiny;
		//this->pixelPerDeltaTimeOfTargets_Med = __pixelPerDeltaTimeOfTargets_med;
		//this->pixelPerDeltaTimeOfTargets_Big = __pixelPerDeltaTimeOfTargets_big;

		this->targetPlayingType = targetptype;
		//this->widthMap = widthMap;
		//this->heightMap = heightmap; // 544 is stable
		this->enemiesCount = enemiescount;
		//this->BackGroundPath = backgroundpath;
	}
};
//}
#endif


