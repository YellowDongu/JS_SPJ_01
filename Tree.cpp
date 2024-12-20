#include "framework.h"
#include "Tree.h"
#include "Wood.h"
#include "SoundManager.h"
#include "TimeManager.h"
#include "GridMap.h"
#include "EntityManager.h"
#include "RenderManager.h"
#include "ItemManager.h"

Tree::Tree() : height(0), liveTime(0.0f), treeTop(nullptr)
{
}

Tree::~Tree()
{
}

Item* Tree::clone() const
{
	return new Tree(*this);
}

void Tree::dragDrop()
{
}

void Tree::use()
{
	if (count == 0) return;
	count -= 1;
	Node* baseNode = gridMap->findNode(cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }));
	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(baseNode->position() * 16 + Vector2Int{ 8,8 }));
	if (distance > 100.0f) return;


	if (!baseNode || baseNode->block() || baseNode->furniture()) return;
	Vector2Int pos = baseNode->position();

	Tree* newItem = new Tree();
	newItem->init(baseNode->position());
	baseNode->furniture(newItem);
	music->playNew("Dig_0.wav");
}

void Tree::init(Vector2Int _position)
{
	disAssemble = true;
	getImgSet("treeSapling");

	itemImg = rendering->findImage("Item_furniture", "acorn", "shadow0rotation0")[0];
	posInfo = { {0,0} };
	itemImgSize.x = 20;
	itemImgSize.y = 20;
	imgPosInfo = { {0,0} };
	placedImgSize = { 16, 36 };
	placedPos = _position;
	code = 15;	
	itemName = L"Acorn";
	itemUsingState = UsingState::Swing;
	maxCount = 999;
	bottomPos = 0;
	imgGridSize = { 1,1 };
	imgGridPos = { 0,0 };
}

void Tree::useInField()
{
}

void Tree::update()
{
	if (liveTime == -1.0f) return;
	liveTime += Time->deltaTime();

	if (liveTime < 3.0f) return;
	liveTime = -1.0f;
	placedImgSize = { 20, 20 };
	srand((unsigned int)Time->deltaTime());
	height = getRandomNumber(8, 15);
	
	getImgSet("tree");

	nodes = gridMap->findNodes(placedPos, placedPos + Vector2Int{ 0, height });
	int i = 0;
	for (auto& node : nodes)
	{
		posInfo.push_back({0,i});
		srand((unsigned int)((int)GetTickCount64() * i));
		imgPosInfo.push_back({0, getRandomNumber(0, 5) });
		node->linkFurniture(this);
		i++;
	}
	Node* topNode = gridMap->findNode(placedPos + Vector2Int{ 0, height + 1 });
	treeTop = new TreeTop();
	treeTop->init(topNode->position());
	topNode->linkFurniture(treeTop);
	topNode->linkFrontBitmap(treeTop->linkTileImg());
	music->playNew("Dig_0.wav");
}

Item* Tree::destroyed(Vector2Int _gridPos)
{
	if (liveTime == -1.0f)
	{
		ULONGLONG currentTime = GetTickCount64();
		if (currentTime - lastTime >= 5000)
		{
			lastTime = currentTime;
			harden = 1.0f;
		}
		else lastTime = currentTime;
		harden -= Time->deltaTime() * 10.0f;

		srand((unsigned int)currentTime);
		int rndInt = getRandomNumber(0, 3);
		switch (rndInt)
		{
		case 0:
			music->playNew("Dig_0.wav");
			break;
		case 1:
			music->playNew("Dig_1.wav");
			break;
		case 2:
			music->playNew("Dig_2.wav");
			break;
		default:
			break;
		}
		if (harden > 0) return nullptr;
		Wood* wood = new Wood();
		wood->init({ -1, -1 });
		wood->addItemCount(6);
		for (auto& node : nodes)
		{
			if (node->position() == placedPos) continue;
			node->unlinkFurniture();
			node->unlinkFrontBitmap();

			Wood* wood = new Wood();
			wood->init({ -1, -1 });
			wood->addItemCount(6);
			wood->position(Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8, 8 }));
			itemMgr->appendList(wood);
		}

		if (treeTop)
		{
			Node* node = gridMap->findNode(treeTop->gridPosition());
			node->unlinkFurniture();
			node->unlinkFrontBitmap();
			delete treeTop;
			treeTop = nullptr;

			Tree* wood = new Tree();
			wood->init({ -1, -1 });
			wood->addItemCount(1);
			wood->position(Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8, 8 }));
			itemMgr->appendList(wood);
		}


		return wood;
	}
	else
	{
		//music->playNew("Dig_0.wav");
		return nullptr;
	}

}
