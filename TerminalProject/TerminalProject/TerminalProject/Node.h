#pragma once

class Node
{
private:
	int code;		//结点编号
	int type;	//节点类型
	double longitude;	//经度
	double latitude;  //纬度
	double weight;    //权重
	Node *next;
public:
	Node() { next = nullptr; }

	Node(int code, int type, double longitude, double latitude, double weight) 
		:code(code), type(type), longitude(longitude), latitude(latitude),weight(weight) { next = nullptr; }

	Node(const Node &node)
	{
		code = node.code;
		type = node.type;
		longitude = node.longitude;
		latitude = node.latitude;
		weight = node.weight;
		next = nullptr;
	}

	void setinfo(int code, int type, double longitude, double latitude, double weight)
	{
		this->code = code;
		this->type = type;
		this->longitude = longitude;
		this->latitude = latitude;
		this->weight = weight;
		next = nullptr;
	}
	bool hasNext()
	{
		if (next != nullptr)
			return true;
		else
			return false;
	}
	void setweight(double weight)
	{
		this->weight = weight;
	}
	void setNext(Node *nextNode)
	{
		next = nextNode;
	}

	int gettype()
	{
		return type;
	}

	double getlongitude()
	{
		return longitude;
	}

	double getlatitude()
	{
		return latitude;
	}

	double getweight()
	{
		return weight;
	}

	int getcode()
	{
		return code;
	}

	Node *getnext()
	{
		return next;
	}

	friend class Graph;
};