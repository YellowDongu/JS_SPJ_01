#include "framework.h"
#include "CraftSlotUI.h"
#include "ImageHandler.h"
#include "Item.h"
#include "RenderManager.h"
#include "EntityManager.h"
#include "SoundManager.h"

CraftSlotUI::CraftSlotUI() : active(false), selected(false), recipe(nullptr), imageSet(nullptr)
{
}

CraftSlotUI::~CraftSlotUI()
{
}

void CraftSlotUI::init(RecipeInfo* _recipe, Vector2 _position)
{
	lt = _position;
	recipe = _recipe;
	auto find = rendering->findImageSet("UI")->find("inventory");
	imageSet = &(*find).second;
}

void CraftSlotUI::update()
{
}

void CraftSlotUI::triggered()
{
	
	if (!selected)
	{
		currentState = UIState::End;
		return;
	}

	InventorySlot* hand = entityMgr->linkPlayer()->linkInven()->pickedItem();

	if (hand->item())
	{
		if (hand->item()->itemCode() == recipe->resItem->itemCode() &&
			hand->item()->itemMaxCount() >= hand->item()->itemCount() + recipe->resItem->itemCount())
		{
			Item* item = Craft->craft(recipe);
			if (!item) return;
			hand->item()->addItemCount(recipe->resItem->itemCount());
			delete item;
			music->playNew("Grab.wav");
			return;
		}
		else return;
	}

	Item* item = Craft->craft(recipe);
	if (item)	
	{
		hand->aquireItem(item, 0);
		music->playNew("Grab.wav");
	}

	currentState = UIState::normal;
}

void CraftSlotUI::render(HDC _hdc)
{
}

void CraftSlotUI::renderSlot(HDC _hdc)
{
	if (selected)
	{
		ImageHandler::renderWithoutBack((*imageSet->find("Hotbar_Selected")).second[0], _hdc, (int)lt.x, (int)lt.y);
		rb.x = lt.x + 55.0f;
		rb.y = lt.y + 55.0f;
		displayItem(_hdc, *recipe->resItem->linkItemImg(), recipe->resItem->itemCount(), Vector2Int{ (int)lt.x, (int)lt.y }, Vector2Int{ 55,55 });
	}
	else
	{
		ImageHandler::renderWithoutBack((*imageSet->find("slot_normal")).second[0], _hdc, (int)lt.x, (int)lt.y);
		rb.x = lt.x + 50.0f;
		rb.y = lt.y + 50.0f;
		displayItem(_hdc, *recipe->resItem->linkItemImg(), recipe->resItem->itemCount(), Vector2Int{ (int)lt.x, (int)lt.y }, Vector2Int{ 50,50 });
	}
}

void CraftSlotUI::displayItem(HDC _hdc, HBITMAP img, int count, Vector2Int start, Vector2Int slotSize)
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