#include "framework.h"
#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
	if (invenSlot.empty()) return;
	for (auto& slot : invenSlot)
	{
		slot->release();
		delete slot;
	}
	invenSlot.clear();
}

void Inventory::chestInit()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			InventorySlot* slot = new InventorySlot();

			invenSlot.push_back(slot);
		}
	}
}

InventorySlot* Inventory::findSlot(int x, int y)
{
	return invenSlot[x + y * 10];
}
