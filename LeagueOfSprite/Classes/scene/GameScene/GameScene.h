#pragma once
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"

#include "HelloWorldScene.h"
#include ".\scene\playScene\SingleMode\LevelChooseScene.h"
#include ".\scene\GameScene\Controller\PlayerController.h"
#include ".\scene\GameScene\Controller\MonsterController.h"
#include ".\public\Constant.h"
#include "GamePause.h"
#include ".\public\soundManager\SoundManager.h"
#include ".\scene\GameScene\Model\ProgressView.h"

#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

using namespace CocosDenshion;
USING_NS_CC;

class GameScene : public cocos2d::Scene {
public:
	static GameScene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	bool onContactBegin(PhysicsContact& contact);
	void onContactSeparate(PhysicsContact& contact);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	
	void ClickStop(CCObject* sender);
	void updata(float t);

private:
	bool isGameOver;
	ProgressView* pro;
};

#endif