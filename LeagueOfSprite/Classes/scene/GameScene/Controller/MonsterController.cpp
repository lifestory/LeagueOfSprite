#include "MonsterController.h"

MonsterController* MonsterController::monsterController = NULL;
//Monster* MonsterController::monster = NULL;

MonsterController* MonsterController::getInstance() {
	if (monsterController == NULL) {
		monsterController = MonsterController::create();
		monsterController->setPosition(800, 200);
		monsterController->setAnchorPoint(Point::ZERO);
	}
	return monsterController;
}

Monster* MonsterController::getMonster() {
	return monster;
}

bool MonsterController::init() {
	if (!Layer::init()) {
		return false;
	}

	monster = Monster::getInstance();
	this->addChild(monster, 1);

	return true;
}