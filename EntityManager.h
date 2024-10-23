#pragma once
#include "Player.h"
#include "Boss.h"

class EntityManager
{
	DECLARE_SINGLETON(EntityManager)
public:

	void update();
	void render(HDC _hdc);
	void release();

	void createPlayer(Vector2 _pos);
	void createPlayer(Vector2Int _pos);
	void addEntity(Entity* _entity) { entityList.push_back(_entity); }
	void addExtraEntity(Entity* _entity) { extraList.push_back(_entity); }

	Player* linkPlayer() { return player; }
	std::list<Entity*>* linkList() { return &entityList; }

private:
	float angle = 0.0f;
	Player* player = nullptr;
	std::list<Entity*> entityList;
	std::list<Entity*> extraList;
};
#define entityMgr GET_SINGLETON(EntityManager)