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
#include "Cursor.h"
#include "DeathUI.h"

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

#include "Trophy.h"


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

	nodes = gridMap->findNodes(Vector2Int{ 0,31 }, Vector2Int{ 800,35 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		if (node->block() || node->furniture()) continue;
		Grass* block = new Grass();
		block->init(node->position());
		node->block(block);
	}
	nodes.clear();



	nodes = gridMap->findNodes(Vector2Int{ 100,32 }, Vector2Int{ 110,35 });
	for (auto& node : nodes)
	{
		if (!node->block()) continue;
		Block* block = node->block();
		node->unlinkBlock();
		delete block;
		Copper* newBlock = new Copper();
		newBlock->init(node->position());
		node->block(newBlock);
	}
	nodes.clear();



	int randInt = 0;
	randInt = getRandomNumber(2, 6);

	nodes = gridMap->findNodes(Vector2Int{ 0,36 }, Vector2Int{ 100,36 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		if (node->block() || node->furniture()) continue;
		Grass* block = new Grass();
		block->init(node->position());
		node->block(block);

		if (randInt <= 0)
		{
			Node* upperNode = gridMap->findNode
			(node->position() + Vector2Int{0,1});
			Tree* newTree = new Tree();
			newTree->init({ -1, -1 });
			newTree->setGrowTime(3.0f);
			newTree->gridPosition(upperNode->position());
			upperNode->furniture(newTree);
			srand(node->position().x);
			randInt = getRandomNumber(2, 6);
		}
		else randInt--;

	}
	nodes.clear();

	nodes = gridMap->findNodes(Vector2Int{ 100,36 }, Vector2Int{ 243,37 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		if (node->block() || node->furniture()) continue;
		Grass* block = new Grass();
		block->init(node->position());
		node->block(block);

		if (randInt <= 0 && (node->position().x < 126 || node->position().x > 174) && node->position().y == 37)
		{
			Node* upperNode = gridMap->findNode(node->position() + Vector2Int{ 0,1 });
			Tree* newTree = new Tree();
			newTree->init({ -1, -1 });
			newTree->setGrowTime(3.0f);
			newTree->gridPosition(upperNode->position());
			upperNode->furniture(newTree);
			randInt = getRandomNumber(2, 6);
		}
		else randInt--;
	}
	nodes.clear();


	nodes = gridMap->findNodes(Vector2Int{ 126,38 }, Vector2Int{ 174,38 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		if (node->block() || node->furniture()) continue;
		Grass* block = new Grass();
		block->init(node->position());
		node->block(block);


		if (randInt <= 0)
		{
			Node* upperNode = gridMap->findNode(node->position() + Vector2Int{ 0,1 });
			Tree* newTree = new Tree();
			newTree->init({ -1, -1 });
			newTree->setGrowTime(3.0f);
			newTree->gridPosition(upperNode->position());
			upperNode->furniture(newTree);
			randInt = getRandomNumber(2, 6);
		}
		else randInt--;
	}
	nodes.clear();



	nodes = gridMap->findNodes(Vector2Int{ 244,36 }, Vector2Int{ 350,36 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		if (node->block() || node->furniture()) continue;
		Grass* block = new Grass();
		block->init(node->position());
		node->block(block);



	}
	nodes.clear();




	nodes = gridMap->findNodes(Vector2Int{ 246,37 }, Vector2Int{ 350,37 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		if (node->block() || node->furniture()) continue;
		Grass* block = new Grass();
		block->init(node->position());
		node->block(block);
	}
	nodes.clear();

	nodes = gridMap->findNodes(Vector2Int{ 248,38 }, Vector2Int{ 350,38 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		if (node->block() || node->furniture()) continue;
		Grass* block = new Grass();
		block->init(node->position());
		node->block(block);

		if (randInt <= 0 && (node->position().x < 312 || node->position().x > 332))
		{
			Node* upperNode = gridMap->findNode(node->position() + Vector2Int{ 0,1 });
			Tree* newTree = new Tree();
			newTree->init({ -1, -1 });
			newTree->setGrowTime(3.0f);
			newTree->gridPosition(upperNode->position());
			upperNode->furniture(newTree);
			randInt = getRandomNumber(2, 6);
		}
		else randInt--;
	}
	nodes.clear();

	nodes = gridMap->findNodes(Vector2Int{ 312,39 }, Vector2Int{ 332,39 });
	for (auto& node : nodes)
	{
		if (!node) continue;
		if (node->block() || node->furniture()) continue;
		Grass* block = new Grass();
		block->init(node->position());
		node->block(block);

		if (randInt <= 0)
		{
			Node* upperNode = gridMap->findNode(node->position() + Vector2Int{ 0,1 });
			Tree* newTree = new Tree();
			newTree->init({ -1, -1 });
			newTree->setGrowTime(3.0f);
			newTree->gridPosition(upperNode->position());
			upperNode->furniture(newTree);
			randInt = getRandomNumber(2, 6);
		}
		else randInt--;
	}
	nodes.clear();





	gridMap->updateAllBlock();

	entityMgr->createPlayer(Vector2{ 900.0f, 650.0f });
	player = entityMgr->linkPlayer();
	player->spawnPoint({ 900.0f, 650.0f });
	
	rendering->linkplayer(player);
	rendering->linkEntityList(entityMgr->linkList());

	CraftUI* craftUI = new CraftUI();
	craftUI->init();
	UIMgr->appendUI(craftUI);
	itemMgr->init(player);

	HPBarUI* hpBar = new HPBarUI();
	hpBar->init(player);
	UIMgr->appendUI(hpBar);
	MPBarUI* mpBar = new MPBarUI();
	mpBar->init(player);
	UIMgr->appendUI(mpBar);

	ArmourUI* armourUI = new ArmourUI();
	armourUI->init();
	UIMgr->appendUI(armourUI);

	InventoryUI* invenUI = new InventoryUI();
	invenUI->init(rendering->linkplayer()->linkInven());
	UIMgr->appendInven(invenUI);
	UIMgr->appendUI(invenUI);

	Cursor* newCursor = new Cursor();
	newCursor->init();
	UIMgr->appendUI(newCursor);
	UIMgr->linkCursor(newCursor);

	DeathUI* deathUI = new DeathUI();
	deathUI->init();
	UIMgr->appendUI(deathUI);

	//DebugUI* testUI = (DebugUI*)UIMgr->appendUI(new DebugUI());
	//testUI->leftTop({ 0.0f,0.0f });
	//testUI->rightBottom({ 0.0f,0.0f });

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


	//Trophy* endTest = new Trophy();
	//endTest->init();
	//player->linkInven()->pickUp(endTest, 1);


	cam->Position(player->position());
	gridMap->getVisiableNodes();

	music->playBGM("Music-Overworld_Day.mp3");
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
