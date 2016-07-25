#pragma once
#ifndef _Player2_H_
#define _Player2_H_

#include "cocos2d.h"

#include "Weapon.h"
#include "Constant.h"

USING_NS_CC;

class  Player2 : public cocos2d::Sprite
{
public:
	static Player2* getInstance();
	CREATE_FUNC(Player2);
	virtual bool init();

	void releasePlayer2();


	//血量
	void setHP(int num);
	int getHP();
	//蓝量
	void setMP(int num);
	int getMP();
	//经验值
	void setExp(int num);
	int getExp();
	//分数
	void setScore(int num);
	int getScore();
	//damage
	void setBasicDamage(int damage);
	int getBasicDamage();

	//action
	void run(int direction);
	void jump();
	void stopRunning();
	void shoot();
	void stopShooting();
	void heal(int value);

	//animation
	Animate* getHealAnimate();
	void playHealAnimate();
	void healAnimateEnded();
	Animate* getShieldAnimate();
	void playShieldAnimate();
	void shieldAnimateEnded();

	//shielding
	bool getShielding();

	// power bar
	ProgressTimer* getPowerBar();
	void setPowerBar(float v);
	static ProgressTimer* getpowerBar();
	float getPowerBarPercentage();
	void setPowerBarVisiable(bool v);

private:
	//basic attribute
	static Player2* player2_;
	int hp_num;
	int mp_num;
	int score;
	int exp;
	int basicDamage;

	//animation
	Sprite* stand;
	Sprite* runAnimate;
	Sprite* shootAnimate;
	Sprite *healAnimate;
	Sprite *shieldAnimate;
	bool shielding;

	//power bar
	static ProgressTimer *powerBar;
	Sprite *bar;
	Sprite *powerBarFrame;

};
#endif // !_Player2_H_