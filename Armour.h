#pragma once
#include "Item.h"
#include "animationContainer.h"

class Armour : public Item
{
public:
	Armour();
	virtual ~Armour();

	virtual void init() abstract;
	virtual void render(HDC _hdc) abstract;

protected:
	int armour;
	animationContainer* aniContainer;

};
