#include "framework.h"
#include "Zombie.h"
#include "Player.h"
#include "TimeManager.h"
#include "RenderManager.h"

Zombie::Zombie() : player(nullptr)
{
}

Zombie::~Zombie()
{
}

void Zombie::init()
{
	sizeInfo = Vector2{ 32.0f, 42.0f };
	speed = 500.0f;
	maxSpeed = 100.0f;
	onGround = true;
	rightSideWall = false;
	LeftSideWall = false;
	hp = 100;
	maxHp = 100;
	imgInit();
}

void Zombie::update()
{
	if (Time->deltaTime() > 0.3f) return;
	worldPos += moveVec * Time->deltaTime();
	if (!onGround)
	{
		if (Time->deltaTime() >= 0.5f) return;
		moveVec.y -= 1000.0f * Time->deltaTime();
	}
	tracePlayer();

}

void Zombie::release()
{
	if (aniCtrl)
	{
		aniCtrl->release();
		delete aniCtrl;
		aniCtrl = nullptr;
	}
}

void Zombie::CollisionWithEntity(Entity* _col)
{
	if (_col == player) return;





}

void Zombie::linkPlayer(Player* _player)
{
	player = _player;
}

void Zombie::tracePlayer()
{
	if (onGround && (rightSideWall || LeftSideWall))
	{
		moveVec.y += 500.0f;
		onGround = false;
	}
	if (player->position().y > worldPos.y + 50.0f)
	{
		moveVec.y += 500.0f;
		onGround = false;
	}

	float x = player->position().x - worldPos.x;
	if (rightSideWall && x > 0.0f)
	{
		x = 0.0f;
	}
	else if (LeftSideWall && x < 0.0f)
	{
		x = 0.0f;
	}

	if (x > 0)
	{
		if (moveVec.x >= maxSpeed)
		{
			moveVec.x = maxSpeed;
			return;
		}
		moveVec.x += speed * Time->deltaTime();
	}
	else
	{
		if (moveVec.x <= -maxSpeed)
		{
			moveVec.x = -maxSpeed;
			return;
		}
		moveVec.x += (-speed) * Time->deltaTime();
	}

	if (moveVec.y != 0)
	{
		aniCtrl->changeAnimation("status", "jumpR");
	}
	else if (moveVec.x != 0)
	{
		aniCtrl->changeAnimation("status", "walkR");
	}
	else
	{
		aniCtrl->changeAnimation("status", "standR");
	}




}

void Zombie::imgInit()
{
	aniCtrl = new AnimationController;

	animationContainer* newAni = new animationContainer();

	newAni->setRawImg(rendering->findImage("Entity_npcEnemy", "zombie", "R_shadow0rotation0")[0]);
	newAni->setBlank({ 2,2 });
	newAni->init(
		{
		{"standR",{{0,0}}},//10
		{"jumpR", {{0,2}}},
		{"walkR", {{0,0}, {0,1}}}
		},
		"standR", &worldPos, { 38, 46 }, { 0,0 });
	aniCtrl->addAnimation("Standard", newAni);
	aniCtrl->changeAnimationContianer("status", "Standard");

}
