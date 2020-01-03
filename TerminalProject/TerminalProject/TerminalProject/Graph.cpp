#include "Graph.h"
#include <QTextStream>
#include <QFile>
#include <qdebug.h>
#include <queue>


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
		NodeNum = num + 1;

		//创建顶点数组，比读入的顶点个数多1，用于存储事故的结点
		Vertex = new Node[num + 1];
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
		int num;	//边条数
		in >> num;

		for (int i = 0; i < num; i++)
		{
			int v1, v2;
			double weight;
			in >> v1 >> v2 >> weight;
			
		//v1上接v2
			//创建一个邻接表上的结点
			Node *tem = new Node(Vertex[v2]);
			tem->setweight(weight);

			//在最后一个位置添加新节点
			Node *cur = &Vertex[v1];
			while (cur->next != nullptr)
				cur = cur->next;
			cur->next = tem;	

		//v2上接v1
			//创建一个邻接表上的结点
			Node *tem1 = new Node(Vertex[v1]);
			tem1->setweight(weight);

			//在最后一个位置添加新节点
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

Graph::~Graph()
{
	delete []Vertex;
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

	//健壮性检查
	if (start >= NodeNum || start < 0 || level < 0 || level>2)
		return nullptr;

	//dijkstra算法
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
	q.push(node{ start ,0 });
	int k = 0;//path数组变量
	while (!q.empty())
	{
		node x = q.top();
		q.pop();
		if (dist[x.vertex] != x.relative_weight)
			continue;

		//当前结点的子结点入队
		Node *cur = &Vertex[x.vertex];
		int curcode = cur->code;		//当前结点的编号
		while (cur->next != nullptr)
		{
			int nextcode = cur->next->code;	//下一个结点的编号
			if (dist[nextcode] > dist[curcode] + cur->next->weight)
			{
				dist[nextcode] = dist[curcode] + cur->next->weight;
				parent[nextcode] = curcode;
				q.push(node{ nextcode,dist[nextcode] });

				//MYH
				path_node[k][0] = curcode;
				path_node[k][1] = nextcode;
				k++;
			}
			cur = cur->next;
		}
	}
	current_path = k;//parent数组变化量
	//找出路径的终点
	int end = 0;
	double minweight = INFINITY;
	for (int i = 0; i < NodeNum; i++)
	{
		if (Vertex[i].type >= level)
			if (minweight > dist[i])
			{
				end = i;
				minweight = dist[i];
			}
	}

	//生成一条从start结点到end结点的路径：用链表存储
	Node *path;

	//首结点，权重代表整条路径的权重
	path = new Node();
	path->setweight(dist[end]);

	Node *cur = path;
	int search = end;

	while (1)
	{
		//添加结点到链表中
		Node *tem = new Node(Vertex[search]);
		cur->next = tem;

		//如果当前加入结点为start结点，终止
		if (parent[search] == -1)
			break;

		//遍历：cur到下一个结点，search在parent数组中前进
		cur = cur->next;
		search = parent[search];
	}

	return path;
}

void Graph::addAccident(double longitude, double latitude)
{
	Vertex[NodeNum - 1].setinfo(NodeNum - 1 , 0, longitude, latitude, 0);
	Vertex[NodeNum - 1].next = nullptr;
}

void Graph::addAccidentEdge(int vertex1, double weight1,int vertex2, double weight2)
{
	Node *cur = &Vertex[NodeNum - 1];

	Node *tem1 = new Node(Vertex[vertex1]);
	tem1->setweight(weight1);
	cur->next = tem1;

	cur = cur->next;
	Node *tem2 = new Node(Vertex[vertex2]);
	tem2->setweight(weight2);
	cur->next = tem2;
}

int Graph::getNodeNum() const
{
	return NodeNum;
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
