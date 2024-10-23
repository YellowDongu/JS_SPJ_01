#pragma once
#include "Plate.h"

class CopperPlate : public Plate
{
public:
	CopperPlate();
	virtual ~CopperPlate();


	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;
	void render(HDC _hdc) override;

private:



};
