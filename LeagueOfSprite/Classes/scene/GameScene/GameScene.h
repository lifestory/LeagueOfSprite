#pragma once
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"

#include "HelloWorldScene.h"
#include "LevelChooseScene.h"
#include "PlayerController.h"
#include "MonsterController.h"
#include "Constant.h"
#include "SoundManager.h"

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

	//void ClickBack(Ref* sender);
	void updata(float t);

private:
	bool isGameOver;
};

#endif