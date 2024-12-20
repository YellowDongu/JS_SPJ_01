#pragma once
#include "Entity.h"

class Gore : public Entity
{
public:
	Gore();
	virtual ~Gore();

	void init() override;
	void update() override;
	void release() override;
	void CollisionWithEntity(Entity* _col) override;
	void CollisionWithItem(Item* _col) override;

	void render(HDC _hdc);
	void initGore(std::string imgName, Vector2 startPos);

private:
	float lifeTime;

	HBITMAP img;
};
