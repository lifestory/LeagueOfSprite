#include "ProgressView.h"

//init
ProgressView::ProgressView()
{
	pBack = NULL;
	pFront = NULL;
	totalHP = 0; 
	curHP = 0;
	scale = 1.0f;
}

//血条背景  
void ProgressView::setBackgroundTexture(const char *pTexture)
{
	pBack = Sprite::create(pTexture);
	this->addChild(pBack);
}
//血条前景  
void ProgressView::setFrontgroundTexture(const char *pTexture)
{
	pFront = Sprite::create(pTexture);
	pFront->setPosition(Point(-pFront->getContentSize().width / 2, 0));
	pFront->setAnchorPoint(Point(0.0f, 0.5f));
	this->addChild(pFront);
}

//总血量
int ProgressView::getTotalProgress()
{
	return totalHP;
}
void ProgressView::setTotalProgress(int totalHP_)
{
	scale = (float)(pFront->getContentSize().width / totalHP_);
	totalHP = totalHP_;
}

//当前血量
int ProgressView::getCurrentProgress()
{
	return curHP;
}
void ProgressView::setCurrentProgress(int curHP_)
{
	if (curHP_ == NULL)
	{
		return;
	}
	if (curHP_ < 0)
	{
		curHP_ = 0;
	}
	if (curHP_ > totalHP)
	{
		curHP_ = totalHP;
	}
	curHP = curHP_;

	float width = curHP_ * scale;
    float height = pFront->getContentSize().height;
	CCPoint sta = pFront->getTextureRect().origin;
	Rect re = CCRectMake(sta.x, sta.y, width, height);
	setTextureRect(re);
}

void ProgressView::setTextureRect(const Rect &rect)
{
	pFront->setTextureRect(rect);
}
