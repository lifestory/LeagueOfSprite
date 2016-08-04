#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include ".\scene\settingScene\SettingScene.h"
#include ".\scene\helpScene\HelpScene.h"
#include ".\scene\aboutScene\AboutScene.h"
#include ".\scene\playScene\modeChooseScene.h"
#include ".\public\soundManager\SoundManager.h"
#include ".\public\gameManager\GameManager.h"
#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::Scene
{
public:
	static HelloWorld* createScene();

    virtual bool init();
    
    // a selector callback
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
