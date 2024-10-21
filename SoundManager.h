#pragma once


class SoundManager
{
	DECLARE_SINGLETON(SoundManager)
public:
	void init();
	void update();
	bool checkPlaying(FMOD_CHANNEL* channel);
	bool checkBGMPlaying();
	void loadSound(std::string filePath);
	void play(FMOD_SOUND* sound, FMOD_CHANNEL*& channel);
	void playBGM(std::string name, bool loop = true);
	void playNew(std::string name);
	void pause(FMOD_CHANNEL* channel, bool pause) { FMOD_Channel_SetPaused(channel, pause); }
	void changeVolume(FMOD_CHANNEL* channel, int volume);
	void changeBGMVolume(float volume);
	void stop(FMOD_CHANNEL* channel);
	void release();
	
private:
	std::map<std::string, FMOD_SOUND*> soundList;
	std::string currentBGM;
	FMOD_CHANNEL* bgmChannel = nullptr;
	std::list<FMOD_CHANNEL*> channelList;
	FMOD_SYSTEM* fmodSys = nullptr;

};
#define music GET_SINGLETON(SoundManager)