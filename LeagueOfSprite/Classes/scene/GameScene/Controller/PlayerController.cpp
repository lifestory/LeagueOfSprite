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
		playercontroller_->setPosition(100, 100);
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
	player_->setTag(100);
	player_->setPosition(Point(100, 100));
	this->addChild(player_);
	player_->setHP(100);
	player_->setMP(100);
	player_->setExp(0);
	player_->setScore(0);
	onAir = false;
	secondJump = false;

	//add weapon
	//auto weapon_ = Weapon::getInstance();
	//weapon_->setPosition(player_->getPosition());
	//this->addChild(weapon_);

	//add keyboard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayerController::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlayerController::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

//Player* PlayerController::getPlayer()
//{
//	return player_;
//}


//¼üÅÌ¿ØÖÆ
void PlayerController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		player_->run(direction::left);
	} else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		player_->run(direction::right);
	} else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		log("PlayerController_OnAir: %d", PlayerController::getInstance()->getOnAir());
		log("PlayerController_SecondJump: %d", PlayerController::getInstance()->getSecondJump());
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