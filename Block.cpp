#include "framework.h"
#include "Block.h"
#include "RenderManager.h"
#include "TimeManager.h"

Block::Block() : harden(0.0f)
{
    category = 0;
}

Block::~Block()
{
}

void Block::getImgSet(std::string name)
{
    placedImgSet = &(*rendering->findImageSet("Tiles_block")->find(name)).second;
    placedImgSize.x = 16;
    placedImgSize.y = 16;
    itemImgSize.x = 16;
    itemImgSize.y = 16;
    count = 1;
    maxCount = 9999;
    onGround = false;
}

void Block::changeBlockImg(std::string state, int shadow)
{
    std::string imgInfo;

    if (shadow == 0) imgInfo = "shadow0";
    else imgInfo = "shadow" + std::to_string(shadow);
    imgInfo += "rotation0";

    auto resOne = placedImgSet->find(imgInfo);
    if ((*resOne).second.empty()) return;

    placedImgPos = imageFinder(state);
    rawPlacedImg = (*resOne).second[0];

}

Vector2Int Block::imageFinder(std::string state)
{
    if (imgInfo.empty())
    {
        imgInfo = {
                 {"1011", {{ 0,0 }, { 0,1 }, { 0,2 }}}// => ������ �� 1011
               , {"1110", {{ 1,0 }, { 2,0 }, { 3,0 }}}// => �ٴڸ� 1110
               , {"1111", {{ 1,1 }, { 2,1 }, { 3,1 }}} //=> �߰� 1111
               , {"1101", {{ 1,2 }, { 2,2 }, { 3,2 }}} //=> õ��� 1101
               , {"0111", {{ 4,0 }, { 4,1 }, { 4,2 }}} //=> ������ �� 0111
               , {"0011", {{ 5,0 }, { 5,1 }, { 5,2 }}} //=> ��� 0011
               , {"1100", {{ 6,4 }, { 7,4 }, { 8,4 }}} //=> ���ں귰 1100
               , {"0010", {{ 6,0 }, { 7,0 }, { 8,0 }}} //=> Ƣ��º�(��) 0010
               , {"0001", {{ 6,3 }, { 7,3 }, { 8,3 }}} //=> Ƣ��� ��(�Ʒ�) 0001
               , {"1000", {{ 9,0 }, { 9,1 }, { 9,2 }}} //=> Ƣ��º�(��) 1000
               , {"0100", {{ 12,0}, { 12,1}, { 12,2}}} //=> Ƣ��� ��(����) 0100
               , {"0000", {{ 9,3 }, { 10,3}, { 11,3}}} //=> ���ߺ� 0000
               , {"1010", {{ 0,3 }, { 2,3 }, { 4,3 }}} //���޸𼭸� 1010
               , {"1001", {{ 0,4 }, { 2,4 }, { 4,4 }}} //�ؿ޸𼭸� 1001
               , {"0110", {{ 1,3 }, { 3,3 }, { 5,3 }}} //�����𼭸� 0110
               , {"0101", {{ 1,4 }, { 3,4 }, { 5,4 }}} //�����𼭸� 0101
        };
    }

    srand((unsigned int)Time->deltaTime());
    int rndInt = rand() % 3;

    return (*imgInfo.find(state)).second[rndInt];
}
