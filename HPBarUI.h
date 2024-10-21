#pragma once
#include "UI.h"

class Player;
class HPBarUI : public UI
{
public:
	HPBarUI();
	~HPBarUI();

	void init(Player* _player);

	void update() override;
	void triggered() override;
	void render(HDC _hdc) override;

private:
	int* playerHP;
	int* playerMaxHP;

	HBITMAP left;
	HBITMAP middle;
	HBITMAP right;
	HBITMAP gauge;
};

