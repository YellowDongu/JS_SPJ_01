#pragma once
#include "UI.h"
#include "InventorySlot.h"
#include "ImageHandler.h"
#include "RenderManager.h"

class InventorySlotUI : public UI
{
public:
	InventorySlotUI();
	~InventorySlotUI();

	void init(InventorySlot* slot, Vector2 _position);
	void update() override;
	void triggered() override;
	void render(HDC _hdc) override;
	void renderSlot(HDC _hdc);
	void displayItem(HDC _hdc, HBITMAP img, int count,Vector2Int start, Vector2Int slotSize);

	void setSelected(bool _value) { selected = _value; }
	void setChestSlot(bool _value) { chest = _value; }
	void linkChestSlot(InventorySlot* _slot) { slot = _slot; }

	InventorySlot* getSlot() { return slot; }

	void linkImageSet(std::map<std::string, std::vector<HBITMAP>>* _imageSet) { imageSet = _imageSet; }

	bool isSelected() const { return selected; }
private:
	bool selected;
	bool chest;

	InventorySlot* slot;
	std::map<std::string, std::vector<HBITMAP>>* imageSet;
};
