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

	void addAccident(int code, int type, double longitude, double latitude, double weight);

	void addAccidentEdge(int vertex1, double weight1, int vertex2, double weight2);

	int getNodeNum();

	void getpath(int a[][2], int &n);//��ȡ����·��

};