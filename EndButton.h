#pragma once
#include "UI.h"

class EndButton : public UI
{
public:
	EndButton();
	~EndButton();

	void update() override;
	void triggered() override;
	void render(HDC _hdc) override;
private:
	float size;

};