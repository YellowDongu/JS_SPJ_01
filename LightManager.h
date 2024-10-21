#pragma once

class GridMap;
class Node;
class LightManager
{
	DECLARE_SINGLETON(LightManager)
public:
	void init();
	void update();

	void setLight(Node& node, int candela);
	void manuallyUpdateWorldLight();

	float getTime() const { return currentTime; }
private:
	float currentTime = 0.0f;
	float dayTime = 0.0f;
	float nightTime = 0.0f;
	float timeSpeed = 1.0f;
	float currentWorldLight = 0.0f;
	float prevWorldLight = 0.0f;
	float maxLight = 10.0f;

};

#define sun GET_SINGLETON(LightManager)