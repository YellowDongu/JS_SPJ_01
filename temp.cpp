#include "framework.h"
/*


void ColllisionHandler::collision(Entity* obj, GridMap* gridMap)
{
    // 1. 자신의 위치 바로 밑에 있는 노드들을 가져와서 바닥 상태를 확인
    Vector2Int min = gridMap->getGridPos(obj->position() - obj->size() / 2);
    Vector2Int max = gridMap->getGridPos(obj->position() + obj->size() / 2);

    std::list<Node*> nodes = gridMap->findNodes(Vector2Int{ min.x, max.y + 1 }, Vector2Int{ max.x, max.y + 1 });
    bool ground = false;

    for (auto& node : nodes)
    {
        if (!node->block()) continue;
        ground = true;
        break;
    }
    obj->setOnGround(ground);

    // 2. 만약 바닥에 없으면 y축 충돌을 확인하여 겹친만큼 이동
    if (!ground)
    {
        nodes.clear();
        nodes = gridMap->findNodes(min, max);

        RECT objRect = { obj->position().x - obj->size().x / 2, obj->position().y - obj->size().y / 2,
                         obj->position().x + obj->size().x / 2, obj->position().y + obj->size().y / 2 };

        for (auto& node : nodes)
        {
            if (!node->block()) continue;

            RECT sbjRect = { node->position().x * 16.0f - 8.0f, node->position().y * 16.0f - 8.0f,
                             node->position().x * 16.0f + 8.0f, node->position().y * 16.0f + 8.0f };
            RECT coll = { 0, 0, 0, 0 };

            if (IntersectRect(&coll, &objRect, &sbjRect))
            {
                float overlapY = (float)(coll.bottom - coll.top);
                obj->translate(Vector2{ 0.0f, -overlapY });
                break;
            }
        }
    }

    // 3. 왼쪽에 있는 노드들을 검사하고 충돌 처리
    nodes.clear();
    nodes = gridMap->findNodes(Vector2Int{ min.x - 1, min.y }, Vector2Int{ min.x - 1, max.y });

    for (auto& node : nodes)
    {
        if (!node->block()) continue;

        // 위쪽 3칸이 비어있고 맨 아래에만 블록이 있는 경우
        bool onlyBottomBlock = true;
        for (int i = 1; i <= 3; ++i)
        {
            Vector2Int checkPos = Vector2Int{ min.x - 1, max.y - i };
            Node* checkNode = gridMap->getNode(checkPos);
            if (checkNode && checkNode->block())
            {
                onlyBottomBlock = false;
                break;
            }
        }

        if (onlyBottomBlock)
        {
            obj->translate(Vector2{ 0.0f, -16.0f });
            break;
        }
        else
        {
            RECT objRect = { obj->position().x - obj->size().x / 2, obj->position().y - obj->size().y / 2,
                             obj->position().x + obj->size().x / 2, obj->position().y + obj->size().y / 2 };
            RECT sbjRect = { node->position().x * 16.0f - 8.0f, node->position().y * 16.0f - 8.0f,
                             node->position().x * 16.0f + 8.0f, node->position().y * 16.0f + 8.0f };
            RECT coll = { 0, 0, 0, 0 };

            if (IntersectRect(&coll, &objRect, &sbjRect))
            {
                float overlapX = (float)(coll.right - coll.left);
                obj->translate(Vector2{ overlapX, 0.0f });
                break;
            }
        }
    }

    // 4. 오른쪽에 있는 노드들을 검사하고 충돌 처리
    nodes.clear();
    nodes = gridMap->findNodes(Vector2Int{ max.x + 1, min.y }, Vector2Int{ max.x + 1, max.y });

    for (auto& node : nodes)
    {
        if (!node->block()) continue;

        // 위쪽 3칸이 비어있고 맨 아래에만 블록이 있는 경우
        bool onlyBottomBlock = true;
        for (int i = 1; i <= 3; ++i)
        {
            Vector2Int checkPos = Vector2Int{ max.x + 1, max.y - i };
            Node* checkNode = gridMap->getNode(checkPos);
            if (checkNode && checkNode->block())
            {
                onlyBottomBlock = false;
                break;
            }
        }

        if (onlyBottomBlock)
        {
            obj->translate(Vector2{ 0.0f, -16.0f });
            break;
        }
        else
        {
            RECT objRect = { obj->position().x - obj->size().x / 2, obj->position().y - obj->size().y / 2,
                             obj->position().x + obj->size().x / 2, obj->position().y + obj->size().y / 2 };
            RECT sbjRect = { node->position().x * 16.0f - 8.0f, node->position().y * 16.0f - 8.0f,
                             node->position().x * 16.0f + 8.0f, node->position().y * 16.0f + 8.0f };
            RECT coll = { 0, 0, 0, 0 };

            if (IntersectRect(&coll, &objRect, &sbjRect))
            {
                float overlapX = (float)(coll.right - coll.left);
                obj->translate(Vector2{ -overlapX, 0.0f });
                break;
            }
        }
    }
}
*/
