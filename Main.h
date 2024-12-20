#pragma once


class MainGame
{
public:
	MainGame() : hWnd(NULL), hdc(NULL) {}
	~MainGame() { release(); }

	void update();
	void render();
	void render(HDC _hdc);
	void release();
	void init(HWND _hWnd);
	void loadGame();


private:
	HWND hWnd;
	HDC hdc;
};