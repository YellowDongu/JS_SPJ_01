#include "framework.h"
#include "MPBarUI.h"
#include "Player.h"
#include "RenderManager.h"
#include "ImageHandler.h"


MPBarUI::MPBarUI() : playerMP(nullptr), playerMaxMP(nullptr), left(NULL), middle(NULL), right(NULL), gauge(NULL)
{
}

MPBarUI::~MPBarUI()
{
}

void MPBarUI::init(Player* _player)
{
	left = rendering->findImage("UI", "panel", "left")[0];
	middle = rendering->findImage("UI", "mpPanel", "middle")[0];
	right = rendering->findImage("UI", "mpPanel", "right")[0];
	gauge = rendering->findImage("UI", "mpGauge", "fill")[0];

	playerMP = _player->linkMana();
	playerMaxMP = _player->linkMaxMana();
	//12/24 Áß°£ y + 10 x=>16
}


void MPBarUI::update()
{

}

void MPBarUI::triggered()
{

}

void MPBarUI::render(HDC _hdc)
{
	int width = (int)cam->getWindowSize().x - 85;
	int height = 40;
	int length = *playerMaxMP / 20;

	ImageHandler::renderWithoutBack(right, _hdc, width, height);
	width += 16 - 12;
	int barStart = width;
	height += 10;
	for (int i = 0; i < length; i++)
	{
		ImageHandler::renderWithoutBack(middle, _hdc, width, height);
		width -= 12;
	}
	width += 6;
	ImageHandler::renderWithoutBack(left, _hdc, width, height);


	length = *playerMP / 20;
	width = barStart;

	for (int i = 0; i < length; i++)
	{
		ImageHandler::renderWithoutBack(gauge, _hdc, width, height + 6);
		width -= 12;
	}

	int restBarWidth = ((*playerMP % 20) * 12) / 20;

	HBITMAP bar = ImageHandler::cropImage(gauge, { 12 - restBarWidth ,0 }, { restBarWidth, 12 });
	ImageHandler::renderWithoutBack(bar, _hdc, width + (12 - restBarWidth), height + 6);
}