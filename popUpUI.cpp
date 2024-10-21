#include "framework.h"
#include "popUpUI.h"
#include "TimeManager.h"
#include "ImageHandler.h"

popUpUI::popUpUI() : liveTime(0), size(0)
{
}

popUpUI::~popUpUI()
{
}

void popUpUI::init(Vector2Int pos, std::wstring _text)
{
	active = true;
	text = _text;
	lt = pos;
	rb = pos;
}

void popUpUI::update()
{
	liveTime += Time->deltaTime();
	if (liveTime > 10.0f)
	{
		size -= Time->deltaTime() * 3.0f;
	}
}

void popUpUI::triggered()
{
}

void popUpUI::render(HDC _hdc)
{
	ImageHandler::textResize((int)size, _hdc);
	ImageHandler::DrawOutlinedText(_hdc, text.c_str(), lt.x, lt.y);
}
