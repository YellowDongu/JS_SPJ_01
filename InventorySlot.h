#pragma once

class Item;
class InventorySlot
{
public:
	InventorySlot();
	~InventorySlot();

	void release();

	bool aquireItem(Item* newItem, int count);
	Item* swapItem(Item* newItem);
	bool useItem();


	Item* item() const { return itemType; }
	int count() const { return *itemCount; }
	//void release();

private:
	Item* itemType;
	int* itemCount;
};