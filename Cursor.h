#pragma once
#include "UI.h"


class Cursor : public UI
{
public:
	Cursor();
	virtual ~Cursor();

	void update() override;
	void triggered() override;
	void render(HDC _hdc) override;

	void init();
	void hovering(UI* ui) { hoveringUI = ui; }
	void notHovering() { hoveringUI = nullptr; }
private:
	float time;

	UI* hoveringUI;

	HBITMAP cursorImg;
	HBITMAP toolTipUI;
};