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
	Scene* currentScene;
	std::vector<Scene*> scenes;
	std::vector<Scene*>::iterator sceneSequence = scenes.begin();
};
#define sceneMgr  SceneManager::getInstance()