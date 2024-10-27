#pragma once
#include "Tool.h"

class CopperHammer : public Tool
{
public:
	CopperHammer();
	virtual ~CopperHammer();


	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;
private:



};
