#include "framework.h"
#include "SoundManager.h"



void SoundManager::init()
{
	FMOD_System_Create(&fmodSys);
	FMOD_System_Init(fmodSys, 1024, FMOD_INIT_NORMAL, NULL);

	for (const auto& entry : std::filesystem::recursive_directory_iterator(".\\Assets\\Sounds"))
	{
		if (entry.is_regular_file() && entry.path().extension() == L".wav")
		{
			std::wstring filePath = entry.path().wstring();
			FMOD_SOUND* newSound;
			std::string path = "Assets/Sounds/" + entry.path().stem().string() + ".wav";
			FMOD_System_CreateSound(fmodSys, path.c_str(), FMOD_DEFAULT | FMOD_UNIQUE, 0, &newSound);
			soundList[entry.path().stem().string() + ".wav"] = newSound;
		}
	}
	for (const auto& entry : std::filesystem::recursive_directory_iterator(".\\Assets\\BGMs"))
	{
		if (entry.is_regular_file() && entry.path().extension() == L".mp3")
		{
			std::wstring filePath = entry.path().wstring();
			FMOD_SOUND* newSound;
			std::string path = "Assets/BGMs/" + entry.path().stem().string() + ".mp3";
			FMOD_System_CreateSound(fmodSys, path.c_str(), FMOD_DEFAULT | FMOD_UNIQUE, 0, &newSound);
			soundList[entry.path().stem().string() + ".mp3"] = newSound;
		}
	}
	FMOD_System_Update(fmodSys);
}

void SoundManager::update()
{
	FMOD_System_Update(fmodSys);
	if (channelList.empty()) return;
	for (auto& channel : channelList)
	{
		if (checkPlaying(channel)) continue;
	}
}

bool SoundManager::checkPlaying(FMOD_CHANNEL* channel)
{
	FMOD_System_Update(fmodSys);
	int condition = 0;
	FMOD_RESULT result = FMOD_Channel_IsPlaying(channel, &condition);

	if (result != FMOD_OK) return false;
	return condition;
}

bool SoundManager::checkBGMPlaying()
{
	if (!checkPlaying(bgmChannel)) return false;

	unsigned int currentPosition = 0;
	unsigned int length = 0;
	FMOD_RESULT result;

	// 현재 재생 위치를 가져옴
	result = FMOD_Channel_GetPosition(bgmChannel, &currentPosition, FMOD_TIMEUNIT_MS);
	if (result != FMOD_OK) return false;

	// 사운드의 전체 길이를 가져옴
	result = FMOD_Sound_GetLength(soundList[currentBGM], &length, FMOD_TIMEUNIT_MS);
	if (result != FMOD_OK) return false;

	// 현재 재생 위치가 전체 길이와 같거나 크면 사운드 재생이 끝난 상태
	if (currentBGM == "Music - Journey's_Beginning_(intro).mp3")
	{
		return currentPosition < length / 2;
	}
	return currentPosition < length;
}

void SoundManager::loadSound(std::string name)
{
	FMOD_SOUND* newSound;
	std::string path = ".\\Assets";
	FMOD_System_CreateSound(fmodSys, (path + name).c_str(), FMOD_DEFAULT, 0, &newSound);
	soundList[name] = newSound;

}

void SoundManager::play(FMOD_SOUND* sound, FMOD_CHANNEL*& channel)
{
	stop(channel);
	FMOD_System_PlaySound(fmodSys, FMOD_CHANNEL_FREE, sound, false, &channel);
	FMOD_System_Update(fmodSys);
}

void SoundManager::playBGM(std::string name, bool loop)
{
	currentBGM = name;
	FMOD_System_Update(fmodSys);
	auto sound = soundList.find(name);
	if (sound == soundList.end()) return;

	// 루프 모드 및 반복 횟수 설정
	FMOD_Sound_SetMode((*sound).second, FMOD_LOOP_NORMAL);
	if (loop)
	{
		FMOD_Sound_SetLoopCount((*sound).second, -1); // 무한 반복
	}
	else
	{
		FMOD_Sound_SetLoopCount((*sound).second, 0); // 한 번만 재생
	}

	// 사운드 재생
	play((*sound).second, bgmChannel);

	FMOD_System_Update(fmodSys);
	/*
	FMOD_System_Update(fmodSys);
	auto sound = soundList.find(name);
	if (sound == soundList.end()) return;
	play((*sound).second, bgmChannel);
	FMOD_Sound_SetMode((*sound).second, FMOD_LOOP_NORMAL);
	if (loop)
	{
		FMOD_Sound_SetLoopCount((*sound).second, -1);
	}
	else
	{
		FMOD_Sound_SetLoopCount((*sound).second, 1);
	}
	FMOD_System_Update(fmodSys);
	*/
}

void SoundManager::playNew(std::string name)
{
	FMOD_System_Update(fmodSys);
	auto sound = soundList.find(name);
	if (sound == soundList.end()) return;
	FMOD_CHANNEL* newChannel = nullptr;
	play((*sound).second, newChannel);
	//channelList.push_back(newChannel);
	FMOD_System_Update(fmodSys);
}

void SoundManager::changeVolume(FMOD_CHANNEL* channel, int volume)
{
}

void SoundManager::changeBGMVolume(float volume)
{
	FMOD_System_Update(fmodSys);
	FMOD_Channel_SetVolume(bgmChannel, volume);
	FMOD_System_Update(fmodSys);
}

void SoundManager::stop(FMOD_CHANNEL* channel)
{
	if (checkPlaying(channel)) FMOD_Channel_Stop(channel);
	FMOD_System_Update(fmodSys);
}

void SoundManager::release()
{
	FMOD_System_Update(fmodSys);
	if (!channelList.empty())
	{
		for (auto& channel : channelList)
		{
			stop(channel);
		}
		channelList.clear();
	}

	if (!soundList.empty())
	{
		for (auto& sound : soundList)
		{
			FMOD_Sound_Release(sound.second);
		}
		soundList.clear();
	}

	FMOD_System_Release(fmodSys);
	FMOD_System_Close(fmodSys);
}
