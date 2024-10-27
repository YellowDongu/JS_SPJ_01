#pragma once
#include "Entity.h"

class SmallEye : public Entity
{
public:
	SmallEye();
	virtual ~SmallEye();

	void init() override;
	void update() override;
	void release() override;
	void CollisionWithEntity(Entity* _col) override;
	void CollisionWithItem(Item* _col) override;
	void render(HDC _hdc);
private:
	float angle;


};
