#pragma once
#ifndef _PLAYCONTROLLER_H_
#define _PLAYCONTROLLER_H_

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"

#include ".\scene\GameScene\Model\Player.h"
#include "Weapon.h"
#include "ProgressView.h"
#include "WeaponBezier.h"
#include "MonsterController.h"

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

	void releasePlayerController();

	//initial part
	void initPlayer();
	void createBloodBar();
	void initSkills();
	void initSkillsAnimation();

	//¼üÅÌ¿ØÖÆ
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

private:
	static PlayerController* playercontroller_;
	Player* player_;
	ProgressView* bloodbar;
	ProgressView* bluebar;
	bool onAir;
	bool secondJump;

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
};

#endif // !_PLAYCONTROLLER_H_