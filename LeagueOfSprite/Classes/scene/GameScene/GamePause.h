#pragma once
#ifndef _GAMEPAUSE_H_
#define _GAMEPAUSE_H_

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include ".\scene\playScene\modeChooseScene.h"
USING_NS_CC;

class GamePause : public cocos2d::CCLayer
{
public:
	virtual bool init();
	//GamePause* init();
	CREATE_FUNC(GamePause);


	static cocos2d::CCScene* scene(CCRenderTexture* sqr);

	//continue
	void ContinueGame(CCObject* pSender);
	//restart
	void RestartGame(CCObject* pSender);
	//jump to Mainmenu
	void JumpMainmenu(CCObject* pSender);
private:
	MenuItemImage *ContinueGameItem;
	MenuItemImage *RestartGameItem;
	MenuItemImage *JumpMainmenuItem;
	Menu *menu;
};

#endif // !_GAMEPAUSE_H_