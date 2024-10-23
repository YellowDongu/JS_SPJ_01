#include "framework.h"
#include "Armour.h"

Armour::Armour()
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