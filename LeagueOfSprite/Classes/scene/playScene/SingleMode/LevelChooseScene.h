#pragma once
#ifndef LEVELCHOOSESCENE_H
#define LEVELCHOOSESCENE_H

#include "cocos2d.h"

#include ".\scene\playScene\modeChooseScene.h"
#include ".\scene\GameScene\GameScene.h"

USING_NS_CC;

class LevelChooseScene : public cocos2d::Scene {
public:
	static LevelChooseScene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelChooseScene);

private:

};
#endif // !LEVELCHOOSESCENE_H