#include "framework.h"
#include "ArmourUI.h"
#include "CameraManager.h"
#include "EntityManager.h"
#include "UIManager.h"

ArmourUI::ArmourUI() : helmet(nullptr), plate(nullptr), leggings(nullptr), player(nullptr)
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

	if (player->helmetSlot())
	{
		helmet->render(_hdc, *player->helmetSlot()->linkItemImg());
	}
	else helmet->render(_hdc, NULL);
	if (player->plateSlot())
	{
		plate->render(_hdc, *player->plateSlot()->linkItemImg());
	}
	else plate->render(_hdc, NULL);
	if (player->leggingsSlot())
	{
		leggings->render(_hdc, *player->leggingsSlot()->linkItemImg());
	}
	else leggings->render(_hdc, NULL);
}

void ArmourUI::release()
{
	/*
	if (plate)
	{
		delete plate;
		plate = nullptr;
	}
	if (helmet)
	{
		delete helmet;
		helmet = nullptr;
	}
	if (leggings)
	{
		delete leggings;
		leggings = nullptr;
	}
	*/

}

