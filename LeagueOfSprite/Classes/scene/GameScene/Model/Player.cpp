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
		//player_->setPosition(100, 200);
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

	//heal animate
	healAnimate = Sprite::create("Model/Player/skills/healAnimation/0.png");
	healAnimate->setVisible(false);
	this->addChild(healAnimate, 1);

	//shield animate
	shieldAnimate = Sprite::create("Model/Player/skills/shieldAnimation/0.png");
	shieldAnimate->setVisible(false);
	this->addChild(shieldAnimate, 1);

	auto body = PhysicsBody::createBox(Size(stand->getContentSize().width*0.6,stand->getContentSize().height), PhysicsMaterial(0.99f, 0.0f, 0.99f));
	body->setTag(Constant::getPlayerTag());
	body->setRotationEnable(false);
	body->setVelocityLimit(200);

	this->setPhysicsBody(body);
	this->getPhysicsBody()->setCategoryBitmask(0x0000000F);
	this->getPhysicsBody()->setCollisionBitmask(0x000000FF);
	this->getPhysicsBody()->setContactTestBitmask(0x0000000F);

	// add power bar
	powerBar = ProgressTimer::create(Sprite::create("GameScene/ProgressView/front.png"));
	powerBar->setPosition(Vec2(stand->getPosition().x, stand->getPosition().y + stand->getContentSize().height/1.5));
	powerBar->setType(ProgressTimer::Type::BAR);
	powerBar->setMidpoint(Point(0, 0));
	powerBar->setBarChangeRate(Point(1, 0));
	powerBar->setScale(1.5f);
	//powerBar->setPercentage(100);
	powerBar->setVisible(false);
	this->addChild(powerBar, 1);

	return true;
}

//Ѫ��
void Player::setHP(int num)
{
	hp_num = num;
}
int Player::getHP()
{
	return hp_num;
}
//����
void Player::setMP(int num)
{
	mp_num = num;
}
int Player::getMP()
{
	return mp_num;
}
//����ֵ
void Player::setExp(int num)
{
	exp = num;
}
int Player::getExp()
{
	return score;
}
//����
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

Animate* Player::getHealAnimate() {
	auto healing = Animation::create();
	for (int i = 0; i < 9; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Player/skills/healAnimation/%d.png", i);
		healing->addSpriteFrameWithFileName(filename);
	}
	healing->setDelayPerUnit(2.0 / 8);
	auto heal = Animate::create(healing);
	return heal;
}

void Player::playHealAnimate() {
	healAnimate->setVisible(true);
	auto action = getHealAnimate();
	healAnimate->runAction(Sequence::create(action, CallFunc::create(CC_CALLBACK_0(Player::healAnimateEnded, this)), NULL));
}

void Player::healAnimateEnded() {
	healAnimate->setVisible(false);
}

Animate* Player::getShieldAnimate() {
	auto shield = Animation::create();
	for (int i = 0; i < 2; i++) {
		char filename[128] = { 0 };
		sprintf(filename, "Model/Player/skills/shieldAnimation/%d.png", i);
		shield->addSpriteFrameWithFileName(filename);
	}
	shield->setDelayPerUnit(0.3f);
	shield->setLoops(5);
	auto animate = Animate::create(shield);
	return animate;
}

void Player::playShieldAnimate() {
	shieldAnimate->setVisible(true);
	auto action = getShieldAnimate();
	shieldAnimate->runAction(Sequence::create(action, CallFunc::create(CC_CALLBACK_0(Player::shieldAnimateEnded, this)), NULL));
}

void Player::shieldAnimateEnded() {
	shieldAnimate->setVisible(false);
}

ProgressTimer* Player::getPowerBar() {
	return powerBar;
}

ProgressTimer* Player::powerBar = NULL;

ProgressTimer* Player::getpowerBar() {
	if (powerBar != NULL) {
		return powerBar;
	}
}

void Player::setPowerBar(float v) {
	powerBar->setPercentage(v);
}

float Player::getPowerBarPercentage() {
	return powerBar->getPercentage();
}