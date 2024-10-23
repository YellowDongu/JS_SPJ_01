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
	return nullptr;
}

void CopperHelmet::dragDrop()
{
}

void CopperHelmet::use()
{
}

void CopperHelmet::init()
{
	aniContainer = new animationContainer();
	Vector2* masterPos = entityMgr->linkPlayer()->linkPosition();
	aniContainer->setRawImg(rendering->findImage("Entity_Player", "headR", 0, 0)[0]);
	aniContainer->setBlank({ 2,2 });
	aniContainer->init({
		{"standR",{ false, {{0,1}}} }, //10
		{"jumpR", { false, {{0,5}}} },
		{"walkR", { false, {{0,6}, {0,7}, {0,8}, {0,9} ,{0,10}, {0,11},
		{0,12}, {0,13}, {0,14}, {0,15}, {0,16}, {0,17}, {0,18}, {0,19}}}} },
		"standR", masterPos, {40, 54}, {0,0});




}

void CopperHelmet::render(HDC _hdc)
{
}
