#pragma once
#include "Item.h"

class Furniture : public Item
{
public:
	Furniture();
	~Furniture();

	virtual void init(Vector2Int _position) abstract;
	virtual Item* destroyed(Vector2Int _gridPos) abstract;

	void getImgSet(std::string name);
	void changeBlockImg(std::string state, int shadow);
	Vector2Int imageFinder(std::string state);

	void gridPosition(Vector2Int& _value) { placedPos = _value; }
	const Vector2Int& gridPosition() const { return placedPos; }
	const std::vector<Vector2Int>& placedInfo() const { return posInfo; }
	const std::vector<Vector2Int>& imagePosInfo() const { return imgPosInfo; }

protected:
	Vector2Int placedPos;

	std::vector<Vector2Int> posInfo;
	std::vector<Vector2Int> imgPosInfo;
};
