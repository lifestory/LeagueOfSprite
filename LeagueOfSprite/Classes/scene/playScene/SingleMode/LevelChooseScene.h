#pragma once
#ifndef LEVELCHOOSESCENE_H
#define LEVELCHOOSESCENE_H

#include "cocos2d.h"

#include "modeChooseScene.h"
#include "GameScene.h"

USING_NS_CC;

class LevelChooseScene : public cocos2d::Scene {
public:
	static LevelChooseScene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelChooseScene);

	void ClickLevel1(Ref* sender);
	void ClickLevel2(Ref* sender);
	void ClickLevel3(Ref* sender);
	void ClickBack(Ref* sender);

private:
	MenuItemImage *back;
	MenuItemImage *level1;
	MenuItemImage *level2;
	MenuItemImage *level3;

};
#endif // !LEVELCHOOSESCENE_H