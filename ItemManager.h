#pragma once

// ���ٴڿ� ������ ������ �����뵵
class Item;
class Player;
class ItemManager
{
	DECLARE_SINGLETON(ItemManager)
public:
	void init(Player* player);
	void update();
	void appendList(Item* _item);
	void render(HDC _hdc);
	void release();
private:
	std::list<std::pair<float, Item*>> itemList;
	Player* player = nullptr;
};
#define itemMgr GET_SINGLETON(ItemManager)
