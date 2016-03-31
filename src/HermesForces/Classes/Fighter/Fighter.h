#ifndef __FIGHTER_H__
#define __FIGHTER_H__
#include "define.h"
#include "Items/Items.h"
#include "Items/AntiRocket.h"
#include "Items/ViewFinder.h"
class Fighter
{
public:
	Fighter(cocos2d::Layer *layer, const cocos2d::Point& leftAlignPos, const int& specialMap = 0);
    //~Fighter();
    //void Fall( bool isGameOver );
	void Drop( );
	const bool& Shoot(const cocos2d::Point& pos);
	//void Explosive(int idBoomTag);
	void hitTarget(const int& idBoomTag);
	void hitLand(const int& idBoomTag);
	//void stopFly();
	void updateBombs();
	void antiRocket(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void disableAntiRocket();
	bool hitRocket(const int& idAntiRocketTag);
	void gameOver(const int& indexFinal);
	void eatRocket();
    void setAntiRocketMap14(const cocos2d::Point& p);
	void setAnimationFighterFly();
    void soundGunMap415();//
private:
    int _nextTimeShootGun , _iGood;
	int _currentTime;
	int _currentAntiRocketTime; // for map 14 and 15
	int systemcrt;
	cocos2d::ui::Button* _specialButton;
    //cocos2d::Size visibleSize;
    //cocos2d::Vec2 origin;
    
    cocos2d::Sprite*  _fighter;
    
	cocos2d::Layer *_layer;
	//FighterItems* _listFighterItems[300];
	FighterItems** _listFighterItems;
	AntiRocket** _listAntiRocketItems;
	ViewFinder* _unlimitedWeapon;
	int _timeDelayAntiRocket ;

	int _restAntiRocket ;
    cocos2d::Point _bombBarrel;
	int restBomb;	
	int _systemCrt,_systemAntiRocketCrt;
	cocos2d::Point _antiRocketFromPos_1,_antiRocketFromPos_2,_antiRocketFromPos_3,_antiRocketToPos_1,_antiRocketToPos_2,_antiRocketToPos_3;
};

#endif // __BIRD_H__
