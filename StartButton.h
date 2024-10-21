#pragma once
#include "UI.h"

class StartButton : public UI
{
public:
	StartButton();
	virtual ~StartButton();
	// UI을(를) 통해 상속됨
	void update() override;
	void render(HDC _hdc) override;
	void triggered() override;

private:
	float size;


};