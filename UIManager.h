#pragma once
#include "InventoryUI.h"

class UI;
class UIManager
{
	DECLARE_SINGLETON(UIManager)
public:
	void clear();
	void release();
	void update();
	bool checkColl();
	void render(HDC _hdc);
	UI* appendUI(UI* ui) { uiList.push_back(ui); return ui; }
	void createPopUpText(Vector2 pos, std::wstring content);
	void appendInven(InventoryUI* _inven) { inven = _inven; }
	InventoryUI* getInven() { return inven; }
	void linkCursor(UI* ui) { cursor = ui; }
	UI* linkCursor() { return cursor; }

private:
	std::list<UI*> uiList;
	std::list<UI*> popUpUIList;
	InventoryUI* inven = nullptr;
	UI* cursor = nullptr;
};
#define UIMgr GET_SINGLETON(UIManager)
