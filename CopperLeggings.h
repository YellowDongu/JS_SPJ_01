#pragma once
#include "Leggings.h"

class CopperLeggings : public Leggings
{
public:
	CopperLeggings();
	virtual ~CopperLeggings();

	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;
	void render(HDC _hdc) override;

private:

};
