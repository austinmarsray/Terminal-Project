#include "Graph.h"
#include <QTextStream>
#include <QFile>
#include <qdebug.h>

bool Graph::createNode()
{
	QFile file("NodeData.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;
	else
	{
		QTextStream in(&file);
		int num;	//结点个数
		in >> num;

		Vertex = new Node[num];	//创建顶点数组
		if (Vertex == nullptr)
			return false;

		for (int i = 0; i < num; i++)
		{
			double latitude, longitude, weight;
			in >> longitude >> latitude >> weight;
			Vertex[i].setinfo(i + 1, longitude, latitude, weight);
		}
		//qDebug() << "Node Success!";
		return true;
	}
}

bool Graph::createEdge()
{
	QFile file("EdgeData.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;
	else
	{
		QTextStream in(&file);
		int num;	//边条数
		in >> num;

		for (int i = 0; i < num; i++)
		{
			int v1, v2;
			double weight;
			in >> v1 >> v2 >> weight;
			
			//创建一个邻接表上的结点
			Node *tem = new Node(Vertex[v2 - 1]);
			tem->setweight(weight);

			//在最后一个位置添加新节点
			Node *cur = &Vertex[v1 - 1];
			while (cur->next != nullptr)
				cur = cur->next;
			cur->next = tem;		
		}
		//qDebug() << "Edge Success!";
		return true;
	}
}

Graph::Graph()
{
	if (createNode() && createEdge())
		qDebug() << "Graph is created successfully!";
	else
		qDebug() << "Graph is fail to be created!";
}