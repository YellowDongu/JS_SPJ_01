#include "framework.h"
#include "DirtWall.h"
#include "RenderManager.h"
#include "ImageHandler.h"
#include "GridMap.h"
#include "SoundManager.h"

DirtWall::DirtWall()
{
}

DirtWall::~DirtWall()
{
}

Item* DirtWall::clone() const
{
	return new DirtWall(*this);
}

void DirtWall::dragDrop()
{
}

void DirtWall::use()
{
	Node* node = gridMap->findNode(cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }));
	if (!node || node->wall()) return;

	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8,8 }));
	if (distance > 100.0f) return;

	DirtWall* newDirt = new DirtWall();
	newDirt->init(node->position());
	node->wall(newDirt);
	gridMap->updateNearNode(node, 3);

	music->playNew("Dig_0.wav");
	count -= 1;
}

void DirtWall::init(Vector2Int _gridPos)
{
	getImgSet("dirt");

	if (_gridPos.x != -1 && _gridPos.y != -1)
	{
		gridMap->updateNearNode(gridMap->findNode(_gridPos), 1);
	}

	itemImg = rendering->findImage("Item_block", "dirtWall", "shadow0rotation0")[0];
	pos = _gridPos;
	code = 2;
	itemUsingState = UsingState::Swing;
}

Wall* DirtWall::destroyed(Vector2Int _gridPos)
{
	return nullptr;
}
