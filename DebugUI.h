#pragma once
#include "UI.h"

class GridMap;
class DebugUI : public UI
{
public:
	DebugUI();
	virtual ~DebugUI();
	// UI��(��) ���� ��ӵ�
	void update() override;
	void render(HDC _hdc) override;
	void triggered() override;

private:
	float size;

};