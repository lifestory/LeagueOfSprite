#pragma once
#ifndef MODECHOOSESCENE_H
#define MODECHOOSESCENE_H

#include "cocos2d.h"

#include "HelloWorldScene.h"
#include "LevelChooseScene.h"
#include ".\scene\playScene\SoloMode\soloscene.h"


USING_NS_CC;

class ModeChooseScene : public cocos2d::Scene {
public:
	static ModeChooseScene* createScene();
	virtual bool init();
	CREATE_FUNC(ModeChooseScene);

	void ClickBack(Ref* sender);
	void ClickSingle(Ref* sender);
	void ClickSolo(Ref* sender);

private:
	MenuItemImage *back;
	MenuItemImage *singleMode;
	MenuItemImage *soloMode;

};
#endif // !MODECHOOSESCENE_H