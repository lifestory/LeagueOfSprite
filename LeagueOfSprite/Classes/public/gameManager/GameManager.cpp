#include "GameManager.h"

int GameManager::gameLevel = 1;
int GameManager::playerweapontype = 1;
int GameManager::player2weapontype = 1;

GameManager* GameManager::gameManager = NULL;

GameManager* GameManager::getInstance() {
	if (gameManager == NULL) {
		gameManager = new GameManager();
	}
	return gameManager;
}

int GameManager::getGameLevel() {
	return gameLevel;
}

void GameManager::setGameLevel(int level) {
	if (level <= 3) {
		gameLevel = level;
	}
	
}

int GameManager::getPlayweapon()
{
	return playerweapontype;
}
void GameManager::setPlayweapon(int type)
{
	playerweapontype = type;
}
int GameManager::getPlay2weapon()
{
	return player2weapontype;
}
void GameManager::setPlay2weapon(int type)
{
	player2weapontype = type;
}