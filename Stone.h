#pragma once
#include "Block.h"

class Stone : public Block
{
public:
	Stone();
	virtual ~Stone();

	// Block��(��) ���� ��ӵ�
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _gridPos) override;
	Item* destroyed(Vector2Int _gridPos) override;
private:



};