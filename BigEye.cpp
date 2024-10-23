#include "framework.h"
#include "BigEye.h"
#include "EntityManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "RenderManager.h"

BigEye::BigEye() : condition(0), phase(0), rushCount(0), spawnCount(0), stopWatch(0.0f)
{
}

BigEye::~BigEye()
{
	release();
}

void BigEye::init()
{
	phase = 1;
	player = entityMgr->linkPlayer();

	speed = 500.0f;
	maxSpeed = 100.0f;
	hp = 300;
	maxHp = 300;
	dead = false;
	onGround = false;
	rightSideWall = false;
	LeftSideWall = false;

	stopWatch = 3.0f;
	condition = 0;
	phase = 1;
	rushCount = 6;
	spawnCount = 6;
	stopWatch = 3.0f;

	sizeInfo = Vector2{ 110.0f,166.0f };
	aniCtrl = new AnimationController;

	animationContainer* newAni = new animationContainer();

	newAni->setRawImg(rendering->findImage("Entity_npcBoss", "bigEye", "shadow0rotation0")[0]);
	newAni->setBlank({ 0,0 });
	newAni->init(
		{
		{"phase1", { false, {{0,0}, {0,1}, {0,2}} }},//10
		{"phase2", { false, {{0,3}, {0,4}, {0,5}} }}
		},
		"phase1", &worldPos, { 110,166 }, { 0,0 });
	aniCtrl->addAnimation("Standard", newAni);
	aniCtrl->changeAnimationContianer("status", "Standard");

}

void BigEye::update()
{
	if (hp <= 0)
		dead = true;
	if (phase != 2 && hp <= maxHp / 2)
		phase = 2;

	if (condition == 0)
	{
		Vector2 destination = player->position();
		destination.y += 300.0f;

		if ((destination - worldPos).magnitude() >= 10.0f)
			moveVec = (destination - worldPos) * 2.0f;

		stopWatch -= Time->deltaTime();

		if (stopWatch <= 0)
		{
			if (phase == 1)
				stopWatch = 3.0f;
			else
				stopWatch = 1.5f;


			spawnCount--;
			if (spawnCount == 0)
			{
				condition++;
				if (phase == 1)
				{
					rushCount = 3;
					moveVec = (player->position() - worldPos) * 1.5f;
				}
				else
				{
					rushCount = 6;
					moveVec = (player->position() - worldPos) * 3.0f;
				}
			}
		}


	}
	else
	{
		if (abs(moveVec.y) > 300.0f)
			int i = 0;


		float xSign = (moveVec.x > 0) ? -1.0f : 1.0f;
		float ySign = (moveVec.y > 0) ? -1.0f : 1.0f;

		moveVec.x += xSign * abs(moveVec.x) * Time->deltaTime();
		moveVec.y += ySign * abs(moveVec.y) * Time->deltaTime();

		stopWatch -= Time->deltaTime();

		if (stopWatch <= 0)
		{
			rushCount--;

			if (phase == 1)
				stopWatch = 3.0f;
			else
				stopWatch = 1.5f;


			if (rushCount <= 0)
			{
				condition--;
				if (phase == 1)
				{
					spawnCount = 3;
					stopWatch = 3.0f;
				}
				else
				{
					spawnCount = 6;
					stopWatch = 1.5f;
				}
			}
			else
			{

				if (phase == 1)
					moveVec = (player->position() - worldPos) * 1.5f;
				else
					moveVec = (player->position() - worldPos) * 0.7f;
			}
		}
	}


	worldPos += moveVec * Time->deltaTime();




}

void BigEye::release()
{
	if (aniCtrl)
	{
		aniCtrl->release();
		delete aniCtrl;
		aniCtrl = nullptr;
	}
}

void BigEye::CollisionWithEntity(Entity* _col)
{
}

void BigEye::CollisionWithItem(Item* _col)
{
}

void BigEye::render(HDC _hdc)
{
	aniCtrl->render(_hdc);
}
