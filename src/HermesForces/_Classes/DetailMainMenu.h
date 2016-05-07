#ifndef DETAIL_MAINMENU
#define DETAIL_MAINMENU
#include "define.h"

class DetailMainMenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
#endif
	// implement the "static create()" method manually
	CREATE_FUNC(DetailMainMenuScene);
private:
	void finishLoadingButton1(float dt);
	void finishLoadingButton2(float dt);
	void finishLoadingButton3(float dt);
	void finishLoadingButton4(float dt);
	void onFinishButtonBackLoading(float dt);

	void GoToGameScene_1(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_2(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_3(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_4(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_5(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_6(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_7(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_8(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_9(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_10(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_11(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_12(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_13(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_14(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void GoToGameScene_15(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void addMapButton(const int&  MapNumber, const std::string& path, const cocos2d::ui::Widget::ccWidgetTouchCallback& callback, const float& col, const float& row);
	void GoToMainMenuScene(Ref* pSender, ui::Widget::TouchEventType eEventType);
	int _mapMax;
	float _deltaScaleX;
	Sprite* _maskClicked;
	bool _isMoving;
	//std::string _pathOfBttImage1, _pathOfBttImage2, _pathOfBttImage3, _pathOfBttImage4;
	float _col1, _col2, _col3, _col4;
	float _row;
	float _deltaScaleBgX;

	cocos2d::ui::Button* _litemButton[4];
	int _kItem;
};
#endif // !DETAIL_MAINMENU
