#pragma once
#ifndef LEVELCHOOSESCENE_H
#define LEVELCHOOSESCENE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
//#include "cocos-ext.h"
//#include "ui\CocosGUI.h"

#include "modeChooseScene.h"
#include "GameScene.h"

//USING_NS_CC_EXT;
USING_NS_CC;

//using namespace cocos2d::extension;
//const int TOUCH_DISTANCE = 100;

class LevelChooseScene : public cocos2d::Scene {
public:
	static LevelChooseScene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelChooseScene);

	

	//void onTouchEnded(Touch*touch, Event *unused_event);
	//bool onTouchBegan(Touch * touch, Event *unused_event);
	//void onTouchMoved(Touch *touch, Event *unused_event);

	//void addScrollView();

	void ClickLevel1(Ref* sender);
	void ClickLevel2(Ref* sender);
	void ClickLevel3(Ref* sender);
	void ClickBack(Ref* sender);

private:
	int currentLevel;
	MenuItemImage *back;
	MenuItemImage *level1;
	MenuItemImage *level2;
	MenuItemImage *level3;
	
};
#endif // !LEVELCHOOSESCENE_H