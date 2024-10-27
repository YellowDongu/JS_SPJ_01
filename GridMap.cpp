#include "framework.h"
#include "GridMap.h"
#include "CameraManager.h"
#include "ImageHandler.h"
#include "RenderManager.h"
#include "Block.h"
#include "Wall.h"
#include "Furniture.h"
#include "InputManager.h"


void GridMap::init(int _width, int _height)
{
	width = _width;
	height = _height;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Node* newNode = new Node();
			newNode->position({x, y});

			nodeList.push_back(newNode);
		}
	}
}

void GridMap::update()
{
	if (visibleNodeList.empty() || screenPos != cam->getWindowSize())
	{
		screenPos = cam->getWindowSize();
		getVisiableNodes();
	}

	if (visibleNodeList.empty()) return;


	bool firstX = false, lastX = false;
	bool firstY = false, lastY = false;
	while (!firstX || !firstY || !lastX || !lastY)
	{
		Vector2 screenPos = cam->calculateScreenPosition(Vector2Int::toVec2(visibleNodeList.front().front()->position() * nodeSize));
		if (!firstY)
		{
			if (screenPos.y > cam->getWindowSize().y + 50.0f)
			{
				visibleNodeList.pop_front();
			}
			else if (screenPos.y < cam->getWindowSize().y + 20.0f)
			{
				Vector2Int gridPos = visibleNodeList.front().front()->position();
				Vector2Int gridEndPos = visibleNodeList.front().back()->position();
				gridPos.y--;
				gridEndPos.y--;
				if (gridPos.y == -1 && gridEndPos.y == -1)
				{
					firstY = true;
					continue;
				}
				visibleNodeList.push_front(findNodes(gridPos, gridEndPos));

			}
			else firstY = true;
		}
		if(!firstX)
		{
			if (screenPos.x < -50.0f)
			{
				for (auto& nodeY : visibleNodeList)
				{
					nodeY.pop_front();
				}

			}
			else if (screenPos.x > -20.0f)
			{
				Vector2Int gridPos = visibleNodeList.front().front()->position();
				gridPos.x--;
				if (gridPos.x == -1)
				{
					firstX = true;
					continue;
				}
				for (auto& nodeY : visibleNodeList)
				{
					gridPos.y = nodeY.front()->position().y;
					nodeY.push_front(findNode(gridPos));
				}

			}
			else firstX = true;
		}
		screenPos = cam->calculateScreenPosition(Vector2Int::toVec2(visibleNodeList.back().back()->position() * nodeSize));
		if (!lastY)
		{
			if (screenPos.y < -50.0f)
			{
				visibleNodeList.pop_back();

			}
			else if (screenPos.y > -20.0f)
			{
				Vector2Int gridPos = visibleNodeList.back().front()->position();
				Vector2Int gridEndPos = visibleNodeList.back().back()->position();
				gridPos.y++;
				gridEndPos.y++;
				if (gridPos.y == height && gridEndPos.y == height)
				{
					lastY = true;
					continue;
				}
				visibleNodeList.push_back(findNodes(gridPos, gridEndPos));

			}
			else lastY = true;
		}
		if(!lastX)
		{
			if (screenPos.x > cam->getWindowSize().x + 50.0f)
			{
				for (auto& nodeY : visibleNodeList)
				{
					nodeY.pop_back();
				}
			}
			else if (screenPos.x < cam->getWindowSize().x + 20.0f)
			{
				Vector2Int gridPos = visibleNodeList.back().back()->position();
				gridPos.x++;
				if (gridPos.y == width)
				{
					lastX = true;
					continue;
				}
				for (auto& nodeY : visibleNodeList)
				{
					gridPos.y = nodeY.back()->position().y;
					nodeY.push_back(findNode(gridPos));
				}

			}
			else lastX = true;
		}
	}

}

void GridMap::render(HDC _hdc)
{
	if (visibleNodeList.empty() || screenPos != cam->getWindowSize())
	{
		screenPos = cam->getWindowSize();
		getVisiableNodes();
	}

	if (visibleNodeList.empty()) return;

	for (auto& nodeY : visibleNodeList)
	{
		for (auto& node : nodeY)
		{
			if (!node->wall()) continue;

			Vector2Int drawPos = Vector2::toVec2Int(cam->calculateScreenPosition(Vector2Int::toVec2(node->position() * nodeSize)));
			int size = node->wall()->size().y;
			drawPos.y -= (size - 9);
			drawPos.x -= 9;
			Vector2Int imgPos = node->wall()->imgPos() * size + node->wall()->imgPos() * 2;
			ImageHandler::renderWithoutBack(node->backImg(), _hdc, drawPos, node->wall()->size(), imgPos);
		}
	}

	for (auto& nodeY : visibleNodeList)
	{
		for (auto& node : nodeY)
		{
			if (node->block())
			{
				Vector2Int drawPos = Vector2::toVec2Int(cam->calculateScreenPosition(Vector2Int::toVec2(node->position() * nodeSize)));
				int size = node->block()->size().y;
				drawPos.y -= size;
				Vector2Int imgPos = node->block()->imgPos() * size + node->block()->imgPos() * 2;
				ImageHandler::renderWithoutBack(node->frontImg(), _hdc, drawPos, node->block()->size(), imgPos);
			}
			else if (node->furniture())
			{
				if (node->position() != node->furniture()->gridPosition()) continue;

				std::list<Node*> nodes;
				for (auto& pos : node->furniture()->placedInfo())
				{
					if (pos.x == 0 && pos.y == 0)
					{
						nodes.push_back(node);
						continue;
					}
					nodes.push_back(gridMap->findNode(node->position() + pos));
				}
				int i = 0;
				for (auto& selectedNode : nodes)
				{
					Vector2Int drawPos = Vector2::toVec2Int(cam->calculateScreenPosition(Vector2Int::toVec2(selectedNode->position() * nodeSize)));
					drawPos.y -= node->furniture()->size().y;
					drawPos.x += (16 - node->furniture()->size().x) / 2;

					Vector2Int imageStartPos = Vector2Int{ 
						node->furniture()->imageGridPosition().x * (node->furniture()->size().x + 2) * node->furniture()->imageGridSize().x ,
						node->furniture()->imageGridPosition().y * (node->furniture()->size().y + 2) * node->furniture()->imageGridSize().y
							+ node->furniture()->imageGridPosition().y * 2
					};
					
					imageStartPos += Vector2Int{ node->furniture()->imagePosInfo()[i].x * node->furniture()->size().x,
						node->furniture()->imagePosInfo()[i].y * node->furniture()->size().y };
					imageStartPos += node->furniture()->imagePosInfo()[i] * 2;

					if (node->furniture()->placedInfo()[i].y == node->furniture()->bottomPosition())
					{
						ImageHandler::renderWithoutBack(node->frontImg(), _hdc, drawPos, node->furniture()->size() + Vector2Int{ 0,2 }, imageStartPos);
					}
					else ImageHandler::renderWithoutBack(node->frontImg(), _hdc, drawPos, node->furniture()->size(), imageStartPos);
					i++;
				}
			}
		}
	}
}

void GridMap::release()
{
	if (nodeList.empty()) return;
	for (auto& node : nodeList)
	{
		node->release();
		delete node;
	}
	nodeList.clear();
}

Node* GridMap::findNode(Vector2Int _gridPos)
{
	if (_gridPos.x >= width || _gridPos.y >= height || _gridPos.x < 0 || _gridPos.y < 0) return nullptr;

	return nodeList[_gridPos.x + (_gridPos.y * (width))];
}

Node* GridMap::findNode(Vector2 _pos)
{
	return findNode(getGridPos(_pos));
}

void GridMap::getVisiableNodes()
{
	visibleNodeList.clear();
	
	Vector2Int minPos = getGridPos(cam->calculateWorldPosition({  -50.0f, screenPos.y + 50.0f }));
	Vector2Int maxPos = getGridPos(cam->calculateWorldPosition(Vector2{ screenPos.x + 50.0f, -50.0f }));
	if (minPos.x < 0) minPos.x = 0;
	if (minPos.y < 0) minPos.y = 0;
	if (maxPos.x < 0) maxPos.x = 0;
	if (maxPos.y < 0) maxPos.y = 0;
	if (minPos.x >= width) minPos.x = width - 1;
	if (minPos.y >= height) minPos.y = height - 1;
	if (maxPos.x >= width) maxPos.x = width - 1;
	if (maxPos.y >= height) maxPos.y = height - 1;

	for (int i = minPos.y; i < maxPos.y; i++)
	{
		visibleNodeList.push_back(findNodes(Vector2Int{ minPos.x, i }, Vector2Int{ maxPos.x, i }));
	}
}

void GridMap::updateNearNode(Node* _node, int range)
{
	_node->update();
	std::list<Node*> nodes = findNodes(_node->position() - Vector2Int{ range, range }, _node->position() + Vector2Int{ range, range });

	for (auto& node : nodes)
	{
		Vector2 relPos = _node->position() - node->position();
		if (abs(relPos.x) + abs(relPos.y) > range) continue;

		node->update();
	}

}

void GridMap::updateAllBlock()
{
	for (auto& node : nodeList)
	{
		node->update();
	}
}

void GridMap::updateWorldLight(int worldLight)
{
	std::list<Node*> up = findNodes(Vector2Int{ 0,height - 1 }, Vector2Int{ width - 1, height - 1 });
	for (auto& node : up)
	{
		node->updateWorldLight(worldLight);
	}
}

void GridMap::nodeInteraction()
{
	Node* node = findNode(cam->calculateWorldPosition({(float)Input->getMousePos().x, (float)Input->getMousePos().y }));
	if (!node) return;
	Furniture* furniture = node->furniture();
	if (!furniture) return;
	furniture->useInField();
}

std::list<Node*> GridMap::findNearNode(Node* _node)
{
	std::list<Node*> result;
	Vector2Int pos = _node->position();
	result.push_back(findNode(pos + Vector2Int{ 1,0 }));
	result.push_back(findNode(pos + Vector2Int{ -1,0 }));
	result.push_back(findNode(pos + Vector2Int{ 0,1 }));
	result.push_back(findNode(pos + Vector2Int{ 0,-1 }));

	return result;
}

// 작은 수를 start로, 큰 수를 end로
std::list<Node*> GridMap::findNodes(const Vector2& _start, const Vector2& _end)
{
	return findNodes(getGridPos(_start), getGridPos(_end));
}

// 작은 수를 start로, 큰 수를 end로
std::list<Node*> GridMap::findNodes(Vector2Int _start, Vector2Int _end)
{
	std::list<Node*> result;

	if (_start.x >= width || _start.y >= height) return std::list<Node*>();
	if (_end.x < 0 || _end.y < 0) return std::list<Node*>();

	if (_end.x >= width) _end.x = (width - 1);
	if (_end.y >= height) _end.y = (height - 1);
	if (_start.x < 0) _start.x = 0;
	if (_start.y < 0) _start.y = 0;

	for (int x = _start.x; x <= _end.x; x++)
	{
		for (int y = _start.y; y <= _end.y; y++)
		{
			Node* node = nodeList[x + (y * width)];
			result.push_back(node);
		}
	}

	return result;
}

Vector2Int GridMap::getGridPos(const Vector2& worldPos)
{
	return Vector2::toVec2Int(worldPos / nodeSize);
}
