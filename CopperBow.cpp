#include "framework.h"
#include "CopperBow.h"
#include "SoundManager.h"
#include "RenderManager.h"
#include "Arrow.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "CameraManager.h"

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
	Item* item = entityMgr->linkPlayer()->linkInven()->getItem(16);
	if (!item) return;
	
	item->addItemCount(-1);
	Arrow* shootingArrow = new Arrow();
	Vector2 dir = (cam->calculateWorldPosition(Vector2{ (float)Input->getMousePos().x, (float)Input->getMousePos().y }) - entityMgr->linkPlayer()->position()).normalize() * 500.0f;
	shootingArrow->shoot(entityMgr->linkPlayer()->position(), dir, dmg);


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
	itemImgCenter = { 8, 16 };
	itemUsingState = UsingState::Directinal;
	category = 0;
	dmg = 20;
	itemName = L"CopperBow";
}
