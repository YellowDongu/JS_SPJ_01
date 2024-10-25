#include "framework.h"
#include "copperPickAxe.h"
#include "GridMap.h"
#include "InputManager.h"
#include "ItemManager.h"
#include "Block.h"
#include "Furniture.h"
#include "RenderManager.h"
#include "CameraManager.h"
#include "SoundManager.h"
#include "EntityManager.h"

copperPickAxe::copperPickAxe()
{
}

copperPickAxe::~copperPickAxe()
{
}

void copperPickAxe::dragDrop()
{
}

void copperPickAxe::use()
{
	Vector2 mousePos = cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y });
	Node* node = gridMap->findNode(mousePos);
	music->playNew("Item_1.wav");

	//if()

	if (node)
	{
		float distance = Vector2::distance(entityMgr->linkPlayer()->position(), Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8,8 }));

		if (distance > 100.0f) return;

		if (node->block())
		{
			Block* item = node->destroyBlock();
			if (!item) return;
			gridMap->updateNearNode(node, 3);
			item->position(Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8,8 }));
			itemMgr->appendList(item);
		}
		else if (node->furniture())
		{
			Furniture* item = node->destroyFurniture();
			if (!item) return;
			item->position(Vector2Int::toVec2(node->position() * 16 + Vector2Int{ 8,8 }));
			itemMgr->appendList(item);
		}
	}

}

void copperPickAxe::init()
{
	maxCount = 1;
	count = 1;
	itemImg = rendering->findImage("Item_tool", "copperPickAxe", "shadow0rotation0")[0];
	itemImgSize.x = 32;
	itemImgSize.y = 32;
	onGround = false;
	code = 10;
	itemImgCenter = { 3, 30 };
	itemUsingState = UsingState::Swing;
	category = 1;
	dmg = 20;
}

Item* copperPickAxe::clone() const
{
	return new copperPickAxe(*this);
}
