#pragma once
#include "UI.h"

class EndUI : public UI
{
public:
	EndUI();
	virtual ~EndUI();

	void update() override;
	void triggered() override;
	void render(HDC _hdc) override;
private:

	HBRUSH hBrush;
	HPEN hPen;

};