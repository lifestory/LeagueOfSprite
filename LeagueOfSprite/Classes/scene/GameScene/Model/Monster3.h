#pragma once
#ifndef MONSTER3_H
#define MONSTER3_H

#include "cocos2d.h"

#include ".\public\Constant.h"
#include ".\scene\GameScene\Model\Weapon.h"

USING_NS_CC;

class Monster3 : public cocos2d::Sprite {
public:
	static Monster3* getInstance();
	virtual bool init();
	CREATE_FUNC(Monster3);

	void releaseMonster3();

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
	static Monster3* monster3_;
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
#endif // !MONSTER3_H