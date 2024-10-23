#include "framework.h"
#include "CopperBow.h"
#include "SoundManager.h"
#include "RenderManager.h"

CopperBow::CopperBow()
{
}

CopperBow::~CopperBow()
{
}

Item* CopperBow::clone() const
{
	return new CopperBow(*this);
}

void CopperBow::dragDrop()
{
}

void CopperBow::use()
{
	music->playNew("Item_5.wav");
}

void CopperBow::init()
{
	maxCount = 1;
	count = 1;
	itemImg = rendering->findImage("Item_tool", "copperBow", "shadow0rotation0")[0];
	itemImgSize.x = 16;
	itemImgSize.y = 32;
	onGround = false;
	code = 11;
	//itemImgCenter = { 0, 16 };
	itemUsingState = UsingState::Directinal;
}
