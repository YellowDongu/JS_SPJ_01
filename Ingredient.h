#pragma once
#include "Item.h"

class Ingredient : public Item
{
public:
	Ingredient();
	virtual ~Ingredient();

	virtual void init() abstract;
	void getImgSet(std::string name);
private:

};
