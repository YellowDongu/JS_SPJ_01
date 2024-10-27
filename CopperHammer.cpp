#include "framework.h"
#include "CopperHammer.h"
#include "EntityManager.h"
#include "GridMap.h"
#include "ItemManager.h"
#include "RenderManager.h"
#include "Wall.h"
#include "SoundManager.h"

CopperHammer::CopperHammer()
{
}

CopperHammer::~CopperHammer()
{
}

Item* CopperHammer::clone() const
{
	return new CopperHammer(*this);
}

void CopperHammer::dragDrop()
{
}

void CopperHammer::use()
{
	Vector2 mousePos = cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y });
	Node* node = gridMap->findNode(mousePos);
	music->playNew("Item_1.wav");
	if (!node) return;

	float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8,8 }));

	if (distance > 100.0f) return;

	if (node->wall())
	{
		Wall* item = node->destroyWall();
		if (!item) return;
		gridMap->updateNearNode(node, 3);
		item->position(Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8,8 }));
		itemMgr->appendList(item);
	}
}

void CopperHammer::init()
{
	maxCount = 1;
	count = 1;
	itemImg = rendering->findImage("Item_tool", "copperHammer", "shadow0rotation0")[0];
	itemImgSize.x = 36;
	itemImgSize.y = 36;
	onGround = false;
	code = 13;
	itemImgCenter = { 3, 34 };
	itemUsingState = UsingState::Swing;
	category = 1;
	dmg = 20;
	itemName = L"CopperHammer";
}
