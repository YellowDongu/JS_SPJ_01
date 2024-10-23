#include "framework.h"
#include "EntityManager.h"
#include "ImageHandler.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "GridMap.h"
#include "Tool.h"
#include "Zombie.h"

void EntityManager::update()
{
	if (player)
	{
		player->update();
		if (player->leggingsSlot())
		{
			for (auto& ani : *player->leggingsSlot()->linkAniList())
			{
				ani->update();
			}
		}
		if (player->plateSlot())
		{
			for (auto& ani : *player->plateSlot()->linkAniList())
			{
				ani->update();
			}
		}
		if (player->helmetSlot())
		{
			for (auto& ani : *player->helmetSlot()->linkAniList())
			{
				ani->update();
			}
		}
	}

	if (!entityList.empty())
	{
		for (auto iter = entityList.begin(); iter != entityList.end(); )
		{
			if ((*iter)->isDead())
			{
				delete* iter;
				iter = entityList.erase(iter);
				continue;
			}


			Item* item = player->currentUsingItem();
			if (item && item->leftTop() != Vector2::zero())
			{
				Tool* tool = static_cast<Tool*>(item);
				
				auto iterOther = tool->hittedList()->begin();
				if(tool->hittedList()->empty())
					iterOther = tool->hittedList()->end();
				for (; iterOther != tool->hittedList()->end(); )
				{
					if (*iter == *iterOther)
						break;
					iterOther++;
				}

				if(iterOther == tool->hittedList()->end())
					CollisionHandler::collision((*iter), (Tool*)(item));
			}
			(*iter)->update();

			iter++;
		}
	}

	if (!bossList.empty())
	{
		for (auto iter = bossList.begin(); iter != bossList.end();)
		{
			Item* item = player->currentUsingItem();
			if (item && item->leftTop() != Vector2::zero())
			{
				Tool* tool = static_cast<Tool*>(item);

				auto iterOther = tool->hittedList()->begin();
				if (tool->hittedList()->empty())
					iterOther = tool->hittedList()->end();
				for (; iterOther != tool->hittedList()->end(); )
				{
					if (*iter == *iterOther)
						break;
					iterOther++;
				}

				if (iterOther == tool->hittedList()->end())
					CollisionHandler::collision((*iter), (Tool*)(item));
			}
			(*iter)->update();
			if ((*iter)->isDead())
			{
				delete* iter;
				iter = bossList.erase(iter);
			}
			else iter++;
		}
	}
	else
	{
		randomSpawnEnemy();
	}



	if (!extraList.empty() && extraList.front()->isDead())
	{
		delete extraList.front();
		extraList.pop_front();
	}
}

void EntityManager::render(HDC _hdc)
{
	if (!entityList.empty())
	{
		for (auto entity : entityList)
			entity->animation()->render(_hdc);
	}
	if (!bossList.empty())
	{
		for (auto entity : bossList)
			entity->render(_hdc);
	}


	if (player)
	{
		player->animation()->render(_hdc);
		if (player->leggingsSlot())
		{
			for (auto& ani : *player->leggingsSlot()->linkAniList())
			{
				ani->render(_hdc);
			}
		}
		if (player->plateSlot())
		{
			(*player->plateSlot()->linkAniList())[0]->render(_hdc);
			(*player->plateSlot()->linkAniList())[1]->render(_hdc);

		}
		if (player->helmetSlot())
		{
			for (auto& ani : *player->helmetSlot()->linkAniList())
			{
				ani->render(_hdc);
			}

		}
		if (player->plateSlot())
		{
			(*player->plateSlot()->linkAniList())[2]->render(_hdc);
			(*player->plateSlot()->linkAniList())[3]->render(_hdc);
		}





		Vector2Int startPos = Vector2::toVec2Int(cam->calculateScreenPosition(player->position()) - player->size() / 2);
		Item*& item = player->currentUsingItem();
		if (item)
		{
			if (!player->animation()->checkTriggered("01.armR"))
			{
				item->leftTop(Vector2::zero());
				item->rightBottom(Vector2::zero());
				if(item->itemCategory() == 1)
					((Tool*)item)->clearHittedList();
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

				if (item->itemCategory() == 1)
				{
					item->leftTop(cam->calculateWorldPosition(size));
					item->rightBottom(Vector2Int::toVec2(item->leftTop() + Vector2Int{ item->itemSize().x, -item->itemSize().y }) * 1.2f);
				}
				else
				{
					item->leftTop(Vector2::zero());
					item->rightBottom(Vector2::zero());
				}

			}
		}
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

void EntityManager::randomSpawnEnemy()
{
	time += Time->deltaTime();

	if (time <= 30.0f) return;

	srand((unsigned int)GetTickCount64());
	int random = rand() % 2;
	if (random == 1)
	{
		Vector2 min = cam->calculateWorldPosition({ -100.0f, cam->getWindowSize().y + 100.0f });
		Vector2 max = cam->calculateWorldPosition({ -16.0f, -100.0f });

		std::list<Node*> spawn = gridMap->findNodes(min, max);

		for (auto& node : spawn)
		{
			if (!node->block()) continue;
			Vector2Int gridPos = node->position();
			bool nope = false;
			for (int x = 0; x < 2; x++)
			{
				if (nope) break;
				for (int y = 0; y < 3; y++)
				{
					if (nope) break;
					Node* finding = gridMap->findNode(gridPos + Vector2Int{x, y});

					if (finding->block()) nope = true;

				}
			}

			if (nope) continue;

			Zombie* enemy = new Zombie();
			enemy->init();
			enemy->position(node->position() * 16 + Vector2Int{64, 8});
			enemy->linkPlayer(player);
			entityList.push_back(enemy);
			time = 0.0f;
			return;

		}
	}
	else
	{
		Vector2 min = cam->calculateWorldPosition({ cam->getWindowSize().x + 16.0f, cam->getWindowSize().y + 100.0f });
		Vector2 max = cam->calculateWorldPosition({ cam->getWindowSize().x + 100.0f, -100.0f });

		std::list<Node*> spawn = gridMap->findNodes(min, max);

		for (auto& node : spawn)
		{
			if (!node->block()) continue;
			Vector2Int gridPos = node->position();
			bool nope = false;
			for (int x = 0; x < 2; x++)
			{
				if (nope) break;
				for (int y = 1; y < 4; y++)
				{
					if (nope) break;
					Node* finding = gridMap->findNode(gridPos + Vector2Int{ x, y });

					if (finding->block()) nope = true;

				}
			}

			if (nope) continue;

			Zombie* enemy = new Zombie();
			enemy->init();
			enemy->position(node->position() * 16 + Vector2Int{ 64, 8 });
			enemy->linkPlayer(player);
			entityList.push_back(enemy);
			time = 0.0f;
			return;

		}
	}
}
