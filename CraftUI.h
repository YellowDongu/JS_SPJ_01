#pragma once
#include "UI.h"
#include "CraftSlotUI.h"

class PlayerInventory;
class CraftUI : public UI
{
public:
	CraftUI();
	~CraftUI();

	void init();
	void update() override;
	void triggered() override;
	void render(HDC _hdc) override;
	void release();

	void scrollDown();
	void scrollUp();
private:
	bool moveUp;
	bool moveDown;
	int index;
	int selectedIndex;

	int minIndex;
	int maxIndex;
	int maxVisiableSlot;

	float moveDist;

	std::list<CraftSlotUI*> currentSlots;
	std::vector<CraftSlotUI*> slots;


	float upLimit;
	float downLimit;

	PlayerInventory* playerInven;

	HBITMAP slotImg;
	HBITMAP selectedSlotImg;
	HBITMAP smallSlotImg;
	Vector2 basePos;

};