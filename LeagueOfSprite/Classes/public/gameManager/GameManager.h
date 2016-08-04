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

	int getPlayweapon();
	void setPlayweapon(int type);
	int getPlay2weapon();
	void setPlay2weapon(int type);

private:
	static int gameLevel;
	static int playerweapontype;
	static int player2weapontype;
	static GameManager* gameManager;
};

#endif