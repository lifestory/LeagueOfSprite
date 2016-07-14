#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

HelloWorld* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = HelloWorld::create();
    

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);*/

	//play background music
	//SoundManager::getInstance()->startSceneinit();

	auto background = Sprite::create("StartScene/startScene.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background);

	menu = Menu::create();
	menu->setPosition(Vec2::ZERO);

	playItem = MenuItemImage::create("StartScene/playClickBefore.png", "StartScene/playClickAfter.png", CC_CALLBACK_1(HelloWorld::ClickPlay, this));
	playItem->setPosition(visibleSize.width / 2, visibleSize.height*0.15);
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
	//auto settingScene = SettingScene::createScene();
	//auto trans = TransitionPageTurn::create(0.5f, settingScene, false);
	if (SettingScene::getInstance() == NULL) {
		auto settingScene = SettingScene::createScene();
		auto trans = TransitionPageTurn::create(0.5f, settingScene, false);
		Director::getInstance()->replaceScene(trans);
	} else {
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