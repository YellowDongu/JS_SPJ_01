#pragma once
#include "Furniture.h"


class Furnace : public Furniture
{
public:
	Furnace();
	~Furnace();

	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _position) override;
	void useInField() override;
	Item* destroyed(Vector2Int _gridPos) override;
private:



};

