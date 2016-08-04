#pragma once
#ifndef _SOLOSCENE_H_
#define _SOLOSCENE_H_

#include "cocos2d.h"

#include ".\scene\playScene\SingleMode\LevelChooseScene.h"
#include ".\scene\GameScene\Controller\PlayerController.h"
#include ".\scene\GameScene\Controller\MonsterController.h"
#include ".\public\Constant.h"
#include ".\public\soundManager\SoundManager.h"
#include ".\scene\GameScene\GamePause.h"
#include ".\scene\GameScene\Model\ProgressView.h"
#include ".\scene\GameScene\Controller\gamecontroller.h"
#include ".\scene\playScene\SoloMode\Controller\player2controller.h"

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

	void ClickStop(Ref* sender);

	void update(float t);

private:
	bool isGameEnded;
	ProgressView* pro;
};

#endif