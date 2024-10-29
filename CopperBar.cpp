#include "framework.h"
#include "CopperBar.h"

CopperBar::CopperBar()
{
}

CopperBar::~CopperBar()
{
}

Item* CopperBar::clone() const
{
	return new CopperBar(*this);
}

void CopperBar::dragDrop()
{
}

void CopperBar::use()
{
}

void CopperBar::init()
{
	getImgSet("copperBar");
	itemImgSize.x = 30;
	itemImgSize.y = 24;
	code = 8;
	itemName = L"CopperBar";
}
