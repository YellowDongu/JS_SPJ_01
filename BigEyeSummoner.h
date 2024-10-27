#pragma once
#include "Ingredient.h"

class BigEyeSummoner : public Ingredient
{
public:
	BigEyeSummoner();
	virtual ~BigEyeSummoner();


	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;


private:


};
