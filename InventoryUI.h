#pragma once
#include "UI.h"
#include "PlayerInventory.h"
#include "InventorySlotUI.h"

class InventoryUI : public UI
{
public:
	InventoryUI();
	~InventoryUI();

	void init(PlayerInventory* _playerInven);
	void update() override;
	void render(HDC _hdc) override;
	void triggered() override;
	void hotBarSelect();
	void inventoryActive(bool _value);

	void chestSelected(Inventory* inven) { chestInven = inven; active = true; }
	void invenOpened() { active = false; }
	void invenClosed();
	void displayItem(HDC _hdc, HBITMAP img, int count, Vector2Int Center, Vector2Int slotSize);
private:
	std::map<std::string, std::vector<HBITMAP>>* imageSet;
	PlayerInventory* inven;
	Inventory* chestInven;

	std::string* hotbarText;

	std::vector<InventorySlotUI*> hotbarSlot;
	std::vector<InventorySlotUI*> invenSlot;
	std::vector<InventorySlotUI*> chestSlot;

};
