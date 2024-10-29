#include "framework.h"
#include "Trophy.h"
#include "UIManager.h"
#include "EndUI.h"

Trophy::Trophy() : stack(0)
{
}

Trophy::~Trophy()
{
}

Item* Trophy::clone() const
{
	return new Trophy(*this);
}

void Trophy::dragDrop()
{
}

void Trophy::use()
{
	if (stack < 1)
	{
		stack++;
		return;
	}


	EndUI* end = new EndUI();
	end->setActive(true);
	UIMgr->appendUI(end);
}

void Trophy::init()
{
	getImgSet("trophy");
	itemImgSize.x = 32;
	itemImgSize.y = 36;
	code = 24;
	itemName = L"Trophy";
	itemUsingState = UsingState::Use;
}
