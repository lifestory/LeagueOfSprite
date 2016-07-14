#pragma once
#ifndef SETTINGSCENE_H
#define SETTINGSCENE_H

#include "cocos2d.h"

#include "HelloWorldScene.h"
#include "SoundManager.h"

USING_NS_CC;

class SettingScene : public cocos2d::Scene {
public:
	static SettingScene* getInstance();
	static SettingScene* createScene();
	virtual bool init();
	CREATE_FUNC(SettingScene);

	void ClickBack(Ref* sender);
	void onMusicEnabled(Ref* sender);
	void onEffectEnabled(Ref* sender);

private:
	static SettingScene* settingScene;
	MenuItemImage *back;
	MenuItemToggle *musicControl;
	MenuItemToggle *effectControl;

	Menu *menu;

};

#endif // !SETTINGSCENE_H