#include "framework.h"
#include "EndUI.h"
#include "CameraManager.h"
#include "ImageHandler.h"
#include "InputManager.h"

EndUI::EndUI() : hBrush(NULL), hPen(NULL)
{
	active = false;
}

EndUI::~EndUI()
{
}

void EndUI::update()
{
	if (!active) return;
	
	if (Input->getButton(KeyType::Escape))
	{
		PostQuitMessage(0);
	}


}

void EndUI::triggered()
{
}

void EndUI::render(HDC _hdc)
{
	if (!active) return;

	if(hBrush == NULL)
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
	if (hPen == NULL)
		hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));


	HPEN oldPen = (HPEN)SelectObject(_hdc, hPen);
	HBRUSH oldbrush = (HBRUSH)SelectObject(_hdc, hBrush);

	Rectangle(_hdc, 0, 0, cam->getWindowSize().x, cam->getWindowSize().y);

	SelectObject(_hdc, oldPen);
	SelectObject(_hdc, oldbrush);

	ImageHandler::deathTextFont(_hdc);
	ImageHandler::DrawOutlinedText(_hdc, L"END", (int)(cam->getWindowSize().x / 2.0f) - 100, (int)(cam->getWindowSize().y / 2.0f) - 50);
}
