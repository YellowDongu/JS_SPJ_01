#include "framework.h"
#include "Dirt.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "GridMap.h"
#include "InputManager.h"
#include "CameraManager.h"
#include "SoundManager.h"
Dirt::Dirt()
{
}

Dirt::~Dirt()
{
}

void Dirt::init(Vector2Int _gridPos)
{
	getImgSet("dirt");

	if (_gridPos.x != -1 && _gridPos.y != -1)
	{
		gridMap->updateNearNode(gridMap->findNode(_gridPos), 1);
	}

	itemImg = rendering->findImage("Item_block", "dirt", "shadow0rotation0")[0];
	pos = _gridPos;
	code = 1;
	itemName = "Dirt";
}

Item* Dirt::destroyed(Vector2Int _gridPos)
{


	return this;
}

void Dirt::dragDrop()
{
}

void Dirt::use()
{
	Node* node = gridMap->findNode(cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }));
	if (!node || node->block()) return;

	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8,8 }));
	if (distance > 100.0f) return;

	Dirt* newDirt = new Dirt();
	newDirt->init(node->position());
	node->block(newDirt);
	gridMap->updateNearNode(node, 3);
	music->playNew("Dig_0.wav");
	count -= 1;
}

Item* Dirt::clone() const
{
	return new Dirt(*this);
}