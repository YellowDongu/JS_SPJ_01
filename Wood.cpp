#include "framework.h"
#include "Wood.h"
#include "RenderManager.h"
#include "GridMap.h"
#include "SoundManager.h"
Wood::Wood()
{
}

Wood::~Wood()
{
}

Item* Wood::clone() const
{
	return new Wood(*this);
}

void Wood::dragDrop()
{
}

void Wood::use()
{
	Node* node = gridMap->findNode(cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }));
	if (!node || node->block()) return;

	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8,8 }));
	if (distance > 100.0f) return;

	Wood* newItem = new Wood();
	newItem->init(node->position());
	node->block(newItem);
	gridMap->updateNearNode(node, 3);
	music->playNew("Dig_0.wav");
	count -= 1;
}

void Wood::init(Vector2Int _gridPos)
{
	getImgSet("wood");

	if (_gridPos.x != -1 && _gridPos.y != -1)
	{
		gridMap->updateNearNode(gridMap->findNode(_gridPos), 1);
	}

	itemImg = rendering->findImage("Item_block", "wood", "shadow0rotation0")[0];
	pos = _gridPos;
	code = 3;
	itemName = L"wood";
	itemUsingState = UsingState::Swing;
}

Item* Wood::destroyed(Vector2Int _gridPos)
{
	return nullptr;
}
