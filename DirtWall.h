#pragma once
#include "Wall.h"

class DirtWall : public Wall
{
public:
	DirtWall();
	~DirtWall();


	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _gridPos) override;
	Wall* destroyed(Vector2Int _gridPos) override;

private:

};