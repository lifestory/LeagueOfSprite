#pragma once
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "cocos2d.h"

#include "PlayerController.h"
#include "MonsterController.h"
#include ".\scene\GameScene\GamePause.h"
#include ".\public\Constant.h"

USING_NS_CC;

class GameController : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameController);

	static GameController* getInstance();

	cocos2d::Scene* scene(RenderTexture* sqr, int stauts, int mode);
	Layer* createWinLayer();
	Layer* createLoseLayer();
	Layer* createPlayerWinLayer();
	Layer* createPlayer2WinLayer();

	void clickAgain();
	void clickNext();
	void clickMenu();

	void soloclickAgain();
	void soloclickNext();
	void soloclickMenu();

	void setGameStatus(int status);
	int getGameStatus();

private:
	static GameController* gameController;
	//game status
	int gameStatus;
};

#endif // !GAMECONTROLLER_H