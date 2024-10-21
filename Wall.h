#pragma once
#include "Item.h"

class Wall : public Item
{
public:
	Wall();
	virtual ~Wall();

	virtual void init(Vector2Int _gridPos) abstract;
	virtual Wall* destroyed(Vector2Int _gridPos) abstract;

	void getImgSet(std::string name);
	void changeBlockImg(std::string state, int shadow);
	Vector2Int imageFinder(std::string state);
private:

};