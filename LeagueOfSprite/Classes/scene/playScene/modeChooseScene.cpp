#include "modeChooseScene.h"

ModeChooseScene* ModeChooseScene::createScene() {
	auto scene = ModeChooseScene::create();
	return scene;
}

bool ModeChooseScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("PlayScene/background.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background);

	auto title = Sprite::create("PlayScene/modeChooseScene/mode.png");
	title->setPosition(visibleSize.width / 2, visibleSize.height*0.8);
	this->addChild(title);

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);

	back = MenuItemImage::create("PlayScene/backClickBefore.png", "PlayScene/backClickAfter.png", CC_CALLBACK_1(ModeChooseScene::ClickBack, this));
	back->setPosition(visibleSize.width / 2, visibleSize.height*0.1);
	menu->addChild(back);
	
	singleMode = MenuItemImage::create("PlayScene/modeChooseScene/singleClickBefore.png", "PlayScene/modeChooseScene/singleClickAfter.png", CC_CALLBACK_1(ModeChooseScene::ClickSingle, this));
	singleMode->setPosition(visibleSize.width / 2, visibleSize.height*0.6);
	menu->addChild(singleMode);

	soloMode = MenuItemImage::create("PlayScene/modeChooseScene/soloClickBefore.png", "PlayScene/modeChooseScene/soloClickAfter.png", CC_CALLBACK_1(ModeChooseScene::ClickSolo, this));
	soloMode->setPosition(visibleSize.width / 2, visibleSize.height*0.4);
	menu->addChild(soloMode);
		
	this->addChild(menu, 1);

	return true;
}

void ModeChooseScene::ClickBack(Ref *sender) {
	SimpleAudioEngine::getInstance()->playEffect("Sound/Click.wav");
	auto scene = HelloWorld::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}

void ModeChooseScene::ClickSingle(Ref *sender) {
	SimpleAudioEngine::getInstance()->playEffect("Sound/Click.wav");
	auto scene = LevelChooseScene::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}

void ModeChooseScene::ClickSolo(Ref *sender) {
	SimpleAudioEngine::getInstance()->playEffect("Sound/Click.wav");
	auto scene = SoloScene::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}