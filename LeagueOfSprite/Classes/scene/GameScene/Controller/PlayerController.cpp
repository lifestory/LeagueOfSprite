#include "PlayerController.h"

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

PlayerController* PlayerController::playercontroller_ = NULL;

PlayerController* PlayerController::getInstance()
{
	if (playercontroller_ == NULL)
	{
		playercontroller_ = PlayerController::create();
		playercontroller_->setPosition(Vec2::ZERO);
		playercontroller_->setAnchorPoint(Point::ZERO);
	}
	return playercontroller_;
}

bool PlayerController::init()
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

	weaponbasic = Sprite::create("Model/Weapon/player_weapon.png");
	weaponbasic->setPosition(100, 440);
	weaponupdate = Sprite::create("Model/Weapon/player_weapon_update.png");
	weaponupdate->setPosition(100, 440);
	weaponbasic->setVisible(true);
	weaponupdate->setVisible(false);
	this->addChild(weaponbasic, 2);
	this->addChild(weaponupdate, 2);

	//add keyboard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayerController::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlayerController::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(PlayerController::weaponShootingSpeedController), 1.0f);
	
	this->schedule(schedule_selector(PlayerController::updateRedAndBluebar), 5.0f);

	return true;
}

Player* PlayerController::getPlayer()
{
	return player_;
}


//¼üÅÌ¿ØÖÆ
void PlayerController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		player_->run(direction::left);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		player_->run(direction::right);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		if (getOnAir() == false) {
			player_->jump();
			setOnAir(true);
		}
		else if (getOnAir() == true && getSecondJump() == false) {
			player_->jump();
			setSecondJump(true);
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		//player_->run(direction::down);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_TAB) {
		weaponChange();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_K) {
		if (isReleasingThunder != true) {
			if (bluebar->getCurrentProgress() >= 20) {
				isReleasingThunder = true;
				releaseThunder();
				updateBluebarforConsuming(20);
				updateBlue(player_->getMP() - 20);
				SimpleAudioEngine::getInstance()->playEffect("Sound/playerSkills/thunder.wav");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_L) {
		if (isHealing != true) {
			if (bluebar->getCurrentProgress() >= 15) {
				isHealing = true;
				releaseHeal();
				player_->heal(player_->getHP()+10);
				updateBloodbar(player_->getHP());
				updateBluebarforConsuming(15);
				updateBlue(player_->getMP() - 15);
				SimpleAudioEngine::getInstance()->playEffect("Sound/playerSkills/heal.wav");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_N) {
		if (isStorm != true) {
			if (bluebar->getCurrentProgress() >= 25) {
				releaseStorm();
				updateBluebarforConsuming(25);
				updateBlue(player_->getMP() - 25);
				SimpleAudioEngine::getInstance()->playEffect("Sound/playerSkills/storm.wav");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_M) {
		if (isShield != true) {
			if (bluebar->getCurrentProgress() >= 15) {
				isShield = true;
				releaseShield();
				updateBluebarforConsuming(15);
				updateBlue(player_->getMP() - 15);
				SimpleAudioEngine::getInstance()->playEffect("Sound/playerSkills/shield.wav");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		if (GameManager::getInstance()->getPlayweapon() == 1)
		{
			if (canShoot == true) {
				totalTimeforPowerBar = 0.0;
				player_->setPowerBarVisiable(true);
				player_->setPowerBar(0.0);
				player_->schedule(schedule_selector(PlayerController::updatePowerBar), 0.1f);

				player_->shoot();
			}
			keyPressed = true;
		}
		else if (GameManager::getInstance()->getPlayweapon() == 2)
		{
			if (canShoot == true && bluebar->getCurrentProgress() >= 5) {
				totalTimeforPowerBar = 0.0;
				player_->setPowerBarVisiable(true);
				player_->setPowerBar(0.0);
				player_->schedule(schedule_selector(PlayerController::updatePowerBar), 0.1f);
				updateBluebarforConsuming(5);
				updateBlue(player_->getMP() - 5);
				player_->shoot();
			}
			
			keyPressed = true;
		}
	}

}

float PlayerController::totalTimeforPowerBar;

void PlayerController::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	
	if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		player_->stopRunning();
		player_->stopActionByTag(actionDir::moveLeft);
	} else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		player_->stopRunning();
		player_->stopActionByTag(actionDir::moveRight);
	} else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		player_->stopRunning();
		player_->stopActionByTag(actionDir::moveUp);
	} else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		player_->stopRunning();
		player_->stopActionByTag(actionDir::moveDown);
	} else if (keyCode == EventKeyboard::KeyCode::KEY_TAB) {

	} else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		if (canShoot == true && keyPressed == true) {
			player_->setPowerBarVisiable(false);
			player_->unschedule(schedule_selector(PlayerController::updatePowerBar));
			float v = player_->getPowerBar()->getPercentage();
			this->addChild(Weapon::newWeapon(player_->getPosition(), v));
			player_->stopShooting();
			canShoot = false;
			keyPressed = false;
		}
		
	}
}

bool PlayerController::getOnAir() {
	return onAir;
}

bool PlayerController::getSecondJump() {
	return secondJump;
}

void PlayerController::setOnAir(bool set) {
	onAir = set;
}

void PlayerController::setSecondJump(bool set) {
	secondJump = set;
}

void PlayerController::releasePlayerController() {
	if (playercontroller_ != NULL) {
		//playercontroller_->getPlayer()->removeFromParentAndCleanup(true);
		playercontroller_->getPlayer()->releasePlayer();
		playercontroller_->removeAllChildrenWithCleanup(true);
		playercontroller_->removeFromParentAndCleanup(true);
		//playercontroller_->release();
		playercontroller_ = NULL;
	}
}

void PlayerController::releaseThunder() {
	thunder->setVisible(false);
	thunderAnimation->setVisible(true);
	playThunderAnimate();
	auto to = ProgressTo::create(5.0f, 100);

	thunderTimer->runAction(Sequence::create(to, CallFunc::create(CC_CALLBACK_0(PlayerController::resetThunder, this)), NULL));

}

void PlayerController::resetThunder() {
	thunder->setVisible(true);
	thunderTimer->setPercentage(0);
	isReleasingThunder = false;
}

void PlayerController::createBloodBar() {
	//create bloodbar
	bloodbar = new ProgressView();
	bloodbar->setPosition(Point(200, 600));
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
	bluebar->setPosition(Point(200, 580));
	bluebar->setScale(3.0f);
	bluebar->setBackgroundTexture("GameScene/ProgressView/back.png");
	bluebar->setFrontgroundTexture("GameScene/ProgressView/blue.png");
	bluebar->setTotalProgress(100);
	bluebar->setCurrentProgress(100);
	this->addChild(bluebar, 2);
}

void PlayerController::initSkills() {
	// thunder skill
	auto visibleSize = Director::getInstance()->getVisibleSize();
	thunderTimer = ProgressTimer::create(Sprite::create("Model/Player/skills/thunder.png"));
	thunderTimer->setPosition(100, 520);
	thunderTimer->setType(ProgressTimerType::RADIAL);
	this->addChild(thunderTimer, 2);
	thunderMiddle = Sprite::create("Model/Player/skills/thunder.png");
	thunderMiddle->setPosition(100, 520);
	thunderMiddle->setOpacity(100);
	this->addChild(thunderMiddle, 2);
	thunder = Sprite::create("Model/Player/skills/thunder.png");
	thunder->setPosition(100, 520);
	this->addChild(thunder, 2);
	isReleasingThunder = false;
	// heal skill
	healTimer = ProgressTimer::create(Sprite::create("Model/Player/skills/heal.png"));
	healTimer->setPosition(100+healTimer->getContentSize().width+10, 520);
	healTimer->setType(ProgressTimerType::RADIAL);
	this->addChild(healTimer, 2);
	healMiddle = Sprite::create("Model/Player/skills/heal.png");
	healMiddle->setPosition(100+healMiddle->getContentSize().width+10, 520);
	healMiddle->setOpacity(100);
	this->addChild(healMiddle, 2);
	heal = Sprite::create("Model/Player/skills/heal.png");
	heal->setPosition(100+heal->getContentSize().width+10, 520);
	this->addChild(heal, 2);
	isHealing = false;
	// storm skill
	stormTimer = ProgressTimer::create(Sprite::create("Model/Player/skills/storm.png"));
	stormTimer->setPosition(100+stormTimer->getContentSize().width*2+20, 520);
	stormTimer->setType(ProgressTimerType::RADIAL);
	this->addChild(stormTimer, 2);
	stormMiddle = Sprite::create("Model/Player/skills/storm.png");
	stormMiddle->setPosition(100+stormMiddle->getContentSize().width*2+20, 520);
	stormMiddle->setOpacity(100);
	this->addChild(stormMiddle, 2);
	storm = Sprite::create("Model/Player/skills/storm.png");
	storm->setPosition(100+storm->getContentSize().width*2+20, 520);
	this->addChild(storm, 2);
	isStorm = false;
	// shield skill
	shieldTimer = ProgressTimer::create(Sprite::create("Model/Player/skills/222.png"));
	shieldTimer->setPosition(100+shieldTimer->getContentSize().width*3+30, 520);
	shieldTimer->setType(ProgressTimerType::RADIAL);
	this->addChild(shieldTimer, 2);
	shieldMiddle = Sprite::create("Model/Player/skills/222.png");
	shieldMiddle->setPosition(100+shieldMiddle->getContentSize().width*3+30, 520);
	shieldMiddle->setOpacity(100);
	this->addChild(shieldMiddle, 2);
	shield = Sprite::create("Model/Player/skills/222.png");
	shield->setPosition(100+shield->getContentSize().width*+30, 520);
	shield->setVisible(true);
	shield->setOpacity(0);
	this->addChild(shield, 2);
	isShield = false;

}

void PlayerController::initPlayer() {
	player_ = Player::getInstance();
	player_->setPosition(Point(100, 150));
	this->addChild(player_);
	player_->setHP(100);
	player_->setMP(100);
	player_->setExp(0);
	player_->setScore(0);
	onAir = false;
	secondJump = false;
	canShoot = true;
	keyPressed = false;
}

void PlayerController::initSkillsAnimation() {
	//thunder skill
	thunderAnimation = Sprite::create("Model/Player/skills/thunderAnimation/0.png");
	thunderAnimation->setVisible(false);
	this->addChild(thunderAnimation, 2);

}

Animate* PlayerController::getThunderAnimate() {
	auto thunding = Animation::create();
	for (int i = 0; i < 8; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Player/skills/thunderAnimation/%d.png", i);
		thunding->addSpriteFrameWithFileName(filename);
	}
	thunding->setDelayPerUnit(2.0/8);
	auto thundingAction = Animate::create(thunding);
	return thundingAction;
}

void PlayerController::playThunderAnimate() {
	thunderAnimation->setVisible(true);
	auto action = getThunderAnimate();
	thunderAnimation->setPosition(MonsterController::getInstance()->getMonster()->getPosition());
	thunderAnimation->runAction(Sequence::create(action, CallFunc::create(CC_CALLBACK_0(PlayerController::thunderAnimateEnded, this)), NULL));
}

void PlayerController::thunderAnimateEnded() {
	thunderAnimation->setVisible(false);
}

void PlayerController::releaseHeal() {
	player_->playHealAnimate();
	heal->setVisible(false);
	auto to = ProgressTo::create(5.0f, 100);
	healTimer->runAction(Sequence::create(to, CallFunc::create(CC_CALLBACK_0(PlayerController::resetHeal, this)), NULL));
}

void PlayerController::resetHeal() {
	heal->setVisible(true);
	healTimer->setPercentage(0);
	isHealing = false;
}

void PlayerController::releaseStorm() {

	isStorm = true;
	storm->setVisible(false);
	auto to = ProgressTo::create(5.0f, 100);
	stormTimer->runAction(Sequence::create(to, CallFunc::create(CC_CALLBACK_0(PlayerController::resetStorm, this)), NULL));
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
	stormSprite->setPosition(player_->getPosition());
	auto body = PhysicsBody::createBox(Size(stormSprite->getContentSize().width*0.6, stormSprite->getContentSize().height*0.9));
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setCategoryBitmask(0x00000F0F);
	body->setCollisionBitmask(0x000000F0);
	body->setContactTestBitmask(0x000000F0);
	body->setTag(Constant::getStormTag());
	stormSprite->setPhysicsBody(body);

	this->addChild(stormSprite, 2);
	stormSprite->runAction(RepeatForever::create(MoveBy::create(1.0f, Vec2(250, 0))));
	stormSprite->runAction(RepeatForever::create(stormAnimate));
}

void PlayerController::resetStorm() {
	isStorm = false;
	storm->setVisible(true);
	stormTimer->setPercentage(0);
}

void PlayerController::releaseShield() {
	shield->setVisible(false);
	player_->playShieldAnimate();
	auto to = ProgressTo::create(5.0f, 100);
	shieldTimer->runAction(Sequence::create(to, CallFunc::create(CC_CALLBACK_0(PlayerController::resetShield, this)), NULL));
}

void PlayerController::resetShield() {
	shield->setVisible(true);
	shieldTimer->setPercentage(0);
	isShield = false;
}

bool PlayerController::getShield() {
	return isShield;
}

void PlayerController::updatePowerBar(float t) {
	totalTimeforPowerBar += t;
	if (totalTimeforPowerBar > 1.5) {
		player_->setPowerBar(0.0);
		totalTimeforPowerBar = 0.0;
		return;
	}
	else {
		player_->setPowerBar(totalTimeforPowerBar / 1.5 * 100);
	}
}


void PlayerController::updateBloodbar(int value) {
	if (value > 0) {
		bloodbar->setCurrentProgress(value);
	} else {
		bloodbar->setCurrentProgress(-1);
	}
}

void PlayerController::updateBluebarforConsuming(int value) {
	if (bluebar->getCurrentProgress() > value) {
		bluebar->setCurrentProgress(bluebar->getCurrentProgress() - value);
	} else {
		bluebar->setCurrentProgress(-1);
	}
}
void PlayerController::updateBluebarforIncreasing(int value) {
	if (bluebar->getCurrentProgress() < 100) {
		bluebar->setCurrentProgress(bluebar->getCurrentProgress() + value);
	}
	else {
		bluebar->setCurrentProgress(100);
	}
}

ProgressView* PlayerController::getBloodBar() {
	return bloodbar;
}

ProgressView* PlayerController::getBlueBar() {
	return bluebar;
}

void PlayerController::updateBlood(int value) {
	if (value > 0 && value < 100) {
		player_->setHP(value);
	}
	else if (value >= 100) {
		player_->setHP(100);
	}
	else if (value <= 0) {
		player_->setHP(0);
	}
}

void PlayerController::updateBlue(int value) {
	if (value > 0 && value < 100) {
		player_->setMP(value);
	}
	else if (value >= 100) {
		player_->setMP(100);
	}
	else if (value <= 0) {
		player_->setMP(0);
	}
}

void PlayerController::weaponShootingSpeedController(float dt) {
	canShoot = true;
}

void PlayerController::weaponChange()
{
	if (GameManager::getInstance()->getPlayweapon() == 1)
	{
		GameManager::getInstance()->setPlayweapon(2);
		weaponbasic->setVisible(false);
		weaponupdate->setVisible(true);
	}
	else if (GameManager::getInstance()->getPlayweapon() == 2)
	{
		GameManager::getInstance()->setPlayweapon(1);
		weaponbasic->setVisible(true);
		weaponupdate->setVisible(false);
	}
}

void PlayerController::updateRedAndBluebar(float t)
{
	int tmpHP = player_->getHP();
	int tmpMP = player_->getMP();

	if (tmpHP < 100)
	{
		if (tmpHP + 1 > 100) {
			player_->setHP(100);
			updateBloodbar(100);
		} else {
			player_->setHP(tmpHP + 1);
			updateBloodbar(tmpHP + 1);
		}
	}
	if (tmpMP <= 100)
	{
		if (tmpMP + 3 > 100) {
			player_->setMP(100);
			updateBluebarforIncreasing(3);
		}
		else {
			player_->setMP(tmpMP + 3);
			updateBluebarforIncreasing(3);
		}
	}
}