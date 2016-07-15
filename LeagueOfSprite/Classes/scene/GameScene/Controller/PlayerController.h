#pragma once
#ifndef _PLAYCONTROLLER_H_
#define _PLAYCONTROLLER_H_

#include "cocos2d.h"
#include ".\scene\GameScene\Model\Player.h"
#include "Weapon.h"
#include "ProgressView.h"
#include "WeaponBezier.h"

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

	//¼üÅÌ¿ØÖÆ
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	//static CCEaseInOut* createParabola(float t, CCPoint staPos, CCPoint endPos, float height = 0, float angle = 0);

private:
	static PlayerController* playercontroller_;
	Player* player_;
	ProgressView* bloodbar;
	bool onAir;
	bool secondJump;
};

#endif // !_PLAYCONTROLLER_H_