#include "framework.h"
#include "TestScene.h"
#include "GridMap.h"
#include "CameraManager.h"
#include "RenderManager.h"
#include "Node.h"
#include "Dirt.h"
#include "Player.h"
#include "EntityManager.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "DebugUI.h"
#include "InventoryUI.h"
#include "HPBarUI.h"
#include "MPBarUI.h"
#include "CraftUI.h"
#include "Zombie.h"
#include "SoundManager.h"
#include "LightManager.h"
#include "copperPickAxe.h"
#include "ItemManager.h"
#include "DirtWall.h"
#include "Wood.h"
#include "Copper.h"
TestScene::TestScene() : player(nullptr)
{
}

TestScene::~TestScene()
{
	release();
}

void TestScene::init()
{
	gridMap->init(800, 600);
	gridMap->setSize(16);

	cam->update();
	cam->setBorder(Vector2::zero(), Vector2{ 800 * 16, 600 * 16 });

	std::list<Node*> nodes = gridMap->findNodes(Vector2Int{ 0,0 }, Vector2Int{1959,1 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		Dirt* dirt = new Dirt();
		dirt->init(node->position());
		node->block(dirt);

		DirtWall* dirtWall = new DirtWall();
		dirtWall->init(node->position());
		node->wall(dirtWall);
	}
	nodes.clear();

	Vector2Int startPos = gridMap->findNode(Vector2{ 712.0f, 360.0f } / 2)->position();
	nodes = gridMap->findNodes(startPos, startPos + Vector2Int{100, 0});
	for (auto& node : nodes)
	{
		if (!node) continue;
		Dirt* dirt = new Dirt();
		dirt->init(node->position());
		node->block(dirt);
	}
	nodes.clear();
	
	nodes = gridMap->findNodes(startPos + Vector2Int{ 0, -1 }, startPos + Vector2Int{ 100, -1 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		Dirt* dirt = new Dirt();
		dirt->init(node->position());
		node->block(dirt);
	}

	nodes.clear();
	nodes = gridMap->findNodes(startPos + Vector2Int{ 0, -2 }, startPos + Vector2Int{ 100, -2 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		Dirt* dirt = new Dirt();
		dirt->init(node->position());
		node->block(dirt);
	}
	nodes.clear();
	
	nodes = gridMap->findNodes(startPos + Vector2Int{ 10, 0 }, startPos + Vector2Int{ 10, 5 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		if (node->block()) continue;
		Dirt* dirt = new Dirt();
		dirt->init(node->position());
		node->block(dirt);
	}
	nodes.clear();

	nodes = gridMap->findNodes(startPos + Vector2Int{ 0, 5 }, startPos + Vector2Int{ 4, 5 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		Dirt* dirt = new Dirt();
		dirt->init(node->position());
		node->block(dirt);
	}
	 
	Node* node = gridMap->findNode(startPos + Vector2Int{ 0, 1 });
	Dirt* dirt = new Dirt();
	dirt->init(node->position());
	node->block(dirt);

	gridMap->updateAllBlock();


	entityMgr->createPlayer(Vector2{430.0f, 230.0f});
	player = entityMgr->linkPlayer();
	
	rendering->linkplayer(player);
	rendering->linkEntityList(entityMgr->linkList());
	
	Zombie* testMob = new Zombie();
	testMob->init();
	testMob->position({ 700.0f, 400.0f });
	testMob->linkPlayer(player);
	entityMgr->addEntity(testMob);
	
	
	InventoryUI* invenUI = new InventoryUI();
	invenUI->init(rendering->linkplayer()->linkInven());
	
	HPBarUI* hpBar = new HPBarUI();
	hpBar->init(player);
	UIMgr->appendUI(hpBar);
	MPBarUI* mpBar = new MPBarUI();
	mpBar->init(player);
	UIMgr->appendUI(mpBar);
	
	CraftUI* craftUI = new CraftUI();
	craftUI->init();
	UIMgr->appendUI(craftUI);
	UIMgr->appendUI(invenUI);

	itemMgr->init(player);


	DebugUI* testUI = (DebugUI*)UIMgr->appendUI(new DebugUI());
	testUI->leftTop({ 0.0f,0.0f });
	testUI->rightBottom({ 0.0f,0.0f });

	copperPickAxe* toolTest = new copperPickAxe();
	toolTest->init();
	player->linkInven()->pickUp(toolTest, 1);

	Dirt* dirtTest = new Dirt();
	dirtTest->init({-1, -1});
	dirtTest->addItemCount(5);
	player->linkInven()->pickUp(dirtTest, 1);

	DirtWall* dirtWallTest = new DirtWall();
	dirtWallTest->init({ -1, -1 });
	dirtWallTest->addItemCount(5);
	player->linkInven()->pickUp(dirtWallTest, 1);

	Wood* woodTest = new Wood();
	woodTest->init({ -1, -1 });
	woodTest->addItemCount(902);
	player->linkInven()->pickUp(woodTest, 1);
	
	Copper* copperTest = new Copper();
	copperTest->init({ -1, -1 });
	copperTest->addItemCount(50);
	player->linkInven()->pickUp(copperTest, 1);
	

	cam->Position(player->position());
	gridMap->getVisiableNodes();

	music->playBGM("Music-Overworld_Day.mp3");
	//sun->init();
	//sun->linkGridMap(map);
	//sun->manuallyUpdateWorldLight();
}

void TestScene::render(HDC _hdc)
{
	rendering->render(_hdc);
	gridMap->render(_hdc);
	entityMgr->render(_hdc);
	itemMgr->render(_hdc);
	UIMgr->render(_hdc);
}

int TestScene::update()
{
	entityMgr->update();
	CollisionHandler::collision(entityMgr->linkPlayer());
	for (auto& entity : *entityMgr->linkList())
	{
		CollisionHandler::collision(entity);
	}

	itemMgr->update();
	cam->Position(player->position());

	UIMgr->update();


	bool check = UIMgr->checkColl();

	if (Input->getButton(KeyType::LeftMouse) && !check)
	{
		player->useItem();
		
	}

	gridMap->update();
	return 0;
}

void TestScene::release()
{
	entityMgr->release();
	gridMap->release();
	itemMgr->release();
	Craft->release();
}
