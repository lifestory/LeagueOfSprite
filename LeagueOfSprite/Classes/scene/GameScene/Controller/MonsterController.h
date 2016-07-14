#pragma once
#ifndef MONSTERCONTROLLER_H
#define MONSTERCONTROLLER_H

#include "cocos2d.h"

#include "Monster.h"

USING_NS_CC;

class MonsterController : public cocos2d::Layer {
public:
	static MonsterController* getInstance();
	virtual bool init();
	CREATE_FUNC(MonsterController);

	Monster* getMonster();
private:
	static MonsterController* monsterController;
	Monster* monster;
};
#endif // !MONSTERCONTROLLER_H