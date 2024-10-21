#include "framework.h"
#include "ItemManager.h"
#include "TimeManager.h"
#include "Item.h"
#include "Player.h"
#include "RenderManager.h"
#include "CameraManager.h"
#include "ImageHandler.h"
#include "CollisionManager.h"

void ItemManager::init(Player* _player)
{
	player = _player;
}

void ItemManager::update()
{
	if (itemList.empty()) return;

	while (true)
	{
		if (itemList.front().first >= 5000.0f)
		{
			delete itemList.front().second;
			itemList.pop_front();
			continue;
		}
		else
		{
			break;
		}
	}

	for (auto iter = itemList.begin(); iter != itemList.end(); )
	{
		auto& itemPair = *iter;
		itemPair.first += Time->deltaTime();

		if (itemPair.second->itemCount() != itemPair.second->itemMaxCount())
		{
			for (auto iterOther = itemList.begin(); iterOther != itemList.end(); )
			{
				auto& otherItemPair = *iterOther;
				if (itemPair == otherItemPair || 
					itemPair.second->itemCode() != otherItemPair.second->itemCode() || 
					itemPair.second->itemCount() + otherItemPair.second->itemCount() > otherItemPair.second->itemMaxCount())
				{
					iterOther++;
					continue;
				}

				if (Vector2::distance(itemPair.second->position(), otherItemPair.second->position()) < 30.0f)
				{

					itemPair.second->addItemCount(otherItemPair.second->itemCount());
					delete otherItemPair.second;
					iterOther = itemList.erase(iterOther);
					continue;
				}
				else iterOther++;
			}

		}

		if (CollisionHandler::collision(itemPair.second))
		{
			iter = itemList.erase(iter);
			continue;
		}

		Vector2 pos = player->position() - itemPair.second->position();
		if (pos.magnitude() <= 50.0f)
		{
			itemPair.second->translate(pos.normalize() * 50.0f * Time->deltaTime());
		}
		iter++;
	}
}


void ItemManager::appendList(Item* _item)
{
	itemList.push_back({ 0.0f, _item });
}

void ItemManager::render(HDC _hdc)
{
	for (auto& itemPair : itemList)
	{
		Vector2 screenPos = cam->calculateScreenPosition(itemPair.second->position());
		if (screenPos.x >= cam->getWindowSize().x + 50.0f || screenPos.x <= -50.0f ||
			screenPos.y >= cam->getWindowSize().y + 50.0f || screenPos.y <= -50.0f) { continue; }

		HBITMAP itemImg = *itemPair.second->linkItemImg();
		BITMAP bitmap;
		GetObject(itemImg, sizeof(BITMAP), &bitmap);
		screenPos -= Vector2{ (float)bitmap.bmWidth / 2, (float)bitmap.bmHeight / 2 };

		ImageHandler::renderWithoutBack(itemImg, _hdc, (int)screenPos.x, (int)screenPos.y);
	}
}

void ItemManager::release()
{
	for (auto& itemPair : itemList)
	{
		if (!itemPair.second) continue;
		delete itemPair.second;
	}
	itemList.clear();
}
