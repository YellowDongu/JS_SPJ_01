#pragma once
#include "UI.h"

class StartButton : public UI
{
public:
	StartButton();
	virtual ~StartButton();
	// UI��(��) ���� ��ӵ�
	void update() override;
	void render(HDC _hdc) override;
	void triggered() override;

private:
	float size;


};