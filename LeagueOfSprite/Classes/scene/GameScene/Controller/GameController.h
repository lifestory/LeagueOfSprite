#pragma once
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "cocos2d.h"

#include "PlayerController.h"
#include "MonsterController.h"
#include "GamePause.h"
#include "Constant.h"

USING_NS_CC;

class GameController : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameController);

	static GameController* getInstance();

	cocos2d::Scene* scene(RenderTexture* sqr, int stauts);
	Layer* createWinLayer();
	Layer* createLoseLayer();

	void clickAgain();
	void clickNext();
	void clickMenu();

	void setGameStatus(int status);
	int getGameStatus();

private:
	/*MenuItemImage *again;
	MenuItemImage *back;
	MenuItemImage *next;
	Menu *menu;*/
	
	static GameController* gameController;
	//game status
	int gameStatus;
};

#endif // !GAMECONTROLLER_H