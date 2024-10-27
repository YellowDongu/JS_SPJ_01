#pragma once

class TimeManager
{
	DECLARE_SINGLETON(TimeManager);

public:
	void Init();
	void update();

	const UINT32& GetFPS() const { return fps; }
	const float& deltaTime() const { return deltaT; }
private:
	UINT64 frequency = 0;
	UINT64 prevCount = 0;
	float deltaT = 0.0f; //���� �����Ӱ� ���� ������ ������ �ð� ���� (�ʴ���)

	UINT32 frameCount = 0; // ���� �� ���� ������ ��
	UINT32 fps = 0; //�ʴ� ������ ��(FPS)
	float frameTime = 0.0f;
};

#ifdef Time
#undef Time
#endif
#define Time GET_SINGLETON(TimeManager)
