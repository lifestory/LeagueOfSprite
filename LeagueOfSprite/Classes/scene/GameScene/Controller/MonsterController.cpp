#include "MonsterController.h"

MonsterController* MonsterController::monsterController = NULL;
//Monster* MonsterController::monster = NULL;

MonsterController* MonsterController::getInstance() {
	if (monsterController == NULL) {
		monsterController = MonsterController::create();
		monsterController->setPosition(Vec2::ZERO);
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
	monster->setPosition(800, 200);
	this->addChild(monster, 1);

	//create bloodbar
	bloodbar = new ProgressView();
	bloodbar->setPosition(Point(820, 600));
	bloodbar->setScale(3.0f);
	bloodbar->setBackgroundTexture("GameScene/ProgressView/back.png");
	bloodbar->setFrontgroundTexture("GameScene/ProgressView/front.png");
	bloodbar->setTotalProgress(100);
	bloodbar->setCurrentProgress(100);
	auto edge = Sprite::create("GameScene/ProgressView/edge.png");
	edge->setPosition(Point(bloodbar->getPositionX(), bloodbar->getPositionY()));
	auto avatar = Sprite::create("GameScene/ProgressView/monster_avatar.png");
	avatar->setPosition(Point(bloodbar->getPositionX() + 150, bloodbar->getPositionY()));
	this->addChild(avatar, 2);
	this->addChild(bloodbar, 2);

	return true;
}

void MonsterController::releaseMonsterController() {
	if (monsterController != NULL) {
		monsterController->getMonster()->releaseMonster();
		monsterController->removeAllChildrenWithCleanup(true);
		monsterController->removeFromParentAndCleanup(true);
		monsterController = NULL;
	}
}

void MonsterController::updateBloodbarforDamaging(int damage) {
	int monsterHp = monster->getHp();
	if (monsterHp >= damage) {
		bloodbar->setCurrentProgress(monsterHp - damage);
	} else {
		bloodbar->setCurrentProgress(0);
	}
}

void MonsterController::updateBlood(int value) {
	if (value > 0) {
		monster->setHp(value);
	} else {
		monster->setHp(0);
	}
	
}