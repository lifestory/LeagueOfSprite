#include "GamePause.h"


Scene* GamePause::scene(RenderTexture* sqr)
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
	if (!Layer::init())
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


	Menu* menu = Menu::create(ContinueGameItem, RestartGameItem, JumpMainmenuItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu, 2);

	return true;
}

Scene* GamePause::soloScene(RenderTexture* sqr) {
	auto scene = Scene::create();

	//get visibleSize
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Continue
	auto soloContinueGameItem = MenuItemImage::create("GameScene/Pause/ContinueClickBefore.png", "GameScene/Pause/ContinueClickAfter.png", scene, menu_selector(GamePause::soloContinueGame));
	soloContinueGameItem->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);

	//Restart
	auto soloRestartGameItem = MenuItemImage::create("GameScene/Pause/RestartClickBefore.png", "GameScene/Pause/RestartClickAfter.png", scene, menu_selector(GamePause::soloRestartGame));
	soloRestartGameItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	//JumptoMainmenu
	auto soloJumpMainmenuItem = MenuItemImage::create("GameScene/Pause/MenuClickBefore.png", "GameScene/Pause/MenuClickAfter.png", scene, menu_selector(GamePause::soloJumpMainmenu));
	soloJumpMainmenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 80);


	Menu* menu = Menu::create(soloContinueGameItem, soloRestartGameItem, soloJumpMainmenuItem, NULL);
	menu->setPosition(Point::ZERO);
	scene->addChild(menu, 1);
	

	Sprite* backspr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	backspr->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	backspr->setFlippedY(true);
	backspr->setColor(Color3B::GRAY);
	scene->addChild(backspr);

	return scene;
}

//continue
void GamePause::ContinueGame(Ref* pSender)
{
	Director::getInstance()->popScene();
}

//restart
void GamePause::RestartGame(Ref* pSender)
{
	Director::getInstance()->popScene();
	PlayerController::getInstance()->releasePlayerController();
	MonsterController::getInstance()->releaseMonsterController();
	auto scene = GameScene::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}
//jump to Mainmenu
void GamePause::JumpMainmenu(Ref* pSender)
{
	Director::getInstance()->popScene();
	PlayerController::getInstance()->releasePlayerController();
	MonsterController::getInstance()->releaseMonsterController();
	auto scene = HelloWorld::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}

void GamePause::soloContinueGame(Ref* pSender) {
	Director::getInstance()->popScene();
}

void GamePause::soloRestartGame(Ref* pSender) {
	Director::getInstance()->popScene();
	PlayerController::getInstance()->releasePlayerController();
	Player2Controller::getInstance()->releasePlayer2Controller();
	auto scene = SoloScene::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}

void GamePause::soloJumpMainmenu(Ref* pSender) {
	Director::getInstance()->popScene();
	PlayerController::getInstance()->releasePlayerController();
	Player2Controller::getInstance()->releasePlayer2Controller();
	auto scene = HelloWorld::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}