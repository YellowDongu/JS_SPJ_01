#pragma once

enum class UsingState
{
	Swing,
	Use,
	Directinal,
	End
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
	void leftTop(Vector2 _value) { lt = _value; }
	void rightBottom(Vector2 _value) { rb = _value; }
	const Vector2& position() const { return pos; }
	const Vector2Int& size() const { return placedImgSize; }
	const Vector2Int& itemSize() const { return itemImgSize; }
	const Vector2Int& itemImageCenter() const { return itemImgCenter; }
	const UsingState& usingState() const { return itemUsingState; }
	const Vector2& leftTop() const { return lt; }
	const Vector2& rightBottom() const { return rb; }
	const std::wstring& name() const { return itemName; }

protected:
	bool onGround;

	int count;
	int maxCount;
	int code;

	float speed;

	HBITMAP itemImg;
	HBITMAP rawPlacedImg;

	ULONGLONG lastTime;

	Vector2 pos;
	Vector2 lt;
	Vector2 rb;

	UsingState itemUsingState;
	std::wstring itemName;
	Vector2Int placedImgSize;
	Vector2Int itemImgSize;
	Vector2Int itemImgCenter;
	Vector2Int placedImgPos;

	std::map<std::string, std::vector<HBITMAP>>* placedImgSet;
	std::map<std::string, std::vector<Vector2Int>> imgInfo;
};
