#pragma once
#include "Block.h"
class Dirt : public Block
{
public:
	Dirt();
	virtual ~Dirt();

	Item* clone() const override;
	void init(Vector2Int _gridPos) override;
	Item* destroyed(Vector2Int _gridPos) override;
	void dragDrop() override;
	void use() override;

private:
};