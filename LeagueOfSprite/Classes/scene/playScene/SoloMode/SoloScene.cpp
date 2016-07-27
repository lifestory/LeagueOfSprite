#include "SoloScene.h"

SoloScene* SoloScene::createScene()
{
	auto scene = new SoloScene();
	//scene->initWithPhysics();
	//scene->getPhysicsWorld()->setGravity(Vec2(0, -200));
	scene->autorelease();
	return scene;
}

bool SoloScene::init() {
	if (!Scene::init())
	{
		return false;
	}

	//play background music
	SoundManager::getInstance()->gameSceneinit();

	this->initWithPhysics();
	this->getPhysicsWorld()->setGravity(Vec2(0, -400));
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	isGameEnded = false;

	//add map
	auto spbk = Sprite::create("GameScene/scene1.png");
	//spbk->setPosition(Point::ZERO);
	//spbk->setAnchorPoint(Point::ZERO);
	spbk->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(spbk);

	//add pause menuitem
	/*MenuItemImage* pPauseItem = MenuItemImage::create("GameScene/Pause/PauseClickBefore.png", "GameScene/Pause/PauseClickAfter.png", this, menu_selector(GameScene::ClickStop));
	pPauseItem->setPosition(Vec2(visibleSize.width - pPauseItem->getContentSize().width / 2, visibleSize.height - pPauseItem->getContentSize().height / 2));
	auto pMenu = Menu::create(pPauseItem, NULL);
	pMenu->setPosition(0, 0);
	this->addChild(pMenu, 1);*/

	//add player
	this->addChild(PlayerController::getInstance(), 1);
	this->addChild(Player2Controller::getInstance(), 1);

	//add fence
	auto fence1 = Sprite::create("Model/fence/fence1.png");
	fence1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.1 + fence1->getContentSize().height / 2));
	auto fenceBody = PhysicsBody::createBox(fence1->getContentSize());
	fenceBody->setGravityEnable(false);
	fenceBody->setDynamic(false);
	fenceBody->setCategoryBitmask(0xFFFFFF0F);
	fenceBody->setCollisionBitmask(0xFFFFFFFF);
	fenceBody->setContactTestBitmask(0x00000000);
	fence1->setPhysicsBody(fenceBody);
	this->addChild(fence1, 1);

	auto ground = Node::create();
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height*0.1), PhysicsMaterial(0.99f, 0.0f, 0.99f));
	body->setTag(Constant::getEdgeTag());
	ground->setPhysicsBody(body);
	ground->setPosition(visibleSize.width / 2, visibleSize.height*0.05);
	//ground->getPhysicsBody()->setDynamic(false);
	ground->getPhysicsBody()->setGravityEnable(false);
	//ground->getPhysicsBody()->setDynamic(false);
	ground->getPhysicsBody()->setCategoryBitmask(0x000000FF);
	ground->getPhysicsBody()->setCollisionBitmask(0xFFFFFFFF);
	ground->getPhysicsBody()->setContactTestBitmask(0x00000FFF);

	this->addChild(ground, 1);

	auto leftwall = Node::create();
	auto wallbody = PhysicsBody::createEdgeSegment(Vec2(0, 100), Vec2(0, 640));
	wallbody->setTag(Constant::getEdgeTag());
	leftwall->setPhysicsBody(wallbody);
	//ground->getPhysicsBody()->setDynamic(false);
	leftwall->getPhysicsBody()->setGravityEnable(false);
	leftwall->getPhysicsBody()->setDynamic(false);
	leftwall->getPhysicsBody()->setCategoryBitmask(0x000000F0);
	leftwall->getPhysicsBody()->setCollisionBitmask(0xFFFFFFFF);
	leftwall->getPhysicsBody()->setContactTestBitmask(0x00000000);

	this->addChild(leftwall, 1);

	auto rightwall = Node::create();
	auto rightwallbody = PhysicsBody::createEdgeSegment(Vec2(1050, 100), Vec2(1050, 640), PhysicsMaterial(0.99f, 0.0f, 0.99f));
	rightwallbody->setTag(Constant::getEdgeTag());
	rightwall->setPhysicsBody(rightwallbody);
	//ground->getPhysicsBody()->setDynamic(false);
	rightwall->getPhysicsBody()->setGravityEnable(false);
	rightwall->getPhysicsBody()->setCategoryBitmask(0x000000FF);
	rightwall->getPhysicsBody()->setCollisionBitmask(0xFFFFFFFF);
	rightwall->getPhysicsBody()->setContactTestBitmask(0x0000000F);

	this->addChild(rightwall, 1);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(SoloScene::onContactBegin, this);
	listener->onContactSeparate = CC_CALLBACK_1(SoloScene::onContactSeparate, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//add keyboardEventListener
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(SoloScene::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(SoloScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	scheduleUpdate();

	return true;
}

bool SoloScene::onContactBegin(PhysicsContact& contact) {
	if (contact.getShapeB()->getBody() == NULL || contact.getShapeB()->getBody()->getNode() == NULL
		|| contact.getShapeA()->getBody() == NULL || contact.getShapeA()->getBody()->getNode() == NULL) {
		return false;
	}


	int tagA = contact.getShapeA()->getBody()->getTag();
	int tagB = contact.getShapeB()->getBody()->getTag();
	log("tagA: %d", tagA);
	log("tagB: %d", tagB);

	//weapon hit ground
	if (tagA == Constant::getEdgeTag() && tagB == Constant::getArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdgeTag() && tagA == Constant::getArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//player2 weapon hit ground
	if (tagA == Constant::getEdgeTag() && tagB == Constant::getPlayer2ArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdgeTag() && tagA == Constant::getPlayer2ArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//player2 weapon hit weapon
	if (tagA == Constant::getPlayer2ArrowTag() && tagB == Constant::getArrowTag()) {
		auto explosion = ParticleExplosion::create();
		auto posA = contact.getShapeA()->getBody()->getNode()->getPosition();
		auto posB = contact.getShapeB()->getBody()->getNode()->getPosition();

		explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
		explosion->setEmitterMode(kCCParticleModeRadius);
		explosion->setEndRadius(15);
		explosion->setDuration(0.1);
		explosion->setLife(0.1);
		explosion->setColor(Color3B::RED);
		this->addChild(explosion);

		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getPlayer2ArrowTag() && tagA == Constant::getArrowTag()) {
		auto explosion = ParticleExplosion::create();
		auto posA = contact.getShapeA()->getBody()->getNode()->getPosition();
		auto posB = contact.getShapeB()->getBody()->getNode()->getPosition();

		explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
		explosion->setEmitterMode(kCCParticleModeRadius);
		explosion->setEndRadius(15);
		explosion->setDuration(0.1);
		explosion->setLife(0.1);
		explosion->setColor(Color3B::RED);
		this->addChild(explosion);

		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//weapon hit player2
	if (tagA == Constant::getPlayer2Tag() && tagB == Constant::getArrowTag()) {
		contact.getShapeB()->getBody()->removeFromWorld();
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		int damage = PlayerController::getInstance()->getPlayer()->getBasicDamage();
		//MonsterController::getInstance()->getMonster()->beingHit();
		Player2Controller::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - damage);
		Player2Controller::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}
	else if (tagB == Constant::getPlayer2Tag() && tagA == Constant::getArrowTag()) {
		contact.getShapeA()->getBody()->removeFromWorld();
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		int damage = PlayerController::getInstance()->getPlayer()->getBasicDamage();
		Player2Controller::getInstance()->updateBlood(Player2Controller::getInstance()->getPlayer2()->getHP() - damage);
		Player2Controller::getInstance()->updateBloodbar(Player2Controller::getInstance()->getPlayer2()->getHP());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}

	//weapon hit player
	if (tagA == Constant::getPlayerTag() && tagB == Constant::getPlayer2ArrowTag()) {
		if (PlayerController::getInstance()->getPlayer()->getShielding() == false) {
			contact.getShapeB()->getBody()->removeFromWorld();
			contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
			int damage = Player2Controller::getInstance()->getPlayer2()->getBasicDamage();
			//PlayerController::getInstance()->updateBloodbarforDamaging(damage);
			log("damage:     %d", PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
			SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
		}
		else {
			auto explosion = ParticleExplosion::create();
			auto posA = contact.getShapeA()->getBody()->getNode()->getPosition();
			auto posB = contact.getShapeB()->getBody()->getNode()->getPosition();
			explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setEmitterMode(kCCParticleModeRadius);
			explosion->setEndRadius(15);
			explosion->setDuration(0.1);
			explosion->setLife(0.1);
			explosion->setColor(Color3B::RED);
			this->addChild(explosion);
			contact.getShapeB()->getBody()->removeFromWorld();
			contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}

	}
	else if (tagB == Constant::getPlayerTag() && tagA == Constant::getPlayer2ArrowTag()) {
		if (PlayerController::getInstance()->getPlayer()->getShielding() == false) {
			contact.getShapeA()->getBody()->removeFromWorld();
			contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
			int damage = Player2Controller::getInstance()->getPlayer2()->getBasicDamage();
			//PlayerController::getInstance()->updateBloodbarforDamaging(damage);
			log("damage:     %d", PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
			SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
		}
		else {
			auto explosion = ParticleExplosion::create();
			auto posA = contact.getShapeA()->getBody()->getNode()->getPosition();
			auto posB = contact.getShapeB()->getBody()->getNode()->getPosition();
			explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setEmitterMode(kCCParticleModeRadius);
			explosion->setEndRadius(15);
			explosion->setDuration(0.1);
			explosion->setLife(0.1);
			explosion->setColor(Color3B::RED);
			this->addChild(explosion);
			contact.getShapeA()->getBody()->removeFromWorld();
			contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}
	}

	//storm hit wall
	if (tagA == Constant::getEdgeTag() && tagB == Constant::getStormTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdgeTag() && tagA == Constant::getStormTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//storm hit player2
	if (tagA == Constant::getPlayer2Tag() && tagB == Constant::getStormTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		Player2Controller::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - 10);
		Player2Controller::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}
	else if (tagB == Constant::getPlayer2Tag() && tagA == Constant::getStormTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		Player2Controller::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - 10);
		Player2Controller::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}

	//storm2 hit player
	if (tagA == Constant::getPlayerTag() && tagB == Constant::getStorm2Tag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		PlayerController::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - 10);
		PlayerController::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}
	else if (tagB == Constant::getPlayerTag() && tagA == Constant::getStorm2Tag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		PlayerController::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - 10);
		PlayerController::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}

	//player land ground
	if (tagA == Constant::getPlayerTag() && tagB == Constant::getEdgeTag()) {
		PlayerController::getInstance()->setOnAir(false);
		PlayerController::getInstance()->setSecondJump(false);
	}
	else if (tagB == Constant::getPlayerTag() && tagA == Constant::getEdgeTag()) {
		PlayerController::getInstance()->setOnAir(false);
		PlayerController::getInstance()->setSecondJump(false);
	}

	//player2 land ground
	if (tagA == Constant::getPlayer2Tag() && tagB == Constant::getEdgeTag()) {
		Player2Controller::getInstance()->setOnAir(false);
		Player2Controller::getInstance()->setSecondJump(false);
	}
	else if (tagB == Constant::getPlayer2Tag() && tagA == Constant::getEdgeTag()) {
		Player2Controller::getInstance()->setOnAir(false);
		Player2Controller::getInstance()->setSecondJump(false);
	}

	return true;
}

void SoloScene::onContactSeparate(PhysicsContact& contact) {

}

void SoloScene::ClickStop(Object* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);


	renderTexture->begin();
	this->visit();
	renderTexture->end();

	Director::getInstance()->pushScene(GamePause::soloScene(renderTexture));
}

void SoloScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
		renderTexture->begin();
		this->visit();
		renderTexture->end();
		Director::getInstance()->pushScene(GamePause::soloScene(renderTexture));
	}
}

void SoloScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {

}

void SoloScene::update(float f) {
	if (isGameEnded == true) {
		return;
	}
	if (Player2Controller::getInstance()->getBloodBar()->getCurrentProgress() <= 0) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
		renderTexture->begin();
		this->visit();
		renderTexture->end();
		Director::getInstance()->pushScene(GameController::getInstance()->scene(renderTexture, Constant::getPlayWin(), Constant::getSoloMode()));
		isGameEnded = true;
	}
	else if (PlayerController::getInstance()->getBloodBar()->getCurrentProgress() <= 0) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
		renderTexture->begin();
		this->visit();
		renderTexture->end();
		Director::getInstance()->pushScene(GameController::getInstance()->scene(renderTexture, Constant::getPlayer2Win(), Constant::getSoloMode()));
		isGameEnded = true;
	}
}