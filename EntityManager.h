#pragma once
#include "Player.h"
#include "BigEye.h"
#include "Gore.h"

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
	void addExtraEntity(Gore* _entity) { extraList.push_back(_entity); }
	void addBossEntity(Boss* _entity) { bossList.push_back(_entity); }
	void randomSpawnEnemy();

	void summonBoss_BigEye();




	Player* linkPlayer() { return player; }
	std::list<Entity*>* linkList() { return &entityList; }
	std::list<Boss*>* linkBossList() { return &bossList; }

private:
	float angle = 0.0f;
	float time = 0.0f;
	Player* player = nullptr;
	std::list<Entity*> entityList;
	std::list<Gore*> extraList;
	std::list<Boss*> bossList;
};
#define entityMgr GET_SINGLETON(EntityManager)