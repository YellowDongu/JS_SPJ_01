#pragma once

enum class ItemCode
{
	Null,
	Block,
	Wall,
	Furniture,
	Tool,
	Armour,
	UseableItem


};


class Item
{
public:
	Item();
	virtual ~Item();

	virtual Item* clone() const abstract;
	virtual void dragDrop() abstract;
	virtual void use() abstract;

	void setOnGround(bool _value) { onGround = _value; }
	bool isOnGround() const { return onGround; }

	HBITMAP* linkTileImg() { return &rawPlacedImg; }
	HBITMAP* linkItemImg() { return &itemImg; }
	const Vector2Int& imgPos() const { return placedImgPos; }
	int itemCount() const { return count; }
	int* linkItemCount() { return &count; }
	int itemMaxCount() const { return maxCount; }
	int itemCode() const { return code; }

	void setItemCount(int _value) { count = _value; }
	void addItemCount(int _value) { count += _value; }
	void position(Vector2 _value) { pos = _value; }
	void translate(Vector2 _value) { pos += _value; }
	const Vector2& position() const { return pos; }
	const Vector2Int& size() const { return placedImgSize; }
	const Vector2Int& itemSize() const { return itemImgSize; }

protected:
	bool onGround;
	int count;
	int maxCount;
	int code;
	float speed;

	HBITMAP itemImg;
	HBITMAP rawPlacedImg;

	Vector2 pos;
	Vector2 hitAreaStart;
	Vector2 hitAreaEnd;

	std::string itemName;
	Vector2Int placedImgSize;
	Vector2Int itemImgSize;
	Vector2Int placedImgPos;

	std::map<std::string, std::vector<HBITMAP>>* placedImgSet;
	std::map<std::string, std::vector<Vector2Int>> imgInfo;
};
