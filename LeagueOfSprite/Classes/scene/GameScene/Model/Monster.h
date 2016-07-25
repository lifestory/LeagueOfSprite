#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include "cocos2d.h";

#include "Constant.h"
#include "Weapon.h"

USING_NS_CC;

class Monster : public cocos2d::Sprite {
public:
	static Monster* getInstance();
	virtual bool init();
	CREATE_FUNC(Monster);

	void releaseMonster();

	//animation and action
	void restoreStand();
	void beingHit();
	void attacking();

	//basic attribute
	//HP
	void setHp(int value);
	int getHp();
	//basic damage
	void setBasicDamage(int damage);
	int getBasicDamage();

private:
	static Monster* monster_;
	Sprite* standAnimate;
	Sprite* forwardAnimate;
	Sprite* injuredAnimate;
	Sprite* attackAnimate;
	Animate* injuringAction;
	Animate* standingAction;
	Animate* attackingAction;

	//basic attribute
	int curhp;
	int maxhp;
	int basicDamage;
};
#endif