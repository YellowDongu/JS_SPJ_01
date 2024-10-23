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
	void CollisionWithItem(Item* _col) override;
	void CollisionWithEntity(Entity* _col) override;

	void keyInput();
	void vertical();
	void imgInit();
	void updateAni();
	void useItem();

	PlayerInventory* linkInven() { return inven; }
	Item*& currentUsingItem() { return usingItem; }
	void deleteUsingItem() { usingItem = nullptr; }

	int* linkMana() { return &mp; }
	int* linkMaxMana() { return &maxMp; }

private:
	//std::map<std::string, animationContainer*> animations;
	std::string currentState;
	std::string currentSubState;
	PlayerInventory* inven;

	int mp;
	int maxMp;

	Item* usingItem;

};
