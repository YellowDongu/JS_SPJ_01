#include "framework.h"
#include "Copper.h"
#include "GridMap.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "TimeManager.h"
Copper::Copper()
{
}

Copper::~Copper()
{
}

Item* Copper::clone() const
{
	return new Copper(*this);
}

void Copper::dragDrop()
{
}

void Copper::use()
{
	Node* node = gridMap->findNode(cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }));
	if (!node || node->block()) return;

	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8,8 }));
	if (distance > 100.0f) return;

	Copper* newItem = new Copper();
	newItem->init(node->position());
	node->block(newItem);
	gridMap->updateNearNode(node, 3);
	music->playNew("Dig_0.wav");
	count -= 1;
}

void Copper::init(Vector2Int _gridPos)
{
	getImgSet("copper");

	if (_gridPos.x != -1 && _gridPos.y != -1)
	{
		gridMap->updateNearNode(gridMap->findNode(_gridPos), 1);
	}

	itemImg = rendering->findImage("Item_block", "copper", "shadow0rotation0")[0];
	pos = _gridPos;
	code = 5;
	itemName = L"Copper";
	itemUsingState = UsingState::Swing;
	harden = 1.0f;
	lastTime = GetTickCount64();
}

Item* Copper::destroyed(Vector2Int _gridPos)
{
	ULONGLONG currentTime = GetTickCount64();
	if (currentTime - lastTime >= 5000)
	{
		lastTime = currentTime;
		harden = 1.0f;
	}
	else lastTime = currentTime;
	harden -= Time->deltaTime() * 5.0f;

	srand((unsigned int)currentTime);
	int rndInt = rand() % 3;
	switch (rndInt)
	{
	case 0:
		music->playNew("Tink_0.wav");
		break;
	case 1:
		music->playNew("Tink_1.wav");
		break;
	case 2:
		music->playNew("Tink_2.wav");
		break;
	default:
		break;
	}
	if (harden > 0) return nullptr;
	return this;
}
