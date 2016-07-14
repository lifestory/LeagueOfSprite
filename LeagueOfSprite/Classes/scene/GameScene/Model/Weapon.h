#pragma once
#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Constant.h"

using namespace CocosDenshion;
USING_NS_CC;

class Weapon : public cocos2d::Sprite
{
public:
	//static Weapon* getInstance();
	CREATE_FUNC(Weapon);
	static Sprite* newWeapon(Vec2 position);
	//void moveWeapon(float t);
	
private:
	
};

#endif // !_WEAPON_H_