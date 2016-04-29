#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "define.h"

class GameOverScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
#endif
	~GameOverScene();
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
    
private:
    //void GoToMainMenuScene( cocos2d::Ref *sender );
    //void GoToGameScene( cocos2d::Ref *sender );
    void GoToMainMenuScene(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void GoToGameScene(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void onFinishLoading(float dt);//onFinishMenuLoading
    void onFinishMenuLoading(float dt);
    
	cocos2d::ui::Button* itemRetryButton;
	cocos2d::ui::Button* itemMenuButton;
	bool _isVictory;
    cocos2d::Sprite* cloudSprite;
    //char mx[300];
    cocos2d::Size visibleSize ;
    cocos2d::Vec2 origin;
    float x,y;
    bool _isLoad;
};

#endif // __GAME_OVER_SCENE_H__
