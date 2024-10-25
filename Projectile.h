#pragma once
#include "Tool.h"

class Projectile : public Tool
{
public:
	Projectile();
	virtual ~Projectile();

	virtual void update() abstract;
	virtual void render(HDC hdc) abstract;
	virtual void shoot(Vector2 startPos, Vector2 shootVec, float damage) abstract;

	void setAngle(float _value) { angle = _value; }
	void setDead(bool _value) { dead = _value; }
	void moveVector(Vector2 _value) { moveVec = _value; }
	void translate(Vector2 _value) { moveVec += _value; }
	
	const float& getAngle() const { return angle; }
	const bool& isDead() const { return dead; }
	const Vector2& moveVector() const { return moveVec; }

protected:
	float angle;
	bool dead;

	Vector2 moveVec;
};
