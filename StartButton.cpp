#include "framework.h"
#include "StartButton.h"
#include "ImageHandler.h"
#include "TimeManager.h"
#include "SoundManager.h"

StartButton::StartButton() : size(100.0f)
{
}

StartButton::~StartButton()
{
}

void StartButton::update()
{
}

void StartButton::render(HDC _hdc)
{
	int x = (int)(lt.x + (size - 100.0f));
	int y = (int)(lt.y + (size - 100.0f));

	COLORREF currnetColor = RGB(0, 0, 0);
	switch (currentState)
	{
	case normal:
		size = 100.0f;
		currnetColor = RGB(100, 100, 100);
		break;
	case hoverMouse:
		if (size < 120.0f) { size += Time->deltaTime() * 250.0f; }
		currnetColor = RGB(255, 215, 0);
		break;
	case clicked:
		break;
	default:
		size = 100.0f;
		break;
	}
	ImageHandler::textResize((int)size, _hdc);

	const TCHAR* text = _T("Start");
	
	SIZE textSize;
	GetTextExtentPoint32(_hdc, text, _tcslen(text), &textSize);
	
	lt = { (cam->getWindowSize().x / 2) - textSize.cx / 2, 400.0f };
	rb = { (cam->getWindowSize().x / 2) + textSize.cx / 2, 400.0f + textSize.cy - 20 };
	ImageHandler::DrawOutlinedText(_hdc, text, (int)lt.x, (int)lt.y, currnetColor);
}

void StartButton::triggered()
{
	currentState = UIState::clicked;
}
