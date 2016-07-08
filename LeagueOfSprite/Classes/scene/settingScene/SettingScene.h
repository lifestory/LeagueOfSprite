#pragma once
#ifndef SETTINGSCENE_H
#define SETTINGSCENE_H

#include "cocos2d.h"

#include "HelloWorldScene.h"

USING_NS_CC;

class SettingScene : public cocos2d::Scene {
public:
	static SettingScene* createScene();
	virtual bool init();
	CREATE_FUNC(SettingScene);

	void ClickBack(Ref* sender);
	void onMusicEnabled(Ref* sender);
	void onEffectEnabled(Ref* sender);

private:
	MenuItemImage *back;
	MenuItemToggle *musicControl;
	MenuItemToggle *effectControl;

	Menu *menu;

};

#endif // !SETTINGSCENE_H