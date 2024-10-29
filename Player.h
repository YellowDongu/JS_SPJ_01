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
	void imgInit();
	void updateAni();
	void useItem();

	PlayerInventory* linkInven() { return inven; }
	Item*& currentUsingItem() { return usingItem; }
	void deleteUsingItem() { usingItem = nullptr; }

	bool* linkDead() { return &dead; }
	int* linkMana() { return &mp; }
	int* linkMaxMana() { return &maxMp; }
	float* linkSpawnCount() { return &spawnTimer; }

	Helmet* helmetSlot() { return helmet; }
	Plate* plateSlot() { return plate; }
	Leggings* leggingsSlot() { return leggings; }
	
	void helmetSlot(Item* newItem);
	void plateSlot(Item* newItem);
	void leggingsSlot(Item* newItem);

	Helmet* helmetOff();
	Plate* plateOff();
	Leggings* leggingsOff();

	const Vector2& spawnPoint() const { return spawnPos; }
	void spawnPoint(const Vector2& _pos) { spawnPos = _pos; }

private:
	int mp;
	int maxMp;
	int defense;

	float healSpeed;
	float hitRecover;
	float spawnTimer;

	Item* usingItem;
	Helmet* helmet;
	Plate* plate;
	Leggings* leggings;
	PlayerInventory* inven;


	Vector2 spawnPos;

	std::string currentState;
	std::string currentSubState;
};
