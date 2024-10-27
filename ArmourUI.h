#pragma once
#include "UI.h"
#include "ArmourSlotUI.h"

class Player;
class ArmourUI : public UI
{
public:
	ArmourUI();
	~ArmourUI();

	// UI��(��) ���� ��ӵ�
	void init();
	void update() override;
	void triggered() override;
	void render(HDC _hdc) override;
	void release();
private:
	ArmourSlotUI* helmet;
	ArmourSlotUI* plate;
	ArmourSlotUI* leggings;

	HBITMAP APSlot;

	Player* player;

};
