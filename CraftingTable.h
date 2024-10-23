#pragma once
#include "Furniture.h"

class CraftingTable : public Furniture
{
public:
	CraftingTable();
	~CraftingTable();


	void useInField() override;
	void init(Vector2Int _position) override;
	void dragDrop() override;
	void use() override;
	Item* clone() const override;
	Item* destroyed(Vector2Int _gridPos) override;
private:




};
