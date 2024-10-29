#include "framework.h"
#include "GoldBar.h"


GoldBar::GoldBar()
{
}

GoldBar::~GoldBar()
{
}

Item* GoldBar::clone() const
{
	return new GoldBar(*this);
}

void GoldBar::dragDrop()
{
}

void GoldBar::use()
{
}

void GoldBar::init()
{
	getImgSet("goldBar");
	itemImgSize.x = 30;
	itemImgSize.y = 24;
	placedImgSize.x = 30;
	placedImgSize.y = 24;
	code = 23;
	itemName = L"GoldBar";
}
