#ifndef MAP_PROCESSOR_H
#define MAP_PROCESSOR_H
#include "../Utility/Utility.h"
//#include "Animes.h"
#define  NO_WEAPONS_INIT -1
class MapProcessor{
public:
	static MapProcessor* Instance()
	{
		if (_instance == 0){
			_instance = new MapProcessor();
		}
		return _instance;
	}
	MapProcessor()
	{
		_currentWeapon = NO_WEAPONS_INIT;
	}
	void InitMapProcessor(const int& MapNumber, const bool& isCached = false);
	std::vector<std::string> getListEnemies();
	//void addEnemies(std::string path);
	void getRandomEnemies(int* listEnemies,const int& enemiesType);
	std::string getPathRandomItemNotLoop(const bool& isEnemy);
	std::string getPathRandomItemNotLoopWithIndex(const bool& isEnemy, int& getIndex);
	int getSpecialNumberFile();
	Vector<SpriteFrame*> getTargetAnimeFramesByIndex(const int& index);
	Vector<SpriteFrame*> getFighterItemAnimeFrames(const int& index);
	//SpriteFrame* getFighterFrame(){ return _fighterFrames; }
	//SpriteFrame* getItemFighterFrame(){ return _fighterItemFrames; }

	void doFighterItems(const int& typeWeapon, cocos2d::Size* &sizeBoom, cocos2d::Vec2 &vec2Boom, 
		const float& scale, int& TimeDelayClickWeapon/*, int& endPointBomb , const int& heightLandY*/);
	void addCarAnimation();
	const std::string& getWeaponsSpriteFrameName();
	void playSoundEffectHitLand();
	//const bool& getSoundEffectHitTarget();
	void playSoundEffectTargetDie(/*const bool& loop*/);
	void playSoundEffectBombFall();
	const bool& isTargetVisible();

private:
	std::string _hitLand, /*_hitTarget,*/ _targetDie , _bombFall;
	int _mapNumber;
	//bool _isCached;
	std::string _weaponFrameName;
	int* _targetRandomList;
	int* _enemiesRandList;
	bool _isVisibleMap;
	int _randEnemies;
	int _randMap;
	int _currPosTargets;
	char _currentEnemiesPath[255];
	//int _typeMap;
	
	std::vector<std::string> _lEnemiesTexture;
	//MapProcessor();
	static MapProcessor* _instance;

	// anime
	std::vector<Vector<SpriteFrame*>> _animTargetFrames;
	std::vector<Vector<SpriteFrame*>> _animFighterFrames;

	int _currentWeapon;

	bool _isTrainMap;
};


#endif