#pragma once
#include "Boss.h"
#include "SmallEye.h"

class BigEye :public Boss
{
public:
	BigEye();
	virtual ~BigEye();

	void init() override;
	void update() override;
	void release() override;
	void CollisionWithEntity(Entity* _col) override;
	void CollisionWithItem(Item* _col) override;
	void render(HDC _hdc) override;
private:
	int phase;
	int condition;
	int rushCount;
	int spawnCount;

	float stopWatch;
	float angle;

	std::vector<SmallEye*> servents;
};
