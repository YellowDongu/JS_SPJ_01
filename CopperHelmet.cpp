#include "framework.h"
#include "CopperHelmet.h"
#include "RenderManager.h"
#include "EntityManager.h"

CopperHelmet::CopperHelmet()
{
}

CopperHelmet::~CopperHelmet()
{
}

Item* CopperHelmet::clone() const
{
	CopperHelmet* newItem = new CopperHelmet(*this);
	newItem->init();
	return newItem;
}

void CopperHelmet::dragDrop()
{
}

void CopperHelmet::use()
{
	if (!entityMgr->linkPlayer()->helmetSlot())
	{
		CopperHelmet* newItem = new CopperHelmet();
		newItem->init();
		entityMgr->linkPlayer()->helmetSlot(newItem);
		count--;
		return;
	}
}

void CopperHelmet::init()
{
	animationContainer* ani = new animationContainer();
	Vector2* masterPos = entityMgr->linkPlayer()->linkPosition();
	itemImg = rendering->findImage("Item_armour", "copperHelmet", "shadow0rotation0")[0];
	ani->setRawImg(rendering->findImage("Entity_armour", "copperHelmet", 0, 0)[0]);
	ani->setBlank({ 2,2 });
	ani->init({
		{"standR",{ false, {{0,1}} } }, //10
		{"jumpR", { false, {{0,5}} } },
		{"walkR", { false, {{0,6}, {0,7}, {0,8}, {0,9} ,{0,10}, {0,11},
		{0,12}, {0,13}, {0,14}, {0,15}, {0,16}, {0,17}, {0,18}, {0,19}}} }
		},
		"standR", masterPos, {40, 54}, {0,0});

	aniContainer.push_back(ani);
	count = 1;
	itemImgSize.x = 24;
	itemImgSize.y = 16;
	onGround = false;
	code = 20;
	itemUsingState = UsingState::Swing;
	itemName = L"CopperHelmet";
	armour = 10;
}

void CopperHelmet::render(HDC _hdc)
{
}
