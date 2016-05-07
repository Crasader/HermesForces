#include "Target.h"
#include "../Missions/MapProccessor.h"

Target::Target(const cocos2d::Point& pos, const int& idTag, const int& type)
{
	switch (type)
	{
		// map 1 iraq
		case TARGET_IS_IRAQ:
			_targetUnit = new IsIraq(idTag, pos);
            _targetUnit->IsEnemies();
			break;

		// map 2 Syria
		case TARGET_IS_SYRIA:
			_targetUnit = new ISSyria(idTag,pos);
            _targetUnit->IsEnemies();
			break;

		case TARGET_IS_EGYPT:
			_targetUnit = new IsEgypt(idTag,pos);
            _targetUnit->IsEnemies();
			break;
		case TARGET_EGYPT_CIVILIANS:
			_targetUnit = new CiviEgypt(idTag,pos);
			_targetUnit->IsEnemies(false);
			break;

		case TARGET_MOROCCO_VICTIM:
			_targetUnit = new IsVictim(idTag,pos);
			_targetUnit->IsEnemies(false);
			break;
		case TARGET_MOROCCO_VICTIM_CAGE:
			_targetUnit = new IsCageVictim(idTag, pos);
			_targetUnit->IsEnemies(false);
			break;
		case TARGET_IS_MOROCCO:
			_targetUnit = new IsMorocco(idTag,pos);
            _targetUnit->IsEnemies();
			break;
		case TARGET_IS_KNIFE:
			_targetUnit = new IsKnife(idTag,pos);
            _targetUnit->IsEnemies();
			break;
		case TARGET_IS_FIRE:
			_targetUnit = new IsFire(idTag,pos);
            _targetUnit->IsEnemies();
			break;
			
		case TARGET_IS_INDIAN:
			_targetUnit = new IsIndian(idTag, pos);
            _targetUnit->IsEnemies();
			break;

		case TARGET_NORMAL_CAR:
			_targetUnit = new NormalCar(idTag,pos);
			_targetUnit->IsEnemies(false);
			break;
		case TARGET_FAKE_CAR:
			_targetUnit = new FakedCar(idTag, pos);
            _targetUnit->IsEnemies();
			break;

		case TARGET_IS_BODY_INVI:
			_targetUnit = new ISBodyInvi(idTag, pos);
            _targetUnit->IsEnemies();
			break;

		case TARGET_IS_BOMB_WARNING:
			_targetUnit = new BombWarning(idTag, pos);
            _targetUnit->IsEnemies();
			break;

		case TARGET_IS_JAKARTA_NOTHING_MAP_BOX:
			_targetUnit = new NormalBoxTrain(idTag, pos, 90);
			_targetUnit->IsEnemies(false);
			break;
		case TARGET_IS_IRAN_NOTHING_MAP_BOX:
			_targetUnit = new NormalBoxTrain(idTag, pos, 95);
			_targetUnit->IsEnemies(false);
			break;
		case TARGET_IS_JAKARTA_TERRORIST_MAP_BOX:
			_targetUnit = new SeriousBoxTrain(idTag, pos, 90);
            _targetUnit->IsEnemies();
			break;
		case TARGET_IS_IRAN_TERRORIST_MAP_BOX:
			_targetUnit = new SeriousBoxTrain(idTag, pos, 95);
            _targetUnit->IsEnemies();
			break;


		case TARGET_IS_MANHOLE :
			_targetUnit = new IsManHole(idTag, pos);
            _targetUnit->IsEnemies();
			break;
		case TARGET_NORMAL_MANHOLE:
			_targetUnit = new NormalManHole(idTag, pos);
			_targetUnit->IsEnemies(false);
			break;

		case TARGET_IS_SUBMARINE:
			_targetUnit = new SubMarine(idTag, pos);
            _targetUnit->IsEnemies();
			break;

		case TARGET_IS_ALQUEDA:
			_targetUnit = new AlQueda(idTag, pos);
            _targetUnit->IsEnemies();
			break;
		case TARGET_IS_ALQUEDA_ROCKET:
			_targetUnit = new AlQuedaRocket(idTag, pos);
            _targetUnit->IsEnemies();
			break; 		
		case TARGET_IS_ALQUEDA_FIRE:
			_targetUnit = new AlQuedaFire(idTag, pos);
            _targetUnit->IsEnemies();
			break;
		case TARGET_ALQUEDA_VICTIM:
			_targetUnit = new AlQuedaVictim(idTag, pos);
			_targetUnit->IsEnemies(false);
			break;
	}
	//_type = type;
}


Target::~Target()
{
	delete _targetUnit;
}

const int& Target::die()
{
	return _targetUnit->die();
}


void Target::setScale(const float& k)
{
	_targetUnit->setScale(k);
}

cocos2d::Sprite* Target::getSprite()
{
	return _targetUnit->sprite();
}

void Target::startMoving()
{
	_targetUnit->startMoving();
}

//void Target::clean()
//{
//	_targetUnit->clean();
//}

const bool& Target::checkDisable()
{
	return _targetUnit->checkDisable();
}

void Target::setOpacity(const int& param)
{
	_targetUnit->setOpacity(param);
}

void Target::detectTarget()
{
	_targetUnit->beDetected();
}

const bool& Target::updatePositionToTheLeft()
{
	return _targetUnit->updatePositionToTheLeft(); // disable position
}

void Target::hitMainCharacter()
{
	_targetUnit->hitMainCharacter();
}

