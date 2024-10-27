#pragma once

class Item;
class PlayerInventory;
class Furniture;
struct RecipeInfo
{
	Item* resItem = nullptr;
	int* resItemCount = nullptr;
	bool craftable = false;

	std::vector<std::pair<int, int>> needed;
	std::vector<HBITMAP> IngredientImg;

	~RecipeInfo()
	{
		release();
	}

	void release();
};


class Recipe
{
	DECLARE_SINGLETON(Recipe)
public:
	void init();
	void update();
	void release();
	Item* craft(RecipeInfo* recipeInfo);
	void setActiveRecipe(int itemCondCode, bool _value);
	void appendFurniture(Furniture*);
	void eraseFurniture(Furniture*);

	std::vector<RecipeInfo*>* linkRecipes() { return &recipes; }
	PlayerInventory* linkInven() { return inven; }

	void linkInven(PlayerInventory* _inven) { inven = _inven; }
	void checkChanged() { changed = false; }
	bool isChanged() const { return changed; }
private:
	bool changed = false;
	PlayerInventory* inven = nullptr;

	std::vector<RecipeInfo*> recipes;
	std::map<int, std::pair<std::vector<RecipeInfo*>, bool>> recipeCategory;

	std::list<Furniture*> placedFurnitureList;
	std::list<Furniture*> activeFurnitures;
};
#define Craft GET_SINGLETON(Recipe)