#pragma once
#include "Tool.h"

class CopperSword : public Tool
{
public:
	CopperSword();
	virtual ~CopperSword();

	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;
private:



};

