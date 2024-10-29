#include "framework.h"
#include "DeathUI.h"
#include "ImageHandler.h"
#include "EntityManager.h"

DeathUI::DeathUI() : dead(nullptr), spawnCount(nullptr)
{
}

DeathUI::~DeathUI()
{
}

void DeathUI::update()
{
}

void DeathUI::triggered()
{
}

void DeathUI::render(HDC _hdc)
{
	if (*dead)
	{
		ImageHandler::deathTextFont(_hdc);
		ImageHandler::DrawOutlinedText(_hdc, text.c_str(), (int)(cam->getWindowSize().x / 2) - 300, (int)(cam->getWindowSize().y / 2) - 120, RGB(255, 195, 222));
		ImageHandler::DrawOutlinedText(_hdc, std::to_wstring((int)*spawnCount).c_str(), (int)(cam->getWindowSize().x / 2) - 20, (int)(cam->getWindowSize().y / 2), RGB(255, 195, 222));
	}

}

void DeathUI::init()
{
	text = L"You were slain...";
	dead = entityMgr->linkPlayer()->linkDead();
	spawnCount = entityMgr->linkPlayer()->linkSpawnCount();
}
