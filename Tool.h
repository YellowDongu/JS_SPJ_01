#pragma once
#include "Item.h"
#include "Entity.h"

class Tool : public Item
{
public:
	Tool();
	virtual ~Tool();

	virtual void init() abstract;
	std::list<Entity*>* hittedList() { return &hitted; }
	void apeendhittedList(Entity* newEntity) { hitted.push_back(newEntity); }
	void clearHittedList() { hitted.clear(); }
	
private:
	bool use;

	float efficiency;
	float damage;
	float speed;

	std::list<Entity*> hitted;

};