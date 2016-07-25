#pragma once
#ifndef MONSTERCONTROLLER_H
#define MONSTERCONTROLLER_H

#include "cocos2d.h"

#include "Monster.h"
#include "ProgressView.h"
#include "Weapon.h"

USING_NS_CC;

class MonsterController : public cocos2d::Layer {
public:
	static MonsterController* getInstance();
	virtual bool init();
	CREATE_FUNC(MonsterController);

	Monster* getMonster();
	void releaseMonsterController();

	void updateBloodbarforDamaging(int damage);
	void updateBlood(int value);
	ProgressView* getBloodBar();

	

	//action
	void randomShoot(float dt);

private:
	static MonsterController* monsterController;
	Monster* monster;
	ProgressView* bloodbar;

	
};
#endif // !MONSTERCONTROLLER_H