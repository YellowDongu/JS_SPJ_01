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
	itemImgSize.x = 16;
	itemImgSize.y = 16;
	code = 8;
	itemName = L"CopperBar";
}
