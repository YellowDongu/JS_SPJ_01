#include "framework.h"
#include "InventoryUI.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "ImageHandler.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "PlayerInventory.h"

InventoryUI::InventoryUI() : imageSet(nullptr), inven(nullptr), hotbarText(nullptr), chestInven(nullptr)
{
}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::init(PlayerInventory* _playerInven)
{
	inven = _playerInven;
	auto find = rendering->findImageSet("UI")->find("inventory");
	active = false;
	chestInven = nullptr;

	Vector2Int SlotPosStart = Vector2Int{ 22, 22 };
	InventorySlot* hotBarSel = inven->selectedAtHotBar();

	int width = 22;
	for (int x = 0; x < 10; x++)
	{
		InventorySlotUI* slotUI = new InventorySlotUI();
		slotUI->linkImageSet(&(*find).second);
		InventorySlot* slot = inven->findSlotAtHotBar(x);
		slotUI->init(slot, { (float)width, 20 });
		if (hotBarSel == slot)
		{
			slotUI->setSelected(true);
			slotUI->rightBottom(slotUI->leftTop() + Vector2{55.0f,55.0f});
			width += 55 + 3;
		}
		else
		{
			slotUI->setSelected(false);
			slotUI->rightBottom(slotUI->leftTop() + Vector2{ 50.0f,50.0f });
			width += 50 + 3;
		}
		slotUI->setActive(true);
		slotUI->setChestSlot(false);
		hotbarSlot.push_back(slotUI);
		UIMgr->appendUI(slotUI);
	}

	width = 22;
	int height = 22 + 50 + 3;
	for (int y = 0; y < 4; y++)
	{
		width = 22;
		for (int x = 0; x < 10; x++)
		{
			InventorySlotUI* slotUI = new InventorySlotUI();
			slotUI->linkImageSet(&(*find).second);
			InventorySlot* slot = inven->findSlot(x, y);
			slotUI->init(slot, { (float)width, (float)height });

			slotUI->setSelected(false);
			slotUI->setChestSlot(false);
			slotUI->rightBottom(slotUI->leftTop() + Vector2{ 50.0f,50.0f });

			invenSlot.push_back(slotUI);
			UIMgr->appendUI(slotUI);

			width += 50 + 3;

		}
		height += 50 + 3;
	}

	width = 22 + 58;
	for (int y = 0; y < 4; y++)
	{
		width = 22 + 58;
		for (int x = 0; x < 10; x++)
		{
			InventorySlotUI* slotUI = new InventorySlotUI();
			slotUI->linkImageSet(&(*find).second);
			slotUI->init(nullptr, { (float)width, (float)height });

			slotUI->setSelected(false);
			slotUI->setChestSlot(true);
			slotUI->rightBottom(slotUI->leftTop() + Vector2{ 45.0f,45.0f });
			chestSlot.push_back(slotUI);
			UIMgr->appendUI(slotUI);
			width += 45 + 2;
		}
		height += 45 + 2;
	}
}

void InventoryUI::update()
{
	if (Input->getButtonDown(KeyType::Escape))
	{
		inventoryActive(!active);
	}
	hotBarSelect();

	if (!active) return;

	InventorySlot* selectedSlot = nullptr;



	for (auto& slot : invenSlot)
	{
		if (slot->state() == UIState::End)
		{
			selectedSlot = slot->getSlot();
			inven->swapSlot(*selectedSlot, *inven->pickedItem());
			slot->changeState(UIState::normal);
		}
	}

	if (chestInven)
	{
		for (auto& slot : chestSlot)
		{
			if (slot->state() == UIState::End)
			{
				selectedSlot = slot->getSlot();
				inven->swapSlot(*selectedSlot, *inven->pickedItem());
				slot->changeState(UIState::normal);
			}
		}
	}


	for (auto& slot : hotbarSlot)
	{
		if (slot->state() == UIState::End)
		{
			selectedSlot = slot->getSlot();
			inven->swapSlot(*selectedSlot, *inven->pickedItem());
			slot->changeState(UIState::normal);
		}
	}
}

void InventoryUI::render(HDC _hdc)
{
	int i = 1;
	for (auto& slot : hotbarSlot)
	{
		slot->renderSlot(_hdc);
		if (i == 10) i = 0;
		ImageHandler::textResize(20, _hdc);
		ImageHandler::DrawOutlinedText(_hdc, std::to_wstring(i).c_str(), (int)slot->leftTop().x + 5, (int)slot->leftTop().y + 5);
		i++;
	}

	if (!active)
	{
		ImageHandler::textResize(20, _hdc);
		ImageHandler::DrawOutlinedText(_hdc, L"Inventory", 200, 0);
		return;
	}
	ImageHandler::textResize(20, _hdc);
	ImageHandler::DrawOutlinedText(_hdc, L"Inventory", 50, 0);

	if (active)
	{
		for (auto& slot : invenSlot)
		{
			slot->renderSlot(_hdc);
		}

		if (chestInven)
		{
			for (auto& slot : chestSlot)
			{
				slot->renderSlot(_hdc);
			}
		}
	}


	if (inven->pickedItem()->item())
	{
		Vector2Int mousePos = { (int)Input->getMousePos().x, (int)Input->getMousePos().y };

		ImageHandler::renderWithoutBack(*inven->pickedItem()->item()->linkItemImg(), _hdc, mousePos.x, mousePos.y);
		if (inven->pickedItem()->item()->itemMaxCount() != 1)
		{
			ImageHandler::textResize(20, _hdc);
			ImageHandler::DrawOutlinedText(_hdc, std::to_wstring(inven->pickedItem()->item()->itemCount()).c_str(), mousePos.x, mousePos.y + 15);
		}
	}
}

void InventoryUI::triggered()
{




}

void InventoryUI::hotBarSelect()
{
	int i = -1;

	if (Input->getButtonDown(KeyType::N1)) { inven->selectAtHotBar(0);i = 0;}
	else if (Input->getButtonDown(KeyType::N2)) { inven->selectAtHotBar(1); i = 1;}
	else if (Input->getButtonDown(KeyType::N3)) { inven->selectAtHotBar(2); i = 2;}
	else if (Input->getButtonDown(KeyType::N4)) { inven->selectAtHotBar(3); i = 3;}
	else if (Input->getButtonDown(KeyType::N5)) { inven->selectAtHotBar(4); i = 4;}
	else if (Input->getButtonDown(KeyType::N6)) { inven->selectAtHotBar(5); i = 5;}
	else if (Input->getButtonDown(KeyType::N7)) { inven->selectAtHotBar(6); i = 6;}
	else if (Input->getButtonDown(KeyType::N8)) { inven->selectAtHotBar(7); i = 7;}
	else if (Input->getButtonDown(KeyType::N9)) { inven->selectAtHotBar(8); i = 8;}
	else if (Input->getButtonDown(KeyType::N0)) { inven->selectAtHotBar(9); i = 9;}
	else
	{
		for (auto& slot : hotbarSlot)
		{
			if (active) break;
			if (slot->state() == UIState::clicked)
			{
				for (auto& slotTemp : hotbarSlot)
				{
					slotTemp->setSelected(false);
				}
				slot->setSelected(true);
				slot->changeState(UIState::normal);
			}
		}
	}

	if (i != -1)
	{
		for (auto& slot : hotbarSlot)
		{
			slot->setSelected(false);
		}
		hotbarSlot[i]->setSelected(true);
	}




	int width = 22;
	for (auto& slot : hotbarSlot)
	{
		slot->leftTop({ (float)width, 20 });
		if (slot->isSelected())
		{
			slot->setSelected(true);
			slot->rightBottom({ (float)width + 55.0f, 20.0f + 55.0f });
			width += 55 + 3;
		}
		else
		{
			slot->setSelected(false);
			slot->rightBottom({ (float)width + 50.0f, 20.0f + 50.0f });
			width += 50 + 3;
		}
	}

}

void InventoryUI::inventoryActive(bool _value)
{
	active = _value;
	if (!active)
	{
		invenClosed();
		music->playNew("Menu_Close.wav");
	}
	else
	{
		music->playNew("Menu_Open.wav");
	}

	for (auto& slot : hotbarSlot)
	{
		slot->setActive(true);
	}

	for (auto& slot : invenSlot)
	{
		slot->setActive(active);
	}

	if (chestInven)
	{
		for (auto& slot : chestSlot)
		{
			slot->setActive(active);
		}
		if (!active) chestInven = nullptr;
	}
}

void InventoryUI::chestSelected(Inventory* inven)
{ 
	chestInven = inven;

	for (int i = 0; i < chestSlot.size(); i++)
	{
		chestSlot[i]->linkChestSlot((*chestInven->linkInven())[i]);
	}

	active = true;
	music->playNew("Menu_Open.wav");
}

void InventoryUI::invenClosed()
{
	if (chestInven)
	{
		for (auto& slot : chestSlot)
		{
			slot->unlinkChestSlot();
		}
		chestInven = nullptr;
	}
}

void InventoryUI::displayItem(HDC _hdc, HBITMAP img, int count, Vector2Int start, Vector2Int slotSize)
{
	Vector2Int middle = start + slotSize / 2;

	BITMAP bitmap;
	GetObject(img, sizeof(BITMAP), &bitmap);
	int imgWidth = bitmap.bmWidth;
	int imgHeight = bitmap.bmHeight;

	ImageHandler::renderWithoutBack(img, _hdc, middle.x - imgWidth / 2, middle.y - imgHeight / 2);
}
