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

	const int& defense() const { return armour; }

	std::vector<animationContainer*>* linkAniList() { return &aniContainer; }

protected:
	int armour;
	std::vector<animationContainer*> aniContainer;

};
