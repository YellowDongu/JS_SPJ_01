#include "framework.h"
#include "InventorySlot.h"
#include "Item.h"
#include "SoundManager.h"
InventorySlot::InventorySlot() : itemType(nullptr), itemCount(nullptr) {}

InventorySlot::~InventorySlot() { release(); }

bool InventorySlot::aquireItem(Item* newItem, int count)
{
	if (!newItem) return false;
	if (!itemType)
	{
		itemType = newItem;
		itemCount = itemType->linkItemCount();
		music->playNew("Grab.wav");
		return true;
	}
	else if (itemType->itemCode() == newItem->itemCode())
	{
		int surplus = itemType->itemMaxCount() - (itemType->itemCount() + newItem->itemCount());
		if (surplus < 0)
		{
			itemType->addItemCount(abs(surplus));
			newItem->addItemCount(surplus);
			music->playNew("Grab.wav");

			return false;
		}
		itemType->addItemCount(newItem->itemCount());
		delete newItem;
		music->playNew("Grab.wav");
		return true;
	}
	else return false;
}

Item* InventorySlot::swapItem(Item* newItem)
{
	if (newItem && itemType &&
		itemType->itemCode() == newItem->itemCode() &&
		itemType->itemMaxCount() >= itemType->itemCount() + newItem->itemCount())
	{
		itemType->addItemCount(newItem->itemCount());
		delete newItem;
		return nullptr;
	}

	Item* old = itemType;
	itemType = newItem;
	itemCount = itemType->linkItemCount();
	music->playNew("Grab.wav");
	return old;
}

bool InventorySlot::useItem()
{
	if (!itemType) return false;
	itemType->use();
	if (*itemCount == 0)
	{
		delete itemType;
		itemCount = nullptr;
		itemType = nullptr;
		return true;
	}
	itemCount = itemType->linkItemCount();
	return true;
}

void InventorySlot::release()
{
	if (!itemType) return;
	delete itemType;
	itemType = nullptr;
}

