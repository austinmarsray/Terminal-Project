#pragma once
#include "Node.h"

class Graph
{
private:
	Node *Vertex;
private:
	bool createNode();
	bool createEdge();
public:
	Graph();
};