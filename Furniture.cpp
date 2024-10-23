#include "framework.h"
#include "Furniture.h"
#include "TimeManager.h"
#include "RenderManager.h"

Furniture::Furniture() : placedPos({-1,-1}), imgGridSize(Vector2Int::zero()), bottomPos(0), imgGridPos(Vector2Int::zero())
{
    category = 0;
}

Furniture::~Furniture()
{
}

void Furniture::getImgSet(std::string name)
{
    placedImgSet = &(*rendering->findImageSet("Tiles_furniture")->find(name)).second;
    rawPlacedImg = (*placedImgSet->find("shadow0rotation0")).second[0];
    count = 1;
    maxCount = 1;
    onGround = false;
}
