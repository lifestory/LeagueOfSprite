#include "Player.h"

enum direction
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

Player* Player::player_ = NULL;


Player* Player::getInstance()
{
	if (player_ == NULL)
	{
		player_ = Player::create();
	}
	
	return player_;
}

bool Player::init()
{
	if (!Sprite::init())
	{
		return false;
	}
    //Sprite* player_ = Sprite::create("Model\player.png");
	//this->addChild(player_);
	stand = Sprite::create("Model/Player/player.png");
	this->addChild(stand, 1);
	
	//running animation
	auto running = Animation::create();
	for (int i = 0; i < 1; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Player/run/run_%d.png", i);
		running->addSpriteFrameWithFileName(filename);
	}
	running->setDelayPerUnit(0.5f);
	auto runningAction = Animate::create(running);
	runAnimate = Sprite::create("Model/Player/run/run_0.png");
	runAnimate->runAction(RepeatForever::create(runningAction));
	this->addChild(runAnimate, 1);
	runAnimate->setVisible(false);

	//shoot animation
	shootAnimate = Sprite::create("Model/Player/shoot/shoot.png");
	shootAnimate->setVisible(false);
	this->addChild(shootAnimate, 1);

	auto body = PhysicsBody::createBox(Size(stand->getContentSize().width*0.6,stand->getContentSize().height),  PhysicsMaterial(0.1f, 0.0f, 0.99f));
	body->setTag(Constant::getPlayerTag());
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	this->getPhysicsBody()->setCategoryBitmask(0x0000000F);
	this->getPhysicsBody()->setCollisionBitmask(0x000000FF);
	this->getPhysicsBody()->setContactTestBitmask(0x0000000F);

	return true;
}

//血量
void Player::setHP(int num)
{
	hp_num = num;
}
int Player::getHP()
{
	return hp_num;
}
//蓝量
void Player::setMP(int num)
{
	mp_num = num;
}
int Player::getMP()
{
	return mp_num;
}
//经验值
void Player::setExp(int num)
{
	exp = num;
}
int Player::getExp()
{
	return score;
}
//分数
void Player::setScore(int num)
{
	score = num;
}
int Player::getScore()
{
	return score;
}

void Player::run(int direc)
{
	stand->setVisible(false);
	runAnimate->setVisible(true);

	if (direc == direction::left) {
		auto action = RepeatForever::create(MoveBy::create(1, Vec2(-200, 0)));
		action->setTag(actionDir::moveLeft);
		player_->runAction(action);
	} else if (direc == direction::right) {
		auto action = RepeatForever::create(MoveBy::create(1, Vec2(200, 0)));
		action->setTag(actionDir::moveRight);
		player_->runAction(action);
	} else if (direc == direction::up) {
		auto action = RepeatForever::create(MoveBy::create(1, Vec2(0, 200)));
		action->setTag(actionDir::moveUp);
		player_->runAction(action);
	} else if (direc == direction::down) {
		auto action = RepeatForever::create(MoveBy::create(1, Vec2(0, -200)));
		action->setTag(actionDir::moveDown);
		player_->runAction(action);
	}
}

void Player::stopRunning() {
	runAnimate->setVisible(false);
	stand->setVisible(true);
}

void Player::jump() {
	auto v = this->getPhysicsBody()->getVelocity();
	this->getPhysicsBody()->setVelocity(Vec2(v.x, v.y + 200));
}

void Player::shoot() {
	stand->setVisible(false);
	shootAnimate->setVisible(true);
	runAnimate->setVisible(false);
}

void Player::stopShooting() {
	stand->setVisible(true);
	shootAnimate->setVisible(false);
	runAnimate->setVisible(false);
}

void Player::releasePlayer() {
	if (player_ != NULL) {
		player_->removeFromParentAndCleanup(true);
		//player_->removeAllChildrenWithCleanup(true);
		player_ = NULL;
	}
}