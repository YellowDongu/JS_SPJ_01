#include "framework.h"
#include "Item.h"

Item::Item() : pos(Vector2::zero()), hitAreaStart(Vector2::zero()), hitAreaEnd(Vector2::zero()), 
placedImgSize(Vector2Int::zero()), placedImgPos(Vector2Int::zero()), itemImgSize(Vector2Int::zero()),
placedImgSet(nullptr), onGround(false), count(0), maxCount(0), code(0), speed(0.0f),
itemImg(NULL), rawPlacedImg(NULL)
{
}

Item::~Item()
{
}