#include "framework.h"
#include "Recipe.h"
#include "PlayerInventory.h"
#include "EntityManager.h"

#include "DirtWall.h"
#include "CraftingTable.h"
#include "Furniture.h"
#include "Chest.h"

void Recipe::init()
{
	Item* item = nullptr;
	RecipeInfo* newRecipe = nullptr;

	inven = entityMgr->linkPlayer()->linkInven();

	{
		DirtWall* newItem = new DirtWall();
		newItem->init({ -1,-1 });
		item = newItem;
		*item->linkItemCount() = 4;
		newRecipe = new RecipeInfo{ item, item->linkItemCount(), true, {{1, 1}} };
		recipes.push_back(newRecipe);
		recipeCategory[0].first.push_back(newRecipe);
		recipeCategory[0].second = true;

	}

	{
		CraftingTable* newItem = new CraftingTable();
		newItem->init({ -1,-1 });
		item = newItem;
		*item->linkItemCount() = 1;
		newRecipe = new RecipeInfo{ item, item->linkItemCount(), true, {{3, 10}} };
		recipes.push_back(newRecipe);
		recipeCategory[0].first.push_back(newRecipe);
		recipeCategory[0].second = true;
	}
	{
		Chest* newItem = new Chest();
		newItem->init({ -1,-1 });
		item = newItem;
		*item->linkItemCount() = 1;
		newRecipe = new RecipeInfo{ item, item->linkItemCount(), false, {{3, 10}} };
		recipes.push_back(newRecipe);
		recipeCategory[4].first.push_back(newRecipe);
		recipeCategory[4].second = false;
	}


}

void Recipe::update()
{
	for (auto iter = activeFurnitures.begin(); iter != activeFurnitures.end();)
	{
		float dist = Vector2::distance((*iter)->gridPosition() * 16 - Vector2Int{8, 8}, entityMgr->linkPlayer()->position());

		if (dist > 200.0f)
		{
			setActiveRecipe((*iter)->itemCode(), false);
			placedFurnitureList.push_back(*iter);
			iter = activeFurnitures.erase(iter);
		}
		else
		{
			setActiveRecipe((*iter)->itemCode(), true);
			iter++;
		}

	}

	for (auto iter = placedFurnitureList.begin(); iter != placedFurnitureList.end();)
	{
		float dist = Vector2::distance((*iter)->gridPosition() * 16 - Vector2Int{ 8, 8 }, entityMgr->linkPlayer()->position());

		if (dist < 200.0f)
		{
			setActiveRecipe((*iter)->itemCode(), true);
			activeFurnitures.push_back(*iter);
			iter = placedFurnitureList.erase(iter);
		}
		else iter++;
	}
}

void Recipe::release()
{
	for (auto& recipe : recipes)
	{
		if (!recipe) continue;
		delete recipe->resItem;
		recipe->resItem = nullptr;
		delete recipe;
		recipe = nullptr;
	}
	recipes.clear();
}

Item* Recipe::craft(RecipeInfo* recipeInfo)
{
	std::map<std::pair<int, int>, std::vector<Item*>> result;
	for (auto& ingredient : recipeInfo->needed)
	{
		int total = ingredient.second;
		int sum = 0;
		
		for (auto& slot : inven->hotbar)
		{
			if (!slot->item() || slot->item()->itemCode() != ingredient.first) continue;
			result[{ingredient.first, ingredient.second}].push_back(slot->item());
			sum += slot->item()->itemCount();
		}
		for (auto& slot : inven->invenSlot)
		{
			if (!slot->item() || slot->item()->itemCode() != ingredient.first) continue;
			result[{ingredient.first, ingredient.second}].push_back(slot->item());
			sum += slot->item()->itemCount();
		}
		if (total > sum) return nullptr;
	}

	for (auto& i : result)
	{
		int total = i.first.second;

		for (auto& ingredient : i.second)
		{
			if (ingredient->itemCount() < total)
			{
				total -= ingredient->itemCount();
				ingredient->addItemCount(-ingredient->itemCount());
			}
			else ingredient->addItemCount(-total);
		}

	}
	return recipeInfo->resItem->clone();
}

void Recipe::setActiveRecipe(int itemCondCode, bool _value)
{
	auto finding = recipeCategory.find(itemCondCode);
	if (finding == recipeCategory.end()) return;
	auto& result = (*finding).second;
	if (result.second == _value) return;
	if (result.first.empty()) return;
	changed = true;

	result.second = _value;
	for (auto& recipe : result.first)
	{
		recipe->craftable = _value;
	}
}

void Recipe::appendFurniture(Furniture* newItem)
{
	placedFurnitureList.push_back(newItem);
}

void Recipe::eraseFurniture(Furniture* target)
{
	for (auto iter = activeFurnitures.begin(); iter != activeFurnitures.end(); )
	{
		if (*iter == target)
		{
			setActiveRecipe((*iter)->itemCode(), false);
			activeFurnitures.erase(iter);
			return;
		}
		else iter++;
	}
	for (auto iter = placedFurnitureList.begin(); iter != placedFurnitureList.end(); )
	{
		if (*iter == target)
		{
			placedFurnitureList.erase(iter);
			return;
		}
		else iter++;
	}
}
