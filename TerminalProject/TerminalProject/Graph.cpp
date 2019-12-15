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
		int num;	//������
		in >> num;

		Vertex = new Node[num];	//������������
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
		int num;	//������
		in >> num;

		for (int i = 0; i < num; i++)
		{
			int v1, v2;
			double weight;
			in >> v1 >> v2 >> weight;
			
			//����һ���ڽӱ��ϵĽ��
			Node *tem = new Node(Vertex[v2 - 1]);
			tem->setweight(weight);

			//�����һ��λ������½ڵ�
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