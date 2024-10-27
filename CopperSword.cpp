#include "framework.h"
#include "CopperSword.h"
#include "RenderManager.h"

CopperSword::CopperSword()
{
}

CopperSword::~CopperSword()
{
}

Item* CopperSword::clone() const
{
	return new CopperSword(*this);
}

void CopperSword::dragDrop()
{
}

void CopperSword::use()
{
}

void CopperSword::init()
{
	maxCount = 1;
	count = 1;
	itemImg = rendering->findImage("Item_tool", "copperSword", "shadow0rotation0")[0];
	itemImgSize.x = 36;
	itemImgSize.y = 36;
	onGround = false;
	code = 12;
	itemImgCenter = { 3, 34 };
	itemUsingState = UsingState::Swing;
	category = 1;
	dmg = 40;
	itemName = L"CopperSword";
}