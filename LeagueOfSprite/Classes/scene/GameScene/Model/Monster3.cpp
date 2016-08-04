#include "Monster3.h"

enum  direction {
	left = 0,
	right,
	up,
	down
};

enum actionDir
{
	moveLeft = 0,
	moveRight,
	moveUp,
	moveDown
};

Monster3* Monster3::monster3_ = NULL;

Monster3* Monster3::getInstance() {
	if (monster3_ == NULL) {
		monster3_ = Monster3::create();
	}
	return monster3_;
}

bool Monster3::init() {
	if (!Sprite::init()) {
		return false;
	}


	//standing animation
	auto standing = Animation::create();
	for (int i = 1; i < 5; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Monster3/stand/stand_%d.png", i);
		standing->addSpriteFrameWithFileName(filename);
	}
	standing->setDelayPerUnit(0.2f);
	standingAction = Animate::create(standing);
	standAnimate = Sprite::create("Model/Monster3/stand/stand_1.png");
	standAnimate->runAction(RepeatForever::create(standingAction));
	this->addChild(standAnimate, 1);

	//attacking animation
	auto attacking = Animation::create();
	for (int i = 1; i < 4; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Monster3/attack/attack_%d.png", i);
		attacking->addSpriteFrameWithFileName(filename);
	}
	attacking->setDelayPerUnit(0.15f);
	attackingAction = Animate::create(attacking);
	attackAnimate = Sprite::create("Model/Monster3/attack/attack_1.png");
	attackAnimate->runAction(RepeatForever::create(attackingAction));
	attackAnimate->setVisible(false);
	this->addChild(attackAnimate, 1);

	//injuring animation
	auto injuring = Animation::create();
	for (int i = 1; i < 4; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Monster3/injured/injured_%d.png", i);
		injuring->addSpriteFrameWithFileName(filename);
	}
	injuring->setDelayPerUnit(0.2f);
	injuringAction = Animate::create(injuring);
	injuredAnimate = Sprite::create("Model/Monster3/injured/injured_1.png");
	injuredAnimate->runAction(RepeatForever::create(injuringAction));
	injuredAnimate->setVisible(false);
	this->addChild(injuredAnimate, 1);

	auto body = PhysicsBody::createBox(standAnimate->getContentSize()*0.8, PhysicsMaterial(0.8f, 0.0f, 0.99f));
	body->setRotationEnable(false);
	body->setVelocityLimit(200);
	this->setPhysicsBody(body);
	this->getPhysicsBody()->setTag(Constant::getMonster3Tag());
	this->getPhysicsBody()->setCategoryBitmask(0x000000FF);
	this->getPhysicsBody()->setCollisionBitmask(0x0000000F);
	this->getPhysicsBody()->setContactTestBitmask(0x0000000F);

	//init status  basic attribute
	maxhp = 100;
	curhp = 100;
	basicDamage = 20;

	return true;
}

void Monster3::beingHit() {
	standAnimate->setVisible(false);
	injuredAnimate->setVisible(true);
	auto delay = DelayTime::create(0.2f);
	auto sq = Sequence::create(injuringAction, delay, CallFunc::create(CC_CALLBACK_0(Monster3::restoreStand, this)), NULL);

	injuredAnimate->runAction(sq);
}

void Monster3::attacking() {
	standAnimate->setVisible(false);
	attackAnimate->setVisible(true);
	//auto delay = DelayTime::create(0.2f);
	auto sq = Sequence::create(attackingAction, CallFunc::create(CC_CALLBACK_0(Monster3::restoreStand, this)), NULL);
	attackAnimate->runAction(sq);
}

void Monster3::restoreStand() {
	standAnimate->setVisible(true);
	injuredAnimate->setVisible(false);
	attackAnimate->setVisible(false);
}

void Monster3::releaseMonster3() {
	if (monster3_ != NULL) {
		//Monster3_->removeAllChildrenWithCleanup(true);
		monster3_->removeFromParentAndCleanup(true);
		monster3_ = NULL;
	}
}

void Monster3::setHp(int value) {
	curhp = value;
}

int Monster3::getHp() {
	return curhp;
}

void Monster3::setBasicDamage(int damage) {
	basicDamage = damage;
}

int Monster3::getBasicDamage() {
	return basicDamage;
}

void Monster3::run(int direc, float speed)
{
	if (direc == direction::left) {
		if (monster3_->getPositionX() <= 512 + 20)
		{
			//monster_->setPositionX(512);
		}
		else {
			auto action = MoveBy::create(1, Vec2(-speed, 0));
			action->setTag(actionDir::moveLeft);
			monster3_->runAction(action);
		}
	}
	else if (direc == direction::right) {
		if (monster3_->getPositionX() >= 1024 - 20)
		{
			//monster_->setPositionX(1000);
		}
		else {
			auto action = MoveBy::create(1, Vec2(speed, 0));
			action->setTag(actionDir::moveRight);
			monster3_->runAction(action);
		}
	}
	else if (direc == direction::up) {
		auto action = MoveBy::create(0.5, Vec2(0, speed * 10));
		action->setTag(actionDir::moveUp);
		monster3_->runAction(action);
	}
	else if (direc == direction::down) {
		auto action = MoveBy::create(0.5, Vec2(0, -speed));
		action->setTag(actionDir::moveDown);
		monster3_->runAction(action);
	}
}
