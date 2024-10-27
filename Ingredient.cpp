#include "framework.h"
#include "Ingredient.h"
#include "RenderManager.h"

Ingredient::Ingredient()
{
    category = 0;
}

Ingredient::~Ingredient()
{
}

void Ingredient::getImgSet(std::string name)
{
    itemImg = rendering->findImage("Item_ingredient", name, "shadow0rotation0")[0];
    count = 1;
    maxCount = 9999;
    onGround = false;
}
