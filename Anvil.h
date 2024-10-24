#pragma once
#include "Furniture.h"

class Anvil : public Furniture
{
public:
	Anvil();
	virtual ~Anvil();

	// Furniture��(��) ���� ��ӵ�
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _position) override;
	void useInField() override;
	Item* destroyed(Vector2Int _gridPos) override;

private:



};
