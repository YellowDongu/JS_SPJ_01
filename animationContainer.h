#pragma once

class animationContainer
{
public:
	animationContainer();
	~animationContainer();

	void update();
	void render(HDC _hdc);
	void init(std::map<std::string, std::vector<Vector2Int>> _posValue, std::string defultState, Vector2* _masterPos, Vector2Int _imgSizeValue, Vector2Int _imgOffsetValue);
	void setRawImg(HBITMAP _rawImg) { rawImg = _rawImg; }
	void changeImg(std::string state);
	void resetAnimation();
	void setSpeed(float _value) { speed = _value; }
	void setTime(float _value) { maxTime = _value; }
	void setBlank(Vector2Int _value) { blank = _value; }
	void setImgPos(std::map<std::string, std::vector<Vector2Int>> _value) { imgPosSet = _value; }
private:
	float speed;
	float time;
	float maxTime;
	int sequence;
	int width;
	int height;

	HBITMAP currentImg;
	HBITMAP rawImg;

	Vector2* masterPos;
	Vector2Int blank;
	Vector2Int imgOffset;
	Vector2Int imgSize;

	std::vector<Vector2Int>* imgPos;
	std::vector<HBITMAP> imgContainer;
	std::map<std::string, std::vector<Vector2Int>> imgPosSet;
};
