#pragma once
#include "UI.h"
#include "Recipe.h"

class CraftSlotUI : public UI
{
public:
	CraftSlotUI();
	~CraftSlotUI();
	void init(RecipeInfo* recipe, Vector2 _position);
	void update() override;
	void triggered() override;
	void render(HDC _hdc) override;
	void renderSlot(HDC _hdc);
	void displayItem(HDC _hdc, HBITMAP img, int count, Vector2Int start, Vector2Int slotSize);

	void setSelected(bool _value) 
	{ 
		selected = _value;
		if (selected)
		{
			rb.x = lt.x + 55.0f;
			rb.y = lt.y + 55.0f;
		}
		else
		{
			rb.x = lt.x + 50.0f;
			rb.y = lt.y + 50.0f;
		}
	}
	void setactive(bool _value) { active = _value; }
	void linkRecipe(RecipeInfo* _target) { recipe = _target; }
	void position(Vector2 _value) { lt = _value; }
	void translate(Vector2 _value) { lt += _value; }

	RecipeInfo* getRecipe() const { return recipe; }
	RecipeInfo* linkRecipe() const{ return recipe; }
	bool isSelected() const { return selected; }
	bool isactive() const { return active; }
	const Vector2& position() const { return lt; }


private:
	bool active;
	bool selected;

	RecipeInfo* recipe;
	std::map<std::string, std::vector<HBITMAP>>* imageSet;
};

