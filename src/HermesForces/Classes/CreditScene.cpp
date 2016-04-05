#include "CreditScene.h"
#include "ScreenManager.h"
Scene* CreditScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CreditScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CreditScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//    // add "HelloWorld" splash screen"
	auto backgroundSprite = Sprite::create("mini/land/syria_s.jpg");
	float deltaScale = (Director::getInstance()->getVisibleSize().height/* + Director::getInstance()->getVisibleOrigin().y*/) / backgroundSprite->getContentSize().height;
	backgroundSprite->setScale(deltaScale);
	backgroundSprite->setPosition(Point(Director::getInstance()->getVisibleOrigin().x + backgroundSprite->getContentSize().width * deltaScale * 0.5,
		Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height / 2));
	this->addChild(backgroundSprite, 0);

	auto content = Sprite::create("mini/scene/copyright_content.png");
	float x = (Director::getInstance()->getVisibleSize().width/* + Director::getInstance()->getVisibleOrigin().x*/) / content->getContentSize().width;
	float y = (Director::getInstance()->getVisibleSize().height/* + Director::getInstance()->getVisibleOrigin().y*/) / content->getContentSize().height;
	content->setScale(x, y);
	content->setPosition(Point(Director::getInstance()->getVisibleOrigin().x / 2 + Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleOrigin().y / 2 + Director::getInstance()->getVisibleSize().height / 2));
	this->addChild(content, 1);

	auto backButton = cocos2d::ui::Button::create();
	backButton->loadTextures("mini/scene/btt_large.png", "mini/scene/btt_large.png", "");
	backButton->setScale(deltaScale);
	float distanceConer = 0.12 * Director::getInstance()->getVisibleSize().height;
	backButton->setPosition(Point(Director::getInstance()->getVisibleSize().width - distanceConer, 
									Director::getInstance()->getVisibleSize().height - distanceConer));
	backButton->addTouchEventListener(CC_CALLBACK_2(CreditScene::GoToMainMenuScene,this));
	this->addChild(backButton);

	auto copyrightLogo = Sprite::create("mini/scene/copyright_logo.png");
	copyrightLogo->setScale(deltaScale);
	copyrightLogo->setPosition(Point(distanceConer,
		Director::getInstance()->getVisibleSize().height - distanceConer));
	this->addChild(copyrightLogo);


	auto underLogo = Sprite::create("mini/scene/title_logo.png");
	underLogo->setScale(deltaScale);
	underLogo->setPosition(Point(distanceConer,
		Director::getInstance()->getVisibleSize().height - distanceConer - copyrightLogo->getContentSize().height * 0.5 * deltaScale - 10 * deltaScale));
	this->addChild(underLogo);

	auto cloudSprite = Sprite::create("mini/scene/cloud.png");
	cloudSprite->setPosition(Point(cloudSprite->getContentSize().width * 0.5 * y + Director::getInstance()->getVisibleOrigin().x * 0.5, 
		Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y * 0.5));
	cloudSprite->setScale(y);
	this->addChild(cloudSprite);

	auto moveToLeft = MoveTo::create(15, Point(cloudSprite->getContentSize().width * y - Director::getInstance()->getVisibleSize().width, 
		Director::getInstance()->getVisibleSize().height * 0.5 + Director::getInstance()->getVisibleOrigin().y * 0.5));
	auto moveToRight = MoveTo::create(15, Point(cloudSprite->getPositionX(), Director::getInstance()->getVisibleSize().height * 0.5 + Director::getInstance()->getVisibleOrigin().y * 0.5));
	auto seq = Sequence::create(moveToLeft, moveToRight, nullptr);
	cloudSprite->runAction(RepeatForever::create(seq));

	return true;
}


void CreditScene::GoToMainMenuScene(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	ScreenManager::Instance()->gotoMainMenu();
}

