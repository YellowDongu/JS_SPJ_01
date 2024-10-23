#include "framework.h"
#include "Gore.h"
#include "TimeManager.h"

Gore::Gore() : lifeTime(0.0f)
{
}

Gore::~Gore()
{
}

void Gore::init()
{
	lifeTime = 60.0f;

	srand(Time->deltaTime());
	int randInt = rand() % 3;
	moveVec.x = randInt * 100.0f;
	if (randInt % 2 == 0) moveVec.x *= -1;
}

void Gore::update()
{
	lifeTime -= Time->deltaTime();
	if (lifeTime <= 0.0f) dead = true;

	if (!onGround) moveVec.y -= Time->deltaTime();
	if (moveVec.x == 0.0f) return;
	if (abs(moveVec.x) < 5.0f)
	{
		moveVec.x == 0.0f;
	}

	moveVec.x -= Time->deltaTime() * speed;
	angle -= Time->deltaTime() * speed;
}

void Gore::release()
{
}

void Gore::CollisionWithEntity(Entity* _col)
{
}

void Gore::CollisionWithItem(Item* _col)
{
}
