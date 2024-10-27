#include "framework.h"
#include "SmallEye.h"
#include "Tool.h"
#include "EntityManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "TimeManager.h"

SmallEye::SmallEye() : angle(0.0f)
{
}

SmallEye::~SmallEye()
{
	release();
}

void SmallEye::init()
{
	sizeInfo = Vector2{ 20.0f, 30.0f };
	speed = 500.0f;
	maxSpeed = 100.0f;
	dmg = 10;
	hp = 50;
	maxHp = 50;
	onGround = false;
	rightSideWall = false;
	LeftSideWall = false;
	dead = false;


	aniCtrl = new AnimationController;

	animationContainer* newAni = new animationContainer();

	newAni->setRawImg(rendering->findImage("Entity_npcEnemy", "smallEye", "R_shadow0rotation0")[0]);
	newAni->setBlank({ 2,2 });
	newAni->init(
		{
		{"base",  { false, {{0,0}, {0,1}} }}
		},
		"base", &worldPos, { 20, 30 }, { 0,0 });
	aniCtrl->addAnimation("Standard", newAni);
	aniCtrl->changeAnimationContianer("status", "Standard");

}

void SmallEye::update()
{
	if (hp <= 0)
	{
		dead = true;
		Gore* deadBody = new Gore();
		deadBody->initGore("smallEyeFront", worldPos);
		deadBody = new Gore();
		deadBody->initGore("smallEyeBack", worldPos);
	}



	Vector2 vec = entityMgr->linkPlayer()->position() - worldPos;
	moveVec = vec.normalize() * 50.0f;
	angle = Vector2::angle(vec) - 90.0f;
	angle *= -1;

	worldPos += moveVec * Time->deltaTime();
}

void SmallEye::release()
{
	if (aniCtrl)
	{
		aniCtrl->release();
		delete aniCtrl;
		aniCtrl = nullptr;
	}
}

void SmallEye::CollisionWithEntity(Entity* _col)
{
}

void SmallEye::CollisionWithItem(Item* _col)
{
	hp -= ((Tool*)_col)->damage();
	music->playNew("NPC_Hit_1.wav");
	
	if (hp <= 0)
	{
		dead = true;
		music->playNew("NPC_Killed_1.wav");
	}
}

void SmallEye::render(HDC _hdc)
{
	aniCtrl->linkDirectToAni("status")->render(_hdc, angle);
}
