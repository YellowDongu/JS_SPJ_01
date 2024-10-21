#pragma once
#include "UI.h"

class popUpUI : public UI
{
public:
	popUpUI();
	~popUpUI();


	void init(Vector2Int pos, std::wstring _text);
	void update() override;
	void triggered() override;
	void render(HDC _hdc) override;

	float time() const { return liveTime; }

private:
	std::wstring text;
	float liveTime;
	float size;
};
