#include "framework.h"
#include "RenderManager.h"
#include "ImageHandler.h"

void RenderManager::init()
{
    loadAllImage(".\\Assets");
}

void RenderManager::relaese()
{
    // 와 이 탑을 어찌하리오
    // 검색 시간 단축을 위해 구조를 이렇게 했다지만 이건 좀 너무한듯;; 근데 이걸 타개할 방법은 모르겠다
    if (imageContainer.empty()) return;

    for (auto& root : imageContainer)
    {
        if (root.second.empty()) continue;
        for (auto& seperator : root.second)
        {
            if (seperator.second.empty()) continue;
            for (auto& detail : seperator.second)
            {
                if (detail.second.empty()) continue;
                for (auto& img : detail.second)
                {
                    DeleteObject(img);
                }
            }
        }
    }
    imageContainer.clear();
}

void RenderManager::render(HDC _hdc)
{
	ImageHandler::renderWithoutBack(backGround, _hdc, 0, 0);
}

std::map<std::string, std::map<std::string, std::vector<HBITMAP>>>* RenderManager::findImageSet(std::string imageName)
{
    if (imageContainer.empty()) return nullptr;

    auto resOne = imageContainer.find(imageName);
    if ((*resOne).second.empty()) return nullptr;

    return &(*resOne).second;
}

std::vector<HBITMAP> RenderManager::findImage(std::string imageName, std::string state, int shadow, int rotation)
{
    if (imageContainer.empty()) return std::vector<HBITMAP>();
    std::string imgInfo;

    if(shadow == 0) imgInfo = "shadow0";
    else imgInfo = "shadow" + shadow;

    if (rotation == 0) imgInfo += "rotation0";
    else imgInfo += "rotation" + rotation;
    

    auto resOne = imageContainer.find(imageName);
    if ((*resOne).second.empty()) return std::vector<HBITMAP>();

    auto resTwo = (*resOne).second.find(state);
    if ((*resTwo).second.empty()) return std::vector<HBITMAP>();

    auto resThree = (*resTwo).second.find(imgInfo);
    if ((*resThree).second.empty()) return std::vector<HBITMAP>();

    return (*resThree).second;
}
//UI전용
std::vector<HBITMAP> RenderManager::findImage(std::string mjrCat, std::string minrCat, std::string imgName)
{
    if (imageContainer.empty()) return std::vector<HBITMAP>();

    auto resOne = imageContainer.find(mjrCat);
    if ((*resOne).second.empty()) return std::vector<HBITMAP>();

    auto resTwo = (*resOne).second.find(minrCat);
    if ((*resTwo).second.empty()) return std::vector<HBITMAP>();

    auto resThree = (*resTwo).second.find(imgName);
    if ((*resThree).second.empty()) return std::vector<HBITMAP>();

    return (*resThree).second;
}

HBITMAP RenderManager::findImage(std::string imageName)
{
    auto res = TestBackImage.find(imageName);
    return (*res).second;
}

void RenderManager::loadAllImage(std::string path)
{
    for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
    {
        if (entry.is_regular_file() && entry.path().extension() == L".bmp")
        {
            std::wstring filePath = entry.path().wstring();
            HBITMAP hBitmap = ImageHandler::loadImg(filePath);
            if (hBitmap)
            {
                TestBackImage[entry.path().stem().string() + "_shadow0rotation0"] = hBitmap;

                std::vector<std::string> tokens;
                std::string token;
                std::stringstream ss(entry.path().stem().string());
                while (std::getline(ss, token, '_'))
                {
                    tokens.push_back(token);
                }
                if (tokens.size() < 3) continue;

                if (tokens[0] == "Entity")
                {
                    if (tokens[1] == "Player")
                    {
                        if (tokens[2] != "Rraw")
                            imageContainer[tokens[0] + "_" + tokens[1]][tokens[2]]["shadow0rotation0"].push_back(hBitmap);

                        imageContainer[tokens[0] + "_" + tokens[1]]["raw"]["shadow0rotation0"].push_back(hBitmap);
                        continue;
                    }
                    processEntityWithState(tokens, hBitmap);
                    continue;
                }

                if (tokens[0] == "UI" || tokens[0] == "BackGround")
                {
                    processUIWithState(tokens, hBitmap);
                    continue;
                }

                if (tokens[0] == "Tiles")
                {
                    processBlockWithState(tokens, hBitmap);
                    continue;
                }

                if (tokens[0] == "Item")
                {
                    imageContainer[tokens[0] + "_" + tokens[1]][tokens[2]]["shadow0rotation0"].push_back(hBitmap);
                    continue;
                }
                imageContainer[tokens[0] + "_" + tokens[1]]["raw"]["shadow0rotation0"].push_back(hBitmap);

            }
        }
    }

}

void RenderManager::processBlockWithState(std::vector<std::string> imageName, HBITMAP blockRaw)
{
    imageContainer[imageName[0] + "_" + imageName[1]][imageName[2]]["shadow0rotation0"].push_back(blockRaw);

    //for (int i = 1; i < 11; i++)
    //{
    //    std::string shadow = "shadow" + std::to_string(i * 10) + "rotation0";
    //    HBITMAP shadowProcessed = ImageHandler::shadowImage(blockRaw, (i * 10));
    //    imageContainer[imageName]["raw"][shadow].push_back(shadowProcessed);
    //}
}

void RenderManager::processPlayerWithState()
{
    std::vector<HBITMAP> imgSet = findImage("Entity_Player", "raw", 0, 0);
    std::vector<std::pair<std::string, std::vector<Vector2Int>>> imgPos =
    {
        {"headStandR",{{0,1}}}, //10
        {"headJumpR", {{0,5}}},
        {"headWalkR", {{0,6}, {0,7}, {0,8}, {0,9} ,{0,10}, {0,11},
        {0,12}, {0,13}, {0,14}, {0,15}, {0,16}, {0,17}, {0,18}, {0,19}}},

        {"eyeStandR",{{0,1}}}, //10
        {"eyeJumpR", {{0,5}}},
        {"eyeWalkR", {{0,6}, {0,7}, {0,8}, {0,9} ,{0,10}, {0,11},
        {0,12}, {0,13}, {0,14}, {0,15}, {0,16}, {0,17}, {0,18}, {0,19}}},

        {"torsoR", {{ 0,0 }}},
        {"torsoWalkR", {{ 0,0 }, { 1,0 }}},
        {"clothesR", {{ 0,0 }}},
        {"clothesWalkR", {{ 0,0 }, { 1,0 }}},

        {"armFStandR", {{2,0}}},
        {"armRStandR", {{2,2}}},
        {"armFJumpR", {{3,0}}},
        {"armRJumpR", {{2,3}}},
        {"armFWalkR", {{3,1}, {4,1}, {5,1}, {6,1}} },
        {"armRWalkR", {{3,3}, {4,3}, {5,3}, {6,3}} },

        {"legStandR",{{0,1}}},//10
        {"legJumpR", {{0,5}}},
        {"legWalkR", {{0,6}, {0,7}, {0,8}, {0,9} ,{0,10}, {0,11},
        {0,12}, {0,13}, {0,14}, {0,15}, {0,16}, {0,17}, {0,18}, {0,19}}}
    };

    Vector2 playerImgInfo = { 40, 54 };

    int index = 0;

    for (int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < imgPos[index].second.size(); j++)
        {
            Vector2 imagePos = Vector2{ (float)(playerImgInfo.x * imgPos[index].second[j].x), (float)(playerImgInfo.y * imgPos[index].second[j].y) } + imgPos[index].second[j] * 2;

            HBITMAP processed = ImageHandler::cropImage(imgSet[0], imagePos, playerImgInfo);
            imageContainer["Entity_Player"][imgPos[index].first]["shadow0rotation0"].push_back(processed);
            for (int i = 1; i < 11; i++)
            {
                std::string shadow;
                if (i == 0) shadow = "shadow0rotation0";
                else shadow = std::string("shadow" + (i * 10)) + "rotation0";
                HBITMAP shadowProcessed = ImageHandler::shadowImage(processed, (i * 10));
                imageContainer["Entity_Player"][imgPos[index].first][shadow].push_back(processed);
            }
        }
        index++;
    }
    for (int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < imgPos[index].second.size(); j++)
        {
            Vector2 imagePos = Vector2{ (float)(playerImgInfo.x * imgPos[index].second[j].x), (float)(playerImgInfo.y * imgPos[index].second[j].y) } + imgPos[index].second[j] * 2;

            HBITMAP processed = ImageHandler::cropImage(imgSet[7], imagePos, playerImgInfo);
            imageContainer["Entity_Player"][imgPos[index].first]["shadow0rotation0"].push_back(processed);
            for (int i = 1; i < 11; i++)
            {
                std::string shadow;
                if (i == 0) shadow = "shadow0rotation0";
                else shadow = std::string("shadow" + (i * 10)) + "rotation0";
                HBITMAP shadowProcessed = ImageHandler::shadowImage(processed, (i * 10));
                imageContainer["Entity_Player"][imgPos[index].first][shadow].push_back(processed);
            }
        }
        index++;

    }


    for (int i = 0; i < 2; i++)
    {
        for (unsigned int j = 0; j < imgPos[index].second.size(); j++)
        {
            Vector2 imagePos = Vector2{ (float)(playerImgInfo.x * imgPos[index].second[j].x), (float)(playerImgInfo.y * imgPos[index].second[j].y) } + imgPos[index].second[j] * 2;
            if (i == 1 || j == 1) imagePos.y += 1;

            HBITMAP processed = ImageHandler::cropImage(imgSet[8], imagePos, playerImgInfo);
            imageContainer["Entity_Player"][imgPos[index].first]["shadow0rotation0"].push_back(processed);
            for (int i = 1; i < 11; i++)
            {
                std::string shadow;
                if (i == 0) shadow = "shadow0rotation0";
                else shadow = std::string("shadow" + (i * 10)) + "rotation0";
                HBITMAP shadowProcessed = ImageHandler::shadowImage(processed, (i * 10));
                imageContainer["Entity_Player"][imgPos[index].first][shadow].push_back(processed);
            }
        }
        index++;

    }

    for (int i = 0; i < 2; i++)
    {
        for (unsigned int j = 0; j < imgPos[index].second.size(); j++)
        {
            Vector2 imagePos = Vector2{ (float)(playerImgInfo.x * imgPos[index].second[j].x), (float)(playerImgInfo.y * imgPos[index].second[j].y) } + imgPos[index].second[j] * 2;
            if (i == 1 || j == 1) imagePos.y += 1;

            HBITMAP processed = ImageHandler::cropImage(imgSet[11], imagePos, playerImgInfo);
            imageContainer["Entity_Player"][imgPos[index].first]["shadow0rotation0"].push_back(processed);
            for (int i = 1; i < 11; i++)
            {
                std::string shadow;
                if (i == 0) shadow = "shadow0rotation0";
                else shadow = std::string("shadow" + (i * 10)) + "rotation0";
                HBITMAP shadowProcessed = ImageHandler::shadowImage(processed, (i * 10));
                imageContainer["Entity_Player"][imgPos[index].first][shadow].push_back(processed);
            }
        }
        index++;

    }

    for (int i = 0; i < 6; i++)
    {
        for (unsigned int j = 0; j < imgPos[index].second.size(); j++)
        {
            Vector2 imagePos = Vector2{ (float)(playerImgInfo.x * imgPos[index].second[j].x), (float)(playerImgInfo.y * imgPos[index].second[j].y) + imgPos[index].second[j].y * 2 };
            HBITMAP processed = ImageHandler::cropImage(imgSet[12], imagePos, playerImgInfo);
            imageContainer["Entity_Player"][imgPos[index].first]["shadow0rotation0"].push_back(processed);
            for (int i = 1; i < 11; i++)
            {
                std::string shadow;
                if (i == 0) shadow = "shadow0rotation0";
                else shadow = std::string("shadow" + (i * 10)) + "rotation0";
                HBITMAP shadowProcessed = ImageHandler::shadowImage(processed, (i * 10));
                imageContainer["Entity_Player"][imgPos[index].first][shadow].push_back(processed);
            }
        }
        index++;

    }
    for (int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < imgPos[index].second.size(); j++)
        {
            Vector2 imagePos = Vector2{ (float)(playerImgInfo.x * imgPos[index].second[j].x), (float)(playerImgInfo.y * imgPos[index].second[j].y) } + imgPos[index].second[j] * 2;

            HBITMAP processed = ImageHandler::cropImage(imgSet[3], imagePos, playerImgInfo);
            imageContainer["Entity_Player"][imgPos[index].first]["shadow0rotation0"].push_back(processed);
            for (int i = 1; i < 11; i++)
            {
                std::string shadow;
                if (i == 0) shadow = "shadow0rotation0";
                else shadow = std::string("shadow" + (i * 10)) + "rotation0";
                HBITMAP shadowProcessed = ImageHandler::shadowImage(processed, (i * 10));
                imageContainer["Entity_Player"][imgPos[index].first][shadow].push_back(processed);
            }
        }
        index++;

    }
}

void RenderManager::processUIWithState(std::vector<std::string> imageName, HBITMAP raw)
{
    if (imageName[1] == "inventory")
    {
        imageContainer[imageName[0]][imageName[1]][imageName[2] + "_" + imageName[3]].push_back(raw);
    }
    else
    {
        if (imageName.size() > 3)
        {
            imageContainer[imageName[0]][imageName[1]][imageName[2] + "_" + imageName[3]].push_back(raw);
        }
        else
        {
            imageContainer[imageName[0]][imageName[1]][imageName[2]].push_back(raw);
        }
    }
    

}

void RenderManager::processEntityWithState(std::vector<std::string>& imageName, HBITMAP raw)
{

    if (imageName[1] == "npcEnemy")
    {
        if (imageName[2] == "slime")
        {
            Vector2Int size = Vector2Int{ 32,24 };
            for (int i = 0; i < 2; i++)
            {
                HBITMAP processed = ImageHandler::cropImage(raw, Vector2Int{0,size.y * i + i * 2}, size);
                imageContainer[imageName[0]+"_"+ imageName[1]][imageName[2]]["R_shadow0rotation0"].push_back(processed);
            } 
        }
        if (imageName[2] == "zombie")
        {
            Vector2Int size = Vector2Int{ 38,46 };
            imageContainer[imageName[0] + "_" + imageName[1]][imageName[2]]["R_shadow0rotation0"].push_back(raw);
            for (int i = 0; i < 3; i++)
            {
                HBITMAP processed = ImageHandler::cropImage(raw, Vector2Int{ 0,size.y * i + i * 2 }, size);
                imageContainer[imageName[0] + "_" + imageName[1]][imageName[2]]["R_shadow0rotation0"].push_back(processed);
            }
        }
        if (imageName[2] == "demonEye")
        {
            Vector2Int size = Vector2Int{ 38,22 };
            for (int i = 0; i < 3; i++)
            {
                HBITMAP processed = ImageHandler::cropImage(raw, Vector2Int{ 0,size.y * i + i * 2 }, size);
                imageContainer[imageName[0] + "_" + imageName[1]][imageName[2]]["R_shadow0rotation0"].push_back(processed);
            }
        }
        if (imageName[2] == "smallEye")
        {
            Vector2Int size = Vector2Int{ 20,30 };
            for (int i = 0; i < 3; i++)
            {
                HBITMAP processed = ImageHandler::cropImage(raw, Vector2Int{ 0,size.y * i + i * 2 }, size);
                imageContainer[imageName[0] + "_" + imageName[1]][imageName[2]]["R_shadow0rotation0"].push_back(processed);
            }
        }
        return;
    }
    else if (imageName[1] == "npcBoss")
    {
        if (imageName[2] == "skeleton")
        {
            imageContainer[imageName[0] + "_" + imageName[1]][imageName[2]+"_"+imageName[3]]["R_shadow0rotation0"].push_back(raw);
        }
        if (imageName[2] == "bigEye")
        {
            Vector2Int size = Vector2Int{ 110,166 };
            for (int i = 0; i < 6; i++)
            {
                imageContainer[imageName[0] + "_" + imageName[1]][imageName[2]]["shadow0rotation0"].push_back(raw);
                HBITMAP processed = ImageHandler::cropImage(raw, Vector2Int{ 0,size.y * i + (i + 1) * 2 }, size);
                if (i < 3)
                {
                    imageContainer[imageName[0]][imageName[1] + "_" + imageName[2] +"_phase1"]["R_shadow0rotation0"].push_back(processed);
                }
                else
                {
                    imageContainer[imageName[0]][imageName[1] + "_" + imageName[2] +"_phase2"]["R_shadow0rotation0"].push_back(processed);
                }
            }
        }

        return;
    }
    else
    {
        imageContainer[imageName[0] + "_" + imageName[1]][imageName[2]]["shadow0rotation0"].push_back(raw);
    }

}
