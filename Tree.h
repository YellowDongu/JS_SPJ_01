#pragma once
#include "TreeTop.h"


class Node;
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

	const float& growTime() const { return liveTime; }
	void setGrowTime(float _value) { liveTime = _value; }
private:
	int height;
	float liveTime;
	std::list<Node*> nodes;
	TreeTop* treeTop;
};
