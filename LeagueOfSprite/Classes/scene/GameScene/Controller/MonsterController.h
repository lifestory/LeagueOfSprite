#pragma once
#ifndef MONSTERCONTROLLER_H
#define MONSTERCONTROLLER_H

#include "cocos2d.h"

#include "Monster.h"
#include "Monster2.h"
#include "Monster3.h"

#include "ProgressView.h"
#include "Weapon.h"
#include "GameManager.h"

USING_NS_CC;

class MonsterController : public cocos2d::Layer {
public:
	static MonsterController* getInstance();
	virtual bool init();
	CREATE_FUNC(MonsterController);

	Monster* getMonster();
	Monster2* getMonster2();
	Monster3* getMonster3();

	void releaseMonsterController();

	void updateBloodbarforDamaging(int damage, int type);
	void updateBlood(int value, int type);
	ProgressView* getBloodBar();

	//monsters AI
	void monsterUpdate(float t);
	void monsterShoot(float t);
	void monster2Update(float t);
	void monster2Shoot(float t);
	void monster3Update(float t);
	void monster3Shoot(float t);

	//action
	void randomShoot(float dt);

private:
	static MonsterController* monsterController;
	Monster* monster;
	Monster2* monster2;
	Monster3* monster3;
	ProgressView* bloodbar;

	
};
#endif // !MONSTERCONTROLLER_H