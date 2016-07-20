#pragma once
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "cocos2d.h"

#include "PlayerController.h"
#include "MonsterController.h"
#include "GamePause.h"

USING_NS_CC;

class GameController : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameController);
	static cocos2d::Scene* scene(RenderTexture* sqr);

	void clickAgain();
	void clickNext();
	void clickMenu();

private:
	MenuItemImage *again;
	MenuItemImage *back;
	MenuItemImage *next;
	Menu *menu;
};

#endif // !GAMECONTROLLER_H