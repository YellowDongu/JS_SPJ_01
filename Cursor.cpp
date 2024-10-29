#include "framework.h"
#include "Cursor.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ImageHandler.h"
#include "TimeManager.h"

Cursor::Cursor() : cursorImg(NULL)
{
}

Cursor::~Cursor()
{
}

void Cursor::update()
{
	if (hoveringUI)
	{
		time -= Time->deltaTime();
	}
}

void Cursor::triggered()
{
}

void Cursor::render(HDC _hdc)
{
	ImageHandler::renderWithoutBack(cursorImg, _hdc, (int)Input->getMousePos().x, (int)Input->getMousePos().y);


}

void Cursor::init()
{
	cursorImg = (rendering->findImage("UI", "cursor", "default")).front();
}
