#pragma once
#include "InventorySlot.h"

class Item;
class Inventory
{
public:
	Inventory();
	virtual ~Inventory();

	void chestInit();
	std::vector<InventorySlot*>* linkInven() { return &invenSlot; }
	InventorySlot* findSlot(int x, int y);
	virtual bool pickUp(Item* item, int count) { return false; }

protected:
	std::vector<InventorySlot*> invenSlot;
};
