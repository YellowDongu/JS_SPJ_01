#pragma once
#include "Block.h"

class Copper : public Block
{
public:
	Copper();
	~Copper();

	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _gridPos) override;
	Item* destroyed(Vector2Int _gridPos) override;
private:



};
