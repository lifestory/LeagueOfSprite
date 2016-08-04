#pragma once
#ifndef _GAMEPAUSE_H_
#define _GAMEPAUSE_H_

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include ".\scene\playScene\modeChooseScene.h"
#include ".\scene\playScene\SoloMode\soloscene.h"

USING_NS_CC;

class GamePause : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GamePause);


	static Scene* scene(RenderTexture* sqr);

	static Scene* soloScene(RenderTexture* sqr);

	//continue
	void ContinueGame(Ref* pSender);
	//restart
	void RestartGame(Ref* pSender);
	//jump to Mainmenu
	void JumpMainmenu(Ref* pSender);

	//soloScene imageitem
	void soloContinueGame(Ref* pSender);
	void soloRestartGame(Ref* pSender);
	void soloJumpMainmenu(Ref* pSender);

private:
	MenuItemImage *ContinueGameItem;
	MenuItemImage *RestartGameItem;
	MenuItemImage *JumpMainmenuItem;
	Menu *menu;
};

#endif // !_GAMEPAUSE_H_