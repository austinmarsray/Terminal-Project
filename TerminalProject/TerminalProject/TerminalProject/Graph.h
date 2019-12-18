#pragma once
#include "Node.h"

class Graph
{
private:
	Node *Vertex;
	int NodeNum;
private:
	bool createNode();
	bool createEdge();
public:
	Graph();
	
	Node* SelectPath(int start, int level);
};