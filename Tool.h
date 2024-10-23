#pragma once
#include "Item.h"

class Tool : public Item
{
public:
	Tool();
	virtual ~Tool();

	virtual void init() abstract;
	
private:
	bool use;

	float efficiency;
	float damage;
	float speed;
};