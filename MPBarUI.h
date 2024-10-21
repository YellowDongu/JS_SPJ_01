#pragma once
#include "UI.h"

class Player;
class MPBarUI : public UI
{
public:
	MPBarUI();
	~MPBarUI();

	void init(Player* _player);

	void update() override;
	void triggered() override;
	void render(HDC _hdc) override;

private:
	int* playerMP;
	int* playerMaxMP;

	HBITMAP left;
	HBITMAP middle;
	HBITMAP right;
	HBITMAP gauge;
};
