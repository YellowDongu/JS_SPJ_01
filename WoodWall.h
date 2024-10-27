#pragma once
#include "Wall.h"

class WoodWall : public Wall
{
public:
	WoodWall();
	virtual ~WoodWall();

	// Wall��(��) ���� ��ӵ�
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _gridPos) override;
	Wall* destroyed(Vector2Int _gridPos) override;
private:



};