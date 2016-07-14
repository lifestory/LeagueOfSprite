#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;
USING_NS_CC;

class SoundManager {
public:
	static SoundManager* getInstance();
	static void startSceneinit();
	static void gameSceneinit();
	static void turnOnOffMusic(int i);
	static void turnOnOffEffect(int i);
	static bool getEffect();
	static bool getMusic();

private:
	static SoundManager* soundManager;
	static bool isMusicOn;
	static bool isEffectOn;
};
#endif // !SOUNDMANAGER_H
