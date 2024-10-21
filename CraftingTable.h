#pragma once
#include "Furniture.h"

class CraftingTable : public Furniture
{
public:
	CraftingTable();
	~CraftingTable();

	Item* destroyed(Vector2Int _gridPos) override;
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _position) override;
private:


};
