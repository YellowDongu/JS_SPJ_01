#include "framework.h"
#include "Boss.h"
#include "Player.h"
Boss::Boss() : player(nullptr)
{
}

Boss::~Boss()
{
}

void Boss::linkPlayer(Player* _player)
{
	player = _player;
}
