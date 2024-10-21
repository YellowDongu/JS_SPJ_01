#pragma once
#include "AnimationController.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	Vector2 position() const { return worldPos; }
	//Vector2* position() { return &worldPos; }
	Vector2 size() const { return sizeInfo; }
	Vector2 moveVector() const { return moveVec; }
	//Vector2* moveVector() { return &moveVec; }
	AnimationController* animation() const { return aniCtrl; }

	void position(Vector2 _value) { worldPos = _value; }
	void translate(Vector2 _value) { moveVec += _value; }

	bool isOnGround() const { return onGround; }
	void setOnGround(bool _value) { onGround = _value; }
	void setRWall(bool _value) { rightSideWall = _value; }
	void setLWall(bool _value) { LeftSideWall = _value; }

	int* linkHealth() { return &hp; }
	int* linkMaxHealth() { return &maxHp; }

	void move() { worldPos += moveVec; }

	virtual void init() abstract;
	virtual void update() abstract;
	virtual void release() abstract;

	//virtual void CollisionWithBlock(Node* _col, Vector2 colAmount) abstract;
	virtual void CollisionWithEntity(Entity* _col) abstract;


protected:
	Vector2 worldPos;
	Vector2 sizeInfo;
	Vector2 moveVec;

	bool onGround;
	bool rightSideWall;
	bool LeftSideWall;


	int light;
	int hp;
	int maxHp;
	float speed;
	float maxSpeed;
	AnimationController* aniCtrl;

	
};