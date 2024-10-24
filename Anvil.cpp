#include "framework.h"
#include "Anvil.h"
#include "GridMap.h"
#include "EntityManager.h"
#include "SoundManager.h"
#include "RenderManager.h"
#include "TimeManager.h"

Anvil::Anvil()
{
}

Anvil::~Anvil()
{
}

Item* Anvil::clone() const
{
	return new Anvil(*this);
}

void Anvil::dragDrop()
{
}

void Anvil::use()
{
	if (count == 0) return;
	Node* baseNode = gridMap->findNode(cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }));
	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(baseNode->position() * 16 + Vector2Int{ 8,8 }));
	if (distance > 100.0f) return;

	std::list<Node*> nodes = gridMap->findNodes(baseNode->position() + Vector2Int{ 0, -1 }, baseNode->position() + Vector2Int{ 1, 0 });

	for (auto& node : nodes)
	{
		if (node->position().y == baseNode->position().y - 1)
		{
			if (!node->block()) return;
			else continue;
		}
		if (node->block() || node->furniture()) return;
	}


	Anvil* newItem = new Anvil();
	newItem->init(baseNode->position());
	baseNode->furniture(newItem);
	count -= 1;
	music->playNew("Dig_0.wav");
}

void Anvil::init(Vector2Int _position)
{
	getImgSet("anvil");

	itemImg = rendering->findImage("Item_furniture", "anvil", "shadow0rotation0")[0];
	posInfo = { {0,0}, {1,0} };
	itemImgSize.x = 16;
	itemImgSize.y = 16;
	imgPosInfo = { {0,0}, {1,0} };
	placedImgSize = { 16, 16 };
	placedPos = _position;
	code = 14;
	itemName = L"Anvil";
	itemUsingState = UsingState::Swing;
	maxCount = 1;
	bottomPos = 0;
	imgGridSize = { 1,0 };
	imgGridPos = { 0,0 };
}

void Anvil::useInField()
{
}

Item* Anvil::destroyed(Vector2Int _gridPos)
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
