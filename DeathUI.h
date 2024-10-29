#pragma once
#include "UI.h"

class DeathUI : public UI
{
public:
	DeathUI();
	virtual ~DeathUI();

	void update() override;
	void triggered() override;
	void render(HDC _hdc) override;

	void init();

private:
	std::wstring text;
	float* spawnCount;
	bool* dead;
};