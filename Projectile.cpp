#include "framework.h"
#include "Projectile.h"

Projectile::Projectile() : moveVec(Vector2::zero()), angle(0.0f), dead(false)
{
}

Projectile::~Projectile()
{
}
