#include "framework.h"
#include "StoneWall.h"
#include "RenderManager.h"
#include "GridMap.h"
#include "SoundManager.h"
#include "TimeManager.h"



StoneWall::StoneWall()
{
}

StoneWall::~StoneWall()
{
}

Item* StoneWall::clone() const
{
	return new StoneWall(*this);
}

void StoneWall::dragDrop()
{
}

void StoneWall::use()
{
	Node* node = gridMap->findNode(cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }));
	if (!node || node->wall()) return;

	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8,8 }));
	if (distance > 100.0f) return;

	StoneWall* wall = new StoneWall();
	wall->init(node->position());
	node->wall(wall);
	gridMap->updateNearNode(node, 3);

	music->playNew("Dig_0.wav");
	count -= 1;
}

void StoneWall::init(Vector2Int _gridPos)
{
	getImgSet("stone");

	if (_gridPos.x != -1 && _gridPos.y != -1)
	{
		gridMap->updateNearNode(gridMap->findNode(_gridPos), 1);
	}

	itemImg = rendering->findImage("Item_block", "stoneWall", "shadow0rotation0")[0];
	pos = _gridPos;
	code = 19;
	itemUsingState = UsingState::Swing;
	itemName = L"Stone Wall";
}

Wall* StoneWall::destroyed(Vector2Int _gridPos)
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
