#include "framework.h"
#include "Gore.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "ImageHandler.h"
#include "EntityManager.h"

Gore::Gore() : lifeTime(0.0f), img(NULL)
{
}

Gore::~Gore()
{
}

void Gore::init()
{
	lifeTime = 10.0f;
	onGround = false;
	rightSideWall = false;
	LeftSideWall = false;
	dead = false;
}

void Gore::update()
{
	lifeTime -= Time->deltaTime();
	if (lifeTime <= 0.0f) dead = true;

	if (!onGround)
		moveVec.y -= Time->deltaTime() * 450.0f;

	worldPos += moveVec * Time->deltaTime();
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

void Gore::render(HDC _hdc)
{
	Vector2Int ScreenPos = cam->calculateScreenPosition(worldPos) - Vector2Int{ (int)(sizeInfo.x / 2.0f), (int)(sizeInfo.y / 2.0f) };
	ImageHandler::renderWithoutBack(img, _hdc, (int)ScreenPos.x, (int)ScreenPos.y);
}

void Gore::initGore(std::string imgName, Vector2 startPos)
{
	img = rendering->findImage("Entity_Gore", imgName, "shadow0rotation0")[0];
	worldPos = startPos;
	BITMAP bitmap;
	GetObject(img, sizeof(BITMAP), &bitmap);
	sizeInfo = Vector2{ (float)bitmap.bmWidth, (float)bitmap.bmHeight * 0.50f };

	init();

	entityMgr->addExtraEntity(this);
}
