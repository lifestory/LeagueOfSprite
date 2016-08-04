#pragma once
#ifndef MONSTER2_H
#define MONSTER2_H

#include "cocos2d.h"

#include ".\public\Constant.h"
#include ".\scene\GameScene\Model\Weapon.h"

USING_NS_CC;

class Monster2 : public cocos2d::Sprite {
public:
	static Monster2* getInstance();
	virtual bool init();
	CREATE_FUNC(Monster2);

	void releaseMonster2();

	//animation and action
	void restoreStand();
	void beingHit();
	void attacking();
	void run(int dir, float speed);
	//basic attribute
	//HP
	void setHp(int value);
	int getHp();
	//basic damage
	void setBasicDamage(int damage);
	int getBasicDamage();

private:
	static Monster2* monster2_;
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

#endif // !MONSTER2_H