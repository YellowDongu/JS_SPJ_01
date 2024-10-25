#pragma once
#include "Entity.h"

class Player;
class Zombie : public Entity
{
public:
	Zombie();
	virtual ~Zombie();


	void init() override;
	void update() override;
	void release() override;
	void CollisionWithItem(Item* _col) override;
	void CollisionWithEntity(Entity* _col) override;

	void linkPlayer(Player* _player);
	void tracePlayer();
	void imgInit();
private:
	Player* player;
	std::string currentState;


};
