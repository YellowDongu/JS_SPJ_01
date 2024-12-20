#include "framework.h"
#include "Node.h"
#include "Block.h"
#include "GridMap.h"
#include "RenderManager.h"
#include "ImageHandler.h"
#include "Furniture.h"
#include "SoundManager.h"
#include "Wall.h"
#include "Recipe.h"

Node::Node() : blockSlot(nullptr), furnitureSlot(nullptr), wallSlot(nullptr), pos(Vector2Int::zero()), backBitmap(NULL), frontBitmap(NULL), light(20), worldLight(20)
{
}

Node::~Node()
{
	release();
}

void Node::release()
{
	if (wallSlot)
	{
		delete wallSlot;
		wallSlot = nullptr;
	}
	if (furnitureSlot)
	{
		Furniture* item = Node::destroyFurniture();
		delete item;
	}
	if (blockSlot)
	{
		delete blockSlot;
		blockSlot = nullptr;
	}
}

void Node::update(int light)
{
	Node* node = nullptr;
	if (wallSlot)
	{
		std::string state = "";
		node = gridMap->findNode(pos + Vector2Int{ 1,0 });
		if (node && !node->wall()) state += "0";
		else state += "1";
		node = gridMap->findNode(pos + Vector2Int{ -1,0});
		if (node && !node->wall()) state += "0";
		else state += "1";
		node = gridMap->findNode(pos + Vector2Int{ 0,-1});
		if (node && !node->wall()) state += "0";
		else state += "1";
		node = gridMap->findNode(pos + Vector2Int{ 0,1 });
		if (node && !node->wall()) state += "0";
		else state += "1";

		wallSlot->changeBlockImg(state, 0);
		
	}


	if (blockSlot)
	{
		std::string state = "";
		node = gridMap->findNode(pos + Vector2Int{ 1,0 });
		if (node && !node->block()) state += "0";
		else state += "1";
		node = gridMap->findNode(pos + Vector2Int{ -1,0 });
		if (node && !node->block()) state += "0";
		else state += "1";
		node = gridMap->findNode(pos + Vector2Int{ 0,-1 });
		if (node && !node->block()) state += "0";
		else state += "1";
		node = gridMap->findNode(pos + Vector2Int{ 0,1 });
		if (node && !node->block()) state += "0";
		else state += "1";

		blockSlot->changeBlockImg(state, 0);
	}
}

void Node::updateWorldLight(int light, bool decresed, bool nearLight)
{
	if (worldLight == light) return;
	if (nearLight)
	{
		if (worldLight <= light)
		{
			worldLight = light;
		}
		return;
	}
	worldLight = light;

	int total = light + worldLight;


	if (total > 10) total = 10;
	if (total < 0) total = 0;
	update(total);

	if (blockSlot)
	{
		decresed = true;
		worldLight -= 2;
	}
	else if(decresed) worldLight -= 1;
	if (worldLight < 0) worldLight = 0;

	Node* node = nullptr;
	node = gridMap->findNode(pos + Vector2Int{ 1,0 });
	if(node) node->updateWorldLight(worldLight, true);
	node = gridMap->findNode(pos + Vector2Int{ -1,0 });
	if (node) node->updateWorldLight(worldLight, true);
	node = gridMap->findNode(pos + Vector2Int{ 0,-1 });
	if (node) node->updateWorldLight(worldLight);
}

void Node::updateLight(int _light)
{
	if (_light == 0) return;
	light += _light;

	int total = light + worldLight;

	if (total > 10) total = 10;
	update(total);

	int afterLight = light;
	if (afterLight > 0)
	{
		if (blockSlot) afterLight -= 2;
		else afterLight -= 1;
	}
	else
	{
		if (blockSlot) afterLight += 2;
		else afterLight += 1;
	}

	Node* node = nullptr;
	node = gridMap->findNode(pos + Vector2Int{ 1,0 });
	if (node) node->updateLight(afterLight);
	node = gridMap->findNode(pos + Vector2Int{ -1,0 });
	if (node) node->updateLight(afterLight);
	node = gridMap->findNode(pos + Vector2Int{ 0,1 });
	if (node) node->updateLight(afterLight);
	node = gridMap->findNode(pos + Vector2Int{ 0,-1 });
	if (node) node->updateLight(afterLight);
}


void Node::wall(Wall* newItem)
{
	if (!newItem) { return; }
	if (wallSlot) { return; }
	wallSlot = newItem;
	backBitmap = wallSlot->linkTileImg();
}

void Node::furniture(Furniture* newItem)
{
	if (!newItem) { return; }
	if (blockSlot || furnitureSlot) { return; }
	std::list<Node*> nodes;
	for (auto& placedPos : newItem->placedInfo())
	{
		if (placedPos.x == 0 && placedPos.y == 0) continue;
		Node* node = gridMap->findNode(pos + placedPos);
		if (node->block() || node->furniture()) return;
		nodes.push_back(node);
	}
	furnitureSlot = newItem;
	frontBitmap = furnitureSlot->linkTileImg();
	for (auto& node : nodes)
	{
		node->linkFurniture(newItem);
	}
	newItem->gridPosition(pos);
	Craft->appendFurniture(newItem);
}

void Node::block(Block* newBlock)
{
	if (!newBlock) { return; }
	if (blockSlot || furnitureSlot) { return; }
	blockSlot = newBlock;
	frontBitmap = blockSlot->linkTileImg();

}

Wall* Node::destroyWall()
{
	if (!wallSlot) { return nullptr; }
	Wall* wall = (Wall*)wallSlot->destroyed(pos);
	if (!wall) return nullptr;
	if (wall != wallSlot) delete wallSlot;
	wallSlot = nullptr;
	backBitmap = nullptr;
	return wall;
}

Furniture* Node::destroyFurniture()
{
	if (!furnitureSlot) { return nullptr; }
	bool disassemble = furnitureSlot->disassemble();
	//Furniture* furniture = furnitureSlot;
	Item* item = furnitureSlot->destroyed(pos);
	if (!item) return nullptr;

	if (item != furnitureSlot)
	{
		Craft->eraseFurniture(furnitureSlot);
		delete furnitureSlot;
		furnitureSlot = nullptr;
		frontBitmap = nullptr;
		return (Furniture*)item;
	}

	Furniture* furniture = (Furniture*)item;
	std::list<Node*> nodes;
	nodes.push_back(gridMap->findNode(furniture->gridPosition()));

	for (auto& pos : furniture->placedInfo())
	{
		if (pos.x == 0 && pos.y == 0) continue;
		nodes.push_back(gridMap->findNode(furniture->gridPosition() + pos));
	}

	for (auto& node : nodes)
	{
		node->frontBitmap = nullptr;
		node->furnitureSlot = nullptr;
	}

	music->playNew("Dig_0.wav");
	Craft->eraseFurniture(furniture);
	return furniture;
}

Block* Node::destroyBlock()
{
	if (!blockSlot) { return nullptr; }
	Block* block = (Block*)blockSlot->destroyed(pos);
	if (block == nullptr) return nullptr;
	if (block != blockSlot) delete blockSlot;
	blockSlot = nullptr;
	frontBitmap = nullptr;
	return block;
}
	