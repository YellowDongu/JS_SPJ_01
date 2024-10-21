#pragma once
#include "Entity.h"
#include "Node.h"
#include "Item.h"
#include "EntityManager.h"

class RenderManager
{
	DECLARE_SINGLETON(RenderManager)
public:
	void init();
	void relaese();
	void render(HDC _hdc);
	std::map<std::string, std::map<std::string, std::vector<HBITMAP>>>* findImageSet(std::string imageName);
	std::vector<HBITMAP> findImage(std::string imageName, std::string state, int shadow, int rotation);
	std::vector<HBITMAP> findImage(std::string mjrCat, std::string minrCat, std::string imgName);
	HBITMAP findImage(std::string imageName);
	void loadAllImage(std::string path);


	void linkplayer(Player* _player) { player = _player; }
	Player* linkplayer() { return player; }
	void linkEntityList(std::list<Entity*>* list) { entityList = list; }

	void setBackGround(HBITMAP img) { backGround = img; }

	void processBlockWithState(std::vector<std::string> imageName, HBITMAP blockRaw);
	void processPlayerWithState();
	void processUIWithState(std::vector<std::string> imageName, HBITMAP raw);
	void processEntityWithState(std::vector<std::string>& imageName, HBITMAP raw);
private:
	std::map<std::string, std::map<std::string, std::map<std::string, std::vector<HBITMAP>>>> imageContainer;
	std::map<std::string, HBITMAP> TestBackImage;

	Player* player = nullptr;
	std::list<Entity*>* entityList = nullptr;
	HBITMAP backGround = NULL;
};
#define rendering GET_SINGLETON(RenderManager)