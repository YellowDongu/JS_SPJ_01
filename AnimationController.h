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
	void reverseImg(bool _value);
	bool reversed(std::string parts);
	void syncTrigger(std::string parts);
	void changeAnimationContianer(std::string current, std::string stateName);
	void changeAnimation(std::string current, std::string stateName);
	void addAnimation(std::string stateName, animationContainer* newAni);
	const std::string& checkCurrentState(std::string parts);
	const int& checkSequence(std::string parts) { return current[parts]->getSequence(); }
	bool checkNormalState(std::string parts);
	void changeAnimationSlpeed(std::string parts, float speed);
	bool checkTriggered(std::string parts) { return current[parts]->triggered(); }

	void linkState(std::string* state) { currentState = state; }
	void linkSubState(std::string* state) { currentSubState = state; }

private:
	std::map<std::string, animationContainer*> current;
	std::map<std::string, animationContainer*> container;
	
	std::string* currentState;
	std::string* currentSubState;

};
