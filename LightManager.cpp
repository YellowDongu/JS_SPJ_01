#include "framework.h"
#include "LightManager.h"
#include "GridMap.h"
#include "Node.h"
#include "TimeManager.h"




void LightManager::init()
{
	dayTime = 108.0f;
	nightTime = 360.0f;
	currentTime = 350.0f;
	maxLight = 10.0f;
	currentWorldLight = maxLight;
	prevWorldLight = maxLight;

}

void LightManager::update()
{
	currentTime += timeSpeed * Time->deltaTime();
	if (currentTime >= 432.0f)
	{
		currentTime -= 432.0f;
	}

	if (currentTime >= nightTime)
	{
		if (prevWorldLight == 0.0f)
			return;

		currentWorldLight -= timeSpeed * Time->deltaTime();
		if (currentWorldLight >= maxLight)
		{
			currentWorldLight = maxLight;
			prevWorldLight = maxLight;
		}
		if (prevWorldLight - 1.0f >= currentWorldLight)
		{
			prevWorldLight = (float)(int)(currentWorldLight);
			gridMap->updateWorldLight((int)prevWorldLight);
		}
		return;
	}

	if (currentTime >= dayTime)
	{
		if (prevWorldLight == maxLight)
			return;

		currentWorldLight += timeSpeed * Time->deltaTime() * 3;
		if (currentWorldLight >= maxLight)
		{
			currentWorldLight = maxLight;
			prevWorldLight = maxLight;
		}
		if (prevWorldLight + 1.0f <= currentWorldLight)
		{
			prevWorldLight = (float)(int)(currentWorldLight);
			gridMap->updateWorldLight((int)prevWorldLight);
		}
	}

}

void LightManager::setLight(Node& node, int candela)
{
	node.updateLight(candela);
}

void LightManager::manuallyUpdateWorldLight()
{
	gridMap->updateWorldLight((int)prevWorldLight);
}
