#include "framework.h"
#include "Zombie.h"
#include "Player.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "SoundManager.h"

Zombie::Zombie() : player(nullptr)
{
}

Zombie::~Zombie()
{
	if (aniCtrl)
	{
		aniCtrl->release();
		delete aniCtrl;
		aniCtrl = nullptr;
	}



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
	dead = false;
	imgInit();
}

void Zombie::update()
{
	if (hp <= 0)
	{
		dead = true;
		music->playNew("NPC_Killed_1.wav");
		music->playNew("NPC_Killed_2.wav");
	}



	if (Time->deltaTime() > 0.3f) return;
	if (!onGround)
	{
		if (Time->deltaTime() >= 0.5f) return;
		moveVec.y -= 1000.0f * Time->deltaTime();
	}
	worldPos += moveVec * Time->deltaTime();
	tracePlayer();

	aniCtrl->update();
	if (moveVec.y != 0)
	{
		if (aniCtrl->checkCurrentState("status") != "jumpR")
			aniCtrl->changeAnimation("status", "jumpR");
	}
	else if (moveVec.y == 0 && moveVec.x != 0)
	{
		if (aniCtrl->checkCurrentState("status") != "walkR")
			aniCtrl->changeAnimation("status", "walkR");
	}
	else
	{
		if (aniCtrl->checkCurrentState("status") != "standR")
			aniCtrl->changeAnimation("status", "standR");
	}


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
	if (onGround && (rightSideWall || LeftSideWall) && abs(player->position().x - worldPos.x) > 50.0f)
	{
		moveVec.y += 500.0f;
		onGround = false;
	}
	if (onGround && player->position().y > worldPos.y + 50.0f && abs(player->position().x - worldPos.x) > 50.0f)
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
		aniCtrl->reverseImg(true);
	}
	else
	{
		if (moveVec.x <= -maxSpeed)
		{
			moveVec.x = -maxSpeed;
			return;
		}
		moveVec.x += (-speed) * Time->deltaTime();
		aniCtrl->reverseImg(false);
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
		{"standR", { false, {{0,0}} }},//10
		{"jumpR",  { false, {{0,2}} }},
		{"walkR",  { false, {{0,0}, {0,1}} }}
		},
		"standR", &worldPos, { 38, 46 }, { 0,0 });
	aniCtrl->addAnimation("Standard", newAni);
	aniCtrl->changeAnimationContianer("status", "Standard");

}

void Zombie::CollisionWithItem(Item* _col)
{

	if (moveVec.x > 0)
	{
		moveVec.x = -500.0f;
		moveVec.y = 500.0f;
	}
	else
	{
		moveVec.x = 500.0f;
		moveVec.y = 500.0f;
	}
	music->playNew("NPC_Hit_1.wav");
	hp -= 20;
}
