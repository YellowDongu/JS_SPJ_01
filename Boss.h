#pragma once
#include "Entity.h"

class Boss : public Entity
{
public:
	Boss();
	~Boss();

	virtual void render(HDC _hdc) abstract;

private:

};
