#include "Weapon.h"

#define pi 3.141592654

Sprite* Weapon::newWeapon(Vec2 position, float v)
{
	auto new_weapon = new Weapon();
	if (GameManager::getInstance()->getPlayweapon() == 1)
	{
		new_weapon->initWithFile("Model/Weapon/player_weapon.png");
	}
	else if (GameManager::getInstance()->getPlayweapon() == 2)
	{
		new_weapon->initWithFile("Model/Weapon/player_weapon_update.png");
	}
	
	new_weapon->autorelease();
	auto weaponBody = PhysicsBody::createBox(new_weapon->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 0.99f));
	

	float a = 600;
	float progressPrecent = 100;
	float arrowVelocityX = progressPrecent / 100 * 600 * sin(30 / 180 * 3.14);
	float arrowVelocityY = progressPrecent / 100 * 600 * cos(30 / 180 * 3.14);


	weaponBody->setVelocity(Vec2(v / 100 * 550, 400));
	

	weaponBody->setCategoryBitmask(0x0000000F);
	weaponBody->setCollisionBitmask(0x00000FF0);
	weaponBody->setContactTestBitmask(0x00000F0F);

	weaponBody->setTag(Constant::getArrowTag());

	new_weapon->setPhysicsBody(weaponBody);
	new_weapon->setPosition(position);

	new_weapon->runAction(RepeatForever::create(RotateBy::create(0.5, 360)));

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


Sprite* Weapon::newMonsterWeapon(Vec2 position, float v, int type) {
	Sprite *new_weapon;
	if (type == Constant::getMonsterArrowTag()) {
		new_weapon = Sprite::create("Model/Weapon/monster_weapon.png");
	} else if (type == Constant::getMonster2ArrowTag()) {
		new_weapon = Sprite::create("Model/Weapon/monster2_weapon.png");
	}
	else if (type == Constant::getMonster3ArrowTag()) {
		new_weapon = Sprite::create("Model/Weapon/monster3_weapon.png");
	} else if (type == Constant::getPlayer2ArrowTag()) {
		//new_weapon = Sprite::create("Model/Weapon/player2_weapon.png");
		if (GameManager::getInstance()->getPlay2weapon() == 1)
		{
			new_weapon = Sprite::create("Model/Weapon/player2_weapon.png");
		}
		else if (GameManager::getInstance()->getPlay2weapon() == 2)
		{
			new_weapon = Sprite::create("Model/Weapon/player2_weapon_update.png");
		}
	}
	
	auto weaponBody = PhysicsBody::createBox(new_weapon->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 0.99f));


	float a = 600;
	float progressPrecent = 100;
	float arrowVelocityX = progressPrecent / 100 * 600 * sin(30 / 180 * 3.14);
	float arrowVelocityY = progressPrecent / 100 * 600 * cos(30 / 180 * 3.14);

	if (type == Constant::getPlayer2ArrowTag()) {
		weaponBody->setVelocity(Vec2(-v / 100 * 550, 450));
	} else {
		weaponBody->setVelocity(Vec2(-v / 100 * 300, 400));
	}



	weaponBody->setCategoryBitmask(0x00000F00);
	weaponBody->setCollisionBitmask(0x000000FF);
	weaponBody->setContactTestBitmask(0x0000000F);

	weaponBody->setTag(type);

	new_weapon->setPhysicsBody(weaponBody);
	new_weapon->setPosition(position);

	if (type != Constant::getPlayer2ArrowTag()) {
		new_weapon->runAction(RepeatForever::create(RotateBy::create(0.5, 360)));
	}

	return new_weapon;
}