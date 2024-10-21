#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();


	void init() override;
	void render(HDC _hdc) override;
	int update() override;
	void release() override;
private:

};