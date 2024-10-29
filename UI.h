#pragma once

enum UIState
{
	normal,
	hoverMouse,
	clicked,
	End
};

class UI
{
public:
	UI() :lt(Vector2::zero()), rb(Vector2::zero()), currentState(UIState::normal), active(true), toolTip(L"NULL") {}
	virtual ~UI() {}

	virtual void update() abstract;
	virtual void triggered() abstract;
	virtual void render(HDC _hdc) abstract;

	Vector2 leftTop() const { return lt; }
	Vector2 rightBottom() const { return rb; }
	void leftTop(Vector2 _leftTop) { lt = _leftTop; }
	void rightBottom(Vector2 _rightBottom) { rb = _rightBottom; }

	void changeState(UIState _newState) { currentState = _newState; }
	UIState state() const { return currentState; }

	const bool& isActive() const { return active; }
	void setActive(bool _value) { active = _value; }

	std::wstring getToolTip() { return toolTip; }
protected:
	Vector2 lt, rb;
	bool active;
	UIState currentState;
	std::wstring toolTip;
};
