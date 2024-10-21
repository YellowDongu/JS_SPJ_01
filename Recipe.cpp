#include "framework.h"
#include "Recipe.h"
#include "PlayerInventory.h"
#include "EntityManager.h"

#include "DirtWall.h"
#include "CraftingTable.h"

void Recipe::init()
{
	Item* item = nullptr;
	RecipeInfo* newRecipe = nullptr;

	inven = entityMgr->linkPlayer()->linkInven();

	DirtWall* rec1 = new DirtWall();
	rec1->init({-1,-1});
	item = rec1;
	*item->linkItemCount() = 4;
	newRecipe = new RecipeInfo{ item, item->linkItemCount(), true, {{1, 1}} };
	recipes.push_back(newRecipe);
	recipeCategory[0].first.push_back(newRecipe);
	recipeCategory[0].second = true;



	CraftingTable* rec2 = new CraftingTable();
	rec2->init({ -1,-1 });
	item = rec2;
	*item->linkItemCount() = 1;
	newRecipe = new RecipeInfo{ item, item->linkItemCount(), true, {{3, 10}} };
	recipes.push_back(newRecipe);
	recipeCategory[0].first.push_back(newRecipe);
	recipeCategory[0].second = true;
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
	auto& result = (*recipeCategory.find(itemCondCode)).second;
	if (result.first.empty()) return;
	if (result.second == _value) return;

	result.second = _value;
	for (auto& recipe : result.first)
	{
		recipe->craftable = _value;
	}
}
