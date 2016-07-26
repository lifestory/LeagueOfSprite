#include "GameManager.h"

int GameManager::gameLevel = 1;

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