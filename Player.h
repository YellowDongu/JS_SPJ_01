#pragma once
#include "Entity.h"
#include "PlayerInventory.h"

class animationContainer;
class Player : public Entity
{
public:
	Player();
	virtual ~Player();

	void init() override;
	void update() override;
	void release() override;
	void CollisionWithEntity(Entity* _col) override;

	void keyInput();
	void vertical();
	void imgInit();
	void updateAni();

	PlayerInventory* linkInven() { return inven; }

	int* linkMana() { return &mp; }
	int* linkMaxMana() { return &maxMp; }

private:
	//std::map<std::string, animationContainer*> animations;
	std::string currentState;
	PlayerInventory* inven;

	int mp;
	int maxMp;

};