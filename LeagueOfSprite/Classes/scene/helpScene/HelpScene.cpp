#include "HelpScene.h"

HelpScene* HelpScene::createScene() {
	auto scene = HelpScene::create();
	return scene;
}

bool HelpScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("HelpScene/background.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	this->addChild(background);

	auto image = Sprite::create("HelpScene/gameManual.png");
	image->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(image, 1);

	back = MenuItemImage::create("HelpScene/backClickBefore.png", "HelpScene/backClickAfter.png", CC_CALLBACK_1(HelpScene::ClickBack, this));
	back->setPosition(visibleSize.width / 2, visibleSize.height*0.1);
	auto menu = Menu::create(back, NULL);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 1);

	return true;
}

void HelpScene::ClickBack(Ref* sender) {
	auto scene = HelloWorld::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}