#pragma once
#include "Item.h"

class Furniture : public Item
{
public:
	Furniture();
	~Furniture();

	virtual void init(Vector2Int _position) abstract;
	virtual void useInField() abstract;
	virtual Item* destroyed(Vector2Int _gridPos) abstract;

	void getImgSet(std::string name);

	void bottomPosition(int& _value) { bottomPos = _value; }
	void gridPosition(Vector2Int& _value) { placedPos = _value; }
	void imageGridSize(Vector2Int& _value) { imgGridSize = _value; }
	void imageGridPosition(Vector2Int& _value) { imgGridPos = _value; }

	const int& bottomPosition() const { return bottomPos; }
	const Vector2Int& imageGridSize() const { return imgGridSize; }
	const Vector2Int& imageGridPosition() const { return imgGridPos; }
	const Vector2Int& gridPosition() const { return placedPos; }
	const std::vector<Vector2Int>& placedInfo() const { return posInfo; }
	const std::vector<Vector2Int>& imagePosInfo() const { return imgPosInfo; }

protected:
	int bottomPos;

	Vector2Int placedPos;
	Vector2Int imgGridSize;
	Vector2Int imgGridPos;

	std::vector<Vector2Int> posInfo;
	std::vector<Vector2Int> imgPosInfo;
};
