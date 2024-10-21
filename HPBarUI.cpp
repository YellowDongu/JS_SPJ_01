#include "framework.h"
#include "HPBarUI.h"
#include "RenderManager.h"
#include "Player.h"
#include "CameraManager.h"
#include "ImageHandler.h"


HPBarUI::HPBarUI() : playerHP(nullptr), playerMaxHP(nullptr), left(NULL), middle(NULL), right(NULL), gauge(NULL)
{
}

HPBarUI::~HPBarUI()
{
}

void HPBarUI::init(Player* _player)
{
	left = rendering->findImage("UI", "panel", "left")[0];
	middle = rendering->findImage("UI", "hpPanel", "middle")[0];
	right = rendering->findImage("UI", "hpPanel", "right")[0];
	gauge = rendering->findImage("UI", "hpGauge", "fill")[0];

	playerHP = _player->linkHealth();
	playerMaxHP = _player->linkMaxHealth();
	//12/24 Áß°£ y + 10 x=>16
}


void HPBarUI::update()
{

}

void HPBarUI::triggered()
{

}

void HPBarUI::render(HDC _hdc)
{
	int width = (int)cam->getWindowSize().x - 76;
	int height = 10;
	int length = *playerMaxHP / 20;

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


	length = *playerHP / 20;
	width = barStart;

	for (int i = 0; i < length; i++)
	{
		ImageHandler::renderWithoutBack(gauge, _hdc, width, height + 6);
		width -= 12;
	}


	int restBarWidth = ((*playerHP % 20) * 12) / 20;

	HBITMAP bar = ImageHandler::cropImage(gauge, { 12 - restBarWidth ,0 }, { restBarWidth, 12 });
	ImageHandler::renderWithoutBack(bar, _hdc, width + (12 - restBarWidth), height + 6);

}