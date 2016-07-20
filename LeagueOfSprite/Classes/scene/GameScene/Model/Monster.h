#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include "cocos2d.h";

#include "Constant.h"

USING_NS_CC;

class Monster : public cocos2d::Sprite {
public:
	static Monster* getInstance();
	virtual bool init();
	CREATE_FUNC(Monster);

	void releaseMonster();

	void restoreStand();
	void beingHit();

	void setHp(int value);
	int getHp();

private:
	static Monster* monster_;
	Sprite* standAnimate;
	Sprite* forwardAnimate;
	Sprite* injuredAnimate;
	Sprite* attackAnimate;
	Animate* injuringAction;
	Animate* standingAction;
	//basic information
	int curhp;
	int maxhp;
};
#endif