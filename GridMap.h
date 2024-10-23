#pragma once
#include "Node.h"

class GridMap
{
	DECLARE_SINGLETON(GridMap)
public:
	void init(int width, int height);
	void update();
	void render(HDC _hdc);
	void release();


	Node* findNode(Vector2Int _gridPos);
	Node* findNode(Vector2 _pos);
	void getVisiableNodes();
	void updateNearNode(Node* _node, int range);
	void updateAllBlock();
	void updateWorldLight(int worldLight);
	void nodeInteraction();
	std::list<Node*> findNearNode(Node* _node);
	std::list<Node*> findNodes(const Vector2& _start, const Vector2& _end);
	std::list<Node*> findNodes(Vector2Int _start, Vector2Int _end);

	std::vector<Node*>* linkNodeList() { return &nodeList; }
	void setSize(int value) { nodeSize = value; }
	int tileSize() const { return nodeSize; }
	Vector2Int getGridPos(Vector2 worldPos);

private:
	int width = 0;
	int height = 0;
	int nodeSize = 0;

	Vector2 screenPos = Vector2::zero();

	std::vector<Node*> nodeList;
	std::list<std::list<Node*>> visibleNodeList;
	HBITMAP test = NULL;
};
#define gridMap GET_SINGLETON(GridMap)