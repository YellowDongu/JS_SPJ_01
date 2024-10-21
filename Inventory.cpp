#include "framework.h"
#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

InventorySlot* Inventory::findSlot(int x, int y)
{
	return invenSlot[x + y * 10];
}
