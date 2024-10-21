#include "framework.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "TestScene.h"

void SceneManager::init()
{
	scenes.push_back(new MainMenuScene());
	scenes.push_back(new TestScene());
	currentScene = scenes.front();
	currentScene->init();
	sceneSequence = scenes.begin();
}

void SceneManager::render(HDC _hdc)
{
	currentScene->render(_hdc);
}

void SceneManager::update()
{
	int output = currentScene->update();
	if (output)
	{
		currentScene->release();
		while (output != 0)
		{
			if (output > 0)
			{
				sceneSequence++;
				output--;
			}
			else if (output < 0)
			{
				sceneSequence--;
				output++;
			}
			if (sceneSequence == scenes.begin()) output = 0;
			if (sceneSequence == scenes.end()) output = 0;
		}

		currentScene = (*sceneSequence);
		currentScene->init();
	}
	
}

void SceneManager::release()
{
	if (!scenes.empty())
	{
		for (auto& scene : scenes)
		{
			scene->release();
			delete scene;
		}
		scenes.clear();
	}

	currentScene = nullptr;
}

void SceneManager::changeScene(int index)
{
	currentScene = scenes[index];
}
