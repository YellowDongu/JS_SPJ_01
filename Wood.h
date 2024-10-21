#pragma once
#include "Block.h"


class Wood : public Block
{
public:
	Wood();
	~Wood();


	// Block��(��) ���� ��ӵ�
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _gridPos) override;
	Item* destroyed(Vector2Int _gridPos) override;
private:


};