#ifndef __TARGET_H__
#define __TARGET_H__

#include "define.h"

//#include "map_iraq/CiviIraq.h"
#include "map_iraq/ISIraq.h"

//#include "map_syria/CiviSyria.h"
#include "map_syria/ISSyria.h"

#include "map_egypt/ISEgypt.h"
#include "map_egypt/CiviEgypt.h"

//#include "map_morocco/CiviMorocco.h"
#include "map_morocco/ISFire.h"
#include "map_morocco/ISKnife.h"
#include "map_morocco/ISMorocco.h"
#include "map_morocco/ISVictim.h"
#include "map_morocco/ISVictim_Cage.h"

//#include "map_india/Indian.h"
//#include "map_india/FakeIndian.h"

#include "map_india/IsIndian.h"

#include "map_car/NormalCar.h"
#include "map_car/FakedCar.h"

#include "map_london_isarel/ISBodyInvi.h"

#include "map_berlin/BombWarning.h"
//#include "map_berlin/NormalWarning.h"

#include "map_train/NormalBoxTrain.h"
#include "map_train/SeriousBoxTrain.h"

#include "map_pakistan/Alqueda.h"
#include "map_pakistan/AlquedaRocket.h"
#include "map_pakistan/AlquedaFire.h"
#include "map_pakistan/AlquedaVictim.h"

#include "map_paris/ISManHole.h"
#include "map_paris/NormalManHole.h"

#include "map_russia/SubMarine.h"

//#include "map_isarel/ISIsarel.h"

//#include "map_jakarta/SeriousBoxTrainJakarta.h"
//#include "map_jakarta/NormalBoxTrainJarkarta.h"

USING_NS_CC;
//class Land;
class Target
{
public:
	Target(const cocos2d::Point& pos, const int& idTag, const int& type);
	~Target();
	//void move();
	const int&  die();
	void setPosition(const cocos2d::Point& p);
	void setScale(const float& k);
	const bool& checkDisable();
	void setOpacity(const int& param);
	//void disable();
	void hitMainCharacter();
	//void comeToScreen();
	void detectTarget();
	const bool&  updatePositionToTheLeft();
	cocos2d::Sprite* getSprite();
	void startMoving();
	//void clean();

private:
	IUnit* _targetUnit;
	//cocos2d::Sprite* test;
	//int _type;
};

#endif // __TARGET_H__
