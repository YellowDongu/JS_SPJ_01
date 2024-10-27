#include "framework.h"
#include "ArmourUI.h"
#include "CameraManager.h"
#include "EntityManager.h"
#include "UIManager.h"

ArmourUI::ArmourUI() : helmet(nullptr), plate(nullptr), leggings(nullptr), player(nullptr), APSlot(NULL)
{
}

ArmourUI::~ArmourUI()
{
	release();
}

void ArmourUI::init()
{
	helmet = new ArmourSlotUI();
	helmet->init();
	UIMgr->appendUI(helmet);
	plate = new ArmourSlotUI();
	plate->init();
	UIMgr->appendUI(plate);
	leggings = new ArmourSlotUI();
	leggings->init();
	UIMgr->appendUI(leggings);

	active = false;

	player = entityMgr->linkPlayer();
	APSlot = (rendering->findImage("UI", "inventory", "armour_point")).front();
}

void ArmourUI::update()
{
	if (Input->getButtonDown(KeyType::Escape))
	{
		active = !active;

		plate->setActive(active);
		helmet->setActive(active);
		leggings->setActive(active);
	}
	if (!active)
	{
		return;
	}

	if (plate->state() == UIState::End)
	{
		Item* item = player->linkInven()->pickedItem()->item();
		if (item && item->itemCategory() == -11)
		{
			Item* itemTemp = player->plateOff();
			player->plateSlot(item);
			player->linkInven()->pickedItem()->swapItem(itemTemp);
			
		}
		plate->changeState(UIState::normal);
	}
	else if (helmet->state() == UIState::End)
	{
		Item* item = player->linkInven()->pickedItem()->item();
		if (item && item->itemCategory() == -11)
		{
			Item* itemTemp = player->helmetOff();
			player->helmetSlot(item);
			player->linkInven()->pickedItem()->swapItem(itemTemp);

		}
		else if(!item)
		{
			Item* itemTemp = player->helmetOff();
			player->linkInven()->pickedItem()->swapItem(itemTemp);
		}
		plate->changeState(UIState::normal);
	}
	else if (leggings->state() == UIState::End)
	{
		Item* item = player->linkInven()->pickedItem()->item();
		if (item && item->itemCategory() == -11)
		{
			Item* itemTemp = player->leggingsOff();
			player->leggingsSlot(item);
			player->linkInven()->pickedItem()->swapItem(itemTemp);

		}
		plate->changeState(UIState::normal);
	}

	plate->leftTop({ cam->getWindowSize().x - 70.0f, cam->getWindowSize().y / 2});
	plate->rightBottom(plate->leftTop() + Vector2{ 50.0f, 50.0f });
	helmet->leftTop( plate->leftTop() - Vector2{ 0.0f, 55.0f });
	helmet->rightBottom(helmet->leftTop() + Vector2{ 50.0f, 50.0f });
	leggings->leftTop(plate->leftTop() + Vector2{ 0.0f, 55.0f });
	leggings->rightBottom(leggings->leftTop() + Vector2{ 50.0f, 50.0f });




}

void ArmourUI::triggered()
{
}

void ArmourUI::render(HDC _hdc)
{
	if (!active) return;

	int point = 0;
	if (player->helmetSlot())
	{
		helmet->render(_hdc, *player->helmetSlot()->linkItemImg());
		point += player->helmetSlot()->defense();
	}
	else helmet->render(_hdc, NULL);
	if (player->plateSlot())
	{
		plate->render(_hdc, *player->plateSlot()->linkItemImg());
		point += player->plateSlot()->defense();
	}
	else plate->render(_hdc, NULL);
	if (player->leggingsSlot())
	{
		leggings->render(_hdc, *player->leggingsSlot()->linkItemImg());
		point += player->leggingsSlot()->defense();
	}
	else leggings->render(_hdc, NULL);

	ImageHandler::renderWithoutBack(APSlot, _hdc, (int)leggings->leftTop().x - 45, (int)leggings->leftTop().y + 12);
	ImageHandler::textResize(20, _hdc);
	if (point < 10)
		ImageHandler::DrawOutlinedText(_hdc, std::to_wstring(point).c_str(), (int)leggings->leftTop().x - 30, (int)leggings->leftTop().y + 22);
	else
		ImageHandler::DrawOutlinedText(_hdc, std::to_wstring(point).c_str(), (int)leggings->leftTop().x - 35, (int)leggings->leftTop().y + 22);



}

void ArmourUI::release()
{
}

