#pragma once
#include "Tool.h"

class copperPickAxe : public Tool
{
public:
	copperPickAxe();
	virtual ~copperPickAxe();

	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;
private:


};
