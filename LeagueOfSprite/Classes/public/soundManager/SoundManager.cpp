#include "SoundManager.h"


SoundManager* SoundManager::soundManager = NULL;
bool SoundManager::isMusicOn = true;
bool SoundManager::isEffectOn = true;

SoundManager* SoundManager::getInstance() {
	if (soundManager == NULL) {
		soundManager = new SoundManager();
	}
	return soundManager;
}

void SoundManager::startSceneinit() {
	if (isMusicOn) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/startMusic.mp3");
	}
}

void SoundManager::gameSceneinit() {
	if (isMusicOn) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/gameSceneMusic.mp3");
	}
}


void SoundManager::turnOnOffMusic(int i) {
	if (i == 0) {
		isMusicOn = true;
	} else {
		isMusicOn = false;
	}
}

void SoundManager::turnOnOffEffect(int i) {
	if (i == 0) {
		isEffectOn = true;
	}
	else {
		isEffectOn = false;
	}
}

bool SoundManager::getEffect() {
	return isEffectOn;
}

bool SoundManager::getMusic() {
	return isMusicOn;
}