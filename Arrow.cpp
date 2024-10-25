#include "framework.h"
#include "Arrow.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "ImageHandler.h"
#include "ItemManager.h"
#include "SoundManager.h"

Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}

Item* Arrow::clone() const
{
	return new Arrow(*this);
}

void Arrow::dragDrop()
{
	
}

void Arrow::use()
{
}

void Arrow::init()
{
	dmg = 10;
	dead = false;
	maxCount = 9999;
	count = 1;
	itemImg = rendering->findImage("Item_tool", "arrow", "shadow0rotation0")[0];
	itemImgSize.x = 14;
	itemImgSize.y = 32;
	placedImgSize.x = 16;
	placedImgSize.y = 16;
	onGround = false;
	code = 16;
	itemImgCenter = { 0, 0 };
	itemUsingState = UsingState::End;
	category = 2;
}

void Arrow::shoot(Vector2 _startPos, Vector2 _shootVec, float _damage)
{
	init();
	dmg += _damage;
	moveVec = _shootVec;
	pos = _startPos;
	itemMgr->appendProjectileList(this);
}

void Arrow::update()
{
	if (onGround)
	{
		music->playNew("Dig_0.wav");
		dead = true;
		return;
	}

	moveVec.y -= 250.0f * Time->deltaTime();
	angle = Vector2::angle(moveVec) - 90.0f;
	angle *= -1;
	pos += moveVec * Time->deltaTime();
	lt = pos + Vector2{ -(float)itemImgSize.x, (float)itemImgSize.y };
	rb = pos + Vector2{ (float)itemImgSize.x, -(float)itemImgSize.y };
}

void Arrow::render(HDC _hdc)
{
	ImageHandler::renderRotateWithoutBack(itemImg, _hdc, cam->calculateScreenPosition(pos), itemImgSize, {0,0}, angle, false);
}
