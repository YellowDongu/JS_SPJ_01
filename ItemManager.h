#pragma once

// ���ٴڿ� ������ ������ �����뵵
class Item;
class Projectile;
class Player;
class ItemManager
{
	DECLARE_SINGLETON(ItemManager)
public:
	void init(Player* player);
	void update();
	void appendList(Item* _item);
	void appendProjectileList(Projectile* _item);
	std::list<Projectile*>* linkProjectileList() { return &projectileList; }
	void render(HDC _hdc);
	void release();

private:
	std::list<std::pair<float, Item*>> itemList;
	std::list<Projectile*> projectileList;
	Player* player = nullptr;
};
#define itemMgr GET_SINGLETON(ItemManager)
