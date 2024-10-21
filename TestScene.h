#pragma once
#include "Scene.h"

class Player;

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	void init() override;
	void render(HDC _hdc) override;
	int update() override;
	void release() override;

private:
	Player* player;


};