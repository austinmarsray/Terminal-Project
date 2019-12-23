#include "Graph.h"
#include <QTextStream>
#include <QFile>
#include <qdebug.h>
#include <queue>
#define __DEBUG__


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
		NodeNum = num;

		Vertex = new Node[num];	//������������
		if (Vertex == nullptr)
			return false;

		for (int i = 0; i < num; i++)
		{
			double latitude, longitude, weight;
			int level;
			in >> longitude >> latitude >> weight >> level;
			Vertex[i].setinfo(i ,level ,longitude, latitude, weight);
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
			
		//v1�Ͻ�v2
			//����һ���ڽӱ��ϵĽ��
			Node *tem = new Node(Vertex[v2]);
			tem->setweight(weight);

			//�����һ��λ������½ڵ�
			Node *cur = &Vertex[v1];
			while (cur->next != nullptr)
				cur = cur->next;
			cur->next = tem;	

		//v2�Ͻ�v1
			//����һ���ڽӱ��ϵĽ��
			Node *tem1 = new Node(Vertex[v1]);
			tem1->setweight(weight);

			//�����һ��λ������½ڵ�
			Node *cur1 = &Vertex[v2];
			while (cur1->next != nullptr)
				cur1 = cur1->next;
			cur1->next = tem1;
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


Node* Graph::SelectPath(int start, int level)
{
	struct node
	{
		int vertex;
		double relative_weight;
		bool operator< (const node &rhs) const
		{
			return (rhs.relative_weight < relative_weight);
		}
	};

	//��׳�Լ��
	if (start >= NodeNum || start < 0 || level < 0 || level>2)
		return nullptr;

	//dijkstra�㷨
	int *parent = new int[NodeNum];
	double *dist = new double[NodeNum];
	for (int i = 0; i < NodeNum; i++)
	{
		parent[i] = -1;
		dist[i] = INFINITY;
	}

	parent[start] = -1;
	dist[start] = 0;

	std::priority_queue<node> q;
	q.push(node{ start ,0});

	int k = 0;//path�������
	
	while (!q.empty()) 
	{
		node x = q.top(); 
		q.pop();
		if (dist[x.vertex] != x.relative_weight)
			continue;

		//��ǰ�����ӽ�����
		Node *cur = &Vertex[x.vertex];
		int curcode = cur->code;		//��ǰ���ı��
		while (cur->next != nullptr)
		{
			int nextcode = cur->next->code;	//��һ�����ı��
			if (dist[nextcode] > dist[curcode] + cur->next->weight)
			{
				dist[nextcode] = dist[curcode] + cur->next->weight;
				parent[nextcode] = curcode;
				q.push(node{ nextcode,dist[nextcode] });

				//---------------------------------------
				//----------�ӿڵ��ã�ʵʱչʾЧ��---------
				//---------------------------------------

				path_node[k][0] = curcode;
				path_node[k][1] = nextcode;
				k++;
			}
			cur = cur->next;
		}
	}

	current_path = k;

	//�ҳ�·�����յ�
	int end = 0;
	double minweight = INFINITY;
	for (int i = 0; i < NodeNum; i++)
	{
		if(Vertex[i].type >= level)
			if (minweight > dist[i])
			{
				end = i;
				minweight = dist[i];
			}
	}

	//����һ����start��㵽end����·����������洢
	Node *path;

	//�׽�㣬Ȩ�ش�������·����Ȩ��
	path = new Node();
	path->setweight(dist[end]);

	Node *cur = path;
	int search = end;

	while (1)
	{
		//��ӽ�㵽������
		Node *tem = new Node(Vertex[search]);
		cur->next = tem;

		//�����ǰ������Ϊstart��㣬��ֹ
		if (parent[search] == -1)
			break;

		//������cur����һ����㣬search��parent������ǰ��
		cur = cur->next;
		search = parent[search];
	}
#ifdef __DEBUG__
	for (int i = 0; i < NodeNum; i++)
	{
		qDebug() << i << " " << parent[i] << " " << dist[i] << endl;
	}

	cur = path;
	qDebug() << "total weight = " <<path->weight << endl;
	cur = cur->next;

	while (cur != nullptr)
	{
		qDebug() << cur->code << "  longitude:" << cur->longitude << "  latitude:" << cur->latitude << endl;
		cur = cur->next;
	}
#endif // __DEBUG__

	return path;
}

void Graph::getpath(int a[][2], int &n)
{
	n = current_path;
	for (int i = 0; i < current_path; i++)
	{
		a[i][0] = path_node[i][0];
		a[i][1] = path_node[i][1];
	}
}