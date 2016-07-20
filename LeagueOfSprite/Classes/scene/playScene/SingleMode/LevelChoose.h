#pragma once
#ifndef _LEVELCHOOSE_H_
#define _LEVELCHOOSE_H_

#include "cocos2d.h"
#include "cocos-ext.h"

#include ".\scene\playScene\SingleMode\LevelChooseScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d;
using namespace cocos2d::extension;

class LevelChoose : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(LevelChoose);

	//´¥¿Ø¿ØÖÆ
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	//void registerWithTouchDispatcher();

	//¼üÅÌ¿ØÖÆ
	//virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	//virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void adjustScrollView(float offset);
	int getCurLevel();
	void setCurLevel(int num);

	void ClickSelect(Ref* sender);
	void ClickBack(Ref* sender);
private:
	ScrollView* scrollView_;
	Point touchPoint;
	Point offsetPoint;
	int curLevel;
};

#endif // !_LEVELCHOOSE_H_