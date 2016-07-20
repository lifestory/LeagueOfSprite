#include "LevelChooseScene.h"

LevelChooseScene* LevelChooseScene::createScene() {
	auto scene = LevelChooseScene::create();
	return scene;
}

bool LevelChooseScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("PlayScene/background.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background);

	auto title = Sprite::create("PlayScene/modeChooseScene/SingleMode/level.png");
	title->setPosition(visibleSize.width / 2, visibleSize.height*0.8);
	this->addChild(title);

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);

	back = MenuItemImage::create("PlayScene/backClickBefore.png", "PlayScene/backClickAfter.png", CC_CALLBACK_1(LevelChooseScene::ClickBack, this));
	back->setPosition(visibleSize.width / 2, visibleSize.height*0.1);
	menu->addChild(back);

	level1 = MenuItemImage::create("PlayScene/modeChooseScene/SingleMode/level1.png", "PlayScene/modeChooseScene/SingleMode/level1.png", CC_CALLBACK_1(LevelChooseScene::ClickLevel1, this));
	level1->setPosition(visibleSize.width*0.2, visibleSize.height / 2);
	//level1->setPosition(visibleSize.width*0.5, visibleSize.height/2);
	menu->addChild(level1);

	level2 = MenuItemImage::create("PlayScene/modeChooseScene/SingleMode/level2.png", "PlayScene/modeChooseScene/SingleMode/level2.png", CC_CALLBACK_1(LevelChooseScene::ClickLevel2, this));
	level2->setPosition(visibleSize.width * 0.5, visibleSize.height / 2);
	//level2->setPosition(visibleSize.width * 1.5, visibleSize.height / 2);
	menu->addChild(level2);

	level3 = MenuItemImage::create("PlayScene/modeChooseScene/SingleMode/level3.png", "PlayScene/modeChooseScene/SingleMode/level3.png", CC_CALLBACK_1(LevelChooseScene::ClickLevel3, this));
	level3->setPosition(visibleSize.width * 0.8, visibleSize.height / 2);
	//level3->setPosition(visibleSize.width * 2.5, visibleSize.height / 2);
	menu->addChild(level3);


	this->addChild(menu, 1);

	//add scrollview
	//this->setContentSize(Size(visibleSize.width * 3, visibleSize.height));
	//auto scrollView = cocos2d::ui::ScrollView::create();
	//scrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
	//scrollView->setInnerContainerSize(Size(visibleSize.width * 3, visibleSize.height));
	//scrollView->setInnerContainerPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//this->addChild(scrollView);
	//scrollView->setTouchEnabled(true);
	//scrollView->setPosition()
	//this->addChild(scrollView);
	return true;
}


void LevelChooseScene::ClickLevel1(Ref *sender) {
	SimpleAudioEngine::getInstance()->playEffect("Sound/Click.wav");
	auto scene = GameScene::create();
	Director::getInstance()->replaceScene(scene);
}

void LevelChooseScene::ClickLevel2(Ref *sender) {

}

void LevelChooseScene::ClickLevel3(Ref *sender) {

}

void LevelChooseScene::ClickBack(Ref *sender) {
	auto scene = ModeChooseScene::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}