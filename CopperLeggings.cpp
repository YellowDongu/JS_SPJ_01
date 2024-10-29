#include "framework.h"
#include "CopperLeggings.h"
#include "EntityManager.h"
#include "RenderManager.h"

CopperLeggings::CopperLeggings()
{
}

CopperLeggings::~CopperLeggings()
{
}

Item* CopperLeggings::clone() const
{
	CopperLeggings* newItem = new CopperLeggings(*this);
	newItem->init();
	return newItem;
}

void CopperLeggings::dragDrop()
{
}

void CopperLeggings::use()
{
	if (!entityMgr->linkPlayer()->leggingsSlot())
	{
		CopperLeggings* newItem = new CopperLeggings();
		newItem->init();
		entityMgr->linkPlayer()->leggingsSlot(newItem);
		count--;
		return;
	}
}

void CopperLeggings::init()
{
	animationContainer* ani = new animationContainer();
	Vector2* masterPos = entityMgr->linkPlayer()->linkPosition();
	itemImg = rendering->findImage("Item_armour", "copperLeggings", "shadow0rotation0")[0];
	ani->setRawImg(rendering->findImage("Entity_armour", "copperLeggings", 0, 0)[0]);
	ani->setBlank({ 2,2 });
	ani->init({
		{"standR",{ false, {{0,1}} }},//10
		{"jumpR", { false, {{0,5}} }},
		{"walkR", { false, {{0,12}, {0,13}, {0,14}, {0,15}, {0,16}, {0,17}, {0,18}, {0,19}, {0,6}, {0,7}, {0,8}, {0,9} ,{0,10}, {0,11}} }}
		},
		"standR", masterPos, { 40, 54 }, { 0,0 });

	aniContainer.push_back(ani);
	count = 1;
	itemImgSize.x = 22;
	itemImgSize.y = 18;
	onGround = false;
	code = 22;
	itemUsingState = UsingState::Swing;
	itemName = L"CopperLeggings";
	armour = 15;
}

void CopperLeggings::render(HDC _hdc)
{
}
