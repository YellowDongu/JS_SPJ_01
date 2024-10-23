#pragma once
#include "Furniture.h"
#include "Inventory.h"
class Chest : public Furniture
{
public:
	Chest();
	~Chest();


	void useInField() override;
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _position) override;
	Item* destroyed(Vector2Int _gridPos) override;


private:
	Inventory* chestInven;



};