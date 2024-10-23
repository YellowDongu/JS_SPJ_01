#pragma once
#include "Helmet.h"

class CopperHelmet : public Helmet
{
public:
	CopperHelmet();
	virtual ~CopperHelmet();

	// Helmet을(를) 통해 상속됨
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;
	void render(HDC _hdc) override;
private:



};
