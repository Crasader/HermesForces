#ifndef __IUNIT_H__
#define __IUNIT_H__

#include "define.h"
//#include "Missions/Land.h"
//#include "ISSoldier.h"

//class Land;
// TO DO :define each target height width, remove getContentSize
// find ->getContentSize() => remove
class IUnit
{
public:	
	IUnit(const int&   idTag, const cocos2d::Point& p);
	virtual ~IUnit();
	// hit bomb
	virtual const int& die() = 0;
	// TO DO : change int -> bool (if int not need)
	virtual const int& beDetected() {return NO_IMPLEMENT;}
	virtual void setScale(const float& k);
	virtual const bool& checkDisable();
	virtual void setOpacity(const int& param);
	virtual void disable();
	void disapeare();
	virtual void setPhysicsBody(const cocos2d::Size& sizeBody);
	cocos2d::Sprite* sprite(){return _targetUnit;}
	virtual void hitMainCharacter() {}
	virtual const bool& updatePositionToTheLeft();
	virtual void startMoving() {}
	//bool IsEnemies() const { return _isEnemies; }
	void IsEnemies(bool val = true) { _isEnemies = val; }
	//virtual void clean();
	//bool isTheEndOfTargetInScene();
protected:
	cocos2d::Sprite* _targetUnit;
	PhysicsBody* _targetBody;
	int _idTag;
	bool _isDead;
	bool _isDisable;
	int _pos;
	int _indexAnime;
	bool _isEnemies;

};

#endif