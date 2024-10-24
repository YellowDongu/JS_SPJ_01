#include "framework.h"
#include "Recipe.h"
#include "PlayerInventory.h"
#include "EntityManager.h"

#include "DirtWall.h"
#include "CraftingTable.h"
#include "Wood.h"
#include "Copper.h"
#include "Chest.h"
#include "Dirt.h"
#include "copperPickAxe.h"
#include "CopperBow.h"
#include "CopperHelmet.h"
#include "CopperPlate.h"
#include "CopperLeggings.h"
#include "CopperBar.h"
#include "Furnace.h"
#include "Stone.h"
#include "Anvil.h"




void Recipe::init()
{

	inven = entityMgr->linkPlayer()->linkInven();

	{
		DirtWall* newItem = new DirtWall();
		newItem->init({ -1,-1 });
		*newItem->linkItemCount() = 4;
		RecipeInfo* newRecipe = new RecipeInfo{ newItem, newItem->linkItemCount(), true, {{1, 1}} };
		recipes.push_back(newRecipe);
		recipeCategory[0].first.push_back(newRecipe);
		recipeCategory[0].second = true;
	}
	{
		CraftingTable* newItem = new CraftingTable();
		newItem->init({ -1,-1 });
		*newItem->linkItemCount() = 1;
		RecipeInfo* newRecipe = new RecipeInfo{ newItem, newItem->linkItemCount(), true, {{3, 10}} };
		recipes.push_back(newRecipe);
		recipeCategory[0].first.push_back(newRecipe);
		recipeCategory[0].second = true;
	}
	{
		Chest* newItem = new Chest();
		newItem->init({ -1,-1 });
		*newItem->linkItemCount() = 1;
		RecipeInfo* newRecipe = new RecipeInfo{ newItem, newItem->linkItemCount(), false, {{3, 10}} };
		recipes.push_back(newRecipe);
		recipeCategory[4].first.push_back(newRecipe);
		recipeCategory[4].second = false;
	}
	{
		CopperBar* newItem = new CopperBar();
		newItem->init();
		*newItem->linkItemCount() = 1;
		RecipeInfo* newRecipe = new RecipeInfo{ newItem, newItem->linkItemCount(), false, {{5, 4}} };
		recipes.push_back(newRecipe);
		recipeCategory[7].first.push_back(newRecipe);
		recipeCategory[7].second = false;
	}
	{
		Furnace* newItem = new Furnace();
		newItem->init({-1, -1});
		*newItem->linkItemCount() = 1;
		RecipeInfo* newRecipe = new RecipeInfo{ newItem, newItem->linkItemCount(), false, {{5, 4}} };
		recipes.push_back(newRecipe);
		recipeCategory[4].first.push_back(newRecipe);
		recipeCategory[4].second = false;
	}
	{
		CopperHelmet* newItem = new CopperHelmet();
		newItem->init();
		*newItem->linkItemCount() = 1;
		RecipeInfo* newRecipe = new RecipeInfo{ newItem, newItem->linkItemCount(), false, {{8, 5}} };
		recipes.push_back(newRecipe);
		recipeCategory[7].first.push_back(newRecipe);
		recipeCategory[7].second = false;
	}
	{
		CopperPlate* newItem = new CopperPlate();
		newItem->init();
		*newItem->linkItemCount() = 1;
		RecipeInfo* newRecipe = new RecipeInfo{ newItem, newItem->linkItemCount(), false, {{8, 5}} };
		recipes.push_back(newRecipe);
		recipeCategory[7].first.push_back(newRecipe);
		recipeCategory[7].second = false;
	}
	{
		CopperLeggings* newItem = new CopperLeggings();
		newItem->init();
		*newItem->linkItemCount() = 1;
		RecipeInfo* newRecipe = new RecipeInfo{ newItem, newItem->linkItemCount(), false, {{8, 5}} };
		recipes.push_back(newRecipe);
		recipeCategory[7].first.push_back(newRecipe);
		recipeCategory[7].second = false;
	}
	{
		copperPickAxe* newItem = new copperPickAxe();
		newItem->init();
		*newItem->linkItemCount() = 1;
		RecipeInfo* newRecipe = new RecipeInfo{ newItem, newItem->linkItemCount(), false, {{8, 5}} };
		recipes.push_back(newRecipe);
		recipeCategory[7].first.push_back(newRecipe);
		recipeCategory[7].second = false;
	}
	{
		CopperBow* newItem = new CopperBow();
		newItem->init();
		*newItem->linkItemCount() = 1;
		RecipeInfo* newRecipe = new RecipeInfo{ newItem, newItem->linkItemCount(), false, {{8, 5}} };
		recipes.push_back(newRecipe);
		recipeCategory[7].first.push_back(newRecipe);
		recipeCategory[7].second = false;
	}


}

void Recipe::update()
{
	for (auto iter = activeFurnitures.begin(); iter != activeFurnitures.end();)
	{
		(*iter)->update();
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
		(*iter)->update();
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
