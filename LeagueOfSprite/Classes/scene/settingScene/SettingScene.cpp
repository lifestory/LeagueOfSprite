#include "SettingScene.h"

SettingScene* SettingScene::settingScene = NULL;

SettingScene* SettingScene::getInstance() {
	return settingScene;
}

SettingScene* SettingScene::createScene() {
	auto scene = SettingScene::create();
	settingScene = scene;
	return scene;
}

bool SettingScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("SettingScene/background.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background);

	auto label = Label::createWithSystemFont("Setting", "Arial", 40);
	label->setPosition(visibleSize.width/2, visibleSize.height*0.8);
	this->addChild(label, 1);

	auto labelMusic = Label::createWithSystemFont("Music", "Arial", 30);
	labelMusic->setPosition(visibleSize.width*0.4, visibleSize.height*0.6);
	this->addChild(labelMusic, 1);

	auto labelSound = Label::createWithSystemFont("Sound", "Arial", 30);
	labelSound->setPosition(visibleSize.width*0.4, visibleSize.height*0.5);
	this->addChild(labelSound, 1);

	menu = Menu::create();
	menu->setPosition(Vec2::ZERO);

	back = MenuItemImage::create("SettingScene/backClickBefore.png", "SettingScene/backClickAfter.png", CC_CALLBACK_1(SettingScene::ClickBack, this));
	back->setPosition(visibleSize.width / 2, visibleSize.height*0.1);

	auto musicOn = MenuItemImage::create("SettingScene/on.png", "SettingScene/off.png");
	auto musicOff = MenuItemImage::create("SettingScene/off.png", "SettingScene/on.png");

	auto effectOn = MenuItemImage::create("SettingScene/on.png", "SettingScene/off.png");
	auto effectOff = MenuItemImage::create("SettingScene/off.png", "SettingScene/on.png");

	musicControl = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::onMusicEnabled, this),musicOn, musicOff, NULL);
	musicControl->setPosition(visibleSize.width*0.6, visibleSize.height*0.6);
	effectControl = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::onEffectEnabled, this), effectOn, effectOff, NULL);
	effectControl->setPosition(visibleSize.width*0.6, visibleSize.height*0.5);

	menu->addChild(back, 1);
	menu->addChild(musicControl, 1);
	menu->addChild(effectControl, 1);

	this->addChild(menu, 1);

	return true;
}

void SettingScene::ClickBack(Ref* sender) {
	auto hello = HelloWorld::createScene();
	auto trans = TransitionPageTurn::create(0.5f, hello, false);
	Director::getInstance()->pushScene(trans);
}

void SettingScene::onMusicEnabled(Ref* sender) {
	SoundManager::getInstance()->turnOnOffMusic(musicControl->getSelectedIndex());
}

void SettingScene::onEffectEnabled(Ref* sender) {
	SoundManager::getInstance()->turnOnOffEffect(effectControl->getSelectedIndex());
}