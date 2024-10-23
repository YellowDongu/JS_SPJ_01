#pragma once
#include "Block.h"

class Stone : public Block
{
public:
	Stone();
	virtual ~Stone();

	// Block을(를) 통해 상속됨
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init(Vector2Int _gridPos) override;
	Item* destroyed(Vector2Int _gridPos) override;
private:



};