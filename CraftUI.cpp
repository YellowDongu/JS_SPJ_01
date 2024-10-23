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
#include "SoundManager.h"

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
	selectedIndex = 0;
	scrollSpeed = 200.0f;
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
	}
	resetSlot();
}

void CraftUI::update()
{
	if (Craft->isChanged())
	{
		resetSlot();
		Craft->checkChanged();
	}



	if (UIMgr->getInven()->isActive() != active)
	{
		active = !active;
		for (auto& slot : currentSlots)
		{
			if (slot->position().y > upLimit) slot->setActive(false);
			else if (slot->position().y < downLimit) slot->setActive(false);
			else slot->setActive(active);
		}
	}
	if (Input->getButtonDown(KeyType::T) && selectedIndex != currentSlots.size() - 1)
	{
		currentSlots[selectedIndex]->setSelected(false);
		selectedIndex++;
		currentSlots[selectedIndex]->setSelected(true);
	}
	if (Input->getButtonDown(KeyType::F) && selectedIndex != 0)
	{
		currentSlots[selectedIndex]->setSelected(false);
		selectedIndex--;
		currentSlots[selectedIndex]->setSelected(true);
	}

	if (moveDown)
	{
		moveDown = index < selectedIndex;
		moveUp = index > selectedIndex;

		scrollDown();
	}
	else if (moveUp)
	{
		moveDown = index < selectedIndex;
		moveUp = index > selectedIndex;

		scrollUp();
	}
	else
	{
		if (index != selectedIndex)
		{
			moveDown = index < selectedIndex;
			moveUp = index > selectedIndex;
		}
		else if (!slots[index]->isSelected())
		{
			int i = 0;
			for (auto& slot : currentSlots)
			{
				if (slot->isSelected())
				{
					selectedIndex = i;
					break;
				}
				i++;
			}
		}
	}


}

void CraftUI::triggered()
{
}

void CraftUI::render(HDC _hdc)
{
	if (!active) return;

	int i = 0;
	for (auto& slot : currentSlots)
	{
		if (slot->state() == UIState::End)
		{
			currentSlots[selectedIndex]->setSelected(false);
			currentSlots[i]->setSelected(true);
			slot->changeState(UIState::normal);
		}

		if (!slot->isActive()) continue;
		slot->renderSlot(_hdc);
		i++;
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
	for (auto& slot : currentSlots)
	{
		slot->position().y += Time->deltaTime() * scrollSpeed;

		if (slot->position().y > basePos.y - 5.0f && slot->position().y < basePos.y + 5.0f)
		{
			float diff = basePos.y - slot->position().y;
			if (slot->isSelected())
			{
				for (auto& slotOther : currentSlots)
				{
					slotOther->position().y += diff;
				}
				moveDown = false;
				if (slot != currentSlots[index])
					index++;
				return;
			}
			else
			{
				if (slot != currentSlots[index])
					index++;
			}

		}

		if (slot->position().y > upLimit) slot->setActive(false);
		else if (slot->position().y < downLimit) slot->setActive(false);
		else slot->setActive(true);
	}


}

void CraftUI::scrollUp()
{
	for (auto& slot : currentSlots)
	{
		slot->position().y -= Time->deltaTime() * scrollSpeed;

		if (slot->position().y > basePos.y - 5.0f && slot->position().y < basePos.y + 5.0f)
		{
			float diff = basePos.y - slot->position().y;
			if (slot->isSelected())
			{
				for (auto& slotOther : currentSlots)
				{
					slotOther->position().y += diff;
				}
				moveUp = false;
				if (slot != currentSlots[index])
					index--;
				return;
			}
			else
			{
				if (slot != currentSlots[index])
					index--;
			}

		}
		if (slot->position().y > upLimit) slot->setActive(false);
		else if (slot->position().y < downLimit) slot->setActive(false);
		else slot->setActive(true);
	}
}

void CraftUI::resetSlot()
{
	currentSlots.clear();
	int i = 0;

	for (auto& slot : slots)
	{
		slot->setActive(false);
		if (slot->isSelected())
		{
			slot->setSelected(false);
		}
		if (slot->getRecipe()->craftable)
		{
			slot->position({ 35.0f, 600.0f - (65.0f * i) });

			currentSlots.push_back(slot);
			i++;
		}
		if (slot->position().y > upLimit && active) slot->setActive(false);
		else if (slot->position().y < downLimit && active) slot->setActive(false);
		else slot->setActive(true);
	}

	selectedIndex = 0;
	index = 0;
	currentSlots.front()->setSelected(true);


	moveUp = false;
	moveDown = false;
}
