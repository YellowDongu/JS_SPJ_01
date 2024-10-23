#pragma once
#include "UI.h"

class ArmourSlotUI : public UI
{
public:
	ArmourSlotUI();
	~ArmourSlotUI();

	// UI��(��) ���� ��ӵ�
	void init();
	void update() override;
	void triggered() override;
	void render(HDC _hdc) override;
	void render(HDC _hdc, HBITMAP item);
private:
	std::map<std::string, std::vector<HBITMAP>>* imageSet;


};
