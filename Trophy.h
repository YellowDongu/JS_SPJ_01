#pragma once
#include "Ingredient.h"

class Trophy : public Ingredient
{
public:
	Trophy();
	virtual ~Trophy();

	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;
private:
	int stack;
};
