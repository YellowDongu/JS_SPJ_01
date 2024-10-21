#pragma once


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

private:
	std::list<UI*> uiList;
	std::list<UI*> popUpUIList;
};
#define UIMgr GET_SINGLETON(UIManager)
