#pragma once
#include "animationContainer.h"

class AnimationController
{
public:
	AnimationController();
	~AnimationController();

	void update();
	void render(HDC _hdc);
	void release();
	void changeAnimationContianer(std::string current, std::string stateName);
	void changeAnimation(std::string current, std::string stateName);
	void addAnimation(std::string stateName, animationContainer* newAni);


private:
	std::map<std::string, animationContainer*> current;
	std::map<std::string, animationContainer*> container;
	


};
