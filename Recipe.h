#pragma once

class Item;
class PlayerInventory;
struct RecipeInfo
{
	Item* resItem = nullptr;
	int* resItemCount = nullptr;
	bool craftable = false;

	std::vector<std::pair<int, int>> needed;

	~RecipeInfo()
	{
		release();
	}

	void release()
	{
		if (resItem)
		{
			delete resItem;
			resItem = nullptr;
		}
	}
};


class Recipe
{
	DECLARE_SINGLETON(Recipe)
public:
	void init();
	void release();
	Item* craft(RecipeInfo* recipeInfo);
	void setActiveRecipe(int itemCondCode, bool _value);

	std::vector<RecipeInfo*>* linkRecipes() { return &recipes; }
	PlayerInventory* linkInven() { return inven; }

	void linkInven(PlayerInventory* _inven) { inven = _inven; }

private:
	std::vector<RecipeInfo*> recipes;
	std::map<int, std::pair<std::vector<RecipeInfo*>, bool>> recipeCategory;
	PlayerInventory* inven;
};
#define Craft GET_SINGLETON(Recipe)