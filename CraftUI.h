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

	void resetSlot();
private:
	bool moveUp;
	bool moveDown;
	int index;

	int minIndex;
	int maxIndex;
	int selectedIndex;
	int maxVisiableSlot;

	float moveDist;
	float upLimit;
	float downLimit;
	float scrollSpeed;

	std::vector<CraftSlotUI*> currentSlots;
	std::vector<CraftSlotUI*> slots;



	PlayerInventory* playerInven;

	HBITMAP slotImg;
	HBITMAP selectedSlotImg;
	HBITMAP smallSlotImg;
	Vector2 basePos;

};