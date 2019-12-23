#pragma once
#include "Node.h"

class Graph
{
private:
	Node *Vertex;
	int NodeNum;
	int path_node[500][2];//存储寻路结点
	int current_path;//当前存入路的结点
private:
	bool createNode();
	bool createEdge();
public:
	Graph();
	Node* SelectPath(int start, int level);

	void getpath(int a[][2], int &n);//获取最终路径
};