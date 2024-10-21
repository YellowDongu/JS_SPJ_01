#pragma once

class cameraManager
{
	DECLARE_SINGLETON(cameraManager)
public:
	/*
	cameraManager() : cameraManager(Vector2::zero()) {}
	cameraManager(const Vector2& startPosition) : centerPosition(startPosition), windowSize(Vector2::zero()), camSpeed(17.7f), hWnd(nullptr) {}
	~cameraManager() {}
	*/


	void				init(const Vector2&, const HWND&);
	void				update();
	void				setBorder(const Vector2&, const Vector2&);

	Vector2				getCamCenterPos()	const { return centerPosition; }
	Vector2				getWindowSize()		const { return windowSize; }

	void				translate(Vector2 _postion) { centerPosition += _postion; }
	void				Position(const Vector2& vector2) { centerPosition = vector2; }


	// ¿ùµåÁÂÇ¥ -> È­¸éÁÂÇ¥
	Vector2				calculateScreenPosition(const Vector2& position);
	// È­¸éÁÂÇ¥ -> ¿ùµåÁÂÇ¥
	Vector2				calculateWorldPosition(const Vector2& position);
	// ¿ùµåÁÂÇ¥ -> È­¸éÁÂÇ¥
	static	Vector2		calculateScreenPosition(const HWND& _hwnd, const Vector2& position, const Vector2& camPosition);
	// È­¸éÁÂÇ¥ -> ¿ùµåÁÂÇ¥
	static	Vector2		calculateWorldPosition(const HWND& _hwnd, const Vector2& position, const Vector2& camPosition);


private:
	HWND			hWnd = NULL;
	float			camSpeed = 0.0f;
	Vector2			centerPosition = Vector2::zero();
	Vector2			windowSize = Vector2::zero();
	Vector2			borderMin = Vector2::zero();
	Vector2			borderMax = Vector2::zero();
};

#define cam GET_SINGLETON(cameraManager)