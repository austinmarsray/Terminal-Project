#pragma once
#include "Node.h"

class Graph
{
private:
	Node *Vertex;
	int NodeNum;
	int path_node[500][2];//�洢Ѱ·���
	int current_path;//��ǰ����·�Ľ��
private:
	bool createNode();
	bool createEdge();
public:
	Graph();
	Node* SelectPath(int start, int level);

	void getpath(int a[][2], int &n);//��ȡ����·��
};