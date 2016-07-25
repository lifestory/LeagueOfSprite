#pragma once
#ifndef _SOLOSCENE_H_
#define _SOLOSCENE_H_

#include "cocos2d.h"

#include "LevelChooseScene.h"
#include "PlayerController.h"
#include "MonsterController.h"
#include "Constant.h"
#include "SoundManager.h"
#include "GamePause.h"
#include "ProgressView.h"
#include "GameController.h"
#include "Player2Controller.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

class SoloScene : public cocos2d::Scene {
public:
	static SoloScene* createScene();
	virtual bool init();
	CREATE_FUNC(SoloScene);

	bool onContactBegin(PhysicsContact& contact);
	void onContactSeparate(PhysicsContact& contact);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void ClickStop(CCObject* sender);

	void update(float t);

private:
	bool isGameEnded;
	ProgressView* pro;
};

#endif