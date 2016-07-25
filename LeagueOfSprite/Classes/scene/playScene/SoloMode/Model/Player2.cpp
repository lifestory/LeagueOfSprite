#include "Player2.h"

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

Player2* Player2::player2_ = NULL;


Player2* Player2::getInstance()
{
	if (player2_ == NULL)
	{
		player2_ = Player2::create();
		//Player2_->setPosition(100, 200);
	}

	return player2_;
}

bool Player2::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	//Sprite* Player2_ = Sprite::create("Model\Player2.png");
	//this->addChild(Player2_);
	stand = Sprite::create("Model/Player/Player.png");
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

	auto body = PhysicsBody::createBox(Size(stand->getContentSize().width*0.6, stand->getContentSize().height), PhysicsMaterial(0.99f, 0.0f, 0.99f));
	body->setTag(Constant::getPlayer2Tag());
	body->setRotationEnable(false);
	body->setVelocityLimit(200);

	this->setPhysicsBody(body);
	this->getPhysicsBody()->setCategoryBitmask(0x000000FF);
	this->getPhysicsBody()->setCollisionBitmask(0x0000000F);
	this->getPhysicsBody()->setContactTestBitmask(0x0000000F);

	// add power bar
	powerBarFrame = Sprite::create("GameScene/ProgressView/powerBarFrame.png");
	powerBarFrame->setPosition(Vec2(stand->getPosition().x, stand->getPosition().y + stand->getContentSize().height / 1.5));
	powerBar = ProgressTimer::create(Sprite::create("GameScene/ProgressView/powerBar.png"));
	powerBar->setPosition(Vec2(stand->getPosition().x, stand->getPosition().y + stand->getContentSize().height / 1.5));
	powerBar->setType(ProgressTimer::Type::BAR);
	powerBar->setMidpoint(Point(0, 0));
	powerBar->setBarChangeRate(Point(1, 0));
	//powerBar->setScale(1.5f);
	//powerBar->setPercentage(100);
	powerBar->setVisible(false);
	powerBarFrame->setVisible(false);
	this->addChild(powerBar, 1);
	this->addChild(powerBarFrame, 1);

	//HP
	hp_num = 100;
	//basic damage
	basicDamage = 10;
	shielding = false;

	return true;
}

//血量
void Player2::setHP(int num)
{
	hp_num = num;
}

int Player2::getHP()
{
	return hp_num;
}

//蓝量
void Player2::setMP(int num)
{
	mp_num = num;
}
int Player2::getMP()
{
	return mp_num;
}
//经验值
void Player2::setExp(int num)
{
	exp = num;
}
int Player2::getExp()
{
	return score;
}
//分数
void Player2::setScore(int num)
{
	score = num;
}
int Player2::getScore()
{
	return score;
}
//damage value
void Player2::setBasicDamage(int damage) {
	basicDamage = damage;
}

int Player2::getBasicDamage() {
	return basicDamage;
}

//Action and animation
void Player2::run(int direc)
{
	stand->setVisible(false);
	runAnimate->setVisible(true);

	if (direc == direction::left) {
		auto action = RepeatForever::create(MoveBy::create(1, Vec2(-200, 0)));
		action->setTag(actionDir::moveLeft);
		player2_->runAction(action);
	}
	else if (direc == direction::right) {
		auto action = RepeatForever::create(MoveBy::create(1, Vec2(200, 0)));
		action->setTag(actionDir::moveRight);
		player2_->runAction(action);
	}
	else if (direc == direction::up) {
		auto action = RepeatForever::create(MoveBy::create(1, Vec2(0, 200)));
		action->setTag(actionDir::moveUp);
		player2_->runAction(action);
	}
	else if (direc == direction::down) {
		auto action = RepeatForever::create(MoveBy::create(1, Vec2(0, -200)));
		action->setTag(actionDir::moveDown);
		player2_->runAction(action);
	}
}

void Player2::stopRunning() {
	runAnimate->setVisible(false);
	stand->setVisible(true);
}

void Player2::jump() {
	auto v = this->getPhysicsBody()->getVelocity();
	this->getPhysicsBody()->setVelocity(Vec2(v.x, v.y + 200));
}

void Player2::shoot() {
	stand->setVisible(false);
	shootAnimate->setVisible(true);
	runAnimate->setVisible(false);
}

void Player2::stopShooting() {
	stand->setVisible(true);
	shootAnimate->setVisible(false);
	runAnimate->setVisible(false);
}

void Player2::heal(int value) {
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

void Player2::releasePlayer2() {
	if (player2_ != NULL) {
		player2_->removeFromParentAndCleanup(true);
		//Player2_->removeAllChildrenWithCleanup(true);
		player2_ = NULL;
	}
}

Animate* Player2::getHealAnimate() {
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

void Player2::playHealAnimate() {
	healAnimate->setVisible(true);
	auto action = getHealAnimate();
	healAnimate->runAction(Sequence::create(action, CallFunc::create(CC_CALLBACK_0(Player2::healAnimateEnded, this)), NULL));
}

void Player2::healAnimateEnded() {
	healAnimate->setVisible(false);
}

Animate* Player2::getShieldAnimate() {
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

void Player2::playShieldAnimate() {
	shielding = true;
	shieldAnimate->setVisible(true);
	auto action = getShieldAnimate();
	shieldAnimate->runAction(Sequence::create(action, CallFunc::create(CC_CALLBACK_0(Player2::shieldAnimateEnded, this)), NULL));
}

void Player2::shieldAnimateEnded() {
	shieldAnimate->setVisible(false);
	shielding = false;
}

bool Player2::getShielding() {
	return shielding;
}

ProgressTimer* Player2::getPowerBar() {
	return powerBar;
}

ProgressTimer* Player2::powerBar = NULL;

ProgressTimer* Player2::getpowerBar() {
	if (powerBar != NULL) {
		return powerBar;
	}
}

void Player2::setPowerBar(float v) {
	powerBar->setPercentage(v);
}

float Player2::getPowerBarPercentage() {
	return powerBar->getPercentage();
}

void Player2::setPowerBarVisiable(bool v) {
	powerBar->setVisible(v);
	powerBarFrame->setVisible(v);
}