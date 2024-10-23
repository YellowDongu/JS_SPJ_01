#include "framework.h"
#include "EntityManager.h"
#include "ImageHandler.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "Tool.h"

void EntityManager::update()
{
	if (player)
	{
		player->update();
	}
	if (entityList.empty()) return;
	for (auto& entity : entityList)
	{
		Item* item = player->currentUsingItem();
		if (item && item->leftTop() != Vector2::zero())
		{
			CollisionHandler::collision(entity, (Tool*)(item));
		}
		entity->update();
	}

	if (player)
	{
		Item* item = player->currentUsingItem();
		if (!item) return;
	}

	if (!extraList.empty() && extraList.front()->isDead())
	{
		delete extraList.front();
		extraList.pop_front();
	}
}

void EntityManager::render(HDC _hdc)
{
	if (player)
	{
		player->animation()->render(_hdc);
		Vector2Int startPos = Vector2::toVec2Int(cam->calculateScreenPosition(player->position()) - player->size() / 2);
		Item*& item = player->currentUsingItem();
		if (item)
		{
			if (!player->animation()->checkTriggered("01.armR"))
			{
				item->leftTop(Vector2::zero());
				item->rightBottom(Vector2::zero());
				item = nullptr;
				angle = 135.0f;
			}
			else
			{
				Vector2 handPos = Vector2::zero();
				Vector2 size = Vector2::zero();
				bool reversed = player->animation()->reversed("01.armR");

				int sequence = player->animation()->checkSequence("01.armR");

				if (player->animation()->checkCurrentState("01.armR") == "useTopR")
				{
					sequence = 0;
				}

				if (player->animation()->checkCurrentState("01.armR") == "useMiddleR")
				{
					sequence = 1;
				}
				if (player->animation()->checkCurrentState("01.armR") == "useBottomR")
				{
					sequence = 2;
				}


				switch (sequence)
				{
				case 0:
					if (reversed) handPos = { 12 ,7 };
					else handPos = { -12 ,7 };
					angle = -60.0f;
					break;
				case 1:
					if (reversed) handPos = { -5,7 };
					else handPos = { -5,7 };
					angle = 0.0f;
					break;
				case 2:
					if (reversed) handPos = { -6,-9 };
					else handPos = { 6,-9 };
					angle = 60.0f;
					break;
				case 3:
					if (reversed) handPos = { -5,-14 };
					else handPos = { 5,-14 };
					angle = 90.0f;
					break;
				default:
					break;
				}

				item->leftTop(player->position() + handPos);

				ImageHandler::renderRotateWithoutBack(*item->linkItemImg(), _hdc, cam->calculateScreenPosition(item->leftTop()), 
					item->itemImageCenter(), angle, reversed, size);

				item->leftTop(cam->calculateWorldPosition(size));
				item->rightBottom(item->leftTop() + Vector2Int{ item->itemSize().x, -item->itemSize().y} * 1.2);
			}
		}
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
