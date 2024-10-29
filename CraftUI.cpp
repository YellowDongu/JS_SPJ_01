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

CraftUI::CraftUI() : basePos(Vector2::zero()), moveUp(false), moveDown(false), index(0), minIndex(0), maxIndex(0), selectedIndex(0), maxVisiableSlot(0)
, moveDist(0.0f), upLimit(0.0f), downLimit(0.0f), scrollSpeed(0.0f), playerInven(nullptr), slotImg(NULL), selectedSlotImg(NULL), smallSlotImg(NULL)
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
		music->playNew("Menu_Tick.wav");
	}
	if (Input->getButtonDown(KeyType::G) && selectedIndex != 0)
	{
		currentSlots[selectedIndex]->setSelected(false);
		selectedIndex--;
		currentSlots[selectedIndex]->setSelected(true);
		music->playNew("Menu_Tick.wav");
	}

	if (moveDown)
	{
		scrollDown();
	}
	else if (moveUp)
	{
		scrollUp();
	}
	else
	{
		if (index != selectedIndex)
		{
			moveDown = index < selectedIndex;
			moveUp = index > selectedIndex;
		}
		else if (!currentSlots[index]->isSelected())
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
			selectedIndex = i;
			slot->changeState(UIState::normal);
			music->playNew("Menu_Tick.wav");
		}
		i++;


		if (slot->isSelected())
		{
			for (int i = 0; i < (int)slot->linkRecipe()->needed.size(); i++)
			{
				Vector2Int start = Vector2Int{ 100 + 45 * i, 600 };
				Vector2Int slotSize = Vector2Int{ 35, 35 };
				ImageHandler::renderWithoutBack(smallSlotImg, _hdc, start.x, start.y);

				Vector2Int middle = start + slotSize / 2;

				BITMAP bitmap;
				GetObject(slot->linkRecipe()->IngredientImg[i], sizeof(BITMAP), &bitmap);
				int imgWidth = bitmap.bmWidth;
				int imgHeight = bitmap.bmHeight;

				ImageHandler::renderWithoutBack(slot->linkRecipe()->IngredientImg[i], _hdc, middle.x - imgWidth / 2, middle.y - imgHeight / 2);
				if (slot->linkRecipe()->needed[i].second != 1)
				{
					ImageHandler::textResize(20, _hdc);
					ImageHandler::DrawOutlinedText(_hdc, std::to_wstring(slot->linkRecipe()->needed[i].second).c_str(), start.x + (int)(slotSize.y * 0.25f), start.y + (int)(slotSize.y * 0.55f));
				}
			}
		}


		if (slot->isActive())
			slot->renderSlot(_hdc);
	}

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
	int i = 0;
	for (auto& slot : currentSlots)
	{
		slot->position().y += Time->deltaTime() * scrollSpeed;

		if (slot->isSelected())
		{
			if (slot->position().y > basePos.y + 5.0f)
			{
				moveDown = false;
				moveUp = true;
				return;
			}
		}



		if (slot->position().y > basePos.y - 5.0f && slot->position().y < basePos.y + 5.0f)
		{
			float diff = basePos.y - slot->position().y;
			if (slot->isSelected())
			{
				index = selectedIndex;
				music->playNew("Menu_Tick.wav");


				int calIndex = 0;
				for (auto& slotOther : currentSlots)
				{
					slotOther->position({ 35.0f, 600.0f - (55.0f * (calIndex - selectedIndex)) });
					calIndex++;
				}

				moveUp = false;
				moveDown = false;
				return;
			}
			else
			{
				if (slot != currentSlots[index])
				{
					music->playNew("Menu_Tick.wav");
					index = i;
				}
			}

		}

		if (slot->position().y > upLimit) slot->setActive(false);
		else if (slot->position().y < downLimit) slot->setActive(false);
		else slot->setActive(true);

		i++;
	}


}

void CraftUI::scrollUp()
{
	int i = 0;
	for (auto& slot : currentSlots)
	{
		slot->position().y -= Time->deltaTime() * scrollSpeed;

		if (slot->isSelected())
		{
			if (slot->position().y < basePos.y - 5.0f)
			{
				moveDown = true;
				moveUp = false;
			}
		}

		if (slot->position().y > basePos.y - 5.0f && slot->position().y < basePos.y + 5.0f)
		{
			float diff = basePos.y - slot->position().y;
			if (slot->isSelected())
			{
				index = selectedIndex;
				music->playNew("Menu_Tick.wav");

				int calIndex = 0;
				for (auto& slotOther : currentSlots)
				{
					slotOther->position({ 35.0f, 600.0f - (55.0f * (calIndex - selectedIndex)) });
					calIndex++;
				}
				moveUp = false;
				moveDown = false;


				return;
			}
			else
			{
				if (slot != currentSlots[index])
				{
					index = i;
					music->playNew("Menu_Tick.wav");
				}
			}

		}
		if (slot->position().y > upLimit) slot->setActive(false);
		else if (slot->position().y < downLimit) slot->setActive(false);
		else slot->setActive(true);

		i++;
	}
}

void CraftUI::resetSlot()
{
	currentSlots.clear();
	int i = 0;

	for (auto& slot : slots)
	{
		slot->setActive(false);
		slot->setSelected(false);
		if (slot->getRecipe()->craftable)
		{
			currentSlots.push_back(slot);
			slot->position({ 35.0f, 600.0f - (55.0f * i) });

			if (slot->position().y > upLimit && active) slot->setActive(false);
			else if (slot->position().y < downLimit && active) slot->setActive(false);
			else slot->setActive(true);

			i++;
		}
	}

	selectedIndex = 0;
	index = 0;
	currentSlots.front()->setSelected(true);


	moveUp = false;
	moveDown = false;
}
