#include "GamePause.h"


CCScene* GamePause::scene(RenderTexture* sqr)
{
	Scene* scene = Scene::create();
	GamePause* layer = GamePause::create();
	//add scene onto the gamelayer
	scene->addChild(layer, 1);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* backspr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	backspr->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	backspr->setFlippedY(true);
	backspr->setColor(Color3B::GRAY);
	scene->addChild(backspr);

	//Sprite* back_small_spr = Sprite::create("GamePause/back_pause.png");
	//back_small_spr->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//scene->addChild(back_small_spr);

	return scene;
}

//add CCreanerTextrue as a screenshot
bool GamePause::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//get visibleSize
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Continue
	ContinueGameItem = MenuItemImage::create("GameScene/Pause/ContinueClickBefore.png", "GameScene/Pause/ContinueClickAfter.png", this, menu_selector(GamePause::ContinueGame));
	ContinueGameItem->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);

	//Restart
	RestartGameItem = MenuItemImage::create("GameScene/Pause/RestartClickBefore.png", "GameScene/Pause/RestartClickAfter.png", this, menu_selector(GamePause::RestartGame));
	RestartGameItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	//JumptoMainmenu
	JumpMainmenuItem = MenuItemImage::create("GameScene/Pause/MenuClickBefore.png", "GameScene/Pause/MenuClickAfter.png", this, menu_selector(GamePause::JumpMainmenu));
	JumpMainmenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 80);


	CCMenu* menu = CCMenu::create(ContinueGameItem, RestartGameItem, JumpMainmenuItem, NULL);
	menu->setPosition(CCPoint::ZERO);

	this->addChild(menu, 2);

	return true;
}


//continue
void GamePause::ContinueGame(Object* pSender)
{
	Director::getInstance()->popScene();
}
//restart
void GamePause::RestartGame(Object* pSender)
{

	Director::getInstance()->popScene();
	PlayerController::getInstance()->releasePlayerController();
	MonsterController::getInstance()->releaseMonsterController();
	//PlayerController::getInstance()->removeFromParentAndCleanup(true);
	//MonsterController::getInstance()->removeFromParentAndCleanup(true);
	//PlayerController::getInstance()->removeFromParent();
	//MonsterController::getInstance()->removeFromParent();

	auto scene = GameScene::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
	//CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}
//jump to Mainmenu
void GamePause::JumpMainmenu(Object* pSender)
{
	//PlayerController::getInstance()->getParent()->removeAllChildrenWithCleanup(true);
	//PlayerController::getInstance()->removeFromParent();
	//MonsterController::getInstance()->removeFromParent();
	//MonsterController::getInstance()->getParent()->removeAllChildrenWithCleanup(true);
	//PlayerController::getInstance()->removeFromParentAndCleanup(true);
	//MonsterController::getInstance()->removeFromParentAndCleanup(true);
	Director::getInstance()->popScene();
	PlayerController::getInstance()->releasePlayerController();
	MonsterController::getInstance()->releaseMonsterController();
	auto scene = HelloWorld::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
	//CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}


