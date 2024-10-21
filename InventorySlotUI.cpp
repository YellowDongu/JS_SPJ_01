#include "framework.h"
#include "InventorySlotUI.h"


InventorySlotUI::InventorySlotUI() :selected(false), chest(false), slot(nullptr), imageSet(nullptr)
{
}

InventorySlotUI::~InventorySlotUI()
{
}

void InventorySlotUI::init(InventorySlot* _slot, Vector2 _position)
{
	lt = _position;
	slot = _slot;
	auto find = rendering->findImageSet("UI")->find("inventory");
	imageSet = &(*find).second;
}

void InventorySlotUI::update()
{
}

void InventorySlotUI::triggered()
{
	currentState = UIState::End;
}

void InventorySlotUI::render(HDC _hdc)
{
}

void InventorySlotUI::renderSlot(HDC _hdc)
{
	if (selected)
	{
		ImageHandler::renderWithoutBack((*imageSet->find("Hotbar_Selected")).second[0], _hdc, (int)lt.x, 20 - 3);
		if (slot->item())
		{
			displayItem(_hdc, *slot->item()->linkItemImg(), slot->item()->itemCount(), Vector2Int{ (int)lt.x, 20 - 3 }, Vector2Int{ 55,55 });
		}
	}
	else if (chest)
	{
		ImageHandler::renderWithoutBack((*imageSet->find("chest_normal")).second[0], _hdc, (int)lt.x, (int)lt.y);
		if (slot && slot->item())
		{
			displayItem(_hdc, *slot->item()->linkItemImg(), slot->item()->itemCount(), Vector2Int{ (int)lt.x, (int)lt.y }, Vector2Int{ 45,45 });
		}
	}
	else
	{
		ImageHandler::renderWithoutBack((*imageSet->find("slot_normal")).second[0], _hdc, (int)lt.x, (int)lt.y);
		if (slot->item())
		{
			displayItem(_hdc, *slot->item()->linkItemImg(), slot->item()->itemCount(), Vector2Int{ (int)lt.x, (int)lt.y }, Vector2Int{ 50,50 });
		}
	}
}

void InventorySlotUI::displayItem(HDC _hdc, HBITMAP img, int count, Vector2Int start, Vector2Int slotSize)
{
	Vector2Int middle = start + slotSize / 2;

	BITMAP bitmap;
	GetObject(img, sizeof(BITMAP), &bitmap);
	int imgWidth = bitmap.bmWidth;
	int imgHeight = bitmap.bmHeight;

	ImageHandler::renderWithoutBack(img, _hdc, middle.x - imgWidth / 2, middle.y - imgHeight / 2);
	if (count == 1) return;
	ImageHandler::textResize(20, _hdc);
	ImageHandler::DrawOutlinedText(_hdc, std::to_wstring(count).c_str(), start.x + (int)(slotSize.y * 0.25f), start.y + (int)(slotSize.y * 0.55f));
}