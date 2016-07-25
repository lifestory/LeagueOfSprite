#include "Weapon.h"

#define pi 3.141592654

Sprite* Weapon::newWeapon(Vec2 position, float v)
{
	
	//Sprite * new_weapon = Sprite::create("Model/stone.png");
	auto new_weapon = new Weapon();
	new_weapon->initWithFile("Model/stone.png");
	new_weapon->autorelease();
	auto weaponBody = PhysicsBody::createBox(new_weapon->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 0.99f));
	

	float a = 600;
	float progressPrecent = 100;
	float arrowVelocityX = progressPrecent / 100 * 600 * sin(30 / 180 * 3.14);
	float arrowVelocityY = progressPrecent / 100 * 600 * cos(30 / 180 * 3.14);


	weaponBody->setVelocity(Vec2(v / 100 * 600, 400));
	

	weaponBody->setCategoryBitmask(0x0000000F);
	weaponBody->setCollisionBitmask(0x00000FF0);
	weaponBody->setContactTestBitmask(0x00000F0F);

	weaponBody->setTag(Constant::getArrowTag());

	new_weapon->setPhysicsBody(weaponBody);
	new_weapon->setPosition(position);
	std::string name = "hello";

	//auto s = Director::getInstance()->getScheduler();
	//s->schedule(CC_CALLBACK_1(Weapon::updateWeaponAngle, new_weapon, new_weapon, name), new_weapon, 0.0, CC_REPEAT_FOREVER, 0.0, false, "end");

	SimpleAudioEngine::getInstance()->playEffect("Sound/shoot.wav");
	return new_weapon;
}

void Weapon::updateWeaponAngle(float f, void* data, std::string s) {
	auto weapon = ((Sprite*)data);
	Vec2 velocity = weapon->getPhysicsBody()->getVelocity();
	float angle = -atan(velocity.y / velocity.x) / pi * 180;
	if (velocity.x < 0) angle += 180;
	weapon->setRotation(angle);
}


Sprite* Weapon::newMonsterWeapon(Vec2 position, float v) {
	Sprite * new_weapon = Sprite::create("Model/stone.png");
	auto weaponBody = PhysicsBody::createBox(new_weapon->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 0.99f));


	float a = 600;
	float progressPrecent = 100;
	float arrowVelocityX = progressPrecent / 100 * 600 * sin(30 / 180 * 3.14);
	float arrowVelocityY = progressPrecent / 100 * 600 * cos(30 / 180 * 3.14);


	weaponBody->setVelocity(Vec2(-v / 100 * 300, 400));


	weaponBody->setCategoryBitmask(0x00000F00);
	weaponBody->setCollisionBitmask(0x00000FFF);
	weaponBody->setContactTestBitmask(0x0000000F);

	weaponBody->setTag(Constant::getMonsterArrowTag());

	new_weapon->setPhysicsBody(weaponBody);
	new_weapon->setPosition(position);
	//std::string name = "hello";
	//auto s = Director::getInstance()->getScheduler();
	//s->schedule(CC_CALLBACK_1(Weapon::updateWeaponAngle, new_weapon, new_weapon, name), new_weapon, 0, CC_REPEAT_FOREVER, 0, false, "end");
	//SimpleAudioEngine::getInstance()->playEffect("Sound/shoot.wav");
	return new_weapon;
}