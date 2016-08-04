#pragma once
#ifndef _PLAY2CONTROLLER_H_
#define _PLAY2CONTROLLER_H_

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"

#include ".\scene\GameScene\Model\Player.h"
#include ".\scene\GameScene\Model\Weapon.h"
#include ".\scene\GameScene\Model\ProgressView.h"
#include ".\scene\GameScene\Controller\WeaponBezier.h"
#include ".\scene\GameScene\Controller\MonsterController.h"
#include ".\scene\GameScene\Controller\PlayerController.h"
#include ".\scene\playScene\SoloMode\Model\player2.h"

USING_NS_CC;

class Player2Controller : public cocos2d::Layer
{
public:
	static Player2Controller* getInstance();
	virtual bool init();
	CREATE_FUNC(Player2Controller);

	Player2* getPlayer2();

	bool getOnAir();
	bool getSecondJump();
	void setOnAir(bool set);
	void setSecondJump(bool set);
	void weaponShootingSpeedController2(float dt);
	void weaponChange();

	void releasePlayer2Controller();

	//initial part
	void initPlayer();
	void createBloodBar();
	void initSkills();
	void initSkillsAnimation();

	//���̿���
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	//static CCEaseInOut* createParabola(float t, CCPoint staPos, CCPoint endPos, float height = 0, float angle = 0);

	//skill control
	void releaseThunder();
	void resetThunder();
	Animate* getThunderAnimate();
	void playThunderAnimate();
	void thunderAnimateEnded();

	void releaseStorm();
	void resetStorm();

	void releaseHeal();
	void resetHeal();

	void releaseShield();
	void resetShield();
	bool getShield();

	//update red and blue
	void updateRedAndBluebar(float t);
	//power bar
	void updatePowerBar(float t);

	//blood bar
	void updateBloodbar(int value);
	void updateBlood(int value);

	//blue bar
	void updateBluebarforConsuming(int value);
	void updateBluebarforIncreasing(int value);
	void updateBlue(int value);
	ProgressView* getBloodBar();
	ProgressView* getBlueBar();

private:
	static Player2Controller* player2controller_;
	Player2* player2_;
	ProgressView* bloodbar;
	ProgressView* bluebar;
	bool onAir;
	bool secondJump;
	bool canShoot;
	bool keyPressed;

	//weapon
	Sprite* weaponbasic;
	Sprite* weaponupdate;

	// skill set --thunder
	ProgressTimer *thunderTimer;
	Sprite *thunder;
	Sprite *thunderMiddle;
	bool isReleasingThunder;

	//skill set  --healing
	ProgressTimer *healTimer;
	Sprite *heal;
	Sprite *healMiddle;
	bool isHealing;

	//skill set --storm
	ProgressTimer *stormTimer;
	Sprite *storm;
	Sprite *stormMiddle;
	bool isStorm;

	//skillset --shield
	ProgressTimer *shieldTimer;
	Sprite *shield;
	Sprite  *shieldMiddle;
	bool isShield;

	// skill animation
	Sprite *thunderAnimation;

	// time to record power bar
	static float totalTimeforPowerBar;
};

#endif // !_PLAYCONTROLLER_H_