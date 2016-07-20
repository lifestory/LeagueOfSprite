#pragma once
#ifndef _PROGRESSVIEW_H_
#define _PROGRESSVIEW_H_

#include "cocos2d.h"
USING_NS_CC;

class ProgressView : public cocos2d::Node
{
public:
	//init
	ProgressView();

	//血条背景  
	void setBackgroundTexture(const char *pTexture);
	//血条前景  
	void setFrontgroundTexture(const char *pTexture);

	//总血量
	int getTotalProgress();
	void setTotalProgress(int totalHP_);

	//当前血量
	int getCurrentProgress();
	void setCurrentProgress(int curHP_);

	
private:
	//设置前景血条显示的长度  
	void setTextureRect(const CCRect &rect);

	//血条
	Sprite* pBack;
	Sprite* pFront;
	//血量
	int totalHP;
	int curHP;

	float scale;
};

#endif // ! _PROGRESSVIEW_H_