#pragma once
#include "Tool.h"

class CopperBow : public Tool
{
public:
	CopperBow();
	~CopperBow();


	// Tool��(��) ���� ��ӵ�
	Item* clone() const override;
	void dragDrop() override;
	void use() override;
	void init() override;
private:

};
