#include "framework.h"
#include "BigEyeSummoner.h"
#include "EntityManager.h"

BigEyeSummoner::BigEyeSummoner()
{
}

BigEyeSummoner::~BigEyeSummoner()
{
}

Item* BigEyeSummoner::clone() const
{
	return new BigEyeSummoner(*this);
}

void BigEyeSummoner::dragDrop()
{
}

void BigEyeSummoner::use()
{
	entityMgr->summonBoss_BigEye();
	count--;
}

void BigEyeSummoner::init()
{
	getImgSet("BigEyeSummoner");
	itemImgSize.x = 16;
	itemImgSize.y = 16;
	code = 17;
	itemUsingState = UsingState::Use;
	itemName = L"Suspicious Looking Eye";
}
