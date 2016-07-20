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

	//Ѫ������  
	void setBackgroundTexture(const char *pTexture);
	//Ѫ��ǰ��  
	void setFrontgroundTexture(const char *pTexture);

	//��Ѫ��
	int getTotalProgress();
	void setTotalProgress(int totalHP_);

	//��ǰѪ��
	int getCurrentProgress();
	void setCurrentProgress(int curHP_);

	
private:
	//����ǰ��Ѫ����ʾ�ĳ���  
	void setTextureRect(const CCRect &rect);

	//Ѫ��
	Sprite* pBack;
	Sprite* pFront;
	//Ѫ��
	int totalHP;
	int curHP;

	float scale;
};

#endif // ! _PROGRESSVIEW_H_