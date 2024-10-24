#include "framework.h"
#include "Tree.h"
#include "Wood.h"
#include "SoundManager.h"
#include "TimeManager.h"
#include "GridMap.h"
#include "EntityManager.h"
#include "RenderManager.h"

Tree::Tree() : height(0), liveTime(0.0f)
{
}

Tree::~Tree()
{
}

Item* Tree::clone() const
{
	return new Tree(*this);
}

void Tree::dragDrop()
{
}

void Tree::use()
{
	if (count == 0) return;
	count -= 1;
	Node* baseNode = gridMap->findNode(cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }));
	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(baseNode->position() * 16 + Vector2Int{ 8,8 }));
	if (distance > 100.0f) return;


	if (!baseNode || baseNode->block() || baseNode->furniture()) return;
	Vector2Int pos = baseNode->position();

	Tree* newItem = new Tree();
	newItem->init(baseNode->position());
	baseNode->furniture(newItem);
	music->playNew("Dig_0.wav");
}

void Tree::init(Vector2Int _position)
{
	disAssemble = true;
	getImgSet("treeSapling");

	itemImg = rendering->findImage("Item_furniture", "acorn", "shadow0rotation0")[0];
	posInfo = { {0,0} };
	itemImgSize.x = 20;
	itemImgSize.y = 20;
	imgPosInfo = { {0,0} };
	placedImgSize = { 16, 36 };
	placedPos = _position;
	code = 15;	
	itemName = L"Acorn";
	itemUsingState = UsingState::Swing;
	maxCount = 1;
	bottomPos = 0;
	imgGridSize = { 1,1 };
	imgGridPos = { 0,0 };
}

void Tree::useInField()
{
}

void Tree::update()
{
	if (liveTime == -1.0f) return;
	liveTime += Time->deltaTime();

	if (liveTime < 3.0f) return;
	liveTime = -1.0f;
	placedImgSize = { 20, 20 };
	srand(Time->deltaTime());
	height = 10 + rand() % 5;
	
	getImgSet("tree");

	Node* baseNode = gridMap->findNode(cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }));

	std::list<Node*> nodes = gridMap->findNodes(baseNode->position(), baseNode->position() + Vector2Int{ 0, height });
	int i = 0;
	for (auto& node : nodes)
	{
		if (node->block() || node->furniture()) continue;

		posInfo.push_back({0,i});
		srand(GetTickCount64() * i);
		imgPosInfo.push_back({0,rand() % 5});
		node->linkFurniture(this);
		i++;
	}


	music->playNew("Dig_0.wav");
}

Item* Tree::destroyed(Vector2Int _gridPos)
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
	Wood* wood = new Wood();
	wood->init({-1, -1});
	wood->addItemCount(20);
	for (auto pos : posInfo)
	{
		if (pos == Vector2Int::zero()) continue;
		Node* node = gridMap->findNode(placedPos + pos);
		node->linkFurniture(nullptr);
		node->unlinkFrontBitmap();
	}

	Node* node = gridMap->findNode(placedPos);

	return wood;
}
