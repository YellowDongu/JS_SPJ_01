#include "framework.h"
#include "animationContainer.h"
#include "TimeManager.h"
#include "ImageHandler.h"
#include "Entity.h"
#include "CameraManager.h"

animationContainer::animationContainer() : speed(0.0f), time(0.0f), maxTime(0.0f), sequence(0) , currentImg(NULL), width(0), height(0), imgPos(nullptr), blank(Vector2Int::zero()), imgOffset(Vector2Int::zero()), imgSize(Vector2Int::zero())
{
}

animationContainer::~animationContainer()
{
}



void animationContainer::update()
{
	if (maxTime == 0.0f || imgPos->size() <= 1) return;

	time += speed * Time->deltaTime();

	if (time > maxTime)
	{
		time -= maxTime;
		sequence++;
		if (sequence >= imgPos->size()) sequence = 0;
	}
}

void animationContainer::render(HDC _hdc)
{
	Vector2Int ScreenPos = cam->calculateScreenPosition(*masterPos) - Vector2Int{ imgSize.x / 2, imgSize.y / 2 };
	/*
	ImageHandler::renderWithoutBack(currentImg, _hdc, ScreenPos.x, ScreenPos.y);
	*/
	Vector2Int pos = Vector2Int{ imgSize.x * (*imgPos)[sequence].x + (*imgPos)[sequence].x * blank.x, imgSize.y * (*imgPos)[sequence].y + (*imgPos)[sequence].y * blank.y };
	ImageHandler::renderWithoutBack(rawImg, _hdc, ScreenPos + imgOffset, imgSize, pos);



}

void animationContainer::init(std::map<std::string, std::vector<Vector2Int>> _posValue, std::string defultState, Vector2* _masterPos, Vector2Int _imgSizeValue, Vector2Int _imgOffsetValue)
{
	imgPosSet = _posValue;
	changeImg(defultState);

	masterPos = _masterPos;
	imgSize = _imgSizeValue;
	imgOffset = _imgOffsetValue;
	speed = 1.0f;
}

void animationContainer::changeImg(std::string state)
{
	imgPos = &(*imgPosSet.find(state)).second;
	maxTime = 1.0f / (float)imgPos->size();
	time = 0.0f;
	sequence = 0;
}

void animationContainer::resetAnimation()
{
	time = 0.0f;
	sequence = 0;
}
