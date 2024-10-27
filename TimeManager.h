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
	float deltaT = 0.0f; //이전 프레임과 현재 프레임 사이의 시간 간격 (초단위)

	UINT32 frameCount = 0; // 현재 초 동안 프레임 수
	UINT32 fps = 0; //초당 프레임 수(FPS)
	float frameTime = 0.0f;
};

#ifdef Time
#undef Time
#endif
#define Time GET_SINGLETON(TimeManager)
