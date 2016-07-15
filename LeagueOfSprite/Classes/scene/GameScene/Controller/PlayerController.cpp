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
//Player* PlayerController::player_ = NULL;


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

	//player_ = Player::getInstance();
	player_ = Player::getInstance();
	//player_->setTag(100);
	player_->setPosition(Point(100, 200));
	this->addChild(player_);
	player_->setHP(100);
	player_->setMP(100);
	player_->setExp(0);
	player_->setScore(0);
	onAir = false;
	secondJump = false;

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

	//add keyboard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayerController::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlayerController::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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
	} else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		player_->run(direction::right);
	} else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		if (getOnAir() == false) {
			player_->jump();
			setOnAir(true);
		} else if (getOnAir() == true && getSecondJump() == false) {
			player_->jump();
			setSecondJump(true);
		}	
	} else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		//player_->run(direction::down);
	} else if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		this->addChild(Weapon::newWeapon(player_->getPosition()));
		player_->shoot();
	}
}

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
	} else if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		player_->stopShooting();
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