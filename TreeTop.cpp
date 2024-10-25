#include "framework.h"
#include "TreeTop.h"
#include "RenderManager.h"



TreeTop::TreeTop()
{
}

TreeTop::~TreeTop()
{
}

Item* TreeTop::clone() const
{
	return nullptr;
}

void TreeTop::dragDrop()
{
}

void TreeTop::use()
{
}

void TreeTop::init(Vector2Int _position)
{
	getImgSet("treeTop");

	posInfo = { {0,0} };
	itemImgSize.x = 0;
	itemImgSize.y = 0;
	imgPosInfo = { {0,0} };
	placedImgSize = { 80, 80 };
	placedPos = _position;
	code = -1;
	itemName = L"NULL";
	itemUsingState = UsingState::End;
	maxCount = 1;
	bottomPos = 0;
	imgGridSize = { 0,0 };
	imgGridPos = { 0,0 };
}

void TreeTop::useInField()
{
}

Item* TreeTop::destroyed(Vector2Int _gridPos)
{
	return nullptr;
}
