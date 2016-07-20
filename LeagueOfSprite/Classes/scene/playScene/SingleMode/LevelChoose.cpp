#include "LevelChoose.h"
#include "math.h"
#include "string"


bool LevelChoose::init() {
	bool flag = false;
	do
	{
		if (!Layer::init())
		{
			return false;
		}

	//if (!Layer::init()) {
	//	return false;
	//}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	log("vi = %d", visibleSize.width);
	log("%d", visibleSize.height);
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	//auto background = Sprite::create("PlayScene/background.png");
	//background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//this->addChild(background);

	ScrollView* scrollview = ScrollView::create(Size(winSize.width, winSize.height));

	//add layer
	Layer* layer = Layer::create();
	char str[64] = { 0 };
	log("%f", winSize.width);
	log("%f", winSize.height);
	for (int i = 1; i <= 3; i++)
	{
		//String* str = String::createWithFormat("%d.png", i);
		sprintf(str, "PlayScene/modeChooseScene/SingleMode/level%d%d.png", i, i);//Êä³öµ½Ö¸¶¨×Ö·û´®
		//String* end = String::create(".png");
		//String* allstr = "PlayScene/modeChooseScene/SingleMode/level" + i + end;
		log("%s", str);
		Sprite* spr = Sprite::create(str);
		spr->setPosition(winSize.width/2 + winSize.width *(i-1) , winSize.height/2);
		log("spr->getPositionX()");
		log("%f", spr->getPositionX());
		layer->addChild(spr);
	}

	log("ssssssssssssssssss");

	//ÉèÖÃscrollviewÈÝÆ÷´óÐ¡
	scrollview->setContainer(layer);
	scrollview->setContentSize(Size(winSize.width * 5, winSize.height));

	//ÆÁ±Î´¥Ãþ
	scrollview->setTouchEnabled(false);
	scrollview->setContentOffset(Point(0, 0));

	log("ttttttttttttttttttt");

	this->setTouchEnabled(true);
	this->addChild(scrollview);

	scrollView_ = scrollview;
	this->curLevel = 0;


	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);

	auto select = MenuItemImage::create("PlayScene/playClickBefore.png", "PlayScene/playClickAfter.png", CC_CALLBACK_1(LevelChoose::ClickSelect, this));
	select->setPosition(visibleSize.width - select->getContentSize().width/2, visibleSize.height*0.2);
	menu->addChild(select);

	auto back = MenuItemImage::create("PlayScene/backClickBefore.png", "PlayScene/backClickAfter.png", CC_CALLBACK_1(LevelChoose::ClickBack, this));
	back->setPosition(visibleSize.width - back->getContentSize().width / 2, visibleSize.height*0.1);
	menu->addChild(back);


	this->addChild(menu, 1);

	flag = true;
	}
	while (0);

	EventListenerTouchOneByOne * event = EventListenerTouchOneByOne::create();
	event->setSwallowTouches(true);
	event->onTouchBegan = CC_CALLBACK_2(LevelChoose::onTouchBegan, this);
	event->onTouchMoved = CC_CALLBACK_2(LevelChoose::onTouchMoved, this);
	event->onTouchEnded = CC_CALLBACK_2(LevelChoose::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);




	return flag;
}


void LevelChoose::ClickSelect(Ref *sender) {
	SimpleAudioEngine::getInstance()->playEffect("Sound/Click.wav");
	auto scene = GameScene::create();
	Director::getInstance()->replaceScene(scene);
}
void LevelChoose::ClickBack(Ref *sender) {
	auto scene = ModeChooseScene::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}




bool LevelChoose::onTouchBegan(Touch *touch, Event *unused_event)
{
	this->touchPoint = touch->getLocation();
	this->offsetPoint = this->scrollView_->getContentSize();

	if ((int)this->offsetPoint.x % ((int)Director::sharedDirector()->getWinSize().width) == 0)
	{
		return true;
	}

	return false;
}
void LevelChoose::onTouchMoved(Touch *touch, Event *unused_event)
{
	Point point = touch->getLocation();
	Point dir = Point(point - this->touchPoint);
	log("%f", dir.x);
	log("%f", dir.y);
	//x
	Point sprdir = Point(dir.x + this->offsetPoint.x, 0);
	this->scrollView_->setContentOffset(sprdir);
}
void LevelChoose::onTouchEnded(Touch *touch, Event *unused_event)
{
	Point endPos = touch->getLocation();
	float dis = endPos.x - this->touchPoint.x;
	if (fabs(dis) < 20)
	{
		this->adjustScrollView(0);
	}
	else
	{
		this->adjustScrollView(dis);
	}
}

void LevelChoose::adjustScrollView(float offset)
{
	auto winSize = Director::getInstance()->getWinSize();
	if (offset < 0)
	{
		curLevel++;
	}
	else if (offset > 0)
	{
		curLevel--;
	}
	if (curLevel < 1)
	{
		curLevel = 1;
	}
	if (curLevel > 3)
	{
		curLevel = 3;
	}

	auto label = Label::createWithTTF("HelloWorld", "fonts/Marker Felt.ttf", 24);
	//auto label = Label::createWithTTF("fonts/arial.ttf", (char* )curLevel);
	label->setPosition(winSize.width/2, winSize.height/2 - 50);
	Point adjustPoint = Point(-winSize.width*(curLevel-1), 0);
	this->scrollView_->setContentOffsetInDuration(adjustPoint, 0.2f);
}

int LevelChoose::getCurLevel()
{
	return curLevel;
}
void LevelChoose::setCurLevel(int num)
{
	curLevel = num;
}