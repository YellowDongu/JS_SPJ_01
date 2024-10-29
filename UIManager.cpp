#include "framework.h"
#include "UI.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "popUpUI.h"
#include "Cursor.h"

void UIManager::clear()
{
}

void UIManager::release()
{
	if (!uiList.empty())
	{
		for (auto& ui : uiList)
		{
			delete ui;
		}
		uiList.clear();
	}


	if (!popUpUIList.empty())
	{
		for (auto& ui : popUpUIList)
		{
			delete ui;
		}
		popUpUIList.clear();
	}
	inven = nullptr;
	cursor = nullptr;
}

void UIManager::update()
{
	if (!popUpUIList.empty())
	{
		while (true)
		{
			if (popUpUIList.empty()) return;
			popUpUI* pop = (popUpUI*)(popUpUIList.front());

			if (pop->time() > 3.0f)
			{
				delete pop;
				popUpUIList.pop_front();
			}
			else break;
		}

		for (auto& pop : popUpUIList)
		{
			pop->update();
		}
	}

	if (uiList.empty()) return;

	for (auto& ui : uiList)
	{
		ui->update();
	}
}

bool UIManager::checkColl()
{
	for (auto& ui : uiList)
	{
		if (!ui->isActive()) continue;
		if (CollisionHandler::collision(ui))
		{
			if (cursor)
			{
				((Cursor*)cursor)->hovering(ui);
			}

			return true;
		}
	}

	if (cursor)
	{
		((Cursor*)cursor)->notHovering();
	}
	return false;
}

void UIManager::render(HDC _hdc)
{
	if (!uiList.empty())
	{
		for (auto& ui : uiList)
		{
			ui->render(_hdc);
		}
	}
	if (!popUpUIList.empty())
	{
		for (auto& ui : popUpUIList)
		{
			ui->render(_hdc);
		}

	}
}

void UIManager::createPopUpText(Vector2 pos, std::wstring content)
{
	popUpUI* pop = new popUpUI();
	pop->init(pos, content);
	popUpUIList.push_back(pop);
}
