#pragma once
#include "Entity.h"
#include "PlayerInventory.h"
#include "Helmet.h"
#include "Plate.h"
#include "Leggings.h"

class animationContainer;
//class Helmet;
//class Plate;
//class Leggings;
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


	Helmet* helmetSlot() { return helmet; }
	Plate* plateSlot() { return plate; }
	Leggings* leggingsSlot() { return leggings; }
	
	void helmetSlot(Item* newItem);
	void plateSlot(Item* newItem);
	void leggingsSlot(Item* newItem);

	Helmet* helmetOff();
	Plate* plateOff();
	Leggings* leggingsOff();

private:
	//std::map<std::string, animationContainer*> animations;
	std::string currentState;
	std::string currentSubState;
	PlayerInventory* inven;

	int mp;
	int maxMp;
	int defense;

	float healSpeed;

	Item* usingItem;

	Helmet* helmet;
	Plate* plate;
	Leggings* leggings;

};
