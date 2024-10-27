#include "framework.h"
#include "Node.h"
#include "Entity.h"

Entity::Entity() : worldPos(Vector2::zero()), sizeInfo(Vector2::zero()), moveVec(Vector2::zero()), aniCtrl(nullptr), 
onGround(true), dead(false), rightSideWall(false), LeftSideWall(false), light(0), hp(0), maxHp(0), dmg(0), speed(1.0f), maxSpeed(1.0f)
{
}

Entity::~Entity()
{
}