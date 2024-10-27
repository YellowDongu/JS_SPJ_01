#pragma once
#include "Tool.h"

class CopperPickAxe : public Tool
{
public:
	CopperPickAxe();
	virtual ~CopperPickAxe();

	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;
private:


};
