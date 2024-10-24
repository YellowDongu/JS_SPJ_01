#include "framework.h"
#include "Main.h"
#include "CameraManager.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "SoundManager.h"


void MainGame::init(HWND _hWnd)
{
	hWnd = _hWnd;
	hdc = GetDC(hWnd);
	AddFontResourceEx(L".\\Assets\\Font\\ANDYB.TTF", FR_PRIVATE, NULL);
	mainFont = CreateFont(
		20,               // Height
		0,                // Width (0 means default width)
		0,                // Escapement
		0,                // Orientation
		FW_BOLD,        // Weight (normal)
		FALSE,            // Italic
		FALSE,            // Underline
		FALSE,            // StrikeOut
		DEFAULT_CHARSET,  // Charset
		OUT_DEFAULT_PRECIS, // Output precision
		CLIP_DEFAULT_PRECIS, // Clipping precision
		DEFAULT_QUALITY,  // Quality
		DEFAULT_PITCH | FF_SWISS,  // Pitch and Family
		L"Andy"          // Font face
	);


	Input->Init(hWnd);
	cam->init(Vector2::zero(), hWnd);
	sceneMgr->init();
	Time->Init();
	music->init();

	music->playBGM("Music-Journey's_Beginning_(intro).mp3", false);

}

void MainGame::update()
{
	music->update();
	cam->update();
	Time->update();
	Input->update();
	vhInput->Update();
	sceneMgr->update();
}

void MainGame::render()
{
	RECT clientRect;
	hdc = GetDC(hWnd);

	GetClientRect(hWnd, &clientRect);
	int width = clientRect.right - clientRect.left;
	int height = clientRect.bottom - clientRect.top;

	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(hdcMem, hbmMem);


	PatBlt(hdcMem, 0, 0, width, height, WHITENESS);

	// 그리기 작업
	render(hdcMem);

	BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);

	// 원래 객체로 복원
	SelectObject(hdcMem, oldBitmap);

	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
	ReleaseDC(hWnd, hdc);
}

void MainGame::render(HDC _hdc)
{
	sceneMgr->render(_hdc);

}

void MainGame::release()
{
	sceneMgr->release();
	music->release();
}