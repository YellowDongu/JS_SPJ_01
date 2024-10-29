#pragma once
#include "Scene.h"

class SceneManager
{
	DECLARE_SINGLETON(SceneManager)
public:

	void init();
	void render(HDC _hdc);
	void update();
	void release();
	void changeScene(int index);




private:
	Scene* currentScene = nullptr;
	std::vector<Scene*>::iterator sceneSequence = scenes.begin();

	std::vector<Scene*> scenes;
};
#define sceneMgr  SceneManager::getInstance()