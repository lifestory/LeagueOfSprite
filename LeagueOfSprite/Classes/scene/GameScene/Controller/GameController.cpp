#include "GameController.h"

bool GameController::init() {
	if (!Layer::init()) {
		return false;
	}

	//get visibleSize
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	return true;
}

GameController*  GameController::gameController = NULL;
GameController* GameController::getInstance() {
	if (gameController == NULL) {
		gameController = GameController::create();
	}
	return gameController;
}

Scene* GameController::scene(RenderTexture *b, int status, int mode) {
	Scene* scene = Scene::create();
	if (status == Constant::getPlayWin() && mode == Constant::getSingleMode()) {
		Layer *layer = createWinLayer();
		scene->addChild(layer, 1);
	}
	else if (status == Constant::getPlayLose() && mode == Constant::getSingleMode()) {
		Layer *layer = createLoseLayer();
		scene->addChild(layer, 1);
	}
	else if (status == Constant::getPlayWin() && mode == Constant::getSoloMode()) {
		Layer *layer = createPlayerWinLayer();
		scene->addChild(layer, 1);
	}
	else if (status == Constant::getPlayer2Win() && mode == Constant::getSoloMode()) {
		Layer *layer = createPlayer2WinLayer();
		scene->addChild(layer, 1);
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* backspr = Sprite::createWithTexture(b->getSprite()->getTexture());
	backspr->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	backspr->setFlippedY(true);
	backspr->setColor(Color3B::GRAY);
	scene->addChild(backspr);

	return scene;
}

Layer* GameController::createWinLayer() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto layer = Layer::create();
	auto label = Label::create("You Win!", "Arial", 80);
	label->setColor(Color3B::YELLOW);

	label->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	layer->addChild(label, 1);
	//again
	auto next = MenuItemImage::create("GameScene/Gameover/ContinueClickBefore.png", "GameScene/Gameover/ContinueClickAfter.png", CC_CALLBACK_0(GameController::clickNext, this));
	next->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);

	//Restart
	auto again = MenuItemImage::create("GameScene/Gameover/RestartClickBefore.png", "GameScene/Gameover/RestartClickAfter.png", CC_CALLBACK_0(GameController::clickAgain, this));
	again->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	//JumptoMainmenu
	auto back = MenuItemImage::create("GameScene/Gameover/MenuClickBefore.png", "GameScene/Gameover/MenuClickAfter.png", CC_CALLBACK_0(GameController::clickMenu, this));
	back->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 80);


	auto menu = Menu::create(again, next, back, NULL);
	menu->setPosition(Point::ZERO);

	layer->addChild(menu, 2);
	return layer;
}


Layer* GameController::createLoseLayer() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto layer = Layer::create();
	auto label = Label::create("You Lose!", "Arial", 80);
	label->setColor(Color3B::YELLOW);

	label->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	layer->addChild(label, 1);
	//again
	auto next = MenuItemImage::create("GameScene/Gameover/ContinueClickBefore.png", "GameScene/Gameover/ContinueClickAfter.png", CC_CALLBACK_0(GameController::clickNext, this));
	next->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);

	//Restart
	auto again = MenuItemImage::create("GameScene/Gameover/RestartClickBefore.png", "GameScene/Gameover/RestartClickAfter.png", CC_CALLBACK_0(GameController::clickAgain, this));
	again->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	//JumptoMainmenu
	auto back = MenuItemImage::create("GameScene/Gameover/MenuClickBefore.png", "GameScene/Gameover/MenuClickAfter.png", CC_CALLBACK_0(GameController::clickMenu, this));
	back->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 80);


	auto menu = Menu::create(again, next, back, NULL);
	menu->setPosition(Point::ZERO);

	layer->addChild(menu, 2);
	return layer;
}

void GameController::clickAgain() {
	Director::getInstance()->popScene();
	PlayerController::getInstance()->releasePlayerController();
	MonsterController::getInstance()->releaseMonsterController();
	auto scene = GameScene::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}

void GameController::clickNext() {
	Director::getInstance()->popScene();
	PlayerController::getInstance()->releasePlayerController();
	MonsterController::getInstance()->releaseMonsterController();
	GameManager::getInstance()->setGameLevel(GameManager::getInstance()->getGameLevel()+1);
	auto scene = GameScene::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}

void GameController::clickMenu() {
	Director::getInstance()->popScene();
	PlayerController::getInstance()->releasePlayerController();
	MonsterController::getInstance()->releaseMonsterController();
	auto scene = HelloWorld::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}

void GameController::setGameStatus(int status) {
	gameStatus = status;
}

int GameController::getGameStatus() {
	return gameStatus;
}

void GameController::soloclickAgain() {
	Director::getInstance()->popScene();
	PlayerController::getInstance()->releasePlayerController();
	Player2Controller::getInstance()->releasePlayer2Controller();
	auto scene = SoloScene::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}

void GameController::soloclickNext() {

}

void GameController::soloclickMenu() {
	Director::getInstance()->popScene();
	PlayerController::getInstance()->releasePlayerController();
	Player2Controller::getInstance()->releasePlayer2Controller();
	auto scene = HelloWorld::create();
	auto trans = TransitionPageTurn::create(0.5f, scene, false);
	Director::getInstance()->replaceScene(trans);
}

Layer* GameController::createPlayerWinLayer() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto layer = Layer::create();
	auto label = Label::create("Player1 Win!", "Arial", 80);
	label->setColor(Color3B::YELLOW);

	label->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	layer->addChild(label, 1);
	//again
	auto next = MenuItemImage::create("GameScene/Gameover/ContinueClickBefore.png", "GameScene/Gameover/ContinueClickAfter.png", CC_CALLBACK_0(GameController::soloclickNext, this));
	next->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);

	//Restart
	auto again = MenuItemImage::create("GameScene/Gameover/RestartClickBefore.png", "GameScene/Gameover/RestartClickAfter.png", CC_CALLBACK_0(GameController::soloclickAgain, this));
	again->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	//JumptoMainmenu
	auto back = MenuItemImage::create("GameScene/Gameover/MenuClickBefore.png", "GameScene/Gameover/MenuClickAfter.png", CC_CALLBACK_0(GameController::soloclickMenu, this));
	back->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 80);


	auto menu = Menu::create(again, next, back, NULL);
	menu->setPosition(Point::ZERO);

	layer->addChild(menu, 2);
	return layer;
}

Layer* GameController::createPlayer2WinLayer() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto layer = Layer::create();
	auto label = Label::create("Player2 Win!", "Arial", 80);
	label->setColor(Color3B::YELLOW);

	label->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	layer->addChild(label, 1);
	//again
	auto next = MenuItemImage::create("GameScene/Gameover/ContinueClickBefore.png", "GameScene/Gameover/ContinueClickAfter.png", CC_CALLBACK_0(GameController::soloclickNext, this));
	next->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);

	//Restart
	auto again = MenuItemImage::create("GameScene/Gameover/RestartClickBefore.png", "GameScene/Gameover/RestartClickAfter.png", CC_CALLBACK_0(GameController::soloclickAgain, this));
	again->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	//JumptoMainmenu
	auto back = MenuItemImage::create("GameScene/Gameover/MenuClickBefore.png", "GameScene/Gameover/MenuClickAfter.png", CC_CALLBACK_0(GameController::soloclickMenu, this));
	back->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 80);


	auto menu = Menu::create(again, next, back, NULL);
	menu->setPosition(Point::ZERO);

	layer->addChild(menu, 2);
	return layer;
}