#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "define.h"


class MainMenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	#endif
	    // implement the "static create()" method manually
	    CREATE_FUNC(MainMenuScene);
private:
	int _mapMax;

	cocos2d::ui::Button* musicBtt;
	cocos2d::ui::Button* soundBtt;
	cocos2d::ui::Button* copyrightBtt;

	cocos2d::Sprite* _bttDesert, *_bttCity, *_bttSuburb,* _bttAreaX , *_maskClicked;
	//cocos2d::ui::Button* _bttDesert;
	//cocos2d::ui::Button* _bttCity;
	//cocos2d::ui::Button* _bttSuburb;
	//cocos2d::ui::Button* _bttAreaX;

	float _pointDesert, _pointCity, _pointSuburb, _pointAreaX;
	Size visibleSize;
	Vec2 origin;
	float x, y;
	float _scaleMap;
	void turnOnOffMusicButton(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void turnOnOffSoundButton(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void gotoCreditScene(Ref* pSender, ui::Widget::TouchEventType eEventType);


	cocos2d::EventListenerPhysicsContact* _contactListener;
	cocos2d::EventListenerTouchOneByOne* _touchListener;

	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void EndMoving();
	// touch events
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

	float initialTouchPosX, initialTouchPosY;
	float currentTouchPosX, currentTouchPosY;
	float _deltaTouchX, _deltaApply;
	float _minSlide, _maxSlide;
	
	bool isTouchDown;
	//void update(float dt);
	void checkInsideMap(const float& x, const  float& y);


	float xD1, xD2, xC1, xC2, xS1, xS2, xA1, xA2;
	float yD1, yD2, yC1, yC2, yS1, yS2, yA1, yA2;

	void updateXY();
	bool _isInside;

	int _currentBigMap;
};

//class MainMenuScene : public cocos2d::Layer
//{
//public:
//    // there's no 'id' in cpp, so we recommend returning the class instance pointer
//    static cocos2d::Scene* createScene();
//
//    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
//    virtual bool init();
//    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
//#endif
//    // implement the "static create()" method manually
//    CREATE_FUNC(MainMenuScene);
//    
//private:
//	// const std::string& path              const ccMenuCallback& callback pointer
//	// const float& col const float& row
//	void addMapButton(const int&  MapNumber, const std::string& path, const std::string& path_no, const cocos2d::ui::Widget::ccWidgetTouchCallback& callback, const float& col, const float& row);
//
//	void GoToGameScene_1(Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_2( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_3( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_4( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_5( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_6( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_7( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_8( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_9( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_10( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_11( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_12( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_13( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_14( Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void GoToGameScene_15( Ref* pSender, ui::Widget::TouchEventType eEventType);
//
//    void exitGame();
//	void turnOnOffMusicButton(Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void turnOnOffSoundButton(Ref* pSender, ui::Widget::TouchEventType eEventType);
//	void gotoCreditScene(Ref* pSender, ui::Widget::TouchEventType eEventType);
//
//	void onFinishLoading(float dt);
//	Size visibleSize;
//	Vec2 origin;
//	float x, y;
//	float _scaleMap;
//	int _mapMax;
//	cocos2d::ui::Button* musicBtt;
//	cocos2d::ui::Button* soundBtt;
//	cocos2d::ui::Button* copyrightBtt;
//};

//--- Desert
//Iraq
//Syria
//morocco
//Egypt

//
//--- City
//China
//Berlin
//London
//USA
//
//--- Suburb
//India
//Paris
//Jakarta
//Isarel
//
//--- Area-x
//Iran
//Russia
//Pakistan

#endif // __MAIN_MENU_SCENE_H__
