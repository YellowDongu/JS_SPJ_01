#pragma once
#include "Block.h"


class Wood : public Block
{
public:
	Wood();
	~Wood();


	// Block을(를) 통해 상속됨
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _gridPos) override;
	Item* destroyed(Vector2Int _gridPos) override;
private:


};