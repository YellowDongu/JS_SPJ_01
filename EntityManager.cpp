#include "framework.h"
#include "EntityManager.h"
#include "ImageHandler.h"
#include "RenderManager.h"

void EntityManager::update()
{
	if (player)
	{
		player->update();
	}
	if (entityList.empty()) return;
	for(auto& entity : entityList)
		entity->update();

}

void EntityManager::render(HDC _hdc)
{
	if (player)
	{
		player->animation()->render(_hdc);
		Vector2Int startPos = Vector2::toVec2Int(cam->calculateScreenPosition(player->position()) - player->size() / 2);
		//Rectangle(_hdc, startPos.x, startPos.y, startPos.x + (int)player->size().x, startPos.y + (int)player->size().y);
	}
	if (!entityList.empty())
	{
		for (auto entity : entityList)
			entity->animation()->render(_hdc);
	}
}

void EntityManager::release()
{
	if (player)
	{
		player->release();
		delete player;
		player = nullptr;
	}
	if (entityList.empty()) return;
	for (auto& entity : entityList)
	{
		entity->release();
		delete entity;
	}
	entityList.clear();
}

void EntityManager::createPlayer(Vector2 _pos)
{
	if (player) return;
	player = new Player;
	player->init();
	player->position(_pos);
}

void EntityManager::createPlayer(Vector2Int _pos)
{
	createPlayer(Vector2Int::toVec2(_pos) * 16 + Vector2{ 16.0f , 16.0f });
}
