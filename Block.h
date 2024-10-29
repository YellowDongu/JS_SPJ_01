#pragma once
#include "Item.h"

class GridMap;
class Block : public Item
{
public:
	Block();
	virtual ~Block();


	virtual void init(Vector2Int _gridPos) abstract;
	virtual Item* destroyed(Vector2Int _gridPos) abstract;

	void getImgSet(std::string name);
	virtual void changeBlockImg(std::string state, int shadow);
	Vector2Int imageFinder(std::string state);

protected:
	float harden;
};