#ifndef __CREDIT_SCENE_H__
#define __CREDIT_SCENE_H__

#include "define.h"

class CreditScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(CreditScene);

private:
	void GoToMainMenuScene(Ref* pSender, ui::Widget::TouchEventType eEventType);
};

#endif // __SPLASH_SCENE_H__
