#pragma once
#include "Wall.h"

class StoneWall : public Wall
{
public:
	StoneWall();
	virtual ~StoneWall();



	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _gridPos) override;
	Wall* destroyed(Vector2Int _gridPos) override;
private:
};
