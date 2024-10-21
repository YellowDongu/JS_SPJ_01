#include "framework.h"
#include "CraftUI.h"
#include "PlayerInventory.h"
#include "RenderManager.h"
#include "ImageHandler.h"
#include "InputManager.h"
#include "CameraManager.h"
#include "TimeManager.h"
#include "Recipe.h"
#include "UIManager.h"
#include "EntityManager.h"

CraftUI::CraftUI() : basePos(Vector2::zero()), upLimit(0.0f), downLimit(0.0f)
{
}

CraftUI::~CraftUI()
{
	release();
}

void CraftUI::init()
{
	slotImg = (rendering->findImage("UI", "inventory", "slot_normal")).front();
	selectedSlotImg = (rendering->findImage("UI", "inventory", "Hotbar_Selected")).front();
	smallSlotImg = ImageHandler::zoomImage(slotImg, 0.70f);
	active = false;
	upLimit = 700.0f;
	downLimit = 500.0f;
	moveUp = false;
	moveDown = false;
	moveDist = 0.0f;
	basePos.x = 35.0f;
	basePos.y = 600.0f;
	index = 0;
	Vector2 currentPos = basePos;
	playerInven = entityMgr->linkPlayer()->linkInven();
	Craft->init();
	auto* list = Craft->linkRecipes();
	for (auto& slot : *list)
	{
		CraftSlotUI* newSlot = new CraftSlotUI();
		UIMgr->appendUI(newSlot);
		newSlot->init(slot, { 0,0 });

		slots.push_back(newSlot);
		if (slots.size() <= 3)
		{
			currentSlots.push_back(newSlot);
			newSlot->position({ 35.0f, basePos.y - (50.0f * (currentSlots.size() - 1)) });
			
			if (slots.size() == 1) newSlot->setSelected(true);
			else
			{
				newSlot->translate({ 0.0f, -10.0f });
				newSlot->setSelected(false);
			}

		}
	}

}

void CraftUI::update()
{
	if (Input->getButtonDown(KeyType::Escape))
	{
		active = !active;
	}

	if (!active) return;

	for (auto& slot : currentSlots)
	{
		if (slot->state() == UIState::End)
		{
			InventorySlot* hand = playerInven->pickedItem();

			if (hand->item()) return;

			Item* item = Craft->craft(slot->getRecipe());
			if (item)
			{
				hand->aquireItem(item, 0);
				
			}
			slot->changeState(UIState::normal);
			return;
		}

	}




}

void CraftUI::triggered()
{
}

void CraftUI::render(HDC _hdc)
{
	if (!active) return;


	for (auto& slot : currentSlots)
	{
		slot->renderSlot(_hdc);
	}

	ImageHandler::renderWithoutBack(smallSlotImg, _hdc, 100, 600);
	ImageHandler::textResize(20, _hdc);
	ImageHandler::DrawOutlinedText(_hdc, L"Crafting", 100, 640);


}

void CraftUI::release()
{
	slots.clear();
	currentSlots.clear();
}

void CraftUI::scrollDown()
{
}

void CraftUI::scrollUp()
{
}
