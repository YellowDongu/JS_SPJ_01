#pragma once
#include "Tool.h"

class CopperBow : public Tool
{
public:
	CopperBow();
	~CopperBow();


	// Tool을(를) 통해 상속됨
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;
private:

};
