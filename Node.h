#pragma once
#include "Item.h"

class Block;
class Furniture;
class Wall;
class GridMap;

class Node
{
public:
	Node();
	~Node();

	void release();
	void update(int light = 0);
	void updateWorldLight(int light, bool decresed = false, bool nearLight = false);
	void updateLight(int light);

	Wall* wall() { return wallSlot; }
	Furniture* furniture() { return furnitureSlot; }
	Block* block() { return blockSlot; }

	void wall(Wall* newItem);
	void furniture(Furniture* newItem);
	void linkFurniture(Furniture* newItem) { furnitureSlot = newItem; }
	void block(Block* newBlock);


	Wall* destroyWall();
	Furniture* destroyFurniture();
	Block* destroyBlock();
	void unlinkBlock() { blockSlot = nullptr; }
	void unlinkFrontBitmap() { frontBitmap = nullptr; }


	Vector2Int position() const { return pos; }
	void position(Vector2Int _pos) { pos = _pos; }


	HBITMAP& backImg() { return *backBitmap; }
	HBITMAP& frontImg() { return *frontBitmap; }


private:
	int light;
	int worldLight;

	float durable;
	float maxDurable;
	float recoverTime;

	Wall* wallSlot;
	Furniture* furnitureSlot;
	Block* blockSlot;

	HBITMAP* backBitmap;
	HBITMAP* frontBitmap;

	Vector2Int pos;
};
