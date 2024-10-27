#include "framework.h"
#include "BigEye.h"
#include "EntityManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "RenderManager.h"
#include "Tool.h"
#include "CollisionManager.h"

BigEye::BigEye() : condition(0), phase(0), rushCount(0), spawnCount(0), stopWatch(0.0f), angle(0.0f)
{
}

BigEye::~BigEye()
{
	release();
}

void BigEye::init()
{
	music->playBGM("Music-Boss_1.mp3");

	player = entityMgr->linkPlayer();
	dead = false;
	onGround = false;
	rightSideWall = false;
	LeftSideWall = false;
	dmg = 40;
	hp = 100;
	maxHp = 100;
	speed = 500.0f;
	maxSpeed = 100.0f;

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
	{
		music->playNew("NPC_Killed_1.wav");
		music->playNew("NPC_Killed_5.wav");
		Gore* deadBody = new Gore();
		deadBody->initGore("BigEye1", worldPos);
		deadBody = new Gore();
		deadBody->initGore("BigEye2", worldPos + Vector2{ 20, 20 });
		deadBody = new Gore();
		deadBody->initGore("BigEye3", worldPos + Vector2{-20, -20});
		dead = true;
		for (auto& servent : servents)
		{
			music->playNew("NPC_Killed_1.wav");
			Gore* deadBody = new Gore();
			deadBody->initGore("smallEyeFront", servent->position());
			deadBody = new Gore();
			deadBody->initGore("smallEyeBack", servent->position());
			delete servent;
		}
		servents.clear();
	}
	if (phase != 2 && hp <= maxHp / 2)
	{
		aniCtrl->changeAnimation("status", "phase2");
		phase = 2;
	}

	if (!servents.empty())
	{
		for (auto iter = servents.begin(); iter != servents.end();)
		{
			if ((*iter)->isDead())
			{
				delete* iter;
				iter = servents.erase(iter);
				continue;
			}

			(*iter)->update();

			Item* item = player->currentUsingItem();
			if (item && item->leftTop() != Vector2::zero())
			{
				Tool* tool = static_cast<Tool*>(item);

				auto iterOther = tool->hittedList()->begin();
				if (tool->hittedList()->empty())
					iterOther = tool->hittedList()->end();
				for (; iterOther != tool->hittedList()->end(); )
				{
					if (*iter == *iterOther)
						break;
					iterOther++;
				}

				if (iterOther == tool->hittedList()->end())
					CollisionHandler::collision((*iter), (Tool*)(item));
			}

			CollisionHandler::collision(player, *iter);
			iter++;
		}
	}




	if (condition == 0)
	{
		Vector2 destination = player->position();
		destination.y += 300.0f;

		if ((destination - worldPos).magnitude() >= 10.0f)
			moveVec = (destination - worldPos) * 2.0f;

		angle = Vector2::angle(player->position() - worldPos) - 90.0f;
		angle *= -1;

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
					angle = Vector2::angle(player->position() - worldPos) - 90.0f;
					angle *= -1;
				}
				else
				{
					rushCount = 6;
					moveVec = (player->position() - worldPos) * 3.0f;
					angle = Vector2::angle(player->position() - worldPos) - 90.0f;
					angle *= -1;
				}
			}
			else
			{
				SmallEye* servent = new SmallEye();
				servent->init();
				servent->position(worldPos);
				servents.push_back(servent);
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
				{
					moveVec = (player->position() - worldPos) * 1.5f;
					angle = Vector2::angle(player->position() - worldPos) - 90.0f;
					angle *= -1;
				}
				else
				{
					moveVec = (player->position() - worldPos) * 0.7f;
					angle = Vector2::angle(player->position() - worldPos) - 90.0f;
					angle *= -1;
				}
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
	if (!servents.empty())
	{
		for (auto& servent : servents)
		{
			delete servent;
		}
		servents.clear();
	}
}

void BigEye::CollisionWithEntity(Entity* _col)
{
}

void BigEye::CollisionWithItem(Item* _col)
{
	hp -= ((Tool*)_col)->damage();
	music->playNew("NPC_Hit_1.wav");
}

void BigEye::render(HDC _hdc)
{
	if (!servents.empty())
	{
		for (auto& servent : servents)
		{
			servent->render(_hdc);
		}
	}
	aniCtrl->linkDirectToAni("status")->render(_hdc, angle);
}
