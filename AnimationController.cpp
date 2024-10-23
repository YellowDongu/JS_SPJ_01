#include "framework.h"
#include "AnimationController.h"

AnimationController::AnimationController()
{
}

AnimationController::~AnimationController()
{
}

void AnimationController::update()
{
	for (auto& ani : current)
	{
		if (ani.second == nullptr)
			continue;
		ani.second->update();
	}
}

void AnimationController::render(HDC _hdc)
{
	for (auto& ani : current)
	{
		if (ani.second == nullptr)
			continue;
		ani.second->render(_hdc);
	}
}

void AnimationController::release()
{
	if (!container.empty())
	{
		for (auto box : container)
		{
			if (!box.second)
				continue;
			delete box.second;
		}
		container.clear();
	}
}

void AnimationController::reverseImg(bool _value)
{
	for (auto& ani : current)
	{
		ani.second->setLeft(_value);
	}
}

bool AnimationController::reversed(std::string parts)
{
	return current[parts]->isLeft();
}

void AnimationController::syncTrigger(std::string parts)
{
	animationContainer* standard = current[parts];
	for (auto& ani : current)
	{
		if (ani.second == standard) continue;
		ani.second->syncTriggered(standard->triggered());
	}
}

void AnimationController::changeAnimationContianer(std::string _current, std::string stateName)
{
	if (current[_current])
	{
		current[_current]->resetAnimation();
	}
	current[_current] = container[stateName];


}

void AnimationController::changeAnimation(std::string _current, std::string stateName)
{
	if (current[_current] && current[_current] != container[stateName])
	{
		if (current[_current]->triggered()) return;
		current[_current]->resetAnimation();
		current[_current]->changeImg(stateName);
	}


}

void AnimationController::addAnimation(std::string stateName, animationContainer* newAni)
{
	container[stateName] = newAni;
}

const std::string& AnimationController::checkCurrentState(std::string parts)
{
	return current[parts]->getCurrentState();
}

bool AnimationController::checkNormalState(std::string parts)
{
	return current[parts]->isNormalState();
}

void AnimationController::changeAnimationSlpeed(std::string parts, float speed)
{
	current[parts]->setSpeed(speed);
}
