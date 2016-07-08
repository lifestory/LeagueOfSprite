#pragma once
#ifndef HELPSCENE_H
#define HELPSCENE_H

#include "cocos2d.h"

#include "HelloWorldScene.h"

USING_NS_CC;

class HelpScene : public cocos2d::Scene {
public:
	static HelpScene* createScene();
	virtual bool init();
	CREATE_FUNC(HelpScene);

	void ClickBack(Ref* sender);

private:
	MenuItemImage *back;

};
#endif // !HELPSCENE_H