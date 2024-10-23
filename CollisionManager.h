#pragma once

class Entity;
class GridMap;
class UI;
class Item;
class Tool;
class CollisionHandler
{
public:
	CollisionHandler();
	~CollisionHandler();

	static void collision(Entity* obj, Entity* sbj);
	static void collision(Entity* obj, Tool* item);
	static void collision(Entity* obj);
	static bool collision(UI* ui);
	static bool collision(Item* item);

private:
	static bool boxCollision(Vector2 objLT, Vector2 objRB, Vector2 sbjLT, Vector2 SbjRB, Vector2& result);
};
