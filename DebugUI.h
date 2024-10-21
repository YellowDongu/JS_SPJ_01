#pragma once
#include "UI.h"

class GridMap;
class DebugUI : public UI
{
public:
	DebugUI();
	virtual ~DebugUI();
	// UI을(를) 통해 상속됨
	void update() override;
	void render(HDC _hdc) override;
	void triggered() override;

private:
	float size;

};