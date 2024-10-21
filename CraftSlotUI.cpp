#include "framework.h"
#include "CraftSlotUI.h"
#include "ImageHandler.h"
#include "Item.h"
#include "RenderManager.h"


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
	currentState = UIState::End;
}

void CraftSlotUI::render(HDC _hdc)
{
}

void CraftSlotUI::renderSlot(HDC _hdc)
{
	if (selected)
	{
		ImageHandler::renderWithoutBack((*imageSet->find("Hotbar_Selected")).second[0], _hdc, (int)lt.x, (int)lt.y);
		displayItem(_hdc, *recipe->resItem->linkItemImg(), recipe->resItem->itemCount(), Vector2Int{ (int)lt.x, (int)lt.y }, Vector2Int{ 55,55 });
	}
	else
	{
		ImageHandler::renderWithoutBack((*imageSet->find("slot_normal")).second[0], _hdc, (int)lt.x, (int)lt.y);
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