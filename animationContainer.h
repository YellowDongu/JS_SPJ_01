#pragma once

class animationContainer
{
public:
	animationContainer();
	~animationContainer();

	void init(std::map<std::string, std::pair<bool, std::vector<Vector2Int>>> _posValue, std::string defultState, Vector2* _masterPos, Vector2Int _imgSizeValue, Vector2Int _imgOffsetValue);
	void update();
	void render(HDC _hdc);

	void changeImg(std::string state);
	void resetAnimation();

	bool triggered() const { return once; }
	int getSequence() const { return sequence; }
	bool isLeft() const { return left; }

	void syncTriggered(bool value) { reverseBlock = value; }
	void setSpeed(float _value) { speed = _value; }
	void setTime(float _value) { maxTime = _value; }
	void setBlank(Vector2Int _value) { blank = _value; }
	void setRawImg(HBITMAP _rawImg) { rawImg = _rawImg; }
	void setLeft(bool _value) { if (!reverseBlock) left = _value; }
	void setImgPos(std::map<std::string, std::pair<bool, std::vector<Vector2Int>>> _value) { imgPosSet = _value; }

	const std::string& getCurrentState() const { return currentState; }
	const std::string& getNormalState() const { return currentState; }
	bool isNormalState() const { return currentState == currentState; }
private:
	float speed;
	float time;
	float maxTime;
	int sequence;
	int width;
	int height;

	//HBITMAP currentImg;
	HBITMAP rawImg;

	Vector2* masterPos;
	Vector2Int blank;
	Vector2Int imgOffset;
	Vector2Int imgSize;

	std::vector<Vector2Int>* imgPos;
	std::vector<HBITMAP> imgContainer;
	std::map<std::string, std::vector<Vector2Int>> imgPosSetTemp;

	std::string currentState;
	std::string normalState;
	std::map<std::string, std::pair<bool, std::vector<Vector2Int>>> imgPosSet;
	bool once;
	bool left;
	bool reverseBlock;
};
