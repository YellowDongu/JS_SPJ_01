#include "framework.h"
#include "Entity.h"
#include "GridMap.h"
#include "UI.h"
#include "Node.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Item.h"
#include "Block.h"
#include "EntityManager.h"


CollisionHandler::CollisionHandler()
{
}

CollisionHandler::~CollisionHandler()
{
}

void CollisionHandler::collision(Entity* obj, Entity* sbj)
{
	//RECT playerRect = { startPos.x + correction.x, startPos.y + correction.y, endPos.x + correction.x, endPos.y + correction.y };


}

void CollisionHandler::collision(Entity* obj)
{
	Vector2 min = obj->position() - obj->size() / 2;
	Vector2 max = obj->position() + obj->size() / 2;

	Vector2Int minGrid = gridMap->getGridPos(min);
	Vector2Int maxGrid = gridMap->getGridPos(max);


	std::list<Node*> nodes;

	nodes = gridMap->findNodes(minGrid, maxGrid);
	obj->setRWall(false);
	obj->setLWall(false);

	obj->setOnGround(false);
	for (auto& node : nodes)
	{
		if (!node->block()) continue;

		min = obj->position() - obj->size() / 2;
		max = obj->position() + obj->size() / 2;
		Vector2 coll = Vector2::zero();

		if (boxCollision(min, max, Vector2Int::toVec2(node->position() * 16), Vector2Int::toVec2(node->position() * 16) + Vector2(16.0f, 16.0f), coll))
		{
			Vector2 relativePos = obj->position() - Vector2Int::toVec2((node->position() * 16) + Vector2Int{ 8, 8 });

			if (node->position().y == minGrid.y)
			{
				if (coll.y <= 1.0f && obj->moveVector().y <= 0.0f)
				{
					obj->setOnGround(true);
					continue;
				}


				if (obj->isOnGround())
				{
					for (int i = 1; i <= 3; i++)
					{
						Node* upsideNode = gridMap->findNode(node->position() + Vector2Int{ 0 , i });

						if (upsideNode->block())
						{
							if (coll.x == 0.0f) continue;
							obj->position(obj->position() + Vector2{ (coll.x / 10.0f) * (relativePos.x / abs(relativePos.x)) , 0.0f });
							break;
						}

						if (i == 3)
							obj->position(obj->position() + Vector2{ 0.0f, 16.0f });
					}
				}
				else
				{
					if (obj->moveVector().y <= 0.0f)
					{
						obj->position(obj->position() + Vector2{ 0.0f, abs(coll.y) - 0.1f });
						obj->translate(Vector2{ 0,-obj->moveVector().y });
						obj->setOnGround(true);
					}
				}
			}
			else if (node->position().y == maxGrid.y)
			{
				obj->position(obj->position() + Vector2{ 0.0f, -abs(coll.y / 10.0f) });
				obj->translate(Vector2{ 0,-obj->moveVector().y });
			}
			else
			{
				if (node->position().y == minGrid.y + 1 && obj->isOnGround())
				{
					for (int i = 1; i <= 3; i++)
					{
						Node* upsideNode = gridMap->findNode(node->position() + Vector2Int{ 0 , i });

						if (upsideNode->block())
						{
							if (coll.x == 0.0f) continue;
							float sign = (obj->position().x - node->position().x * 16) / abs(obj->position().x - node->position().x * 16);
							obj->position(obj->position() + Vector2{ coll.x * (relativePos.x / abs(relativePos.x)) , 0.0f });
							obj->translate(Vector2{ -obj->moveVector().x ,0 });
							break;
						}

						if (i == 3)
							obj->position(obj->position() + Vector2{ 0.0f, 16.0f });
					}
				}
				else
				{
					float sign = (obj->position().x - node->position().x * 16) / abs(obj->position().x - node->position().x * 16);
					obj->position(obj->position() + Vector2{ coll.x * (relativePos.x / abs(relativePos.x)) , 0.0f });
					obj->translate(Vector2{ -obj->moveVector().x ,0 });

					if (relativePos.x > 0) obj->setRWall(true);
					else obj->setLWall(true);
				}
			}
		}
	}

}


bool CollisionHandler::collision(UI* ui)
{
	POINT mousePos = Input->getMousePos();
	if (ui->leftTop().x > mousePos.x || ui->rightBottom().x < mousePos.x) { ui->changeState(UIState::normal); return false; }
	if (ui->leftTop().y > mousePos.y || ui->rightBottom().y < mousePos.y) { ui->changeState(UIState::normal); return false; }

	if (Input->getButtonUp(KeyType::LeftMouse))
	{
		ui->triggered();
	}
	else if (Input->getButton(KeyType::LeftMouse)) 
	{ 
		ui->changeState(UIState::clicked); 
	}
	else
	{
		ui->changeState(UIState::hoverMouse);
	}

	return true;
}
bool CollisionHandler::collision(Item* item)
{
	if (!item) return false;
	Player& player = *entityMgr->linkPlayer();
	Vector2 temp = Vector2::zero();
	if (boxCollision(player.position() - (player.size() / 2), player.position() + (player.size() / 2),
		item->position() - Vector2Int::toVec2(item->size() / 2), item->position() + Vector2Int::toVec2(item->size() / 2), temp))
	{
		player.linkInven()->pickUp(item, item->itemCount());
		return true;
	}

	return false;
}

bool CollisionHandler::boxCollision(Vector2 objMin, Vector2 objMax, Vector2 sbjMin, Vector2 sbjMax, Vector2& result)
{
	float collisionX = 0;
	float collisionY = 0;

	// x축 충돌 검사
	if (objMax.x >= sbjMin.x && sbjMax.x >= objMin.x)
	{
		float overlapStart = (sbjMin.x < objMin.x) ? objMin.x : sbjMin.x;
		float overlapEnd = (sbjMax.x > objMax.x) ? objMax.x : sbjMax.x;

		collisionX = overlapEnd - overlapStart;
	}

	// y축 충돌 검사
	if (objMax.y >= sbjMin.y && sbjMax.y >= objMin.y)
	{
		float overlapStart = (sbjMin.y < objMin.y) ? objMin.y : sbjMin.y;
		float overlapEnd = (sbjMax.y > objMax.y) ? objMax.y : sbjMax.y;

		collisionY = overlapEnd - overlapStart;
	}

	result = Vector2{ collisionX, collisionY };
	return (collisionX != 0.0f) && (collisionY != 0.0f);
}

