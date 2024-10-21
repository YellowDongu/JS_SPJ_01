#include "framework.h"
#include "DebugUI.h"
#include "InputManager.h"
#include "ImageHandler.h"
#include "CameraManager.h"
#include "GridMap.h"
#include "TimeManager.h"
#include "LightManager.h"

DebugUI::DebugUI()
{
}

DebugUI::~DebugUI()
{
}

void DebugUI::update()
{
}

void DebugUI::render(HDC _hdc)
{
	Vector2 pos = cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y });
	std::string text = std::to_string((int)pos.x) + "/" + std::to_string((int)pos.y);
	std::wstring wText;
	wText.assign(text.begin(), text.end());
	ImageHandler::textResize(20, _hdc);
	ImageHandler::DrawOutlinedText(_hdc, wText.c_str(), (int)lt.x, (int)lt.y);

	text = std::to_string(Time->GetFPS());
	wText.assign(text.begin(), text.end());
	ImageHandler::textResize(20, _hdc);
	ImageHandler::DrawOutlinedText(_hdc, wText.c_str(), (int)lt.x, (int)lt.y + 25);

	Node* node = gridMap->findNode(pos);
	if (!node) return;
	Vector2Int gridPos = node->position();
	text = std::to_string(gridPos.x) + "/" + std::to_string(gridPos.y);
	wText.assign(text.begin(), text.end());
	ImageHandler::textResize(20, _hdc);
	ImageHandler::DrawOutlinedText(_hdc, wText.c_str(), (int)lt.x, (int)lt.y + 50);

	text = std::to_string(sun->getTime());
	wText.assign(text.begin(), text.end());
	ImageHandler::textResize(20, _hdc);
	ImageHandler::DrawOutlinedText(_hdc, wText.c_str(), (int)lt.x, (int)lt.y + 75);
}

void DebugUI::triggered()
{
}
