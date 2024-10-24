#include "framework.h"
#include "Furnace.h"
#include "GridMap.h"
#include "EntityManager.h"
#include "SoundManager.h"
#include "RenderManager.h"
#include "TimeManager.h"

Furnace::Furnace()
{
}

Furnace::~Furnace()
{
}

Item* Furnace::clone() const
{
	return new Furnace(*this);
}

void Furnace::dragDrop()
{
}

void Furnace::use()
{
	if (count == 0) return;
	Node* baseNode = gridMap->findNode(cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }));
	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(baseNode->position() * 16 + Vector2Int{ 8,8 }));
	if (distance > 100.0f) return;

	std::list<Node*> nodes = gridMap->findNodes(baseNode->position() + Vector2Int{ 0, -2 }, baseNode->position() + Vector2Int{ 2, 0 } );

	for (auto& node : nodes)
	{
		if (node->position().y == baseNode->position().y - 2)
		{
			if (!node->block()) return;
			else continue;
		}
		if (node->block() || node->furniture()) return;
	}


	Furnace* newItem = new Furnace();
	newItem->init(baseNode->position());
	baseNode->furniture(newItem);
	count -= 1;
	music->playNew("Dig_0.wav");
}

void Furnace::init(Vector2Int _position)
{
	getImgSet("furnace");

	itemImg = rendering->findImage("Item_furniture", "furnace", "shadow0rotation0")[0];
	posInfo = { {0,0}, {1,0}, {2,0}, {0,-1}, {1,-1}, {2,-1} };
	itemImgSize.x = 16;
	itemImgSize.y = 16;
	imgPosInfo = { {0,0}, {1,0}, {2,0}, {0,1}, {1,1}, {2,1} };
	placedImgSize = { 16, 16 };
	pos = _position;
	code = 7;
	itemName = L"furnace";
	itemUsingState = UsingState::Swing;
	maxCount = 16;
	bottomPos = -1;
	imgGridSize = { 3,2 };
	imgGridPos = { 0,0 };

}

void Furnace::useInField()
{
}

Item* Furnace::destroyed(Vector2Int _gridPos)
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
