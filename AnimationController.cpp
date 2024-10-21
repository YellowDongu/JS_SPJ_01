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
		current[_current]->resetAnimation();
		current[_current]->changeImg(stateName);
	}


}

void AnimationController::addAnimation(std::string stateName, animationContainer* newAni)
{
	container[stateName] = newAni;
}
