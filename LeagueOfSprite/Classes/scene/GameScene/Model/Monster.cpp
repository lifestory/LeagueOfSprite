#include "Monster.h"

Monster* Monster::monster_ = NULL;

Monster* Monster::getInstance() {
	if (monster_ == NULL) {
		monster_ = Monster::create();
	}
	return monster_;
}

bool Monster::init() {
	if (!Sprite::init()) {
		return false;
	}


	//standing animation
	auto standing = Animation::create();
	for (int i = 0; i < 3; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Monster/stand/stand_%d.png", i);
		standing->addSpriteFrameWithFileName(filename);
	}
	standing->setDelayPerUnit(0.2f);
	standingAction = Animate::create(standing);
	standAnimate = Sprite::create("Model/Monster/stand/stand_0.png");
	standAnimate->runAction(RepeatForever::create(standingAction));
	this->addChild(standAnimate, 1);

	//attacking animation
	/*auto attacking = Animation::create();
	for (int i = 0; i < 1; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Monster/stand/attack_%d.png", i);
		attacking->addSpriteFrameWithFileName(filename);
	}
	attacking->setDelayPerUnit(0.5f);
	auto attackingAction = Animate::create(attacking);
	attackAnimate = Sprite::create("Model/Monster/stand/attack_0.png");
	attackAnimate->runAction(RepeatForever::create(attackingAction));
	attackAnimate->setVisible(false);
	this->addChild(attackAnimate, 1);*/

	//injuring animation
	auto injuring = Animation::create();
	for (int i = 0; i < 1; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Monster/injured/injured_%d.png", i);
		injuring->addSpriteFrameWithFileName(filename);
	}
	injuring->setDelayPerUnit(0.2f);
	injuringAction = Animate::create(injuring);
	injuredAnimate = Sprite::create("Model/Monster/injured/injured_0.png");
	injuredAnimate->runAction(RepeatForever::create(injuringAction));
	injuredAnimate->setVisible(false);
	this->addChild(injuredAnimate, 1);

	//forwarding animation
	/*auto forwarding = Animation::create();
	for (int i = 0; i < 1; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Monster/stand/stand_%d.png", i);
		forwarding->addSpriteFrameWithFileName(filename);
	}
	forwarding->setDelayPerUnit(0.5f);
	auto forwardingAction = Animate::create(forwarding);
	forwardAnimate = Sprite::create("Model/Monster/forward/forward_0.png");
	forwardAnimate->runAction(RepeatForever::create(forwardingAction));
	forwardAnimate->setVisible(false);
	this->addChild(forwardAnimate, 1);*/

	auto body = PhysicsBody::createBox(standAnimate->getContentSize()*0.8, PhysicsMaterial(0.99f, 0.0f, 0.99f));
	body->setRotationEnable(false);
	//body->setDynamic(false);
	body->setVelocityLimit(200);
	this->setPhysicsBody(body);
	this->getPhysicsBody()->setTag(Constant::getMonsterTag());
	this->getPhysicsBody()->setCategoryBitmask(0x000000FF);
	this->getPhysicsBody()->setCollisionBitmask(0x0000000F);
	this->getPhysicsBody()->setContactTestBitmask(0x0000000F);

	//init status
	maxhp = 100;
	curhp = 100;

	return true;
}

void Monster::beingHit() {
	standAnimate->setVisible(false);
	injuredAnimate->setVisible(true);
	auto delay = DelayTime::create(0.2f);
	auto sq = Sequence::create(injuringAction, delay, CallFunc::create(CC_CALLBACK_0(Monster::restoreStand, this)), NULL);
	
	injuredAnimate->runAction(sq);
}

void Monster::restoreStand() {
	standAnimate->setVisible(true);
	injuredAnimate->setVisible(false);
}

void Monster::releaseMonster() {
	if (monster_ != NULL) {
		//monster_->removeAllChildrenWithCleanup(true);
		monster_->removeFromParentAndCleanup(true);
		monster_ = NULL;
	}
}

void Monster::setHp(int value) {
	curhp = value;
}

int Monster::getHp() {
	return curhp;
}