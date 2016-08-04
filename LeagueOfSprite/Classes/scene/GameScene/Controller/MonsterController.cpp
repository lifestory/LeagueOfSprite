#include "MonsterController.h"

enum  direction {
	left = 0,
	right,
	up,
	down
};

int dir = 0;

MonsterController* MonsterController::monsterController = NULL;

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

Monster2* MonsterController::getMonster2() {
	return monster2;
}

Monster3* MonsterController::getMonster3() {
	return monster3;
}

bool MonsterController::init() {
	if (!Layer::init()) {
		return false;
	}

	//init level
	if (GameManager::getInstance()->getGameLevel() == 1) {
		monster = Monster::getInstance();
		monster->setPosition(800, 200);
		this->addChild(monster, 1);
		this->schedule(schedule_selector(MonsterController::monsterUpdate), 0.1f);
		this->schedule(schedule_selector(MonsterController::monsterShoot), 4.0f);
	}
	else if (GameManager::getInstance()->getGameLevel() == 2) {
		monster2 = Monster2::getInstance();
		monster2->setPosition(800, 200);
		this->addChild(monster2, 1);
		this->schedule(schedule_selector(MonsterController::monster2Update), 0.2f);
		this->schedule(schedule_selector(MonsterController::monster2Shoot), 3.0f);
	} else if (GameManager::getInstance()->getGameLevel() == 3) {
		monster3 = Monster3::getInstance();
		monster3->setPosition(800, 200);
		this->addChild(monster3, 1);
		this->schedule(schedule_selector(MonsterController::monster3Update), 0.1f);
		this->schedule(schedule_selector(MonsterController::monster3Shoot), 2.0f);
	}


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
		monsterController->getMonster2()->releaseMonster2();
		monsterController->getMonster3()->releaseMonster3();
		monsterController->removeAllChildrenWithCleanup(true);
		monsterController->removeFromParentAndCleanup(true);
		monsterController = NULL;
	}
}

void MonsterController::updateBloodbarforDamaging(int damage, int type) {
	int tempHp;
	if (type == Constant::getMonsterTag()) {
		tempHp = monster->getHp();
	} else if (type == Constant::getMonster2Tag()) {
		tempHp = monster2->getHp();
	} else if (type == Constant::getMonster3Tag()) {
		tempHp = monster3->getHp();
	}

	if (tempHp >= damage) {
		bloodbar->setCurrentProgress(tempHp - damage);
	} else {
		bloodbar->setCurrentProgress(-1);
	}
}

void MonsterController::updateBlood(int value, int type) {
	if (type == Constant::getMonsterTag()) {
		if (value > 0) {
			monster->setHp(value);
		}
		else {
			monster->setHp(0);
		}
	}
	else if (type == Constant::getMonster2Tag()) {
		if (value > 0) {
			monster2->setHp(value);
		}
		else {
			monster2->setHp(0);
		}
	}
	else if (type == Constant::getMonster3Tag()) {
		if (value > 0) {
			monster3->setHp(value);
		}
		else {
			monster3->setHp(0);
		}
	}
}

ProgressView* MonsterController::getBloodBar() {
	return bloodbar;
}


void MonsterController::monsterUpdate(float t)
{
	if (dir == 0)
	{
		monster->run(direction::left, 10);
		if (monster->getPositionX() < 662)
		{
			dir = 1;
		}
	}
	else if (dir == 1)
	{
		monster->run(direction::right, 10);
		if (monster->getPositionX() > 874)
		{
			dir = 0;
		}
	}
}

void MonsterController::monsterShoot(float t)
{
	this->addChild(Weapon::newMonsterWeapon(monster->getPosition(), 100, Constant::getMonsterArrowTag()));
	monster->attacking();
}

void MonsterController::monster2Update(float t)
{
	float f = CCRANDOM_0_1() * 4;

	if (f >= 3 && monster2->getPositionY() < 115)
	{
		monster2->run(direction::up, 15);
	}
	else {
		if (dir == 0)
		{
			monster2->run(direction::left, 15);
			if (monster2->getPositionX() < 662)
			{
				dir = 1;
			}
		}
		else if (dir == 1)
		{
			monster2->run(direction::right, 15);
			if (monster2->getPositionX() > 874)
			{
				dir = 0;
			}
		}
	}
}

void MonsterController::monster2Shoot(float t)
{
	this->addChild(Weapon::newMonsterWeapon(monster2->getPosition(), 100, Constant::getMonster2ArrowTag()));
	this->addChild(Weapon::newMonsterWeapon(monster2->getPosition(), 80, Constant::getMonster2ArrowTag()));
	monster2->attacking();
}

void MonsterController::monster3Update(float t)
{
	float f = CCRANDOM_0_1() * 4;
	if (f >= 2.5 && monster3->getPositionY() < 115)
	{
		monster3->run(direction::up, 25);
	}
	else {
		if (dir == 0)
		{
			monster3->run(direction::left, 25);
			if (monster3->getPositionX() < 662)
			{
				dir = 1;
			}
		}
		else if (dir == 1)
		{
			monster3->run(direction::right, 25);
			if (monster3->getPositionX() > 874)
			{
				dir = 0;
			}
		}
	}
}

void MonsterController::monster3Shoot(float t)
{
	float f = CCRANDOM_0_1() * 4;
	if (f > 3.2)
	{
		this->addChild(Weapon::newMonsterWeapon(monster3->getPosition(), 100, Constant::getMonster3ArrowTag()));
		this->addChild(Weapon::newMonsterWeapon(monster3->getPosition(), 90, Constant::getMonster3ArrowTag()));
		this->addChild(Weapon::newMonsterWeapon(monster3->getPosition(), 80, Constant::getMonster3ArrowTag()));
		this->addChild(Weapon::newMonsterWeapon(monster3->getPosition(), 110, Constant::getMonster3ArrowTag()));
		this->addChild(Weapon::newMonsterWeapon(monster3->getPosition(), 70, Constant::getMonster3ArrowTag()));
	}
	else if (f < 0.8)
	{
		for (int i = 10; i < 180; i = i + 20)
		{
			this->addChild(Weapon::newMonsterWeapon(monster3->getPosition(), i, Constant::getMonster3ArrowTag()));
		}
	}
	else
	{
		this->addChild(Weapon::newMonsterWeapon(monster3->getPosition(), 40, Constant::getMonster3ArrowTag()));
		this->addChild(Weapon::newMonsterWeapon(monster3->getPosition(), 120, Constant::getMonster3ArrowTag()));
		this->addChild(Weapon::newMonsterWeapon(monster3->getPosition(), 80, Constant::getMonster3ArrowTag()));
	}

	monster3->attacking();
}