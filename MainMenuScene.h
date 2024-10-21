#pragma once

class StartButton;
class MainMenuScene : public Scene
{
public:
	MainMenuScene() : startBtn(nullptr), logo(NULL) {}
	virtual ~MainMenuScene() {}

	// Scene을(를) 통해 상속됨
	void init() override;
	void render(HDC _hdc) override;
	int update() override;
	void release() override;





private:
	StartButton* startBtn;
	HBITMAP logo;

};
