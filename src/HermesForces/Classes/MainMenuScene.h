#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "define.h"

class MainMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
#endif
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
    
private:
	// const std::string& path              const ccMenuCallback& callback pointer
	// const float& col const float& row
	void addMapButton(const int&  MapNumber, const std::string& path, const std::string& path_no, const cocos2d::ui::Widget::ccWidgetTouchCallback& callback, const float& col, const float& row);

	void GoToGameScene_1(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_2( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_3( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_4( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_5( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_6( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_7( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_8( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_9( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_10( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_11( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_12( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_13( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_14( Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_15( Ref* pSender, ui::Widget::TouchEventType eEventType);

    void exitGame();
	void turnOnOffMusicButton(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void turnOnOffSoundButton(Ref* pSender, ui::Widget::TouchEventType eEventType);

	float _scaleMap;
	int _mapMax;
	cocos2d::ui::Button* musicBtt;
	cocos2d::ui::Button* soundBtt;
};

#endif // __MAIN_MENU_SCENE_H__
