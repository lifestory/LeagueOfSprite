#pragma once
#ifndef ABOUTSCENE_H
#define ABOUTSCENE_H

#include "cocos2d.h"

#include "HelloWorldScene.h"

USING_NS_CC;

class AboutScene : public cocos2d::Scene {
public:
	AboutScene* createScene();
	virtual bool init();
	CREATE_FUNC(AboutScene);

	void ClickBack(Ref* sender);

private:
	MenuItemImage* back;
};
#endif // !ABOUTSCENE_H