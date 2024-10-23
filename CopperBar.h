#pragma once
#include "Ingredient.h"

class CopperBar : public Ingredient
{
public:
	CopperBar();
	virtual ~CopperBar();


	void init() override;
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
private:

};

