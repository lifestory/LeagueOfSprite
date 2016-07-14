#pragma once

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "SettingScene.h"
#include "HelpScene.h"
#include "AboutScene.h"
#include "modeChooseScene.h"
#include "SoundManager.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
    static HelloWorld* createScene();

    virtual bool init();
    
	void cleanup();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void ClickPlay(Ref* sender);
	void ClickHelp(Ref* sender);
	void ClickSetting(Ref* sender);
	void ClickAbout(Ref* sender);

private:
	MenuItemImage *playItem;
	MenuItemImage *helpItem;
	MenuItemImage *settingItem;
	MenuItemImage *aboutItem;
	Menu *menu;

};

#endif // __HELLOWORLD_SCENE_H__
