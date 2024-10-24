#include "framework.h"
#include "animationContainer.h"
#include "TimeManager.h"
#include "ImageHandler.h"
#include "Entity.h"
#include "CameraManager.h"

animationContainer::animationContainer() : speed(0.0f), time(0.0f), maxTime(0.0f), sequence(0), width(0), height(0), imgPos(nullptr), once(false), left(false),
blank(Vector2Int::zero()), imgOffset(Vector2Int::zero()), imgSize(Vector2Int::zero()), masterPos(NULL), rawImg(NULL)
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
		if (sequence >= (int)imgPos->size())
		{

			if (once)
			{
				changeImg(normalState);
			}
			else
			{
				sequence = 0;
			}
		}
	}
}

void animationContainer::render(HDC _hdc)
{
	Vector2Int ScreenPos = cam->calculateScreenPosition(*masterPos) - Vector2Int{ imgSize.x / 2, imgSize.y / 2 };
	Vector2Int pos = Vector2Int{ imgSize.x * (*imgPos)[sequence].x + (*imgPos)[sequence].x * blank.x, imgSize.y * (*imgPos)[sequence].y + (*imgPos)[sequence].y * blank.y };
	//ImageHandler::renderWithoutBack(rawImg, _hdc, ScreenPos + imgOffset, imgSize, pos);
	ImageHandler::renderWithoutBack(rawImg, _hdc, ScreenPos + imgOffset, imgSize, pos, left);



}

void animationContainer::init(std::map<std::string, std::pair<bool, std::vector<Vector2Int>>> _posValue, std::string defultState, Vector2* _masterPos, Vector2Int _imgSizeValue, Vector2Int _imgOffsetValue)
{
	imgPosSet = _posValue;
	normalState = defultState;
	currentState = defultState;
	changeImg(normalState);

	masterPos = _masterPos;
	imgSize = _imgSizeValue;
	imgOffset = _imgOffsetValue;
	speed = 1.0f;
}

void animationContainer::changeImg(std::string state)
{
	auto iter = imgPosSet.find(state);
	imgPos = &(iter->second.second);
	once = iter->second.first;
	reverseBlock = iter->second.first;
	maxTime = 1.0f / static_cast<float>(imgPos->size());
	time = 0.0f;
	sequence = 0;
	speed = 1.0f;
	currentState = state;
}

void animationContainer::resetAnimation()
{
	time = 0.0f;
	sequence = 0;
}
