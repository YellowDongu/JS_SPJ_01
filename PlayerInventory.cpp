#include "framework.h"
#include "PlayerInventory.h"
#include "InputManager.h"
#include "GridMap.h"
#include "Item.h"

PlayerInventory::PlayerInventory() : onHand(nullptr), selected(nullptr)
{
}

PlayerInventory::~PlayerInventory()
{
	release();
}

void PlayerInventory::init()
{
	for (int x = 0; x < 10; x++)
	{
		InventorySlot* slot = new InventorySlot();

		hotbar.push_back(slot);
	}
	selected = hotbar[0];

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			InventorySlot* slot = new InventorySlot();

			invenSlot.push_back(slot);
		}
	}
	onHand = new InventorySlot();
}

void PlayerInventory::update()
{
}

void PlayerInventory::release()
{
	if (!invenSlot.empty())
	{
		for (auto& slot : invenSlot)
		{
			slot->release();
			delete slot;
		}
		invenSlot.clear();
	}
	if (!hotbar.empty())
	{
		for (auto& slot : hotbar)
		{
			slot->release();
			delete slot;
		}
		hotbar.clear();
	}

	if (onHand)
	{
		delete onHand;
		onHand = nullptr;
	}
}

void PlayerInventory::swapSlot(InventorySlot& obj, InventorySlot& sbj)
{
	Item* temp = obj.swapItem(sbj.item());
	sbj.swapItem(temp);
}

InventorySlot* PlayerInventory::findSlotAtHotBar(int _index)
{
	if (_index < 0 || _index > 9) return nullptr;
	return hotbar[_index];
}

bool PlayerInventory::pickUp(Item* item, int count)
{
	for (auto slot :hotbar)
	{	
		if (slot->aquireItem(item, count)) return true;
	}

	for (auto slot : invenSlot)
	{
		if (slot->aquireItem(item, count)) return true;
	}

	return false;
}
