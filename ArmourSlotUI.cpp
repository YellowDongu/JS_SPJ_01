#include "framework.h"
#include "ArmourSlotUI.h"
#include "RenderManager.h"
#include "ImageHandler.h"

ArmourSlotUI::ArmourSlotUI()
{
}

ArmourSlotUI::~ArmourSlotUI()
{
}

void ArmourSlotUI::init()
{
	auto find = rendering->findImageSet("UI")->find("inventory");
	imageSet = &(*find).second;
}

void ArmourSlotUI::update()
{
}

void ArmourSlotUI::triggered()
{
	currentState = UIState::End;

}

void ArmourSlotUI::render(HDC _hdc)
{
}

void ArmourSlotUI::render(HDC _hdc, HBITMAP item)
{
	ImageHandler::renderWithoutBack((*imageSet->find("armour_slot")).second[0], _hdc, (int)lt.x, (int)lt.y);
	if (item != NULL)
	{
		Vector2Int middle = Vector2::toVec2Int(lt) + Vector2Int{ 25, 25 };

		BITMAP bitmap;
		GetObject(item, sizeof(BITMAP), &bitmap);
		int imgWidth = bitmap.bmWidth;
		int imgHeight = bitmap.bmHeight;

		ImageHandler::renderWithoutBack(item, _hdc, middle.x - imgWidth / 2, middle.y - imgHeight / 2);
	}
}
