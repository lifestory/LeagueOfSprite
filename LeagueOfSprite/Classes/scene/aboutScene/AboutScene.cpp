#include "AboutScene.h"

AboutScene* AboutScene::createScene() {
	auto scene = AboutScene::create();
	return scene;
}

bool AboutScene::init() {
	if (!Scene::create()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bk = Sprite::create("AboutScene/background.png");
	bk->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bk);

	/*auto manual = Sprite::create("AboutScene/gameManual.png");
	manual->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(manual, 1);*/

	back = MenuItemImage::create("AboutScene/backClickBefore.png", "AboutScene/backClickAfter.png", CC_CALLBACK_1(AboutScene::ClickBack, this));
	back->setPosition(visibleSize.width / 2, visibleSize.height*0.1);

	auto menu = Menu::create(back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void AboutScene::ClickBack(Ref* sender) {
	auto scene = HelloWorld::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}