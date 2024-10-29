#pragma once
#include "Block.h"

class Grass : public Block
{
public:
	Grass();
	virtual ~Grass();


	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _gridPos) override;
	Item* destroyed(Vector2Int _gridPos) override;
	void changeBlockImg(std::string state, int shadow) override;
private:



};

