#pragma once
#ifndef LEVELCHOOSESCENE_H
#define LEVELCHOOSESCENE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
//#include "cocos-ext.h"
//#include "ui\CocosGUI.h"

#include ".\scene\playScene\modeChooseScene.h"
#include ".\scene\GameScene\GameScene.h"
#include ".\public\gameManager\GameManager.h"

//USING_NS_CC_EXT;
USING_NS_CC;

//using namespace cocos2d::extension;
//const int TOUCH_DISTANCE = 100;

class LevelChooseScene : public cocos2d::Scene {
public:
	static LevelChooseScene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelChooseScene);

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