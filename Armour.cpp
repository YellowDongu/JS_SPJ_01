#include "framework.h"
#include "Armour.h"

Armour::Armour() : armour(0)
{
}

Armour::~Armour()
{
	for (auto ani : aniContainer)
	{
		if (!ani) continue;
		delete ani;
	}
	aniContainer.clear();
}