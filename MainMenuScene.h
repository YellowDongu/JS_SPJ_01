#pragma once

class StartButton;
class MainMenuScene : public Scene
{
public:
	MainMenuScene() : startBtn(nullptr), logo(NULL) {}
	virtual ~MainMenuScene() {}

	// Scene��(��) ���� ��ӵ�
	void init() override;
	void render(HDC _hdc) override;
	int update() override;
	void release() override;





private:
	StartButton* startBtn;
	HBITMAP logo;

};
