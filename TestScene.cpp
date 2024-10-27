#include "framework.h"
#include "TestScene.h"

#include "CameraManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "ItemManager.h"
#include "EntityManager.h"

#include "GridMap.h"

#include "Player.h"

#include "UIManager.h"
#include "DebugUI.h"
#include "InventoryUI.h"
#include "HPBarUI.h"
#include "MPBarUI.h"
#include "CraftUI.h"
#include "ArmourUI.h"

#include "DirtWall.h"
#include "Wood.h"
#include "Copper.h"
#include "Dirt.h"
#include "copperPickAxe.h"
#include "CopperBow.h"
#include "Stone.h"
#include "Tree.h"
#include "CopperSword.h"
#include "Grass.h"
#include "BigEyeSummoner.h"
#include "Arrow.h"

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

	std::list<Node*> nodes = gridMap->findNodes(Vector2Int{ 0,0 }, Vector2Int{ 800,30 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		if (node->block() || node->furniture()) continue;
		Stone* block = new Stone();
		block->init(node->position());
		node->block(block);
	}
	nodes.clear();

	nodes = gridMap->findNodes(Vector2Int{ 0,31 }, Vector2Int{ 800,39 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		if (node->block() || node->furniture()) continue;
		Dirt* block = new Dirt();
		block->init(node->position());
		node->block(block);
	}
	nodes.clear();

	nodes = gridMap->findNodes(Vector2Int{ 0,40 }, Vector2Int{ 800,40 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		if (node->block() || node->furniture()) continue;
		Grass* block = new Grass();
		block->init(node->position());
		node->block(block);
	}
	nodes.clear();


	gridMap->updateAllBlock();


	entityMgr->createPlayer(Vector2{900.0f, 900.0f});
	player = entityMgr->linkPlayer();
	player->spawnPoint({ 900.0f, 900.0f });
	
	rendering->linkplayer(player);
	rendering->linkEntityList(entityMgr->linkList());
	
	InventoryUI* invenUI = new InventoryUI();
	invenUI->init(rendering->linkplayer()->linkInven());
	UIMgr->appendInven(invenUI);
	UIMgr->appendUI(invenUI);
	
	HPBarUI* hpBar = new HPBarUI();
	hpBar->init(player);
	UIMgr->appendUI(hpBar);
	MPBarUI* mpBar = new MPBarUI();
	mpBar->init(player);
	UIMgr->appendUI(mpBar);
	
	CraftUI* craftUI = new CraftUI();
	craftUI->init();
	UIMgr->appendUI(craftUI);
	itemMgr->init(player);

	ArmourUI* armourUI = new ArmourUI();
	armourUI->init();
	UIMgr->appendUI(armourUI);

	DebugUI* testUI = (DebugUI*)UIMgr->appendUI(new DebugUI());
	testUI->leftTop({ 0.0f,0.0f });
	testUI->rightBottom({ 0.0f,0.0f });

	CopperPickAxe* toolTest = new CopperPickAxe();
	toolTest->init();
	player->linkInven()->pickUp(toolTest, 1);

	Tree* tree = new Tree();
	tree->init({ -1, -1 });
	tree->addItemCount(5);
	player->linkInven()->pickUp(tree, 1);

	Wood* woodTest = new Wood();
	woodTest->init({ -1, -1 });
	woodTest->addItemCount(902);
	player->linkInven()->pickUp(woodTest, 1);
	
	Copper* copperTest = new Copper();
	copperTest->init({ -1, -1 });
	copperTest->addItemCount(999);
	player->linkInven()->pickUp(copperTest, 1);

	CopperBow* bowTest = new CopperBow();
	bowTest->init();
	player->linkInven()->pickUp(bowTest, 1);

	BigEyeSummoner* itemTest = new BigEyeSummoner();
	itemTest->init();
	itemTest->addItemCount(12);
	player->linkInven()->pickUp(itemTest, 1);

	Stone* stoneTest = new Stone();
	stoneTest->init({-1, -1});
	stoneTest->addItemCount(322);
	player->linkInven()->pickUp(stoneTest, 1);

	Arrow* arrowTest = new Arrow();
	arrowTest->init();
	arrowTest->addItemCount(300);
	player->linkInven()->pickUp(arrowTest, 1);

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

	itemMgr->update();
	cam->Position(player->position());
	cam->update();

	Craft->update();
	UIMgr->update();


	bool check = UIMgr->checkColl();

	if (Input->getButton(KeyType::LeftMouse) && !check)
	{
		player->useItem();
		
	}
	if (Input->getButton(KeyType::RightMouse) && !check)
	{
		gridMap->nodeInteraction();
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
