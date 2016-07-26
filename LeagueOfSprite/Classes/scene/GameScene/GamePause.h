#pragma once
#ifndef _GAMEPAUSE_H_
#define _GAMEPAUSE_H_

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include ".\scene\playScene\modeChooseScene.h"
#include "SoloScene.h"

USING_NS_CC;

class GamePause : public cocos2d::Layer
{
public:
	virtual bool init();
	//GamePause* init();
	CREATE_FUNC(GamePause);


	static Scene* scene(RenderTexture* sqr);

	static Scene* soloScene(RenderTexture* sqr);

	//continue
	void ContinueGame(Object* pSender);
	//restart
	void RestartGame(Object* pSender);
	//jump to Mainmenu
	void JumpMainmenu(Object* pSender);

	//soloScene imageitem
	void soloContinueGame(Object* pSender);
	void soloRestartGame(Object* pSender);
	void soloJumpMainmenu(Object* pSender);

private:
	MenuItemImage *ContinueGameItem;
	MenuItemImage *RestartGameItem;
	MenuItemImage *JumpMainmenuItem;
	Menu *menu;
};

#endif // !_GAMEPAUSE_H_