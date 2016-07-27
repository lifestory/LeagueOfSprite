#include "GameScene.h"



GameScene* GameScene::createScene()
{
	auto scene = new GameScene();
	//scene->initWithPhysics();
	//scene->getPhysicsWorld()->setGravity(Vec2(0, -200));
	scene->autorelease();
	return scene;
}

bool GameScene::init() {
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

	if (GameManager::getInstance()->getGameLevel() == 1) {
		auto spbk = Sprite::create("GameScene/scene1.png");
		spbk->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(spbk);

		//add fence1
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

		auto listener = EventListenerPhysicsContact::create();
		listener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
		listener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeparate, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	}
	else if (GameManager::getInstance()->getGameLevel() == 2) {
		auto spbk = Sprite::create("GameScene/scene2.png");
		spbk->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(spbk);

		//add fence2
		auto fence2 = Sprite::create("Model/fence/fence2.png");
		fence2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.1 + fence2->getContentSize().height / 2));
		auto fenceBody = PhysicsBody::createBox(fence2->getContentSize());
		fenceBody->setGravityEnable(false);
		fenceBody->setDynamic(false);
		fenceBody->setCategoryBitmask(0xFFFFFF0F);
		fenceBody->setCollisionBitmask(0xFFFFFFFF);
		fenceBody->setContactTestBitmask(0x00000000);
		fence2->setPhysicsBody(fenceBody);
		this->addChild(fence2, 1);

		auto listener = EventListenerPhysicsContact::create();
		listener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin2, this);
		listener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeparate2, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	}
	else if (GameManager::getInstance()->getGameLevel() == 3) {
		auto spbk = Sprite::create("GameScene/scene3.png");
		spbk->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(spbk);

		//add fence3
		auto fence3 = Sprite::create("Model/fence/fence3.png");
		fence3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.1+fence3->getContentSize().height/2));
		auto fenceBody = PhysicsBody::createBox(fence3->getContentSize());
		fenceBody->setGravityEnable(false);
		fenceBody->setDynamic(false);
		fenceBody->setCategoryBitmask(0xFFFFFF0F);
		fenceBody->setCollisionBitmask(0xFFFFFFFF);
		fenceBody->setContactTestBitmask(0x00000000);
		fence3->setPhysicsBody(fenceBody);
		this->addChild(fence3, 1);

		auto listener = EventListenerPhysicsContact::create();
		listener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin3, this);
		listener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeparate3, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	}

	//add player
	this->addChild(PlayerController::getInstance(), 1);
	this->addChild(MonsterController::getInstance(), 1);
	

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


	//add keyboardEventListener
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	scheduleUpdate();

	return true;
}

bool GameScene::onContactBegin(PhysicsContact& contact) {
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

	//monster weapon hit ground
	if (tagA == Constant::getEdgeTag() && tagB == Constant::getMonsterArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdgeTag() && tagA == Constant::getMonsterArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//monster weapon hit weapon
	if (tagA == Constant::getMonsterArrowTag() && tagB == Constant::getArrowTag()) {
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
	else if (tagB == Constant::getMonsterArrowTag() && tagA == Constant::getArrowTag()) {
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

	//weapon hit monster
	if (tagA == Constant::getMonsterTag() && tagB == Constant::getArrowTag()) {
		contact.getShapeB()->getBody()->removeFromWorld();
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		int damage = PlayerController::getInstance()->getPlayer()->getBasicDamage();
		MonsterController::getInstance()->getMonster()->beingHit();
		MonsterController::getInstance()->updateBloodbarforDamaging(damage, Constant::getMonsterTag());
		MonsterController::getInstance()->updateBlood(MonsterController::getInstance()->getMonster()->getHp() - damage, Constant::getMonsterTag());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}
	else if (tagB == Constant::getMonsterTag() && tagA == Constant::getArrowTag()) {
		contact.getShapeA()->getBody()->removeFromWorld();
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		int damage = PlayerController::getInstance()->getPlayer()->getBasicDamage();
		MonsterController::getInstance()->getMonster()->beingHit();
		MonsterController::getInstance()->updateBloodbarforDamaging(damage, Constant::getMonsterTag());
		MonsterController::getInstance()->updateBlood(MonsterController::getInstance()->getMonster()->getHp() - damage, Constant::getMonsterTag());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}

	//weapon hit player
	if (tagA == Constant::getPlayerTag() && tagB == Constant::getMonsterArrowTag()) {
		if (PlayerController::getInstance()->getPlayer()->getShielding() == false) {
			contact.getShapeB()->getBody()->removeFromWorld();
			contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
			int damage = MonsterController::getInstance()->getMonster()->getBasicDamage();
			//PlayerController::getInstance()->updateBloodbarforDamaging(damage);
			log("damage:     %d", PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
			SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
		} else {
			auto explosion = ParticleSystemQuad::create("Model/explosion/particle.plist");
			//explosion->setLife(1.0);
			//explosion->setLifeVar(0.5);
			//explosion->setEndRadius(15);
			explosion->setDuration(1.0);
			//explosion->setEmissionRate(500);
			auto posA = contact.getShapeA()->getBody()->getNode()->getPosition();
			auto posB = contact.getShapeB()->getBody()->getNode()->getPosition();

			explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setAutoRemoveOnFinish(true);
			/*explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setEmitterMode(kCCParticleModeRadius);
			explosion->setEndRadius(15);
			explosion->setDuration(1.0);
			explosion->setLife(1.0);
			explosion->setLifeVar(0.5);
			explosion->setStartColor(Color4F(255, 0, 0, 1));
			explosion->setStartColorVar(Color4F(0, 0, 0, 0));
			explosion->setEndColor(Color4F(255, 0, 0, 1));
			explosion->setEndColorVar(Color4F(0, 0, 0, 0));
			explosion->setEmissionRate(500);*/
			this->addChild(explosion);
			contact.getShapeB()->getBody()->removeFromWorld();
			contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}
		
	}
	else if (tagB == Constant::getPlayerTag() && tagA == Constant::getMonsterArrowTag()) {
		if (PlayerController::getInstance()->getPlayer()->getShielding() == false) {
			contact.getShapeA()->getBody()->removeFromWorld();
			contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
			int damage = MonsterController::getInstance()->getMonster()->getBasicDamage();
			//PlayerController::getInstance()->updateBloodbarforDamaging(damage);
			log("damage:     %d", PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
			SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
		} else {
			//auto explosion = ParticleExplosion::create();
			auto explosion = ParticleSystemQuad::create("Model/explosion/particle.plist");
			//explosion->setLife(1.0);
			//explosion->setLifeVar(0.5);
			//explosion->setEndRadius(15);
			explosion->setDuration(1.0);
			//explosion->setEmissionRate(500);
			auto posA = contact.getShapeA()->getBody()->getNode()->getPosition();
			auto posB = contact.getShapeB()->getBody()->getNode()->getPosition();

			explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setAutoRemoveOnFinish(true);
			/*explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setEmitterMode(kCCParticleModeRadius);
			explosion->setEndRadius(15);
			explosion->setDuration(0.1);
			explosion->setLife(0.1);
			explosion->setColor(Color3B::RED);*/
			this->addChild(explosion);
			contact.getShapeA()->getBody()->removeFromWorld();
			contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}
	}

	//storm hit monster
	if (tagA == Constant::getEdgeTag() && tagB == Constant::getStormTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdgeTag() && tagA == Constant::getStormTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//storm hit right wall
	if (tagA == Constant::getMonsterTag() && tagB == Constant::getStormTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		MonsterController::getInstance()->getMonster()->beingHit();
		MonsterController::getInstance()->updateBloodbarforDamaging(10, Constant::getMonsterTag());
		MonsterController::getInstance()->updateBlood(MonsterController::getInstance()->getMonster()->getHp() - 10, Constant::getMonsterTag());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}
	else if (tagB == Constant::getMonsterTag() && tagA == Constant::getStormTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		MonsterController::getInstance()->getMonster()->beingHit();
		MonsterController::getInstance()->updateBloodbarforDamaging(10, Constant::getMonsterTag());
		MonsterController::getInstance()->updateBlood(MonsterController::getInstance()->getMonster()->getHp() - 10, Constant::getMonsterTag());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}

	//player land ground
	if (tagA == Constant::getPlayerTag() && tagB == Constant::getEdgeTag()) {
		PlayerController::getInstance()->setOnAir(false);
		PlayerController::getInstance()->setSecondJump(false);
	} else if (tagB == Constant::getPlayerTag() && tagA == Constant::getEdgeTag()) {
		PlayerController::getInstance()->setOnAir(false);
		PlayerController::getInstance()->setSecondJump(false);
	}

	return true;
}

void GameScene::onContactSeparate(PhysicsContact& contact) {

}

bool GameScene::onContactBegin2(PhysicsContact& contact) {
	if (contact.getShapeB()->getBody() == NULL || contact.getShapeB()->getBody()->getNode() == NULL
		|| contact.getShapeA()->getBody() == NULL || contact.getShapeA()->getBody()->getNode() == NULL) {
		return false;
	}


	int tagA = contact.getShapeA()->getBody()->getTag();
	int tagB = contact.getShapeB()->getBody()->getTag();

	//weapon hit ground
	if (tagA == Constant::getEdgeTag() && tagB == Constant::getArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdgeTag() && tagA == Constant::getArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//monster2 weapon hit ground
	if (tagA == Constant::getEdgeTag() && tagB == Constant::getMonster2ArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdgeTag() && tagA == Constant::getMonster2ArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//monster weapon hit weapon
	if (tagA == Constant::getMonster2ArrowTag() && tagB == Constant::getArrowTag()) {
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
	else if (tagB == Constant::getMonster2ArrowTag() && tagA == Constant::getArrowTag()) {
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

	//weapon hit monster2
	if (tagA == Constant::getMonster2Tag() && tagB == Constant::getArrowTag()) {
		contact.getShapeB()->getBody()->removeFromWorld();
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		int damage = PlayerController::getInstance()->getPlayer()->getBasicDamage();
		MonsterController::getInstance()->getMonster2()->beingHit();
		MonsterController::getInstance()->updateBloodbarforDamaging(damage, Constant::getMonster2Tag());
		MonsterController::getInstance()->updateBlood(MonsterController::getInstance()->getMonster2()->getHp() - damage, Constant::getMonster2Tag());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}
	else if (tagB == Constant::getMonster2Tag() && tagA == Constant::getArrowTag()) {
		contact.getShapeA()->getBody()->removeFromWorld();
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		int damage = PlayerController::getInstance()->getPlayer()->getBasicDamage();
		MonsterController::getInstance()->getMonster2()->beingHit();
		MonsterController::getInstance()->updateBloodbarforDamaging(damage, Constant::getMonster2Tag());
		MonsterController::getInstance()->updateBlood(MonsterController::getInstance()->getMonster2()->getHp() - damage, Constant::getMonster2Tag());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}

	//weapon hit player
	if (tagA == Constant::getPlayerTag() && tagB == Constant::getMonster2ArrowTag()) {
		if (PlayerController::getInstance()->getPlayer()->getShielding() == false) {
			contact.getShapeB()->getBody()->removeFromWorld();
			contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
			int damage = MonsterController::getInstance()->getMonster2()->getBasicDamage();
			//PlayerController::getInstance()->updateBloodbarforDamaging(damage);
			log("damage:     %d", PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
			SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
		}
		else {
			auto explosion = ParticleSystemQuad::create("Model/explosion/particle.plist");
			//explosion->setLife(1.0);
			//explosion->setLifeVar(0.5);
			//explosion->setEndRadius(15);
			explosion->setDuration(1.0);
			//explosion->setEmissionRate(500);
			auto posA = contact.getShapeA()->getBody()->getNode()->getPosition();
			auto posB = contact.getShapeB()->getBody()->getNode()->getPosition();

			explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setAutoRemoveOnFinish(true);
			/*explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setEmitterMode(kCCParticleModeRadius);
			explosion->setEndRadius(15);
			explosion->setDuration(1.0);
			explosion->setLife(1.0);
			explosion->setLifeVar(0.5);
			explosion->setStartColor(Color4F(255, 0, 0, 1));
			explosion->setStartColorVar(Color4F(0, 0, 0, 0));
			explosion->setEndColor(Color4F(255, 0, 0, 1));
			explosion->setEndColorVar(Color4F(0, 0, 0, 0));
			explosion->setEmissionRate(500);*/
			this->addChild(explosion);
			contact.getShapeB()->getBody()->removeFromWorld();
			contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}

	}
	else if (tagB == Constant::getPlayerTag() && tagA == Constant::getMonster2ArrowTag()) {
		if (PlayerController::getInstance()->getPlayer()->getShielding() == false) {
			contact.getShapeA()->getBody()->removeFromWorld();
			contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
			int damage = MonsterController::getInstance()->getMonster2()->getBasicDamage();
			//PlayerController::getInstance()->updateBloodbarforDamaging(damage);
			log("damage:     %d", PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
			SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
		}
		else {
			//auto explosion = ParticleExplosion::create();
			auto explosion = ParticleSystemQuad::create("Model/explosion/particle.plist");
			//explosion->setLife(1.0);
			//explosion->setLifeVar(0.5);
			//explosion->setEndRadius(15);
			explosion->setDuration(1.0);
			//explosion->setEmissionRate(500);
			auto posA = contact.getShapeA()->getBody()->getNode()->getPosition();
			auto posB = contact.getShapeB()->getBody()->getNode()->getPosition();

			explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setAutoRemoveOnFinish(true);
			/*explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setEmitterMode(kCCParticleModeRadius);
			explosion->setEndRadius(15);
			explosion->setDuration(0.1);
			explosion->setLife(0.1);
			explosion->setColor(Color3B::RED);*/
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

	//storm hit monster2
	if (tagA == Constant::getMonster2Tag() && tagB == Constant::getStormTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		MonsterController::getInstance()->getMonster2()->beingHit();
		MonsterController::getInstance()->updateBloodbarforDamaging(10, Constant::getMonster2Tag());
		MonsterController::getInstance()->updateBlood(MonsterController::getInstance()->getMonster2()->getHp() - 10, Constant::getMonster2Tag());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}
	else if (tagB == Constant::getMonster2Tag() && tagA == Constant::getStormTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		MonsterController::getInstance()->getMonster2()->beingHit();
		MonsterController::getInstance()->updateBloodbarforDamaging(10, Constant::getMonster2Tag());
		MonsterController::getInstance()->updateBlood(MonsterController::getInstance()->getMonster2()->getHp() - 10, Constant::getMonster2Tag());
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

	return true;
}

void GameScene::onContactSeparate2(PhysicsContact& contact) {

}

bool GameScene::onContactBegin3(PhysicsContact& contact) {
	if (contact.getShapeB()->getBody() == NULL || contact.getShapeB()->getBody()->getNode() == NULL
		|| contact.getShapeA()->getBody() == NULL || contact.getShapeA()->getBody()->getNode() == NULL) {
		return false;
	}


	int tagA = contact.getShapeA()->getBody()->getTag();
	int tagB = contact.getShapeB()->getBody()->getTag();

	//weapon hit ground
	if (tagA == Constant::getEdgeTag() && tagB == Constant::getArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdgeTag() && tagA == Constant::getArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//monster3 weapon hit ground
	if (tagA == Constant::getEdgeTag() && tagB == Constant::getMonster3ArrowTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}
	else if (tagB == Constant::getEdgeTag() && tagA == Constant::getMonster3ArrowTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	//monster weapon hit weapon
	if (tagA == Constant::getMonster3ArrowTag() && tagB == Constant::getArrowTag()) {
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
	else if (tagB == Constant::getMonster3ArrowTag() && tagA == Constant::getArrowTag()) {
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

	//weapon hit monster3
	if (tagA == Constant::getMonster3Tag() && tagB == Constant::getArrowTag()) {
		contact.getShapeB()->getBody()->removeFromWorld();
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		int damage = PlayerController::getInstance()->getPlayer()->getBasicDamage();
		MonsterController::getInstance()->getMonster3()->beingHit();
		MonsterController::getInstance()->updateBloodbarforDamaging(damage, Constant::getMonster3Tag());
		MonsterController::getInstance()->updateBlood(MonsterController::getInstance()->getMonster3()->getHp() - damage, Constant::getMonster3Tag());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}
	else if (tagB == Constant::getMonster3Tag() && tagA == Constant::getArrowTag()) {
		contact.getShapeA()->getBody()->removeFromWorld();
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		int damage = PlayerController::getInstance()->getPlayer()->getBasicDamage();
		MonsterController::getInstance()->getMonster3()->beingHit();
		MonsterController::getInstance()->updateBloodbarforDamaging(damage, Constant::getMonster3Tag());
		MonsterController::getInstance()->updateBlood(MonsterController::getInstance()->getMonster3()->getHp() - damage, Constant::getMonster3Tag());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}

	//weapon hit player
	if (tagA == Constant::getPlayerTag() && tagB == Constant::getMonster3ArrowTag()) {
		if (PlayerController::getInstance()->getPlayer()->getShielding() == false) {
			contact.getShapeB()->getBody()->removeFromWorld();
			contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
			int damage = MonsterController::getInstance()->getMonster3()->getBasicDamage();
			//PlayerController::getInstance()->updateBloodbarforDamaging(damage);
			log("damage:     %d", PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
			SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
		}
		else {
			auto explosion = ParticleSystemQuad::create("Model/explosion/particle.plist");
			//explosion->setLife(1.0);
			//explosion->setLifeVar(0.5);
			//explosion->setEndRadius(15);
			explosion->setDuration(1.0);
			//explosion->setEmissionRate(500);
			auto posA = contact.getShapeA()->getBody()->getNode()->getPosition();
			auto posB = contact.getShapeB()->getBody()->getNode()->getPosition();

			explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setAutoRemoveOnFinish(true);
			/*explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setEmitterMode(kCCParticleModeRadius);
			explosion->setEndRadius(15);
			explosion->setDuration(1.0);
			explosion->setLife(1.0);
			explosion->setLifeVar(0.5);
			explosion->setStartColor(Color4F(255, 0, 0, 1));
			explosion->setStartColorVar(Color4F(0, 0, 0, 0));
			explosion->setEndColor(Color4F(255, 0, 0, 1));
			explosion->setEndColorVar(Color4F(0, 0, 0, 0));
			explosion->setEmissionRate(500);*/
			this->addChild(explosion);
			contact.getShapeB()->getBody()->removeFromWorld();
			contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		}

	}
	else if (tagB == Constant::getPlayerTag() && tagA == Constant::getMonster3ArrowTag()) {
		if (PlayerController::getInstance()->getPlayer()->getShielding() == false) {
			contact.getShapeA()->getBody()->removeFromWorld();
			contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
			int damage = MonsterController::getInstance()->getMonster3()->getBasicDamage();
			//PlayerController::getInstance()->updateBloodbarforDamaging(damage);
			log("damage:     %d", PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBlood(PlayerController::getInstance()->getPlayer()->getHP() - damage);
			PlayerController::getInstance()->updateBloodbar(PlayerController::getInstance()->getPlayer()->getHP());
			SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
		}
		else {
			//auto explosion = ParticleExplosion::create();
			auto explosion = ParticleSystemQuad::create("Model/explosion/particle.plist");
			//explosion->setLife(1.0);
			//explosion->setLifeVar(0.5);
			//explosion->setEndRadius(15);
			explosion->setDuration(1.0);
			//explosion->setEmissionRate(500);
			auto posA = contact.getShapeA()->getBody()->getNode()->getPosition();
			auto posB = contact.getShapeB()->getBody()->getNode()->getPosition();

			explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setAutoRemoveOnFinish(true);
			/*explosion->setPosition(Vec2((posA.x + posB.x) / 2, (posA.y + posB.y) / 2));
			explosion->setEmitterMode(kCCParticleModeRadius);
			explosion->setEndRadius(15);
			explosion->setDuration(0.1);
			explosion->setLife(0.1);
			explosion->setColor(Color3B::RED);*/
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

	//storm hit monster3
	if (tagA == Constant::getMonster3Tag() && tagB == Constant::getStormTag()) {
		contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
		MonsterController::getInstance()->getMonster3()->beingHit();
		MonsterController::getInstance()->updateBloodbarforDamaging(10, Constant::getMonster3Tag());
		MonsterController::getInstance()->updateBlood(MonsterController::getInstance()->getMonster3()->getHp() - 10, Constant::getMonster3Tag());
		SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	}
	else if (tagB == Constant::getMonster3Tag() && tagA == Constant::getStormTag()) {
		contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
		MonsterController::getInstance()->getMonster3()->beingHit();
		MonsterController::getInstance()->updateBloodbarforDamaging(10, Constant::getMonster3Tag());
		MonsterController::getInstance()->updateBlood(MonsterController::getInstance()->getMonster3()->getHp() - 10, Constant::getMonster3Tag());
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

	return true;
}

void GameScene::onContactSeparate3(PhysicsContact& contact) {

}

void GameScene::ClickStop(Object* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);


	renderTexture->begin();
	this->visit();
	renderTexture->end();

	Director::getInstance()->pushScene(GamePause::scene(renderTexture));
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
		renderTexture->begin();
		this->visit();
		renderTexture->end();
		Director::getInstance()->pushScene(GamePause::scene(renderTexture));
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	
}

void GameScene::update(float f) {
	if (isGameEnded == true) {
		return;
	}
	if (MonsterController::getInstance()->getBloodBar()->getCurrentProgress() <= 0) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
		renderTexture->begin();
		this->visit();
		renderTexture->end();
		Director::getInstance()->pushScene(GameController::getInstance()->scene(renderTexture, Constant::getPlayWin(), Constant::getSingleMode()));
		isGameEnded = true;
	}
	else if (PlayerController::getInstance()->getBloodBar()->getCurrentProgress() <= 0) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
		renderTexture->begin();
		this->visit();
		renderTexture->end();
		Director::getInstance()->pushScene(GameController::getInstance()->scene(renderTexture, Constant::getPlayLose(), Constant::getSingleMode()));
		isGameEnded = true;
	}
}