#include "framework.h"
#include "CameraManager.h"
#include "EntityManager.h"

void cameraManager::init(const Vector2& startPosition, const HWND& _hwnd)
{
	centerPosition = startPosition;
	hWnd = _hwnd;
}

void cameraManager::update()
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	windowSize = Vector2{ static_cast<float>(clientRect.right - clientRect.left), static_cast<float>(clientRect.bottom - clientRect.top) };

	if (centerPosition.x - windowSize.x / 2 < borderMin.x)
		centerPosition.x = borderMin.x + windowSize.x / 2;
	if (centerPosition.x + windowSize.x / 2 > borderMax.x)
		centerPosition.x = borderMax.x - windowSize.x / 2;
	if (centerPosition.y - windowSize.y / 2 < borderMin.y)
		centerPosition.y = borderMin.y + windowSize.y / 2;
	if (centerPosition.y + windowSize.y / 2 > borderMax.y)
		centerPosition.y = borderMax.y - windowSize.y / 2;
}

void cameraManager::setBorder(const Vector2& _posMin, const Vector2& _posMax)
{
	borderMin = _posMin;
	borderMax = _posMax;
}

// ¿ùµåÁÂÇ¥ -> È­¸éÁÂÇ¥
Vector2 cameraManager::calculateScreenPosition(const Vector2& position)
{
	Vector2 relativePos = position - centerPosition;
	return windowSize / 2 + Vector2(relativePos.x, -relativePos.y);
}
// È­¸éÁÂÇ¥ -> ¿ùµåÁÂÇ¥
Vector2 cameraManager::calculateWorldPosition(const Vector2& position)
{
	Vector2 relativePos = position - windowSize / 2;
	return centerPosition + Vector2(relativePos.x, -relativePos.y);
}
// ¿ùµåÁÂÇ¥ -> È­¸éÁÂÇ¥
Vector2 cameraManager::calculateScreenPosition(const HWND& _hwnd, const Vector2& position, const Vector2& camPosition)
{
	RECT clientRect;
	GetClientRect(_hwnd, &clientRect);
	float width = static_cast<float>(clientRect.right - clientRect.left);
	float height = static_cast<float>(clientRect.bottom - clientRect.top);

	Vector2 relativePos = position - camPosition;
	return Vector2{ width, height } / 2 + Vector2{ relativePos.x, -relativePos.y };
}
// È­¸éÁÂÇ¥ -> ¿ùµåÁÂÇ¥
Vector2 cameraManager::calculateWorldPosition(const HWND& _hwnd, const Vector2& position, const Vector2& camPosition)
{
	RECT clientRect;
	GetClientRect(_hwnd, &clientRect);
	float width = static_cast<float>(clientRect.right - clientRect.left);
	float height = static_cast<float>(clientRect.bottom - clientRect.top);

	Vector2 relativePos = position - Vector2{ width, height } / 2;
	return camPosition + Vector2{ relativePos.x, -relativePos.y };
}
