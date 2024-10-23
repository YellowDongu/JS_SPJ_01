#include "framework.h"
#include "CopperPlate.h"
#include "EntityManager.h"
#include "RenderManager.h"

CopperPlate::CopperPlate()
{
}

CopperPlate::~CopperPlate()
{
}

Item* CopperPlate::clone() const
{
	CopperPlate* newItem = new CopperPlate();
	newItem->init();
	return newItem;
}

void CopperPlate::dragDrop()
{
}

void CopperPlate::use()
{
	if (!entityMgr->linkPlayer()->plateSlot())
	{
		CopperPlate* newItem = new CopperPlate();
		newItem->init();
		entityMgr->linkPlayer()->plateSlot(newItem);
		count--;
		return;
	}
}

void CopperPlate::init()
{
	animationContainer* ani = new animationContainer();
	Vector2* masterPos = entityMgr->linkPlayer()->linkPosition();
	itemImg = rendering->findImage("Item_armour", "copperPlate", "shadow0rotation0")[0];
	ani->setRawImg(rendering->findImage("Entity_armour", "copperPlate", 0, 0)[0]);
	ani->setBlank({ 2,2 });
	ani->init({
		{"standR",{ false, {{0,1}} } }, //10
		{"jumpR", { false, {{0,5}} } },
		{"walkR", { false, {{0,6}, {0,7}, {0,8}, {0,9} ,{0,10}, {0,11},
		{0,12}, {0,13}, {0,14}, {0,15}, {0,16}, {0,17}, {0,18}, {0,19}}} }
		},
		"standR", masterPos, { 40, 54 }, { 0,0 });

	aniContainer.push_back(ani);

	ani = new animationContainer();
	ani->setRawImg(rendering->findImage("Entity_armour", "copperPlateHand", 0, 0)[0]);
	ani->setBlank({ 0,2 });
	ani->init(
		{
		{"standR",{ false, {{2,2}} }},
		{"jumpR", { false, {{2,3}} }},
		{"walkR", { false, {{3,3}, {5,3}, {6,3}, {6,3}, {5,3}, {3,3}, {4,3}} }},
		{"swingR",{ true,  {{3,2}, {4,2}, {5,2}, {6,2}} }},
		{"useTopR",{ true, {{4,2}, {4,2}} }},
		{"useMiddleR",{ true,{{5,2},{5,2}} }},
		{"useBottomR",{ true,{{6,2},{6,2}} }}
		},
		"standR", masterPos, { 40, 54 }, { 0,0 });
	aniContainer.push_back(ani);

	ani = new animationContainer();
	ani->setRawImg(rendering->findImage("Entity_armour", "copperPlateHand", 0, 0)[0]);
	ani->setBlank({ 0,2 });
	ani->init(
		{
		{"standR",{ false, {{2,0}} }},
		{"jumpR", { false, {{3,0}} }},
		{"walkR", { false, {{3,1}, {5,1}, {6,1}, {6,1}, {5,1}, {3,1}, {4,1}} }},
		{"swingR",{ true,  {{3,0}, {4,0}, {5,0}, {6,0}} }},
		{"useTopR",{ true, {{4,0}, {4,0}} }},
		{"useMiddleR",{ true,{{5,0}, {5,0}} }},
		{"useBottomR",{ true,{{6,0}, {6,0}} }}
		},
		"standR", masterPos, { 40, 54 }, { 0,0 });
	aniContainer.push_back(ani);



	ani = new animationContainer();
	ani->setRawImg(rendering->findImage("Entity_armour", "copperPlateHand", 0, 0)[0]);
	ani->setBlank({ 0,2 });
	ani->init(
		{
		{"standR",{ false, {{0,1}} }},
		{"jumpR", { false, {{1,1}} }},
		{"walkR", { false, {{0,1}} }},
		{"swingR",{ true,  {{1,1}, {0,1}} }},
		{"useTopR",{ true, {{1,1}, {1,1}} }},
		{"useMiddleR",{ true,{{0,1}, {0,1}} }},
		{"useBottomR",{ true,{{0,1}, {0,1}} }}
		},
		"standR", masterPos, { 40, 54 }, { 0,0 });
	aniContainer.push_back(ani);


	count = 1;
	itemImgSize.x = 30;
	itemImgSize.y = 20;
	onGround = false;
	code = 21;
	itemUsingState = UsingState::Swing;
}

void CopperPlate::render(HDC _hdc)
{
}
