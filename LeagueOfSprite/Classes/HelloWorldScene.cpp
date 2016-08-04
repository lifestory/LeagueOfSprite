#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

HelloWorld* HelloWorld::createScene()
{
	auto scene = HelloWorld::create();
	return scene;
}

bool HelloWorld::init()
{
    if (!Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//play background music
	SoundManager::getInstance()->startSceneinit();

	auto background = Sprite::create("StartScene/startScene.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background);

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);

	playItem = MenuItemImage::create("StartScene/playClickBefore.png", "StartScene/playClickAfter.png", CC_CALLBACK_1(HelloWorld::ClickPlay, this));
	playItem->setPosition(visibleSize.width -playItem->getContentSize().width/2, visibleSize.height*0.4);
	menu->addChild(playItem, 1);

	helpItem = MenuItemImage::create("StartScene/helpClickBefore.png", "StartScene/helpClickAfter.png", CC_CALLBACK_1(HelloWorld::ClickHelp, this));
	helpItem->setPosition(visibleSize.width - helpItem->getContentSize().width / 2, visibleSize.height*0.3);
	menu->addChild(helpItem, 1);

	settingItem = MenuItemImage::create("StartScene/setClickBefore.png", "StartScene/setClickAfter.png", CC_CALLBACK_1(HelloWorld::ClickSetting, this));
	settingItem->setPosition(visibleSize.width - settingItem->getContentSize().width / 2, visibleSize.height*0.2);
	menu->addChild(settingItem, 1);

	aboutItem = MenuItemImage::create("StartScene/aboutClickBefore.png", "StartScene/aboutClickAfter.png", CC_CALLBACK_1(HelloWorld::ClickAbout, this));
	aboutItem->setPosition(visibleSize.width - aboutItem->getContentSize().width / 2, visibleSize.height*0.1);
	menu->addChild(aboutItem, 1);

	this->addChild(menu, 1);


    
    return true;
}


void HelloWorld::ClickPlay(Ref *sender) {
	auto scene = ModeChooseScene::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
	if (SoundManager::getInstance()->getEffect()) {
		SimpleAudioEngine::getInstance()->playEffect("Sound/Click.wav");
	}
}

void HelloWorld::ClickHelp(Ref *sender) {
	auto scene = HelpScene::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
	if (SoundManager::getInstance()->getEffect()) {
		SimpleAudioEngine::getInstance()->playEffect("Sound/Click.wav");
	}
}

void HelloWorld::ClickSetting(Ref *sender) {
	if (SettingScene::getInstance() == NULL) {
		auto settingScene = SettingScene::createScene();
		auto trans = TransitionPageTurn::create(0.5f, settingScene, false);
		Director::getInstance()->replaceScene(trans);
	}
	else {
		Director::getInstance()->popScene();
	}
	if (SoundManager::getInstance()->getEffect()) {
		SimpleAudioEngine::getInstance()->playEffect("Sound/Click.wav");
	}

}

void HelloWorld::ClickAbout(Ref *sender) {
	auto aboutScene = AboutScene::create();
	auto trans = TransitionPageTurn::create(0.5f, aboutScene, false);
	Director::getInstance()->replaceScene(trans);
	if (SoundManager::getInstance()->getEffect()) {
		SimpleAudioEngine::getInstance()->playEffect("Sound/Click.wav");
	}
}

void HelloWorld::cleanup() {
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}