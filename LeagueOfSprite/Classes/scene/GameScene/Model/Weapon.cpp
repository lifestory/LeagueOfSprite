#include "Weapon.h"


Sprite* Weapon::newWeapon(Vec2 position)
{
	Sprite * new_weapon = Sprite::create("Model/stone.png");
	auto weaponBody = PhysicsBody::createBox(new_weapon->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 0.99f));
	

	float a = 600;
	float progressPrecent = 100;
	float arrowVelocityX = progressPrecent / 100 * 600 * sin(30 / 180 * 3.14);
	float arrowVelocityY = progressPrecent / 100 * 600 * cos(30 / 180 * 3.14);
	weaponBody->setVelocity(Vec2(300, 400));

	weaponBody->setCategoryBitmask(0x0000000F);
	weaponBody->setCollisionBitmask(0x00000FF0);
	weaponBody->setContactTestBitmask(0x0000000F);

	weaponBody->setTag(Constant::getArrowTag());

	new_weapon->setPhysicsBody(weaponBody);
	new_weapon->setPosition(position);

	SimpleAudioEngine::getInstance()->playEffect("Sound/shoot.wav");
	return new_weapon;
}



//void Weapon::moveWeapon(float t)
//{
//	for (int i = 0; i < allWeapon.size(); i++) {
//		auto nowWeapon = allWeapon.at(i);
//		//nowbullet->setPositionX(nowbullet->getPositionX() + 64);
//		nowWeapon->setPosition(ccp(nowWeapon->getPositionX(), nowWeapon->getPositionY()));
//		nowWeapon->runAction(
//			CCSpawn::create(
//				CCRotateBy::create(1, 360),
//				GameScene::createParabola(1, nowWeapon->getPosition(), ccp(1000, 50), 100),
//				NULL)
//		);
//		if (nowWeapon->getPositionX() > 1024 || nowWeapon->getPositionX() < 0 || nowWeapon->getPositionY() < 0 || nowWeapon->getPositionY() > 768) {
//			nowWeapon->removeFromParent();
//			allWeapon.eraseObject(nowWeapon);
//			//allWeapon.erase(nowbullet);
//		}
//	}
//}


