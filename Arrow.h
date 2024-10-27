#pragma once
#include "Projectile.h"

class Arrow : public Projectile
{
public:
	Arrow();
	virtual ~Arrow();


	void update() override;
	void render(HDC hdc) override;
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;
	void shoot(Vector2 startPos, Vector2 shootVec, int damage) override;

	void setMoveVec(Vector2 _vec) { moveVec = _vec; }
private:

};
