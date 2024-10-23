#pragma once
#include "Entity.h"

class Player;
class Boss : public Entity
{
public:
	Boss();
	virtual ~Boss();

	virtual void render(HDC _hdc) abstract;
	void linkPlayer(Player* player);
protected:
	Player* player;
};
