#include "framework.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&prevCount));
}

void TimeManager::update()
{
	UINT64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	deltaT = (currentCount - prevCount) / static_cast<float>(frequency);
	prevCount = currentCount;
	frameCount++;
	frameTime += deltaT;
	if (frameTime >= 1.0f)
	{
		fps = static_cast<UINT32>(frameCount / frameTime);

		frameTime = 0.0f;
		frameCount = 0;
	}
}