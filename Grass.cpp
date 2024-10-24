#include "framework.h"
#include "Grass.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "Dirt.h"
#include "GridMap.h"
#include "RenderManager.h"
Grass::Grass()
{
}

Grass::~Grass()
{
}

Item* Grass::clone() const
{
	return new Grass(*this);
}

void Grass::dragDrop()
{
}

void Grass::use()
{
}

void Grass::init(Vector2Int _gridPos)
{
	getImgSet("dirt");

	if (_gridPos.x != -1 && _gridPos.y != -1)
	{
		gridMap->updateNearNode(gridMap->findNode(_gridPos), 1);
	}

	itemImg = rendering->findImage("Item_block", "grass", "shadow0rotation0")[0];
	pos = _gridPos;
	code = 1;
	itemName = L"Dirt";

	itemUsingState = UsingState::Swing;
}

Item* Grass::destroyed(Vector2Int _gridPos)
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

	gridMap->findNode(_gridPos)->unlinkBlock();
	Dirt* newItem = new Dirt();
	newItem->init(_gridPos);
	
	return newItem;
}