#include "framework.h"
#include "CraftingTable.h"
#include "GridMap.h"
#include "EntityManager.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "SoundManager.h"

CraftingTable::CraftingTable()
{
}

CraftingTable::~CraftingTable()
{
}

Item* CraftingTable::clone() const
{
	return new CraftingTable(*this);
}

void CraftingTable::dragDrop()
{
}

void CraftingTable::use()
{
	if (count == 0) return;
	Node* node = gridMap->findNode(cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }));
	if (!node || node->block() || node->furniture()) return;
	Vector2Int pos = node->position();
	pos.x += 1;
	Node* nodeCheck = gridMap->findNode(pos);
	if (!nodeCheck || nodeCheck->block() || nodeCheck->furniture()) return;
	
	pos.x -= 1;
	pos.y += -1;
	nodeCheck = gridMap->findNode(pos);
	if (!nodeCheck || !nodeCheck->block()) return;
	pos.x += 1;
	nodeCheck = gridMap->findNode(pos);
	if (!nodeCheck || !nodeCheck->block()) return;
	
	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8,8 }));
	if (distance > 100.0f) return;
	
	Furniture* newItem = new CraftingTable();
	newItem->init(node->position());
	node->furniture(newItem);
	count -= 1;
	music->playNew("Dig_0.wav");
}

void CraftingTable::init(Vector2Int _position)
{
	getImgSet("craftingTable");

	itemImg = rendering->findImage("Item_furniture", "craftingTable", "shadow0rotation0")[0];
	posInfo = { {0,0}, {1,0} };
	itemImgSize.x = 16;
	itemImgSize.y = 16;
	imgPosInfo = { {0,0}, {1,0} };
	placedImgSize = { 16, 16 };
	placedPos = _position;
	code = 4;
	itemName = L"CraftingTable";
	itemUsingState = UsingState::Swing;
	maxCount = 1;
	bottomPos = 0;
	imgGridSize = { 1,1 };
	imgGridPos = { 0,0 };
}

void CraftingTable::useInField()
{
}

Item* CraftingTable::destroyed(Vector2Int _gridPos)
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
	int rndInt = rand() % 3;
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
	return this;
}
