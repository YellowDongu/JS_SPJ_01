#pragma once
#include "Furniture.h"

class Tree : public Furniture
{
public:
	Tree();
	virtual ~Tree();

	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _position) override;
	void useInField() override;
	void update() override;
	Item* destroyed(Vector2Int _gridPos) override;
private:
	int height;
	float liveTime;

};
