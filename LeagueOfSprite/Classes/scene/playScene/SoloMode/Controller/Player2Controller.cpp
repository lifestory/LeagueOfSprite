#include "Player2Controller.h"

enum  direction
{
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

Player2Controller* Player2Controller::player2controller_ = NULL;
//Player* Player2Controller::player2_ = NULL;


Player2Controller* Player2Controller::getInstance()
{
	if (player2controller_ == NULL)
	{
		player2controller_ = Player2Controller::create();
		player2controller_->setPosition(Vec2::ZERO);
		player2controller_->setAnchorPoint(Point::ZERO);
	}
	return player2controller_;
}

bool Player2Controller::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	initPlayer();
	createBloodBar();
	initSkills();
	initSkillsAnimation();

	//add keyboard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Player2Controller::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Player2Controller::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(Player2Controller::weaponShootingSpeedController2), 1.0f);

	return true;
}

Player2* Player2Controller::getPlayer2()
{
	return player2_;
}


//¼üÅÌ¿ØÖÆ
void Player2Controller::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		player2_->run(direction::left);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		player2_->run(direction::right);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		if (getOnAir() == false) {
			player2_->jump();
			setOnAir(true);
		}
		else if (getOnAir() == true && getSecondJump() == false) {
			player2_->jump();
			setSecondJump(true);
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		//player2_->run(direction::down);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		//this->addChild(Weapon::newWeapon(player2_->getPosition()));
		//player2_->shoot();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_1) {
		if (isReleasingThunder != true) {
			if (bluebar->getCurrentProgress() >= 40) {
				isReleasingThunder = true;
				releaseThunder();
				updateBluebarforConsuming(40);
				SimpleAudioEngine::getInstance()->playEffect("Sound/playerSkills/thunder.wav");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_2) {
		if (isHealing != true) {
			if (bluebar->getCurrentProgress() >= 10) {
				isHealing = true;
				releaseHeal();
				player2_->heal(player2_->getHP() + 10);
				updateBloodbar(player2_->getHP());
				updateBluebarforConsuming(10);
				SimpleAudioEngine::getInstance()->playEffect("Sound/playerSkills/heal.wav");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_3) {
		if (isStorm != true) {
			if (bluebar->getCurrentProgress() >= 20) {
				releaseStorm();
				updateBluebarforConsuming(20);
				SimpleAudioEngine::getInstance()->playEffect("Sound/playerSkills/storm.wav");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_4) {
		if (isShield != true) {
			if (bluebar->getCurrentProgress() >= 30) {
				isShield = true;
				releaseShield();
				updateBluebarforConsuming(30);
				SimpleAudioEngine::getInstance()->playEffect("Sound/playerSkills/shield.wav");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_0) {
		if (canShoot == true) {
			totalTimeforPowerBar = 0.0;
			player2_->setPowerBarVisiable(true);
			player2_->setPowerBar(0.0);
			player2_->schedule(schedule_selector(Player2Controller::updatePowerBar), 0.1f);
			player2_->shoot();
			keyPressed = true;
		}
		
	}

}

float Player2Controller::totalTimeforPowerBar;

void Player2Controller::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		player2_->stopRunning();
		player2_->stopActionByTag(actionDir::moveLeft);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		player2_->stopRunning();
		player2_->stopActionByTag(actionDir::moveRight);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		player2_->stopRunning();
		player2_->stopActionByTag(actionDir::moveUp);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		player2_->stopRunning();
		player2_->stopActionByTag(actionDir::moveDown);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_J) {

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_0) {
		if (canShoot == true && keyPressed == true) {
			player2_->setPowerBarVisiable(false);
			player2_->unschedule(schedule_selector(Player2Controller::updatePowerBar));
			float v = player2_->getPowerBar()->getPercentage();
			this->addChild(Weapon::newMonsterWeapon(player2_->getPosition(), v, Constant::getPlayer2ArrowTag()));
			player2_->stopShooting();
			canShoot = false;
			keyPressed = false;
		}
		
	}
}

bool Player2Controller::getOnAir() {
	return onAir;
}

bool Player2Controller::getSecondJump() {
	return secondJump;
}

void Player2Controller::setOnAir(bool set) {
	onAir = set;
}

void Player2Controller::setSecondJump(bool set) {
	secondJump = set;
}

void Player2Controller::releasePlayer2Controller() {
	if (player2controller_ != NULL) {
		//Player2Controller_->getPlayer()->removeFromParentAndCleanup(true);
		player2controller_->getPlayer2()->releasePlayer2();
		player2controller_->removeAllChildrenWithCleanup(true);
		player2controller_->removeFromParentAndCleanup(true);
		//Player2Controller_->release();
		player2controller_ = NULL;
	}
}

void Player2Controller::releaseThunder() {
	thunder->setVisible(false);
	thunderAnimation->setVisible(true);
	//thunderAnimation->runAction(thundingAction);
	playThunderAnimate();
	auto to = ProgressTo::create(5.0f, 100);

	//auto action = CSLoader::createTimeline("Model/Player/skills/Node.csd");

	thunderTimer->runAction(Sequence::create(to, CallFunc::create(CC_CALLBACK_0(Player2Controller::resetThunder, this)), NULL));
}

void Player2Controller::resetThunder() {
	thunder->setVisible(true);
	//thunderAnimation->setVisible(false);
	thunderTimer->setPercentage(0);
	isReleasingThunder = false;
}

void Player2Controller::createBloodBar() {
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
	auto avatar = Sprite::create("GameScene/ProgressView/player_avatar.png");
	avatar->setPosition(Point(bloodbar->getPositionX() - 150, bloodbar->getPositionY()));
	this->addChild(avatar, 2);
	this->addChild(bloodbar, 2);

	//create bluebar
	bluebar = new ProgressView();
	bluebar->setPosition(Point(820, 580));
	bluebar->setScale(3.0f);
	bluebar->setBackgroundTexture("GameScene/ProgressView/back.png");
	bluebar->setFrontgroundTexture("GameScene/ProgressView/blue.png");
	bluebar->setTotalProgress(100);
	bluebar->setCurrentProgress(100);
	this->addChild(bluebar, 2);
}

void Player2Controller::initSkills() {
	// thunder skill
	auto visibleSize = Director::getInstance()->getVisibleSize();
	thunderTimer = ProgressTimer::create(Sprite::create("Model/Player/skills/thunder.png"));
	thunderTimer->setPosition(750, 520);
	thunderTimer->setType(ProgressTimerType::RADIAL);
	this->addChild(thunderTimer, 2);
	thunderMiddle = Sprite::create("Model/Player/skills/thunder.png");
	thunderMiddle->setPosition(750, 520);
	thunderMiddle->setOpacity(100);
	this->addChild(thunderMiddle, 2);
	thunder = Sprite::create("Model/Player/skills/thunder.png");
	thunder->setPosition(750, 520);
	this->addChild(thunder, 2);
	isReleasingThunder = false;
	// heal skill
	healTimer = ProgressTimer::create(Sprite::create("Model/Player/skills/heal.png"));
	healTimer->setPosition(750 + healTimer->getContentSize().width + 10, 520);
	healTimer->setType(ProgressTimerType::RADIAL);
	this->addChild(healTimer, 2);
	healMiddle = Sprite::create("Model/Player/skills/heal.png");
	healMiddle->setPosition(750 + healMiddle->getContentSize().width + 10, 520);
	healMiddle->setOpacity(100);
	this->addChild(healMiddle, 2);
	heal = Sprite::create("Model/Player/skills/heal.png");
	heal->setPosition(750 + heal->getContentSize().width + 10, 520);
	this->addChild(heal, 2);
	isHealing = false;
	// storm skill
	stormTimer = ProgressTimer::create(Sprite::create("Model/Player/skills/storm.png"));
	stormTimer->setPosition(750 + stormTimer->getContentSize().width * 2 + 20, 520);
	stormTimer->setType(ProgressTimerType::RADIAL);
	this->addChild(stormTimer, 2);
	stormMiddle = Sprite::create("Model/Player/skills/storm.png");
	stormMiddle->setPosition(750 + stormMiddle->getContentSize().width * 2 + 20, 520);
	stormMiddle->setOpacity(100);
	this->addChild(stormMiddle, 2);
	storm = Sprite::create("Model/Player/skills/storm.png");
	storm->setPosition(750 + storm->getContentSize().width * 2 + 20, 520);
	this->addChild(storm, 2);
	isStorm = false;
	// shield skill
	shieldTimer = ProgressTimer::create(Sprite::create("Model/Player/skills/222.png"));
	shieldTimer->setPosition(750 + shieldTimer->getContentSize().width * 3 + 30, 520);
	shieldTimer->setType(ProgressTimerType::RADIAL);
	this->addChild(shieldTimer, 2);
	shieldMiddle = Sprite::create("Model/Player/skills/222.png");
	shieldMiddle->setPosition(750 + shieldMiddle->getContentSize().width * 3 + 30, 520);
	shieldMiddle->setOpacity(100);
	this->addChild(shieldMiddle, 2);
	shield = Sprite::create("Model/Player/skills/222.png");
	shield->setPosition(750 + shield->getContentSize().width*+30, 520);
	shield->setVisible(true);
	shield->setOpacity(0);
	this->addChild(shield, 2);
	isShield = false;

}

void Player2Controller::initPlayer() {
	player2_ = Player2::getInstance();
	player2_->setPosition(Point(800, 150));
	this->addChild(player2_);
	player2_->setHP(100);
	player2_->setMP(100);
	player2_->setExp(0);
	player2_->setScore(0);
	onAir = false;
	secondJump = false;
	canShoot = true;
	keyPressed = false;
}

void Player2Controller::initSkillsAnimation() {
	//thunder skill
	thunderAnimation = Sprite::create("Model/Player/skills/thunderAnimation/0.png");
	thunderAnimation->setVisible(false);
	this->addChild(thunderAnimation, 2);

}

Animate* Player2Controller::getThunderAnimate() {
	auto thunding = Animation::create();
	for (int i = 0; i < 8; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Player/skills/thunderAnimation/%d.png", i);
		thunding->addSpriteFrameWithFileName(filename);
	}
	thunding->setDelayPerUnit(2.0 / 8);
	auto thundingAction = Animate::create(thunding);
	return thundingAction;
}

void Player2Controller::playThunderAnimate() {
	thunderAnimation->setVisible(true);
	auto action = getThunderAnimate();
	thunderAnimation->setPosition(PlayerController::getInstance()->getPlayer()->getPosition());
	thunderAnimation->runAction(Sequence::create(action, CallFunc::create(CC_CALLBACK_0(Player2Controller::thunderAnimateEnded, this)), NULL));
}

void Player2Controller::thunderAnimateEnded() {
	thunderAnimation->setVisible(false);
}

void Player2Controller::releaseHeal() {
	player2_->playHealAnimate();
	heal->setVisible(false);
	auto to = ProgressTo::create(5.0f, 100);
	healTimer->runAction(Sequence::create(to, CallFunc::create(CC_CALLBACK_0(Player2Controller::resetHeal, this)), NULL));
}

void Player2Controller::resetHeal() {
	heal->setVisible(true);
	//thunderAnimation->setVisible(false);
	healTimer->setPercentage(0);
	isHealing = false;
}

void Player2Controller::releaseStorm() {

	isStorm = true;
	storm->setVisible(false);
	auto to = ProgressTo::create(5.0f, 100);
	stormTimer->runAction(Sequence::create(to, CallFunc::create(CC_CALLBACK_0(Player2Controller::resetStorm, this)), NULL));
	//storm skill
	auto stormAnimation = Animation::create();
	for (int i = 5; i < 9; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Player/skills/stormAnimation/%d.png", i);
		stormAnimation->addSpriteFrameWithFileName(filename);
	}
	stormAnimation->setDelayPerUnit(0.5 / 4);
	auto stormAnimate = Animate::create(stormAnimation);

	auto stormSprite = Sprite::create("Model/Player/skills/stormAnimation/5.png");
	stormSprite->setPosition(player2_->getPosition());
	auto body = PhysicsBody::createBox(Size(stormSprite->getContentSize().width*0.6, stormSprite->getContentSize().height*0.9));
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setCategoryBitmask(0x00000F0F);
	body->setCollisionBitmask(0x0000F000);
	body->setContactTestBitmask(0x0000F0F0);
	body->setTag(Constant::getStorm2Tag());
	stormSprite->setPhysicsBody(body);

	this->addChild(stormSprite, 2);
	//auto spawn = Spawn::createWithTwoActions(RepeatForever::create(MoveBy::create(1.0f, Vec2(100, 0))), RepeatForever::create(stormAnimate));
	stormSprite->runAction(RepeatForever::create(MoveBy::create(1.0f, Vec2(-250, 0))));
	stormSprite->runAction(RepeatForever::create(stormAnimate));
}

void Player2Controller::resetStorm() {
	isStorm = false;
	storm->setVisible(true);
	stormTimer->setPercentage(0);
}

void Player2Controller::releaseShield() {
	shield->setVisible(false);
	player2_->playShieldAnimate();
	auto to = ProgressTo::create(5.0f, 100);
	shieldTimer->runAction(Sequence::create(to, CallFunc::create(CC_CALLBACK_0(Player2Controller::resetShield, this)), NULL));
}

void Player2Controller::resetShield() {
	shield->setVisible(true);
	shieldTimer->setPercentage(0);
	isShield = false;
}

bool Player2Controller::getShield() {
	return isShield;
}

void Player2Controller::updatePowerBar(float t) {
	totalTimeforPowerBar += t;
	if (totalTimeforPowerBar > 1.5) {
		player2_->setPowerBar(0.0);
		totalTimeforPowerBar = 0.0;
		return;
	}
	else {
		player2_->setPowerBar(totalTimeforPowerBar / 1.5 * 100);
		log("powerBar:   %f", player2_->getPowerBar()->getPercentage());
	}
}


void Player2Controller::updateBloodbar(int value) {
	if (value > 0) {
		bloodbar->setCurrentProgress(value);
	}
	else {
		bloodbar->setCurrentProgress(-1);
	}
}

void Player2Controller::updateBluebarforConsuming(int value) {
	if (bluebar->getCurrentProgress() > value) {
		bluebar->setCurrentProgress(bluebar->getCurrentProgress() - value);
	}
	else {
		bluebar->setCurrentProgress(-1);
	}
}

ProgressView* Player2Controller::getBloodBar() {
	return bloodbar;
}

void Player2Controller::updateBlood(int value) {
	if (value > 0 && value < 100) {
		player2_->setHP(value);
	}
	else if (value >= 100) {
		player2_->setHP(100);
	}
	else if (value <= 0) {
		player2_->setHP(0);
	}
}

void Player2Controller::weaponShootingSpeedController2(float dt) {
	canShoot = true;
}
