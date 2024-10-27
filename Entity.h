#pragma once
#include "AnimationController.h"
class Item;
class Entity
{
public:
	Entity();
	virtual ~Entity();

	const int damage() const { return dmg; }
	const Vector2& position() const { return worldPos; }
	const Vector2& size() const { return sizeInfo; }
	const Vector2& moveVector() const { return moveVec; }

	void position(Vector2 _value) { worldPos = _value; }
	void translate(Vector2 _value) { moveVec += _value; }

	const bool& isOnGround() const { return onGround; }
	const bool& isDead() const { return dead; }

	void setOnGround(bool _value) { onGround = _value; }
	void setDead(bool _value) { dead = _value; }
	void setRWall(bool _value) { rightSideWall = _value; }
	void setLWall(bool _value) { LeftSideWall = _value; }

	int* linkHealth() { return &hp; }
	int* linkMaxHealth() { return &maxHp; }
	Vector2* linkPosition() { return &worldPos; }
	AnimationController* animation() { return aniCtrl; }

	void move() { worldPos += moveVec; }

	virtual void init() abstract;
	virtual void update() abstract;
	virtual void release() abstract;

	//virtual void CollisionWithBlock(Node* _col, Vector2 colAmount) abstract;
	virtual void CollisionWithEntity(Entity* _col) abstract;
	virtual void CollisionWithItem(Item* _col) abstract;


protected:
	bool dead;
	bool onGround;
	bool rightSideWall;
	bool LeftSideWall;

	int hp;
	int maxHp;
	int light;
	int dmg;

	float speed;
	float maxSpeed;
	
	AnimationController* aniCtrl;

	Vector2 worldPos;
	Vector2 sizeInfo;
	Vector2 moveVec;
	
};