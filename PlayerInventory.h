#pragma once
#include "Inventory.h"

class Item;
class PlayerInventory : public Inventory
{
public:
	PlayerInventory();
	virtual ~PlayerInventory();

	void init();
	void update();
	void release();
	void selectAtHotBar(int _index) { selected = hotbar[_index]; }
	void swapSlot(InventorySlot& obj, InventorySlot& sbj);
	Item* getItem(int itemCode);
	std::list<Item*> getItems(int itemCode);
	InventorySlot* selectedAtHotBar() { return selected; }
	InventorySlot* findSlotAtHotBar(int _index);
	InventorySlot* pickedItem() { return onHand; }
	bool pickUp(Item* item, int count) override;
private:
	friend class Recipe;
	std::vector<InventorySlot*> hotbar;
	InventorySlot* onHand;
	InventorySlot* selected;
	std::map<std::string, std::map<std::string, std::vector<HBITMAP>>> imageSet;
};

