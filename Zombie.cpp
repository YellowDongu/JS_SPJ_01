#include "framework.h"
#include "Zombie.h"
#include "Player.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "Tool.h"

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
	if (!aniCtrl->reversed("status"))
		int itemp = 0;
	if (hp <= 0)
	{
		dead = true;
		music->playNew("NPC_Killed_1.wav");
		music->playNew("NPC_Killed_2.wav");
	}


	tracePlayer();

	if (Time->deltaTime() > 0.3f) return;
	if (!onGround)
	{
		if (Time->deltaTime() >= 0.5f) return;
		moveVec.y -= 1000.0f * Time->deltaTime();
	}
	worldPos += moveVec * Time->deltaTime();

	aniCtrl->update();
	if (currentState != "jumpR" && moveVec.y != 0)
	{
		aniCtrl->changeAnimation("status", "jumpR");
		currentState = "jumpR";
	}
	else if (currentState != "walkR" && moveVec.y == 0 && moveVec.x != 0)
	{
		aniCtrl->changeAnimation("status", "walkR");
		currentState = "walkR";
	}
	//else if (currentState != "standR" && moveVec.y == 0 && moveVec.x == 0)
	//{
	//	aniCtrl->changeAnimation("status", "standR");
	//	currentState = "standR";
	//}
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
		aniCtrl->reverseImg(true);
		if (moveVec.x >= maxSpeed)
		{
			moveVec.x = maxSpeed;
			return;
		}
		moveVec.x += speed * Time->deltaTime();
	}
	else
	{
		aniCtrl->reverseImg(false);
		if (moveVec.x <= -maxSpeed)
		{
			moveVec.x = -maxSpeed;
			return;
		}
		moveVec.x += (-speed) * Time->deltaTime();
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
	currentState = "standR";
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
	hp -= ((Tool*)_col)->damage();
}
