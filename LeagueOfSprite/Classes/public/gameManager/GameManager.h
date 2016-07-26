#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "cocos2d.h"

USING_NS_CC;

class GameManager {
public:
	static GameManager* getInstance();
	int getGameLevel();
	void setGameLevel(int level);
private:
	static int gameLevel;
	static GameManager* gameManager;
};

#endif