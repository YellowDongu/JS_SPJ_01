#include "framework.h"
#include "Chest.h"
#include "RenderManager.h"
#include "GridMap.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "InventoryUI.h"

Chest::Chest() : chestInven(nullptr)
{
}

Chest::~Chest()
{
	if (!chestInven) return;

	delete chestInven;
}

Item* Chest::clone() const
{
	return new Chest(*this);
}

void Chest::dragDrop()
{
}

void Chest::use()
{
	if (count == 0) return;
	Node* baseNode = gridMap->findNode(cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }));
	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(baseNode->position() * 16 + Vector2Int{ 8,8 }));
	if (distance > 100.0f) return;

	std::list<Node*> nodes = gridMap->findNodes(baseNode->position() + Vector2Int{ -1, -2 }, baseNode->position());

	for (auto& node : nodes)
	{
		if (node->position().y == baseNode->position().y - 2)
		{
			if (!node->block()) return;
			else continue;
		}
		if (node->block() || node->furniture()) return;
	}


	Chest* newItem = new Chest();
	newItem->init(baseNode->position());
	baseNode->furniture(newItem);
	count -= 1;
	music->playNew("Dig_0.wav");
}

void Chest::init(Vector2Int _position)
{
	getImgSet("chest");

	itemImg = rendering->findImage("Item_furniture", "chest", "shadow0rotation0")[0];
	posInfo = { {0,0}, {1,0}, {0,-1}, {1,-1} };
	itemImgSize.x = 16;
	itemImgSize.y = 16;
	imgPosInfo = { {0,0}, {1,0} , {0,1}, {1,1} };
	//imgPosInfo = { {0,4}, {1,4} , {0,5}, {1,5} };
	placedImgSize = { 16, 16 };
	pos = _position;
	code = 6;
	itemName = L"Chest";
	itemUsingState = UsingState::Swing;
	maxCount = 16;
	bottomPos = -1;
	imgGridSize = { 2,2 };
	imgGridPos = { 0,2 };

	chestInven = new Inventory();
	chestInven->chestInit();
}

Item* Chest::destroyed(Vector2Int _gridPos)
{
	return nullptr;
}

void Chest::useInField()
{
	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(pos * 16 + Vector2Int{ 8,8 }));
	if (distance > 100.0f) return;

	UIMgr->getInven()->chestSelected(this->chestInven);

}
