#pragma once
#include "Ingredient.h"

class GoldBar : public Ingredient
{
public:
	GoldBar();
	virtual ~GoldBar();

	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;
private:


};
