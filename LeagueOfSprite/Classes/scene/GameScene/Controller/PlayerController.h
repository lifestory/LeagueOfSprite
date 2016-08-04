#pragma once
#ifndef _PLAYCONTROLLER_H_
#define _PLAYCONTROLLER_H_

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"

#include ".\scene\GameScene\Model\Player.h"
#include ".\scene\GameScene\Model\Weapon.h"
#include ".\scene\GameScene\Model\ProgressView.h"
#include "WeaponBezier.h"
#include "MonsterController.h"
#include ".\public\gameManager\GameManager.h"

USING_NS_CC;

class PlayerController : public cocos2d::Layer
{
public:
	static PlayerController* getInstance();
	virtual bool init();
	CREATE_FUNC(PlayerController);
	
	Player* getPlayer();

	bool getOnAir();
	bool getSecondJump();
	void setOnAir(bool set);
	void setSecondJump(bool set);
	void weaponChange();

	void releasePlayerController();

	//initial part
	void initPlayer();
	void createBloodBar();
	void initSkills();
	void initSkillsAnimation();

	//¼üÅÌ¿ØÖÆ
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	
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
	
	//controll weapon shooting speed
	void weaponShootingSpeedController(float dt);

private:
	static PlayerController* playercontroller_;
	Player* player_;
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