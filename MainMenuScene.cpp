#include "framework.h"
#include "Scene.h"
#include "StartButton.h"
#include "MainMenuScene.h"
#include "RenderManager.h"
#include "ImageHandler.h"
#include "EndButton.h"
#include "UIManager.h"
#include "CameraManager.h"
#include "SoundManager.h"
#include "Cursor.h"


void MainMenuScene::init()
{
	rendering->setBackGround(rendering->findImage("mainMenuSplash_shadow0rotation0"));
	startBtn = (StartButton*)UIMgr->appendUI(new StartButton());
	cam->update();
	startBtn->leftTop({ (cam->getWindowSize().x / 2), 500.0f });
	startBtn->rightBottom({ (cam->getWindowSize().x / 2), 580.0f });
	EndButton* endBtn = (EndButton*)UIMgr->appendUI(new EndButton());
	endBtn->leftTop({ 500.0f,600.0f });
	endBtn->rightBottom({ 670.0f,680.0f });
	logo = rendering->findImage("UI_Title_logo_shadow0rotation0");
	logo = rendering->findImage("UI", "Title", "logo")[0];

	Cursor* newCursor = new Cursor();
	newCursor->init();
	UIMgr->appendUI(newCursor);
}

void MainMenuScene::render(HDC _hdc)
{
	rendering->render(_hdc);
	UIMgr->render(_hdc);
	ImageHandler::renderWithoutBack(logo, _hdc, (int)(cam->getWindowSize().x / 2) - 243, 100);
}

int MainMenuScene::update()
{
	UIMgr->update();
	UIMgr->checkColl();
	if (startBtn->state() == UIState::clicked)
	{
		music->playNew("Menu_Open.wav");
		return 1;
	}

	//if (!music->checkBGMPlaying())
	//	music->playBGM("Music-Title_Screen.mp3");
	
	return 0;
}

void MainMenuScene::release()
{
	UIMgr->release();
}
